#include "Bullet.h"

#include "common.h"


// Private funtions

void Bullet::initBody(sf::Texture& texture)
{
	this->body.setTexture(&texture);
	this->body.setSize(sf::Vector2f(10.f, 25.f));
	this->body.setOrigin(5.f, 12.f);
}

// Constructor, destructor

Bullet::Bullet(sf::Vector2f size, sf::Vector2f position, sf::Vector2f speed, sf::Texture& texture, unsigned int demage)
{
	this->initBody(texture);

	this->body.setSize(size);
	this->body.setPosition(position);
	this->speed = speed;
	this->demage = demage;
}

Bullet::~Bullet()
{
}

// Accessors

sf::FloatRect Bullet::getBounds()
{
	return this->body.getGlobalBounds();
}

unsigned int Bullet::getDemage()
{
	return this->demage;
}

// Public Funtions

void Bullet::update()
{
	this->body.move(this->speed);
}

void Bullet::render(sf::RenderTarget& target)
{
	target.draw(this->body);
}
