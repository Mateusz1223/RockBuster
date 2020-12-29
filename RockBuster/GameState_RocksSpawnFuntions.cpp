#include "GameState.h"

// rocks spawning

void GameState::spawnRocks()
{
	typedef void (GameState::* SpawnFunction) ();
	SpawnFunction stages[18] = { &GameState::spawnRock0, &GameState::spawnRock1, &GameState::spawnRock2,
								&GameState::spawnRock3, &GameState::spawnRock4, &GameState::spawnRock5,

								&GameState::spawnRock6,&GameState::spawnRock7,&GameState::spawnRock8,
								&GameState::spawnRock9,&GameState::spawnRock10,&GameState::spawnRock11,

								&GameState::spawnRock12,&GameState::spawnRock13,&GameState::spawnRock14,
								&GameState::spawnRock15,&GameState::spawnRock16,&GameState::spawnRock17 };

	if (this->rockSpawnTimer > this->rockSpawningInterval)
		this->rockSpawnTimer = 0;

	if (this->player->getPoints() > this->sequence)
	{
		this->sequence = static_cast <unsigned int> (
			static_cast <float> (this->sequence) * 1.5f
			);

		this->rockLevel++;

		if (this->rockLevel > 17) // attention here!!!!!!! potential MISTAKES (index)
			this->rockLevel = 17;

		this->rockSpeed += this->data->displayField.height / 700.f / 17.f;
		if (this->rockSpeed > this->data->displayField.height / 700.f * 2.05f)
			this->rockSpeed = this->data->displayField.height / 700.f * 2.05f;

		this->rockSpawningInterval -= 3;
		if (this->rockSpawningInterval < 60)
			this->rockSpawningInterval = 60;

		if (this->sequence > 19000)
			this->pointsMultiplier++;
		if (this->sequence > 65000)
			this->pointsMultiplier++;
	}

	if (this->rockSpawnTimer == 0)
	{
		int rockNum = randInRange(0, this->rockLevel);
		(this->*stages[rockNum])();
	}

	rockSpawnTimer++;
}

// -------------------------stage 0-------------------------------

# define SMALL_ROCK_POINTS_0 10
# define BIG_ROCK_POINTS_0 20

