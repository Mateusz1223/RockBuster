#include "CreditsState.h"

#include "common.h"

// Private funtions

void CreditsState::initBackground()
{
	this->background.setSize(this->data->displayField.size);

	this->background.setPosition(this->data->displayField.position);

	this->background.setFillColor(sf::Color::Color(0, 0, 0, 170));
}

void CreditsState::initTexts()
{
	if (!this->font.loadFromFile("Fonts/astroarmadacondital.ttf"))
	{
		std::cout << "ERROR: CreditsState::initTexts(): Font cannot be loaded\n";
	}

	this->creditsText.setFont(this->font);
	this->creditsText.setString("Credits");
	this->creditsText.setCharacterSize(
		static_cast <unsigned int> (this->data->displayField.height / 14.f)
	);
	this->creditsText.setFillColor(sf::Color::White);
	this->creditsText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->creditsText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 6.f
	)
	);

	this->contentText.setFont(this->font);
	this->contentText.setString("Developer:  Mateusz Piasecki\n\nTextures from www.pexels.com\n\nSounds from freesound.org\n\n\nrocksbuster.piaseckimateusz.pl");
	this->contentText.setCharacterSize(
		static_cast <unsigned int> (this->data->displayField.height / 25.f)
	);
	this->contentText.setFillColor(sf::Color::White);
	this->contentText.setOutlineThickness(2);
	this->contentText.setOutlineColor(sf::Color(0, 0, 139, 255));
	this->contentText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->contentText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 3.f
	)
	);
}

void CreditsState::initButtons()
{
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

void CreditsState::updateButtons()
{
	this->backToMenuButton.update(this->mousePosition);
}

CreditsState::CreditsState(StateData* data)
{
	this->data = data;

	this->initBackground();
	this->initTexts();
	this->initButtons();

	this->flag = NONE_FLAG;
}

// Public Funtions

int CreditsState::update(sf::Vector2f mousePosition)
{
	this->flag = NONE_FLAG;

	this->mousePosition = mousePosition;

	this->updateButtons();

	if (this->backToMenuButton.isPressed())
	{
		this->flag = BACK_TO_MENU_REQUEST_CREDITS_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}

	if (this->flag != NONE_FLAG) // used for preventing unwanted press when state change
	{
		this->backToMenuButton.setholdMouseLeft();
	}

	return this->flag;
}

void CreditsState::render(sf::RenderTarget& target)
{
	target.draw(background);

	target.draw(this->creditsText);
	target.draw(this->contentText);

	this->backToMenuButton.render(target);
}