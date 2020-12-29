#include "Button.h"

// Private funtions

void Button::initVariables()
{
	if (!this->font.loadFromFile("Fonts/astroarmada.ttf"))
	{
		std::cout << "ERROR: Button::initVariables(): Font cannot be loaded\n";
	}

	this->content.setFont(this->font);

	this->hovered = false;
	this->pressed = false;

	this->content.setOutlineColor(sf::Color(0,0,0, 0));
	this->content.setOutlineThickness(3); // makes it easier to press (I don't like this solution must think about something prettier)
	this->content.setOrigin(sf::Vector2f( // sets origin to top left corner of Global Bounds (dependent from outline thickness)
		-30.f,
		-30.f
		));

	this->holdMouseLeft = true;
}

Button::Button(std::string content, sf::Vector2f position)
{
	this->initVariables();
	this->setContent(content);
	this->setPosition(position);
}

// Accessors

sf::FloatRect Button::getBounds()
{
	return this->content.getGlobalBounds();
}

bool Button::isPressed()
{
	return this->pressed;
}

// Public funtions

void Button::setPosition(sf::Vector2f position)
{
	this->content.setPosition(position);
}

void Button::setContent(std::string content)
{
	this->content.setString(content);
}

void Button::setCharacterSize(int size)
{
	this->content.setCharacterSize(size);
	this->content.setOutlineThickness(static_cast <float> (size)); // makes it easier to press (I don't like this solution must think about something prettier)
	this->content.setOrigin(sf::Vector2f( // sets origin to top left corner of Global Bounds (dependent from outline thickness)
		-static_cast <float> (size),
		-static_cast <float> (size)
	));
}

void Button::setholdMouseLeft()
{
	this->holdMouseLeft = true;
}

void Button::update(sf::Vector2f mousePosition)
{
	if (this->getBounds().contains(mousePosition))
		this->hovered = true;
	else
		this->hovered = false;

	//std::cout << this->getBounds().height << "\n"; // !!!!!!!!!!!!!!!!!!!!!!!!!

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!this->holdMouseLeft)
		{
			if (this->hovered)
			{
				this->holdMouseLeft = true;
				this->pressed = true;
			}
			else
				this->pressed = false;
		}
		else
			this->pressed = false;
	}
	else
	{
		this->holdMouseLeft = false;
		this->pressed = false;
	}

	if (this->hovered)
		this->content.setFillColor(sf::Color::Color(150, 150, 150, 255));
	else
		this->content.setFillColor(sf::Color::White);

}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->content);
}
