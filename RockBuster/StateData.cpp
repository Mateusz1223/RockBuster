#include "StateData.h"

#include <windows.h> // SHGetKnownFolderPath (must be here because colidates with SFML)
#include <wchar.h>
#include <KnownFolders.h>
#include <shlobj.h>

StateData::StateData(Field displayField)
{
	PWSTR path = NULL;

	HRESULT hr = SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &path);

	if (SUCCEEDED(hr)) {

		//wprintf(L"%ls", path);

		std::wstring ws(path);
		std::string str(ws.begin(), ws.end());

		documentsPath = str;
	}
	else
	{
		std::cout << "StateData::StateData() Cannot find documents path\n";

		documentsPath = ""; // should never happen (lost of score history when game updated)
	}

	CoTaskMemFree(path);

	this->displayField = displayField;

	this->texturePack = new TexturePack();
	this->soundPack = new SoundPack();

	this->bestScore = 0;

	// Loading data from file
	std::cout << documentsPath + "\\RockBusterData\\data.dat" << std::endl;

	char line[21];
	std::ifstream file(documentsPath + "\\RockBusterData\\data.dat"); // Windows specific

	while (file.read(line, 20))
	{
		std::string date(line+1, 10);

		std::string version(line+15, 4);

		this->scoreHistory.push_back(
			new ScoreHistoryEntry(
				line[0],
				date,
				*reinterpret_cast<int*>(&line[11]),
				version
			)
		);

		if (line[0] == 'B' && version[1] == VERSION[1]) // if best score and current main version
			this->bestScore = *reinterpret_cast<int*>(&line[11]);
	}

	file.close();

	this->soundRegulator.setRegulator(
		sf::Vector2f(
			this->displayField.left + this->displayField.width / 60.f,
			this->displayField.top + this->displayField.height / 60.f
		),
		"Sound",
		static_cast <unsigned int> (this->displayField.reference / 40.f),
		sf::Vector2f(
			this->displayField.reference / 8.f,
			this->displayField.reference / 70.f
		)
	);

	this->historyChanged = true;
}

StateData::~StateData()
{
	delete this->texturePack;
	delete this->soundPack;
}

void StateData::saveScore(unsigned int score, char type)
{
	// Make sure data folder exists

	std::string str = this->documentsPath + "\\RockBusterData";

	const char *dir = str.c_str();
	_mkdir(dir);

	// get date
	time_t rawtime;
	time(&rawtime);

	struct tm* timeinfo;
#pragma warning(suppress : 4996)
	timeinfo = localtime(&rawtime);

	char buffer[11];
	strftime(buffer, sizeof(buffer), "%d-%m-%Y", timeinfo);
	std::string date(buffer);

	std::ofstream file;
	file.open(documentsPath + "\\RockBusterData\\data.dat", std::ios::app); // Windows specific
	file << type; // stands for best score
	file << date;
	file.write(reinterpret_cast<char*>(&score), sizeof(score));
	file << VERSION;
	file << '\n';
	file.close();

	this->scoreHistory.push_back(
		new ScoreHistoryEntry(
			type,
			date,
			score,
			VERSION
		)
	);

	this->historyChanged = true;
}
