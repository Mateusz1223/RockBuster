#pragma once

#include "common.h"

class HealthPointsBonus
{
private:
	// Body
	sf::RectangleShape body;

	// Logic variables
	sf::Vector2f speed; // speed in axis x and y

	// Private funtions
	void initBody(sf::Texture& bodyTexture);

public:
	HealthPointsBonus(sf::Vector2f position, sf::Vector2f size, sf::Vector2f speed, sf::Texture& texture);
	~HealthPointsBonus() {};

	// Accessors
	sf::FloatRect getBounds();

	// Public Funtions
	void setPosition(sf::Vector2f position);
	void setSpeed(sf::Vector2f speed);
	void setSize(sf::Vector2f size);

	void update();
	void render(sf::RenderTarget& target);
};

