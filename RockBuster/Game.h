#pragma once

#include "common.h"
#include "Player.h"
#include "Rock.h"
#include "Bullet.h"
#include "GameState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "CreditsState.h"
#include "HistoryState.h"
#include "StateData.h"

#include <vector>

#define PLAY_STATE 0
#define PAUSE_STATE 1
#define MENU_STATE 2
#define CREDITS_STATE 3
#define HISTORY_STATE 4
#define EXIT_STATE 5

class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	sf::Vector2f mousePosition;

	bool windowFocused;

	// States
	int state;

	GameState* gameState;
	MenuState* menuState;
	PauseState* pauseState;
	CreditsState* creditsState;
	HistoryState* historyState;

	// Sidebars
	sf::RectangleShape leftSidebar;
	sf::RectangleShape rightSidebar;

	// Texts
	sf::Font font;
	sf::Text versionText;

	// Private funtions
	void initWindow();
	void initStates();
	void initSideBars();
	void initTexts();

	void pollEvents();

	void updateMousePosition();

	Field getDisplayField();

public:
	Game();
	~Game();

	StateData* stateData;

	// Accessors
	bool isWindowOpen();

	// Public Funtions
	void update();
	void render();
};

