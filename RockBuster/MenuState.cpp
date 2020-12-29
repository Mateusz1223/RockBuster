#include "MenuState.h"

#include "common.h"

// Private funtions

void MenuState::initBackground()
{
	this->background.setSize(this->data->displayField.size);

	this->background.setPosition(this->data->displayField.position);

	this->background.setFillColor(sf::Color::Color(0,0,0, 170));
}

void MenuState::initTexts()
{
	if (!this->font.loadFromFile("Fonts/astroarmada.ttf"))
	{
		std::cout << "ERROR: MenuState::initTexts(): Font cannot be loaded\n";
	}

	this->titleText.setFont(this->font);
	this->titleText.setString("Rock Buster");
	this->titleText.setCharacterSize( // used to be 55px
		static_cast <unsigned int> (this->data->displayField.height / 14.f)
	);
	this->titleText.setFillColor(sf::Color::White);
	this->titleText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->titleText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 5.f
	)
	);
	

	this->bestScoreText.setFont(this->font);
	this->bestScoreText.setString("Best Score: " + std::to_string(this->data->bestScore));
	this->bestScoreText.setCharacterSize( // used to be 38px
		static_cast <unsigned int> (this->data->displayField.height / 21.f)
	);
	this->bestScoreText.setFillColor(sf::Color::White);
	this->bestScoreText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->bestScoreText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 2.8f
	)
	);

	this->lastScoreText.setFont(this->font);
	this->lastScoreText.setCharacterSize( // used to be 38px
		static_cast <unsigned int> (this->data->displayField.height / 21.f)
	);
	this->lastScoreText.setFillColor(sf::Color::White);
}

void MenuState::initButtons()
{
	this->playButton.setContent("Play");
	this->playButton.setCharacterSize( // used to be 40px
		static_cast <unsigned int> (this->data->displayField.height / 20.f)
	);
	this->playButton.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width / 2.f - this->playButton.getBounds().width / 2.f,
		this->data->displayField.top + this->data->displayField.height / 2.2f
	)
	);

	this->exitButton.setContent("Exit Game");
	this->exitButton.setCharacterSize(// used to be 26px
		static_cast <unsigned int> (this->data->displayField.height / 30.f)
	);
	this->exitButton.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width - this->exitButton.getBounds().width,
		this->data->displayField.top + this->data->displayField.height - this->exitButton.getBounds().height - 20.f // something is wrong with the height of button (now it's a little bit different because of button contnt outline but anyway height of font doesnt match)
	)
	);

	this->creditsButton.setContent("Credits");
	this->creditsButton.setCharacterSize(
		static_cast <unsigned int> (this->data->displayField.height / 30.f)
	);
	this->creditsButton.setPosition(sf::Vector2f(
		this->data->displayField.left,
		this->data->displayField.top + this->data->displayField.height - this->creditsButton.getBounds().height - 20.f // something is wrong with the height of button (now it's a little bit different because of button contnt outline but anyway height of font doesnt match)
	)
	);

	this->historyButton.setContent("History");
	this->historyButton.setCharacterSize(
		static_cast <unsigned int> (this->data->displayField.height / 30.f)
	);
	this->historyButton.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width / 2.f - this->historyButton.getBounds().width / 2.f,
		this->data->displayField.top + this->data->displayField.height / 1.6f
	)
	);
}

void MenuState::updateButtons()
{
	this->playButton.update(this->mousePosition);

	this->exitButton.update(this->mousePosition);

	this->creditsButton.update(this->mousePosition);

	this->historyButton.update(this->mousePosition);

	this->data->soundRegulator.update(this->mousePosition);

	this->data->soundPack->volume = this->data->soundRegulator.getValue();
}

MenuState::MenuState(StateData* data)
{
	this->data = data;

	this->initBackground();
	this->initTexts();
	this->initButtons();

	this->flag = NONE_FLAG;
}

// Public Funtions

int MenuState::update(sf::Vector2f mousePosition)
{
	this->flag = NONE_FLAG;

	this->mousePosition = mousePosition;

	this->updateButtons();

	if (this->exitButton.isPressed())
	{
		this->flag = EXIT_REQUEST_MENU_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}
	else if (this->playButton.isPressed())
	{
		this->flag = PLAY_REQUEST_MENU_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}
	else if (this->creditsButton.isPressed())
	{
		this->flag = CREDITS_REQUEST_MENU_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}
	else if (this->historyButton.isPressed())
	{
		this->flag = HISTORY_REQUEST_MENU_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}

	if (this->flag != NONE_FLAG) // used for preventing unwanted press when state change
	{
		this->playButton.setholdMouseLeft();
		this->exitButton.setholdMouseLeft();
	}

	return this->flag;
}

void MenuState::render(sf::RenderTarget& target)
{
	target.draw(this->background);

	target.draw(this->titleText);
	target.draw(this->lastScoreText);
	target.draw(this->bestScoreText);

	this->playButton.render(target);
	this->exitButton.render(target);
	this->creditsButton.render(target);
	this->historyButton.render(target);
	this->data->soundRegulator.render(target);
}

void MenuState::setLastScore(unsigned int score)
{
	if (this->data->bestScore < score)
	{
		this->data->bestScore = score;
		this->lastScoreText.setString("NEW BEST SCORE: " + std::to_string(score) + "!!!");
		this->lastScoreText.setPosition(sf::Vector2f
		(
			this->data->displayField.left
			+ this->data->displayField.width / 2.f
			- this->lastScoreText.getGlobalBounds().width / 2.f,

			this->data->displayField.top + this->data->displayField.height / 2.8f
		)
		);

		this->bestScoreText.setString("");

		this->data->saveScore(score, 'B');
	}
	else if (this->data->bestScore * 0.9 < score)
	{
		this->lastScoreText.setString("Good Score: " + std::to_string(score) + "!");
		this->lastScoreText.setPosition(sf::Vector2f
		(
			this->data->displayField.left
			+ this->data->displayField.width / 2.f
			- this->lastScoreText.getGlobalBounds().width / 2.f,

			this->data->displayField.top + this->data->displayField.height / 3.f
		)
		);

		this->bestScoreText.setString("Best Score: " + std::to_string(this->data->bestScore));

		this->data->saveScore(score, 'G');
	}
	else
	{
		this->lastScoreText.setString("Score: " + std::to_string(score));
		this->lastScoreText.setPosition(sf::Vector2f
		(
			this->data->displayField.left
			+ this->data->displayField.width / 2.f
			- this->lastScoreText.getGlobalBounds().width / 2.f,

			this->data->displayField.top + this->data->displayField.height / 3.f
		)
		);

		this->bestScoreText.setString("Best Score: " + std::to_string(this->data->bestScore));
	}

	this->bestScoreText.setCharacterSize( // used to be 32px
		static_cast <unsigned int> (this->data->displayField.height / 25)
	);
	this->bestScoreText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2
		- this->bestScoreText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 2.4f
	)
	);

	this->playButton.setContent("Play again!");
	this->playButton.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width / 2.f - this->playButton.getBounds().width / 2.f,
		this->data->displayField.top + this->data->displayField.height / 2.f
	)
	);
}


