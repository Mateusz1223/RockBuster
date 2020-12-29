#include "HistoryState.h"

// Private funtions

void HistoryState::initBackground()
{
	this->background.setSize(this->data->displayField.size);

	this->background.setPosition(this->data->displayField.position);

	this->background.setFillColor(sf::Color::Color(0, 0, 0, 170));
}

void HistoryState::initTexts()
{
	if (!this->font.loadFromFile("Fonts/astroarmadacondital.ttf"))
	{
		std::cout << "ERROR: HistoryState::initTexts(): Font cannot be loaded\n";
	}

	this->historyText.setFont(this->font);
	this->historyText.setString("Score History");
	this->historyText.setCharacterSize(
		static_cast <unsigned int> (this->data->displayField.height / 14.f)
	);
	this->historyText.setFillColor(sf::Color::White);
	this->historyText.setPosition(sf::Vector2f
	(
		this->data->displayField.left
		+ this->data->displayField.width / 2.f
		- this->historyText.getGlobalBounds().width / 2.f,

		this->data->displayField.top + this->data->displayField.height / 6.f
	)
	);

	this->contentText.setFont(this->font);
	this->contentText.setCharacterSize(
		static_cast <unsigned int> (this->data->displayField.height / 25.f)
	);
	this->contentText.setFillColor(sf::Color::White);
	this->contentText.setOutlineThickness(2);
	this->contentText.setOutlineColor(sf::Color(0, 0, 139, 255));
}

void HistoryState::initButtons()
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

void HistoryState::updateButtons()
{
	this->backToMenuButton.update(this->mousePosition);
}

void HistoryState::updateContent()
{
	if (this->data->historyChanged)
	{
		std::string content;

		if (this->data->scoreHistory.size() == 0)
		{
			content = "No succeses yet. Go get some...";
		}
		else
		{
			content = "---------------------------------------------------------------------\n";

			int counter = 1;
			for (int i = this->data->scoreHistory.size() - 1; i >= 0; i--)
			{
				if (counter > 6) // show 8 entries
					break;

				content += this->data->scoreHistory[i]->getString();
				content += "\n---------------------------------------------------------------------\n";
				counter++;
			}
		}

		this->contentText.setString(content);

		this->contentText.setPosition(sf::Vector2f
		(
			this->data->displayField.left
			+ this->data->displayField.width / 2.f
			- this->contentText.getGlobalBounds().width / 2.f,

			this->data->displayField.top + this->data->displayField.height / 3.f
		)
		);

		this->data->historyChanged = false;
	}
}

HistoryState::HistoryState(StateData* data)
{
	this->data = data;

	this->initBackground();
	this->initTexts();
	this->initButtons();

	this->flag = NONE_FLAG;
}

// Public Funtions

int HistoryState::update(sf::Vector2f mousePosition)
{
	this->flag = NONE_FLAG;

	this->mousePosition = mousePosition;

	this->updateButtons();

	this->updateContent();

	if (this->backToMenuButton.isPressed())
	{
		this->flag = BACK_TO_MENU_REQUEST_HISTORY_STATE_FLAG;
		this->data->soundPack->clickSound.setVolume(this->data->soundPack->volume);
		this->data->soundPack->clickSound.play();
	}

	if (this->flag != NONE_FLAG) // used for preventing unwanted press when state change
	{
		this->backToMenuButton.setholdMouseLeft();
	}

	return this->flag;
}

void HistoryState::render(sf::RenderTarget& target)
{
	target.draw(background);

	target.draw(this->historyText);
	target.draw(this->contentText);

	this->backToMenuButton.render(target);
}