#include "GameState.h"

// Private functions

void GameState::initVariables()
{
	this->initBackground();
	this->initPlayer(); // 1.1 important order
	this->initRocks();
	this->initUI(); // 1.2 important order
	this->initBullets();

	this->holdSpace = false;
	this->holdEscape = false;

	this->flag = NONE_FLAG;
}

void GameState::initPlayer()
{
	this->player = new Player(
		sf::Vector2f(
			this->data->displayField.reference / 12.f,
			this->data->displayField.reference / 12.f * 2.25f
		), // size

		sf::Vector2f(
			this->data->displayField.left + (this->data->displayField.reference / 2),
			this->data->displayField.top + this->data->displayField.reference - this->data->displayField.reference / 12.f * 2.25f / 2.f - this->data->displayField.reference / 80.f
		), // position

		this->data->displayField.reference / 70.f // max speed
	);

	this->player->setTexture(this->data->texturePack->normalPlayerTexture);
}

void GameState::initRocks()
{
	this->rockSpawningInterval = (unsigned int) 120; // here
	this->rockSpawnTimer = (unsigned int) 0;
	this->rockSpeed = this->data->displayField.height / 700.f; // here
	this->smallRockRadius = this->data->displayField.width / 25.f;
	this->bigRockRadius = this->data->displayField.width / 15.f;
	this->rockLevel = 0; // here
	this->sequence = 100; // first expression  // here
	this->pointsMultiplier = 1; // here
}

void GameState::initBullets()
{
	this->maxBullets = 3;
}

void GameState::initBackground()
{
	this->background.setTexture(&this->data->texturePack->backgroundTexture);

	if (this->data->texturePack->backgroundTexture.getSize().x < this->data->texturePack->backgroundTexture.getSize().y)
	{
		this->background.setTextureRect(sf::IntRect(
			0,
			0,
			static_cast <int> (this->data->texturePack->backgroundTexture.getSize().x),
			static_cast <int> (this->data->texturePack->backgroundTexture.getSize().x)
		));
	}
	else
	{
		this->background.setTextureRect(sf::IntRect(
			0,
			0,
			static_cast <int> (this->data->texturePack->backgroundTexture.getSize().y),
			static_cast <int> (this->data->texturePack->backgroundTexture.getSize().y)
		));
	}

	this->background.setSize(this->data->displayField.size);
	this->background.setPosition(this->data->displayField.position);
}

void GameState::initUI()
{
	if (!this->font.loadFromFile("Fonts/astroarmada.ttf"))
	{
		std::cout << "ERROR: GameState::initUI(): Font cannot be loaded\n";
	}

	this->UItext.setFont(this->font);
	this->UItext.setString("NONE");
	this->UItext.setCharacterSize(// used to be 24px
		static_cast <unsigned int> (this->data->displayField.height / 32)
	);
	this->UItext.setFillColor(sf::Color::White);
	this->UItext.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width / 80,
		this->data->displayField.top + this->data->displayField.height / 80
	));

	this->UItext.setOutlineThickness(1.f);
	this->UItext.setOutlineColor(sf::Color(0, 0, 139, 255));
}

void GameState::checkPlayerCollision()
{
	for (size_t i = 0; i < this->rocks.size(); i++)
	{
		if (rectCircleCollision(this->player->getBounds(), this->rocks[i]->getBounds())) // detects collision a little bit to fast !!!!!!!!!!!!!
		{
			this->player->takeDamage();
			this->data->soundPack->playerDamagedSound.setVolume(this->data->soundPack->volume);
			this->data->soundPack->playerDamagedSound.play();

			if (this->player->getHealthPoints() == 0)
			{
				this->flag = GAME_OVER_GAME_STATE_FLAG;
				this->data->soundPack->gameOverSound.setVolume(this->data->soundPack->volume);
				this->data->soundPack->gameOverSound.play();
				this->player->setTexture(this->data->texturePack->brokenPlayerTexture);
			}

			// Add explosion
			this->explosions.push_back(
				new Explosion(
					this->rocks[i]->getPosition(),
					sf::Vector2f(
						this->rocks[i]->getBounds().width,
						this->rocks[i]->getBounds().height
					),
					this->data->texturePack->explosionTexture
				)
			);

			delete this->rocks[i];
			this->rocks.erase(this->rocks.begin() + i);
			i--;
		}
	}
}

