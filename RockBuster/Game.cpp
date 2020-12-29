#include "Game.h"
#include "Field.h"

// Private functions

void Game::initWindow()
{
	this->videoMode.width = sf::VideoMode::getDesktopMode().width * 4/5; // szerokosc na podstawie wysokoœæi
	this->videoMode.height = sf::VideoMode::getDesktopMode().height * 4/5;

	this->window = new sf::RenderWindow(this->videoMode, "Rock buster", sf::Style::Default);

	this->window->setFramerateLimit(120);
}

void Game::initStates()
{
	this->gameState = new GameState(this->stateData);
	this->menuState = new MenuState(this->stateData);
	this->pauseState = new PauseState(this->stateData);
	this->creditsState = new CreditsState(this->stateData);
	this->historyState = new HistoryState(this->stateData);
}

void Game::initSideBars()
{
	this->leftSidebar.setFillColor(sf::Color::Black);
	this->rightSidebar.setFillColor(sf::Color::Black);

	if (this->videoMode.width > this->videoMode.height)
	{
		this->leftSidebar.setSize(
			sf::Vector2f(
				(this->videoMode.width - this->getDisplayField().width) / 2.f,
				static_cast <float> (this->videoMode.height)
			)
		);

		this->rightSidebar.setSize(
			sf::Vector2f(
				(this->videoMode.width - this->getDisplayField().width) / 2.f,
				static_cast <float> (this->videoMode.height)
			)
		);

		this->leftSidebar.setPosition(sf::Vector2f(0.f, 0.f));
		this->rightSidebar.setPosition(
			sf::Vector2f(
				this->getDisplayField().left + this->getDisplayField().width,
				0.f
			)
		);
	}
	else
	{
		this->leftSidebar.setSize(
			sf::Vector2f(
				static_cast <float> (this->videoMode.width),
				(this->videoMode.height - this->getDisplayField().height) / 2.f
			)
		);

		this->rightSidebar.setSize(
			sf::Vector2f(
				static_cast <float> (this->videoMode.width),
				(static_cast <float> (this->videoMode.height) - this->getDisplayField().height) / 2.f
			)
		);

		this->leftSidebar.setPosition(sf::Vector2f(0.f, 0.f));
		this->rightSidebar.setPosition(
			sf::Vector2f(
				0.f,
				this->getDisplayField().top + this->getDisplayField().height
			)
		);
	}
	
}

