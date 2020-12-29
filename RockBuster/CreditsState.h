#pragma once

#include "common.h"

#include "Field.h"
#include "Button.h"
#include "StateData.h"

#define NONE_FLAG 0
#define BACK_TO_MENU_REQUEST_CREDITS_STATE_FLAG 1

class CreditsState
{
private:
	StateData* data;

	// Input
	sf::Vector2f mousePosition;

	// Background
	sf::RectangleShape background;

	// Logic
	int flag;

	// Texts
	sf::Font font;

	sf::Text creditsText;
	sf::Text contentText;

	// Buttons
	Button backToMenuButton;

	// Private funtions
	void initBackground();
	void initTexts();
	void initButtons();

	void updateButtons();

public:
	CreditsState(StateData* data);
	~CreditsState() {};

	// Public Funtions
	int update(sf::Vector2f mousePosition); // return flag
	void render(sf::RenderTarget& target);
};

