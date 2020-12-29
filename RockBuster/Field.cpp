#include "Field.h"

Field::Field()
{
	this->left = 0.f;
	this->top = 0.f;
	this->width = 0.f;
	this->height = 0.f;

	this->size = sf::Vector2f(0.f, 0.f);
	this->position = sf::Vector2f(0.f, 0.f);
}

void Field::setField(float left, float top, float width, float height, float reference)
{
	this->left = left;
	this->top = top;
	this->width = width;
	this->height = height;
	this->reference = reference;

	this->size = sf::Vector2f(width, height);
	this->position = sf::Vector2f(left, top);
}
