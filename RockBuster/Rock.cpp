#include "Rock.h"

#include "common.h"

// Private funtions

void Rock::initBody(sf::Texture& rockTexture, sf::Texture& fireTexture)
{
	int rockNum = randInRange(0, 3);

	this->appearance.setTexture(&rockTexture);

	this->fire.setTexture(&fireTexture);
}

Rock::Rock(sf::Vector2f position, sf::Vector2f speed, int healthPoints, int points,
			float rotateSpeed, float radius, sf::Texture& rockTexture, sf::Texture& fireTexture)
{
	this->initBody(rockTexture, fireTexture);
	this->setPosition(position);
	this->setSpeed(speed);
	this->setHealthPoints(healthPoints);
	this->setPoints(points);
	this->setRotateSpeed(rotateSpeed);
	this->setRadius(radius);
}

// Accessors

sf::FloatRect Rock::getBounds()
{
	return this->body.getGlobalBounds();
}

unsigned int Rock::getHealthPoints()
{
	return this->healthPoints;
}

unsigned int Rock::getPoints()
{
	return this->points;
}

sf::Vector2f Rock::getPosition()
{
	return this->body.getPosition();
}

// Public Funtions

void Rock::setPosition(sf::Vector2f position)
{
	this->body.setPosition(position);
	this->appearance.setPosition(position);
	this->fire.setPosition(position);
}

void Rock::setSpeed(sf::Vector2f speed)
{
	this->speed = speed;

	if (speed.y < 0.f)
	{
		speed.y = -speed.y; // prevents rocks going up
	}

	float tangens = speed.x / speed.y;
	float angle = - atan(tangens) * 57.3f;;

	this->fire.setRotation(0);
	this->fire.rotate(angle);
}

void Rock::setHealthPoints(unsigned int healthPoints)
{
	this->healthPoints = healthPoints;
}

void Rock::setPoints(unsigned int points)
{
	this->points = points;
}

void Rock::setRotateSpeed(float rotateSpeed)
{
	this->rotateSpeed = rotateSpeed;
}

void Rock::setRadius(float radius)
{
	this->body.setRadius(radius);
	this->body.setOrigin(sf::Vector2f(radius, radius));


	this->appearance.setRadius(radius);
	this->appearance.setOrigin(sf::Vector2f(radius, radius));

	this->fire.setSize(
		sf::Vector2f(
			radius * 2.5f,
			radius * 2.5f * 3.f
		)
	);

	this->fire.setOrigin(
		sf::Vector2f(
			this->fire.getSize().x / 2.f,
			this->fire.getSize().y * 0.84f
		)
	);
}

void Rock::takeDemage(unsigned int healthPoints)
{
	if (this->healthPoints >= healthPoints)
		this->healthPoints -= healthPoints;
	else
		this->healthPoints = 0;
}

void Rock::update()
{
	this->body.move(this->speed);
	this->appearance.move(this->speed);
	this->fire.move(this->speed);
	this->appearance.rotate(this->rotateSpeed);
}

void Rock::render(sf::RenderTarget& target)
{
	target.draw(this->fire);
	target.draw(this->appearance);
}
