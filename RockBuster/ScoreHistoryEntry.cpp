#include "ScoreHistoryEntry.h"

ScoreHistoryEntry::ScoreHistoryEntry(char type, std::string date, unsigned int score, std::string version)
{
	this->type = type;
	this->date = date;
	this->score = score;
	this->version = version;
}

std::string ScoreHistoryEntry::getString()
{
	std::string str = "";
	if (this->type == 'B')
		str += "New Best Score";
	else
		str += "Good Score       ";

	
	str += "    ";
	str += this->version;
	str += "    ";
	str += this->date;
	str += "    Score: ";
	str += std::to_string(this->score);

	return str;
}