void Game::initTexts()
{
	if (!this->font.loadFromFile("Fonts/astroarmada.ttf"))
	{
		std::cout << "ERROR: MenuState::initTexts(): Font cannot be loaded\n";
	}

	this->versionText.setFont(this->font);
	this->versionText.setString(VERSION);
	this->versionText.setCharacterSize(
		static_cast <unsigned int> (this->stateData->displayField.height / 50.f)
	);
	this->versionText.setFillColor(sf::Color::White);
	this->versionText.setPosition(sf::Vector2f
	(
		this->stateData->displayField.left
		+ this->stateData->displayField.width
		- this->versionText.getGlobalBounds().width * 1.5f,

		this->stateData->displayField.top
		+ this->versionText.getGlobalBounds().height
	)
	);
}

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		// check the type of the event...
		switch (this->event.type)
		{
		case sf::Event::Closed:

			if (this->state == PLAY_STATE || this->state == PAUSE_STATE)
			{
				this->menuState->setLastScore(this->gameState->getPoints());

				this->gameState->stopGame();
			}

			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
			{
				if (this->state == PLAY_STATE)
				{
					this->pauseState->setScore(this->gameState->getPoints());
					this->gameState->stopGame();
					this->state = PAUSE_STATE;
				}
				else if (this->state == PAUSE_STATE)
				{
					this->state = PLAY_STATE;
					this->gameState->reassumeGame();
				}
			}
			break;

		case sf::Event::GainedFocus:
			this->windowFocused = true;
			break;

		case sf::Event::LostFocus:
			this->windowFocused = false;
			break;

		default:
			break;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosition = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

Field Game::getDisplayField()
{
	Field displayField;
	float left, top, width, height, reference;

	if (this->videoMode.height < this->videoMode.width)
	{
		width = static_cast <float> (this->videoMode.height);
		height = static_cast <float> (this->videoMode.height);

		left = this->videoMode.width / 2.f - width / 2.f;
		top = 0.f;

		reference = static_cast <float> (this->videoMode.height);
	}
	else
	{
		width = static_cast <float> (this->videoMode.width);
		height = static_cast <float> (this->videoMode.width);

		left = 0.f;
		top = this->videoMode.height / 2.f - height / 2.f;

		reference = static_cast <float> (this->videoMode.width);
	}

	displayField.setField(left, top, width, height, reference); // width is equal to height
	
	return displayField;
}

// Constructor, destructor

Game::Game()
{
	this->initWindow();

	this->state = MENU_STATE;
	this->stateData = new StateData(this->getDisplayField());
	this->initStates();
	this->initSideBars();
	this->initTexts();

	this->windowFocused = true;
}

Game::~Game()
{
	delete this->window;
	delete this->gameState;
	delete this->pauseState;
	delete this->creditsState;
	delete this->historyState;
}

// Accessors

bool Game::isWindowOpen()
{
	return this->window->isOpen();
}

//Public functions

void Game::update()
{
	this->pollEvents();
	this->updateMousePosition();

	if (this->windowFocused == false)
		return;

	if (this->state == MENU_STATE)
	{
		int flag = NONE_FLAG;
		flag = this->menuState->update(this->mousePosition);

		if (flag == EXIT_REQUEST_MENU_STATE_FLAG)
			this->state = EXIT_STATE;
		else if (flag == PLAY_REQUEST_MENU_STATE_FLAG)
		{
			this->gameState->restartGame();
			this->state = PLAY_STATE;
		}
		else if (flag == CREDITS_REQUEST_MENU_STATE_FLAG)
		{
			this->state = CREDITS_STATE;
		}
		else if (flag == HISTORY_REQUEST_MENU_STATE_FLAG)
		{
			this->state = HISTORY_STATE;
		}
	}
	else if (this->state == PLAY_STATE)
	{
		int flag = NONE_FLAG;
		flag = this->gameState->update();

		if (flag == GAME_OVER_GAME_STATE_FLAG)
		{
			this->menuState->setLastScore(this->gameState->getPoints());

			this->gameState->stopGame();
			this->state = MENU_STATE;
		}

	}
	else if (this->state == PAUSE_STATE)
	{
		int flag = NONE_FLAG;
		flag = this->pauseState->update(this->mousePosition);

		if (flag == BACK_TO_MENU_REQUEST_PAUSE_STATE_FLAG)
		{
			this->menuState->setLastScore(this->gameState->getPoints());
			this->state = MENU_STATE;
		}
		else if (flag == CONTINUE_REQUEST_PAUSE_STATE_FLAG)
		{
			this->state = PLAY_STATE;
			this->gameState->reassumeGame();
		}
	}
	else if (this->state == CREDITS_STATE)
	{
		int flag = NONE_FLAG;
		flag = this->creditsState->update(this->mousePosition);

		if (flag == BACK_TO_MENU_REQUEST_CREDITS_STATE_FLAG)
		{
			this->state = MENU_STATE;
		}
	}
	else if (this->state == HISTORY_STATE)
	{
		int flag = NONE_FLAG;
		flag = this->historyState->update(this->mousePosition);

		if (flag == BACK_TO_MENU_REQUEST_HISTORY_STATE_FLAG)
		{
			this->state = MENU_STATE;
		}
	}
	else if (this->state == EXIT_STATE)
		this->window->close();
}

void Game::render()
{
	this->window->clear();

	this->gameState->render(*this->window);

	if (state == MENU_STATE)
		this->menuState->render(*this->window);
	else if (state == PAUSE_STATE)
		this->pauseState->render(*this->window);
	else if (state == CREDITS_STATE)
		this->creditsState->render(*this->window);
	else if (state == HISTORY_STATE)
		this->historyState->render(*this->window);

	this->window->draw(this->leftSidebar);
	this->window->draw(this->rightSidebar);

	this->window->draw(this->versionText);

	this->window->display();
}