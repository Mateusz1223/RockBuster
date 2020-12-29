#pragma once

#include "common.h"

#include "Field.h"
#include "TexturePack.h"
#include "SoundPack.h"
#include "Regulator.h"
#include "ScoreHistoryEntry.h"

class StateData
{
public:
	Field displayField;

	// score history
	bool historyChanged;
	std::vector<ScoreHistoryEntry*> scoreHistory;
	unsigned int bestScore;

	TexturePack* texturePack;
	SoundPack* soundPack;

	Regulator soundRegulator;

	std::string documentsPath;

	StateData(Field displayField);
	~StateData();

	void saveScore(unsigned int score, char type);
};

