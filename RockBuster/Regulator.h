#pragma once

#include "common.h"

class Regulator
{
private:
	sf::Font font;
	sf::Text text;
	sf::RectangleShape bar;
	sf::RectangleShape barOutline;

	float value; // from 0 to 100

public:
	Regulator();
	~Regulator() {};

	float getValue();

	void setRegulator(sf::Vector2f position, std::string text, unsigned int textSize, sf::Vector2f barSize);

	void update(sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);
};
