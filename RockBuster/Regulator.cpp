#include "Regulator.h"

Regulator::Regulator()
{
	if (!this->font.loadFromFile("Fonts/astroarmada.ttf"))
	{
		std::cout << "ERROR: Regulator::Regulator(): Font cannot be loaded\n";
	}

	this->text.setFont(this->font);

	this->bar.setFillColor(sf::Color::White);

	this->barOutline.setOutlineThickness(1.f);
	this->barOutline.setOutlineColor(sf::Color::White);
	this->barOutline.setFillColor(sf::Color(0, 0, 0, 100));

	this->value = 100.f;
}

float Regulator::getValue()
{
	return this->value;
}

void Regulator::setRegulator(sf::Vector2f position, std::string text, unsigned int textSize, sf::Vector2f barSize)
{
	this->text.setCharacterSize(textSize);
	this->text.setString(text);
	this->text.setPosition(position);

	this->bar.setSize(barSize);
	this->bar.setOrigin(
		sf::Vector2f(
			0.f,
			barSize.y / 2.f
		)
	);
	this->bar.setPosition(
		sf::Vector2f(
			this->text.getGlobalBounds().left + this->text.getGlobalBounds().width * 1.2f,
			this->text.getGlobalBounds().top + this->text.getGlobalBounds().height / 2.f
		)
	);

	this->barOutline.setSize(barSize);
	this->barOutline.setOrigin(
		sf::Vector2f(
			0.f,
			barSize.y / 2.f
		)
	);
	this->barOutline.setPosition(
		sf::Vector2f(
			this->text.getGlobalBounds().left + this->text.getGlobalBounds().width * 1.2f,
			this->text.getGlobalBounds().top + this->text.getGlobalBounds().height / 2.f
		)
	);
}

void Regulator::update(sf::Vector2f mousePosition)
{
	if (this->barOutline.getGlobalBounds().contains(mousePosition))
	{
		this->bar.setFillColor(sf::Color::Color(150, 150, 150, 255));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->value = (mousePosition.x - this->barOutline.getGlobalBounds().left) / this->barOutline.getSize().x * 100.f;

			if (this->value < 1.f)
				this->value = 0.f;
			else if (this->value > 99.f)
				this->value = 100.f;
		}
	}
	else
		this->bar.setFillColor(sf::Color::White);

	this->bar.setSize
	(
		sf::Vector2f(
			this->barOutline.getSize().x * this->value / 100.f,
			this->bar.getGlobalBounds().height
		)
	);
}

void Regulator::render(sf::RenderTarget& target)
{
	target.draw(this->text);
	target.draw(this->barOutline);
	target.draw(this->bar);
}
