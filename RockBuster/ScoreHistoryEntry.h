#pragma once

#include "common.h"

class ScoreHistoryEntry
{
public:
	char type;
	std::string date;
	unsigned int score;
	std::string version;

	ScoreHistoryEntry(char type, std::string date, unsigned int score, std::string version);

	std::string getString();
};

