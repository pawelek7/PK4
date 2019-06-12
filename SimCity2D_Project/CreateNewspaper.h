#ifndef CreateNewspaper_hpp
#define CreateNewspaper_hpp

#include "HoldGameplay.h"
#include "Article.h"

#include <string>
#include <unordered_map>
#include <array>
#include <iostream>
#include <fstream>
#include <regex>

class CreateNewspaper
{
	HoldGameplay *holdGameplay = nullptr;

	TemplateNewspaper templateNewspaper;

	std::string headline = "unknown";

	void HeadlinesToEvent(TypeOfNewspaper typeOfNewspaper);

public:
	CreateNewspaper() = default;
	CreateNewspaper(HoldGameplay *holdGameplay) 
		: holdGameplay(holdGameplay) 
	{
		//nothing
	}
	virtual ~CreateNewspaper();

	TemplateNewspaper GenerateNewspaper(TypeOfNewspaper typeOfNewspaper);
	void LoadNewspapersFromFile(const std::string & filePath);
};

#endif // !LoadArticle_hpp