void GameState::updatePlayer()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		this->player->useLeftEngine();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		this->player->useRightEngine();

	if (this->player->getBounds().left < this->data->displayField.left && this->player->getSpeed() < 0.f)
		this->player->stop();
	if (this->player->getBounds().left + this->player->getBounds().width > this->data->displayField.left + this->data->displayField.width && this->player->getSpeed() > 0.f)
		this->player->stop();


	this->player->update(); // important position

	this->checkPlayerCollision();
}

void GameState::deleteRocks()
{
	// deletes rocks out of bonds and with 0 health points

	for (size_t i = 0; i < this->rocks.size(); i++)
	{
		if (this->rocks[i]->getHealthPoints() == 0)
		{
			if (this->player->getPoints() > 700)
			{
				int rand = randInRange(1, 100);
				if (rand == 100) // 1% chance for dropping health points bonus
					this->spawnBonus(this->rocks[i]->getPosition());
			}

			// Add explosion
			this->explosions.push_back(
				new Explosion(
					this->rocks[i]->getPosition(),
					sf::Vector2f(
						this->rocks[i]->getBounds().width,
						this->rocks[i]->getBounds().height
					),
					this->data->texturePack->explosionTexture
				)
			);

			this->player->addPoints(this->rocks[i]->getPoints());

			delete this->rocks[i];
			this->rocks.erase(this->rocks.begin() + i);
			i--;

			continue;
		}
		else if (this->rocks[i]->getBounds().top - this->rocks[i]->getBounds().height * 3.5f > this->data->displayField.top + this->data->displayField.height)
		{
			delete this->rocks[i];
			this->rocks.erase(this->rocks.begin() + i);
			i--;
		}
	}
}

void GameState::updateRocks()
{
	for (auto& r : this->rocks) {
		r->update();
	}

	this->deleteRocks();

	this->spawnRocks();
}

void GameState::shootBullet()
{
	this->bullets.push_back(
		new Bullet(
			sf::Vector2f(
				this->data->displayField.reference / 75.f,
				this->data->displayField.reference / 30.f
			),
			sf::Vector2f(
				this->player->getPosition().x,
				this->player->getBounds().top
			),
			sf::Vector2f(
				0.f,
				-this->data->displayField.height / 120
			),
			this->data->texturePack->bulletTexture
		)
	);

	this->data->soundPack->shootSound.setVolume(this->data->soundPack->volume);
	this->data->soundPack->shootSound.play();
}

void GameState::deleteBullets()
{
	// deletes bullets out of bonds

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		if (this->bullets[i]->getBounds().top + this->bullets[i]->getBounds().height < 0)
		{
			delete this->bullets[i];
			this->bullets.erase(this->bullets.begin() + i);
			i--;
		}
	}
}

void GameState::checkBulletsCollision()
{
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		for (size_t j = 0; j < this->rocks.size(); j++)
		{
			if (rectCircleCollision(this->bullets[i]->getBounds(), this->rocks[j]->getBounds()))
			{
				this->rocks[j]->takeDemage(this->bullets[i]->getDemage());
				this->data->soundPack->hitRockSound.setVolume(this->data->soundPack->volume);
				this->data->soundPack->hitRockSound.play();

				delete this->bullets[i];
				this->bullets.erase(this->bullets.begin() + i);
				i--;
				break;
			}
		}
	}
}

void GameState::updateBullets()
{
	for (auto& b : this->bullets) {
		b->update();
	}

	this->deleteBullets();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (this->holdSpace == false)
			if (this->bullets.size() < this->maxBullets)
				this->shootBullet();
			else
			{
				this->data->soundPack->outOfAmmoSound.setVolume(this->data->soundPack->volume);
				this->data->soundPack->outOfAmmoSound.play();
			}

		this->holdSpace = true;
	}
	else
		this->holdSpace = false;

	this->checkBulletsCollision();
}

