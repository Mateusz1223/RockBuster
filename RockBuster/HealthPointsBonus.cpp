#include "HealthPointsBonus.h"

// Private funtions

void HealthPointsBonus::initBody(sf::Texture& texture)
{
	this->body.setTexture(&texture);
	this->body.setFillColor(sf::Color::Green);
}

// Constructor

HealthPointsBonus::HealthPointsBonus(sf::Vector2f position, sf::Vector2f size, sf::Vector2f speed, sf::Texture& texture)
{
	this->initBody(texture);

	this->setPosition(position);
	this->setSize(size);
	this->setSpeed(speed);
}

// Accessors

sf::FloatRect HealthPointsBonus::getBounds()
{
	return this->body.getGlobalBounds();
}

// Public Funtions

void HealthPointsBonus::setPosition(sf::Vector2f position)
{
	this->body.setPosition(position);
}

void HealthPointsBonus::setSpeed(sf::Vector2f speed)
{
	this->speed = speed;
}

void HealthPointsBonus::setSize(sf::Vector2f size)
{
	this->body.setSize(size);
	this->body.setOrigin(
		sf::Vector2f(
			this->body.getSize().x / 2,
			this->body.getSize().y / 2
		)
	);
}

void HealthPointsBonus::update()
{
	this->body.move(speed);
}

void HealthPointsBonus::render(sf::RenderTarget& target)
{
	target.draw(body);
}
