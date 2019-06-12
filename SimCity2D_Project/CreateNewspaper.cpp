#include "CreateNewspaper.h"

CreateNewspaper::~CreateNewspaper()
{
	if (this->holdGameplay != nullptr)
	{
		delete this->holdGameplay;
		this->holdGameplay = nullptr;
	}
}

void CreateNewspaper::LoadNewspapersFromFile(const std::string & filePath)
{
	templateNewspaper.date = "";
	templateNewspaper.text = "";
	templateNewspaper.title = "";

	std::ifstream newspaperFile;

	std::string bodyTmp;

	newspaperFile.open(filePath);
	if (newspaperFile.good())
	{
		std::getline(newspaperFile, templateNewspaper.date);
		std::getline(newspaperFile, templateNewspaper.title);

		while (!newspaperFile.eof())
		{
			std::getline(newspaperFile, bodyTmp);
			this->templateNewspaper.text += bodyTmp;
		}
		newspaperFile.close();
	}
}

void CreateNewspaper::HeadlinesToEvent(TypeOfNewspaper typeOfNewspaper)
{
	switch (typeOfNewspaper)
	{
	case TypeOfNewspaper::NEW_GAME:
		this->headline = "has new mayor";
		break;
	case TypeOfNewspaper::REGULAR:
		this->headline = "made a few changes";
		break;
	}
}

TemplateNewspaper CreateNewspaper::GenerateNewspaper(TypeOfNewspaper typeOfNewspaper)
{
	std::smatch matches;

	std::string eventString = "event";
	std::string cityString = "town_name";
	std::string homelessString = "homeless";
	std::string unemployedString = "unemployed";
	std::string populationString = "population";
	std::string happinessString = "happiness";

	std::regex pattern_date("([0-9]{2})-([0-9]{2})-([0-9]{4})");
	std::regex pattern_event(R"(\{\{)" + eventString + R"(\}\})");
	std::regex pattern_cityName(R"(\{\{)" + cityString + R"(\}\})");
	std::regex pattern_seed("([0-9]{8})");
	std::regex pattern_mapSize("(xxx){1}");
	std::regex pattern_money("(0{1})");
	std::regex pattern_homeless(R"(\{\{)" + homelessString + R"(\}\})");
	std::regex pattern_unemployed(R"(\{\{)" + unemployedString + R"(\}\})");
	std::regex pattern_population(R"(\{\{)" + populationString + R"(\}\})");
	std::regex pattern_happiness(R"(\{\{)" + happinessString + R"(\}\})");

	this->HeadlinesToEvent(typeOfNewspaper);

	templateNewspaper.date = std::regex_replace(templateNewspaper.date, pattern_date, this->holdGameplay->GetDate());
	templateNewspaper.title = std::regex_replace(templateNewspaper.title, pattern_event, this->headline);
	templateNewspaper.title = std::regex_replace(templateNewspaper.title, pattern_cityName, this->holdGameplay->GetCityName());
	

	switch (typeOfNewspaper)
	{
	case TypeOfNewspaper::NEW_GAME:
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_seed, std::to_string(this->holdGameplay->GetGameSeed()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_mapSize, std::to_string(this->holdGameplay->GetMaptile()->GetSizeOfMap()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_money, std::to_string(this->holdGameplay->GetCityMoney()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_homeless, std::to_string(this->holdGameplay->GetHomeless()));
		break;
	case TypeOfNewspaper::REGULAR:
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_money, std::to_string(this->holdGameplay->GetCityMoney()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_homeless, std::to_string(this->holdGameplay->GetHomeless()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_unemployed, std::to_string(this->holdGameplay->GetUnemployed()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_population, std::to_string(this->holdGameplay->GetPopulation()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_happiness, std::to_string(this->holdGameplay->GetAverageHappiness()));
		templateNewspaper.text = std::regex_replace(templateNewspaper.text, pattern_cityName, this->holdGameplay->GetCityName());
		break;
	}


	std::string modifiedBody;
	std::regex pattern_newLine("^.{1,50} ");
	while (std::regex_search(templateNewspaper.text, matches, pattern_newLine))
	{
		for (auto x : matches)
		{
			modifiedBody += x;
			modifiedBody += '\n';
			templateNewspaper.text = matches.suffix().str();
		}
	}
	templateNewspaper.text = modifiedBody;

	return templateNewspaper;
}