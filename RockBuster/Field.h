#pragma once

#include "SFML-headers.h"

class Field
{
public:
	float left;
	float top;
	float width;
	float height;
	float reference;  // not sure if this is needed

	sf::Vector2f size;
	sf::Vector2f position;

	Field();
	~Field() {};

	void setField(float left, float top, float width, float height, float reference);
};