void GameState::deleteBonuses()
{
	// deletes bonuses out of bonds

	for (size_t i = 0; i < this->bonuses.size(); i++)
	{
		if (this->bonuses[i]->getBounds().top - this->bonuses[i]->getBounds().height > this->data->displayField.top + this->data->displayField.height)
		{
			delete this->bonuses[i];
			this->bonuses.erase(this->bonuses.begin() + i);
			i--;
		}
		else if (this->bonuses[i]->getBounds().intersects(this->player->getBounds()))
		{
			this->player->takeHealthPointsBonus();
			this->data->soundPack->lifeUpSound.setVolume(this->data->soundPack->volume);
			this->data->soundPack->lifeUpSound.play();

			delete this->bonuses[i];
			this->bonuses.erase(this->bonuses.begin() + i);
			i--;
		}
	}
}

void GameState::updateBonuses()
{
	for (auto& b : this->bonuses) {
		b->update();
	}

	this->deleteBonuses();
}

void GameState::spawnBonus(sf::Vector2f position)
{
	this->bonuses.push_back(
		new HealthPointsBonus(
			position,
			sf::Vector2f(
				this->data->displayField.reference / 9.f,
				this->data->displayField.reference / 9.f * 285.f / 385.f
			),
			sf::Vector2f(
				0.f,
				this->data->displayField.reference / 530.f
			),
			this->data->texturePack->bonusTexture
		)
	);
}

void GameState::updateExplosions()
{
	for (auto& e : this->explosions) {
		e->update();
	}

	for (size_t i = 0; i < this->explosions.size(); i++)
	{
		if (this->explosions[i]->getLifeSpan() > 60) // each explosion is displayer for 60 frames
		{
			delete this->explosions[i];
			this->explosions.erase(this->explosions.begin() + i);
			i--;
		}
	}
}

void GameState::updateUI()
{
	this->UItext.setString("Best Score: " + std::to_string(this->data->bestScore)
		+"\n\nScore: " + std::to_string(this->player->getPoints())
		+"\n\nHealth: " + std::to_string(this->player->getHealthPoints())
	);
}

void GameState::clearVariables()
{
	delete this->player;

	for (size_t i = 0; i < this->rocks.size(); i++)
	{
		delete this->rocks[i];
		this->rocks.erase(this->rocks.begin() + i);
		i--;
	}

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		delete this->bullets[i];
		this->bullets.erase(this->bullets.begin() + i);
		i--;
	}

	for (size_t i = 0; i < this->bonuses.size(); i++)
	{
		delete this->bonuses[i];
		this->bonuses.erase(this->bonuses.begin() + i);
		i--;
	}

	for (size_t i = 0; i < this->explosions.size(); i++)
	{
		delete this->explosions[i];
		this->explosions.erase(this->explosions.begin() + i);
		i--;
	}
}

// Constructor, destructor

GameState::GameState(StateData* data)
{
	this->gameRunning = false;

	this->data = data;

	this->initVariables();
}

GameState::~GameState()
{
	this->clearVariables();
}

// Accessors

unsigned int GameState::getPoints()
{
	return this->player->getPoints();
}

//Public functions

int GameState::update()
{
	this->flag = NONE_FLAG;

	if (gameRunning)
	{
		this->updatePlayer();

		this->updateBullets();

		this->updateRocks();

		this->updateBonuses();

		this->updateExplosions();

		this->updateUI();
	}

	return this->flag;
}

void GameState::render(sf::RenderTarget& target)
{
	// Draw game
	target.draw(this->background);

	for (auto& b : this->bullets) {
		b->render(target);
	}

	for (auto& b : this->bonuses) {
		b->render(target);
	}

	this->player->render(target);

	for (auto& r : this->rocks) {
		r->render(target);
	}

	for (auto& e : this->explosions) {
		e->render(target);
	}

	if(gameRunning)
		target.draw(this->UItext);
}

void GameState::stopGame()
{
	this->gameRunning = false;
}

void GameState::restartGame()
{
	this->clearVariables();
	this->initVariables();

	this->gameRunning = true;
}

void GameState::reassumeGame()
{
	this->gameRunning = true;
}