void GameState::spawnRock0() // small rock from the top 1HP, 10Points
{
	int texNum = randInRange(0, 3);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.left), static_cast <int>(this->data->displayField.left + this->data->displayField.width))),
				this->data->displayField.top - 2.f * this->smallRockRadius
			),
			sf::Vector2f(
				0.f,
				this->rockSpeed
			),
			1,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_0 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock1() // big rock from the top 2HP, 20Points
{
	int texNum = randInRange(0, 3);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.left), static_cast <int>(this->data->displayField.left + this->data->displayField.width))),
				this->data->displayField.top - 2.f * this->bigRockRadius
			),
			sf::Vector2f(
				0.f,
				this->rockSpeed
			),
			2,
			static_cast <unsigned int> (BIG_ROCK_POINTS_0 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock2() // small rock from the right 1HP, 10Points
{
	int texNum = randInRange(0, 3);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left + this->data->displayField.width + 2.f * this->smallRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				-this->rockSpeed,
				this->rockSpeed
			),
			1,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_0 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock3() // small rock from the left 1HP, 10Points
{
	int texNum = randInRange(0, 3);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left - 2.f * this->smallRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				this->rockSpeed,
				this->rockSpeed
			),
			1,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_0 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock4() // big rock from the right 2HP, 20Points
{
	int texNum = randInRange(0, 3);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left + this->data->displayField.width + 2.f * this->bigRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				-this->rockSpeed,
				this->rockSpeed
			),
			2,
			static_cast <unsigned int> (BIG_ROCK_POINTS_0 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock5() // big rock from the left 2HP, 20Points
{
	int texNum = randInRange(0, 3);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left - 2.f * this->bigRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				this->rockSpeed,
				this->rockSpeed
			),
			2,
			static_cast <unsigned int> (BIG_ROCK_POINTS_0 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

// -------------------------stage 1-------------------------------

# define SMALL_ROCK_POINTS_1 30
# define BIG_ROCK_POINTS_1 50

void GameState::spawnRock6() // small rock from the top 2HP, 20Points
{
	int texNum = randInRange(4, 5);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.left), static_cast <int>(this->data->displayField.left + this->data->displayField.width))),
				this->data->displayField.top - 2.f * this->smallRockRadius
			),
			sf::Vector2f(
				0.f,
				this->rockSpeed
			),
			2,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_1 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock7() // big rock from the top 4HP, 40Points
{
	int texNum = randInRange(4, 5);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.left), static_cast <int>(this->data->displayField.left + this->data->displayField.width))),
				this->data->displayField.top - 2.f * this->bigRockRadius
			),
			sf::Vector2f(
				0.f,
				this->rockSpeed
			),
			4,
			static_cast <unsigned int> (BIG_ROCK_POINTS_1 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock8() // small rock from the right 2HP, 20Points
{
	int texNum = randInRange(4, 5);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left + this->data->displayField.width + 2.f * this->smallRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				-this->rockSpeed,
				this->rockSpeed
			),
			2,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_1 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock9() // small rock from the left 2HP, 20Points
{
	int texNum = randInRange(4, 5);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left - 2.f * this->smallRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				this->rockSpeed,
				this->rockSpeed
			),
			2,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_1 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock10() // big rock from the right 4HP, 40Points
{
	int texNum = randInRange(4, 5);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left + this->data->displayField.width + 2.f * this->bigRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				-this->rockSpeed,
				this->rockSpeed
			),
			4,
			static_cast <unsigned int> (BIG_ROCK_POINTS_1 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock11() // big rock from the left 4HP, 40Points
{
	int texNum = randInRange(4, 5);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left - 2.f * this->bigRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				this->rockSpeed,
				this->rockSpeed
			),
			4,
			static_cast <unsigned int> (BIG_ROCK_POINTS_1 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

// -------------------------stage 2-------------------------------

# define SMALL_ROCK_POINTS_2 60
# define BIG_ROCK_POINTS_2 100

void GameState::spawnRock12() // small rock from the top 3HP, 30Points
{
	int texNum = randInRange(8, 9);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.left), static_cast <int>(this->data->displayField.left + this->data->displayField.width))),
				this->data->displayField.top - 2.f * this->smallRockRadius
			),
			sf::Vector2f(
				0.f,
				this->rockSpeed
			),
			3,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_2 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock13() // big rock from the top 5HP, 50Points
{
	int texNum = randInRange(8, 9);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.left), static_cast <int>(this->data->displayField.left + this->data->displayField.width))),
				this->data->displayField.top - 2.f * this->bigRockRadius
			),
			sf::Vector2f(
				0.f,
				this->rockSpeed
			),
			5,
			static_cast <unsigned int> (BIG_ROCK_POINTS_2 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock14() // small rock from the right 3HP, 30Points
{
	int texNum = randInRange(8, 9);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left + this->data->displayField.width + 2.f * this->smallRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				-this->rockSpeed,
				this->rockSpeed
			),
			3,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_2 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock15() // small rock from the left 3HP, 30Points
{
	int texNum = randInRange(8, 9);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left - 2.f * this->smallRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				this->rockSpeed,
				this->rockSpeed
			),
			3,
			static_cast <unsigned int> (SMALL_ROCK_POINTS_2 * this->pointsMultiplier),
			0.7f,
			this->smallRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock16() // big rock from the right 5HP, 50Points
{
	int texNum = randInRange(8, 9);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left + this->data->displayField.width + 2.f * this->bigRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				-this->rockSpeed,
				this->rockSpeed
			),
			5,
			static_cast <unsigned int> (BIG_ROCK_POINTS_2 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}

void GameState::spawnRock17() // big rock from the left 5HP, 50Points
{
	int texNum = randInRange(8, 9);

	rocks.push_back(
		new Rock(
			sf::Vector2f(
				this->data->displayField.left - 2.f * this->bigRockRadius,
				static_cast <float> (randInRange(static_cast <int>(this->data->displayField.top), static_cast <int>(this->data->displayField.top + this->data->displayField.height / 2.f)))
			),
			sf::Vector2f(
				this->rockSpeed,
				this->rockSpeed
			),
			5,
			static_cast <unsigned int> (BIG_ROCK_POINTS_2 * this->pointsMultiplier),
			0.7f,
			this->bigRockRadius,
			this->data->texturePack->rockTextures[texNum],
			this->data->texturePack->fireTexture
		)
	);
}