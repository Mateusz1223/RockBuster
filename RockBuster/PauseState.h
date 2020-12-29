#pragma once

#include "common.h"

#include "Field.h"
#include "Button.h"
#include "StateData.h"
#include "Regulator.h"

#define NONE_FLAG 0
#define CONTINUE_REQUEST_PAUSE_STATE_FLAG 1
#define BACK_TO_MENU_REQUEST_PAUSE_STATE_FLAG 2

class PauseState
{
private:
	StateData* data;

	// Data
	unsigned int score;

	// Input
	sf::Vector2f mousePosition;

	// Background
	sf::RectangleShape background;

	// Logic
	int flag;

	// Texts
	sf::Font font;

	sf::Text gamePausedText;
	sf::Text scoreText;

	// Buttons
	Button continueButton;
	Button backToMenuButton;

	// Private funtions
	void initBackground();
	void initTexts();
	void initButtons();

	void updateButtons();

public:
	PauseState(StateData* data);
	~PauseState() {};

	// Public Funtions
	int update(sf::Vector2f mousePosition); // return flag
	void render(sf::RenderTarget& target);

	void setScore(unsigned int score);
};

