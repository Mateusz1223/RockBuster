#pragma once

#include "common.h"

#include "Field.h"
#include "Button.h"
#include "StateData.h"
#include "Regulator.h"

#define NONE_FLAG 0
#define PLAY_REQUEST_MENU_STATE_FLAG 1
#define CREDITS_REQUEST_MENU_STATE_FLAG 2
#define HISTORY_REQUEST_MENU_STATE_FLAG 3
#define EXIT_REQUEST_MENU_STATE_FLAG 4

class MenuState
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

	sf::Text titleText;
	sf::Text bestScoreText;
	sf::Text lastScoreText;

	// Buttons
	Button playButton;
	Button exitButton;
	Button creditsButton;
	Button historyButton;

	// Private funtions
	void initBackground();
	void initTexts();
	void initButtons();

	void updateButtons();

public:
	MenuState(StateData* data);
	~MenuState() {};

	// Accessors
	

	// Public Funtions
	int update(sf::Vector2f mousePosition); // return flag
	void render(sf::RenderTarget& target);

	void setLastScore(unsigned int score);
};

