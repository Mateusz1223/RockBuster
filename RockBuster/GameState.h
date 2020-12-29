#pragma once

#include "common.h"

#include "Player.h"
#include "Rock.h"
#include "Bullet.h"
#include "HealthPointsBonus.h"
#include "Field.h"
#include "Explosion.h"
#include "StateData.h"

#define NONE_FLAG 0
#define PAUSE_REQUEST_GAME_STATE_FLAG 1
#define GAME_OVER_GAME_STATE_FLAG 2

class GameState
{
private:
	StateData* data;
	
	// Input
	sf::Vector2f mousePosition;
	bool holdSpace;
	bool holdEscape;

	// Background
	sf::RectangleShape background;

	// Logic
	int flag;

	// User interface
	sf::Font font;
	sf::Text UItext;

	// Game logic
	bool gameRunning;

	// Game objects
	Player* player;


	// Rocks
	unsigned int rockSpawningInterval;
	unsigned int rockSpawnTimer;

	float rockSpeed;
	float smallRockRadius;
	float bigRockRadius;

	unsigned int rockLevel;
	unsigned int sequence; // Geometrical sequence used for determining if rock level should be increased

	unsigned int pointsMultiplier;

	std::vector<Rock*> rocks;

	// Bullet

	size_t maxBullets;
	std::vector<Bullet*> bullets;

	std::vector<HealthPointsBonus*> bonuses;

	std::vector<Explosion*> explosions;

	// Private funtions
	void initVariables();
	void initBackground();
	void initUI();
	void initPlayer();
	void initRocks();
	void initBullets();

	void checkPlayerCollision();
	void updatePlayer();

	void deleteRocks();
	void updateRocks();

	// rocks spawning
	void spawnRocks();
	// ---------------
	void spawnRock0();
	void spawnRock1();
	void spawnRock2();
	void spawnRock3();
	void spawnRock4();
	void spawnRock5();
	// ---------------
	void spawnRock6();
	void spawnRock7();
	void spawnRock8();
	void spawnRock9();
	void spawnRock10();
	void spawnRock11();
	// ---------------
	void spawnRock12();
	void spawnRock13();
	void spawnRock14();
	void spawnRock15();
	void spawnRock16();
	void spawnRock17();

	void updateBullets();

	void deleteBonuses();
	void updateBonuses();
	void spawnBonus(sf::Vector2f position);

	void shootBullet();
	void deleteBullets();
	void checkBulletsCollision();

	void updateExplosions();

	void updateUI();

	void clearVariables();

public:
	GameState(StateData* data);
	~GameState();

	// Accessors
	unsigned int getPoints();

	// Public Funtions
	int update();
	void render(sf::RenderTarget& target);

	void stopGame(); // used for stopping game
	void restartGame(); // used for starting new game
	void reassumeGame(); // used for reassuming game
};

