#include "PauseState.h"

#include "common.h"

// Private funtions

void PauseState::initBackground()
{
	this->background.setSize(this->data->displayField.size);

	this->background.setPosition(this->data->displayField.position);

	this->background.setFillColor(sf::Color::Color(0, 0, 0, 170));
}

void PauseState::initTexts()
{
	if (!this->font.loadFromFile("Fonts/astroarmada.ttf"))
	{
		std::cout << "ERROR: PauseState::initTexts(): Font cannot be loaded\n";
	}

	this->gamePausedText.setFont(this->font);
	this->gamePausedText.setString("Game Paused");
	this->gamePausedText.setCharacterSize( // used to be 55px
		static_cast <unsigned int> (this->data->displayField.height / 14.f)
	);
	this->gamePausedText.setFillColor(sf::Color::White);
	this->gamePausedText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->gamePausedText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 5.f
	)
	);


	this->scoreText.setFont(this->font);
	this->scoreText.setString("Score: " + std::to_string(this->score)); // needs to be updated after every score set
	this->scoreText.setCharacterSize( // used to be 38px
		static_cast <unsigned int> (this->data->displayField.height / 21.f)
	);
	this->scoreText.setFillColor(sf::Color::White);
	this->scoreText.setPosition(sf::Vector2f // needs to be updated after every score set too
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->scoreText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 2.9f
	)
	);
}

void PauseState::initButtons()
{
	this->continueButton.setContent("Continue");
	this->continueButton.setCharacterSize( // used to be 40px
		static_cast <unsigned int> (this->data->displayField.height / 20.f)
	);
	this->continueButton.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width / 2.f - this->continueButton.getBounds().width / 2.f,
		this->data->displayField.top + this->data->displayField.height / 2.3f
	)
	);

	this->backToMenuButton.setContent("Back to menu");
	this->backToMenuButton.setCharacterSize( // used to be 26px
		static_cast <unsigned int> (this->data->displayField.height / 30.f)
	);
	this->backToMenuButton.setPosition(sf::Vector2f(
		this->data->displayField.left + this->data->displayField.width - this->backToMenuButton.getBounds().width - 10.f,
		this->data->displayField.top + this->data->displayField.height - this->backToMenuButton.getBounds().height - 20.f // something is wrong with the height of button (now it's a little bit different because of button contnt outline but anyway height of font doesnt match)
	)
	);
}

void PauseState::updateButtons()
{
	this->continueButton.update(this->mousePosition);
	this->backToMenuButton.update(this->mousePosition);

	this->data->soundRegulator.update(this->mousePosition);

	this->data->soundPack->volume = this->data->soundRegulator.getValue();
}

PauseState::PauseState(StateData* data)
{
	this->data = data;
	
	this->score = 0;

	this->initBackground();
	this->initTexts();
	this->initButtons();

	this->flag = NONE_FLAG;
}

// Public Funtions

int PauseState::update(sf::Vector2f mousePosition)
{
	this->flag = NONE_FLAG;

	this->mousePosition = mousePosition;

	this->updateButtons();

	if (this->backToMenuButton.isPressed())
	{
		this->flag = BACK_TO_MENU_REQUEST_PAUSE_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}
	else if (this->continueButton.isPressed())
	{
		this->flag = CONTINUE_REQUEST_PAUSE_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}

	if (this->flag != NONE_FLAG) // used for preventing unwanted press when state change
	{
		this->continueButton.setholdMouseLeft();
		this->backToMenuButton.setholdMouseLeft();
	}

	return this->flag;
}

void PauseState::render(sf::RenderTarget& target)
{
	target.draw(background);

	target.draw(this->gamePausedText);
	target.draw(this->scoreText);

	this->continueButton.render(target);
	this->backToMenuButton.render(target);
	this->data->soundRegulator.render(target);
}

void PauseState::setScore(unsigned int score)
{
	this->score = score;
	this->scoreText.setString("Score: " + std::to_string(this->score));
	this->scoreText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->scoreText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 2.9f
	)
	);
}



