#include "Explosion.h"

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size, sf::Texture& texture)
{
	this->body.setPosition(position);

	this->body.setSize(size);
	this->body.setOrigin(
		sf::Vector2f(
			size.x / 2.f,
			size.y / 2.f
		)
	);

	this->body.setTexture(&texture);

	this->lifeSpan = 0;
}

unsigned int Explosion::getLifeSpan()
{
	return this->lifeSpan;
}

void Explosion::update()
{
	this->lifeSpan++;
}

void Explosion::render(sf::RenderTarget& target)
{
	target.draw(this->body);
}
