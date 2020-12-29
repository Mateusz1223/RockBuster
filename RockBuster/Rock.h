#pragma once

#include "SFML-headers.h"

class Rock
{
private:
	// Rock body
	sf::CircleShape body; // used as hitbox
	sf::CircleShape appearance; // used for texture display
	sf::RectangleShape fire; // fire around rock

	// Logic variables
	sf::Vector2f speed; // speed in axis x and y
	unsigned int healthPoints; 
	unsigned int points; // number of points given to player after destroing this rock
	float rotateSpeed;

	// Private funtions
	void initBody(sf::Texture& rockTexture, sf::Texture& fireTexture);

public:
	Rock(sf::Vector2f position, sf::Vector2f speed, int healthPonts, int points,
			float rotateSpeed, float radius, sf::Texture& rockTexture, sf::Texture& fireTexture);
	~Rock() {};

	// Accessors
	sf::FloatRect getBounds();
	unsigned int getHealthPoints();
	unsigned int getPoints();
	sf::Vector2f getPosition();

	// Public Funtions
	void setPosition(sf::Vector2f position);
	void setSpeed(sf::Vector2f speed);
	void setHealthPoints(unsigned int healthPoints);
	void setPoints(unsigned int points);
	void setRotateSpeed(float rotateSpeed);
	void setRadius(float radius);

	void takeDemage(unsigned int healthPoints);

	void update();
	void render(sf::RenderTarget& target);
};

