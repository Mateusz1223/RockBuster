#pragma once

#include "common.h"

class Explosion
{
private:
	sf::RectangleShape body;

	unsigned int lifeSpan;

public:
	Explosion(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture);
	~Explosion() {};

	// Accesors
	unsigned int getLifeSpan();

	// Public functions
	void update();
	void render(sf::RenderTarget& target);
};

