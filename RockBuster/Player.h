#pragma once

#include "common.h"

#include "TexturePack.h"

class Player
{
private:
	// Player body
	sf::RectangleShape body;

	// Logic variables
	float maxSpeed; // always positive value
	float speed;
	float acceleration;

	unsigned int points;
	unsigned int healthPoints;

	// Private funtions
	void initVariables(sf::Vector2f size, float maxSpeed);
	void initBody(sf::Vector2f size);

public:
	Player(sf::Vector2f size, sf::Vector2f position, float maxSpeed);
	~Player();

	// Accessors
	sf::Vector2f getPosition(); // don't needed
	sf::FloatRect getBounds();
	unsigned int getPoints();
	unsigned int getHealthPoints();
	float getSpeed();

	// Public Funtions
	void setPosition(sf::Vector2f position);
	void setTexture(sf::Texture& texture);

	void useLeftEngine();
	void useRightEngine();
	void stop();

	void addPoints(unsigned int p); // takes amount of points to be added
	void takeDamage();
	void takeHealthPointsBonus();

	void update();
	void render(sf::RenderTarget& target);
};

