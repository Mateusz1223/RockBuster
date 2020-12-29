#include "Player.h"

// Private funtions

void Player::initBody(sf::Vector2f size)
{
	this->body.setSize(size); // sf::Vector2f(66.f, 106.f)
	this->body.setOrigin(
		size.x/2,
		size.y/2
	);
}

// Constructor, destructor

Player::Player(sf::Vector2f size, sf::Vector2f position, float maxSpeed)
{
	this->maxSpeed = maxSpeed;
	this->speed = 0;
	this->acceleration = this->maxSpeed / 40;

	this->points = 0;
	this->healthPoints = 1;

	this->initBody(size);

	this->setPosition(position);
}

Player::~Player()
{
}

// Accessors

sf::Vector2f Player::getPosition()
{
	return sf::Vector2f(this->body.getPosition());
}

sf::FloatRect Player::getBounds()
{
	return this->body.getGlobalBounds();
}

unsigned int Player::getPoints()
{
	return this->points;
}

unsigned int Player::getHealthPoints()
{
	return this->healthPoints;
}

float Player::getSpeed()
{
	return this->speed;
}

// Public Funtions

void Player::useLeftEngine()
{
	this->speed -= this->acceleration * 2;

	if (this->speed < -this->maxSpeed)
		this->speed = -this->maxSpeed;
}

void Player::useRightEngine()
{
	this->speed += this->acceleration * 2;

	if (this->speed > this->maxSpeed)
		this->speed = this->maxSpeed;
}

void Player::stop()
{
	this->speed = 0.f;
}

void Player::update()
{
	if (this->speed < 0.f)
		this->speed += this->acceleration;
	else if (this->speed > 0.f)
		this->speed -= this->acceleration;

	if (this->speed > -this->acceleration && this->speed < this->acceleration)
		this->stop();

	this->body.move(this->speed, 0.f);
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->body);
}

void Player::addPoints(unsigned int p)
{
	this->points += p;
}

void Player::takeDamage()
{
	if(this->healthPoints > 0)
		this->healthPoints--;
}

void Player::takeHealthPointsBonus()
{
	this->healthPoints++;
}

void Player::setPosition(sf::Vector2f position)
{
	this->body.setPosition(position);
}

void Player::setTexture(sf::Texture& texture)
{
	this->body.setTexture(&texture);
}


