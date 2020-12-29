#pragma once

#include "common.h"

#include "SoundPack.h"

class Button
{
private:
	// Content
	sf::Font font;
	sf::Text content;

	sf::Vector2f position;

	// States
	bool hovered;
	bool pressed;

	// Input
	bool holdMouseLeft;

	// Private funtions
	void initVariables();

public:
	Button(std::string content = "NONE", sf::Vector2f position = sf::Vector2f(0.f, 0.f));
	~Button() {};

	// Accessors
	bool isPressed();
	sf::FloatRect getBounds();

	// Public functions
	void setPosition(sf::Vector2f position);
	void setContent(std::string content);
	void setCharacterSize(int size);

	void setholdMouseLeft(); // used for preventing unwanted press when state change

	void update(sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);
};

