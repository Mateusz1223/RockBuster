#pragma once

#include "common.h"

class Bullet
{
private:
	// Bullet body
	sf::RectangleShape body;

	// Logic variables
	sf::Vector2f speed; // speed in axis x and y
	unsigned int demage;

	// Private funtions
	void initBody(sf::Texture& texture);

public:
	Bullet(sf::Vector2f size, sf::Vector2f position, sf::Vector2f speed, sf::Texture& texture, unsigned int demage = 1);
	~Bullet();

	// Accessors
	sf::FloatRect getBounds();
	unsigned int getDemage();

	// Public Funtions
	void update();
	void render(sf::RenderTarget& target);
};

