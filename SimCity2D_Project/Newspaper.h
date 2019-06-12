#ifndef Newspaper_hpp
#define Newspaper_hpp

#include "CreateNewspaper.h"
#include "TextButton.h"
#include "ButtonBase.h"
#include "HoldGameplay.h"
#include "Article.h"
#include "TableBase.h"

class CreateNewspaper;

class Newspaper : public TableBase
{
	TemplateNewspaper templateNewspaper2;

	CreateNewspaper *createNewspaper = nullptr;
	TextButton *exitButton = nullptr;
	sf::Font font;
	sf::Text dataText, titleText, bodyText;

	virtual void InitializeFont() override;
	virtual void InitializeButtons() override;
	virtual void InitializeText() override;
	virtual void InitializeBackground() override;

public:
	Newspaper() = default;
	Newspaper(std::shared_ptr<AssetsOfGame> ptrGame, HoldGameplay *holdGameplay, int sizeMap);
	virtual ~Newspaper();

	virtual void UpdateTable(float elapsedTime) override;
	virtual void DrawTable() override;

	void NewspaperEvent(TypeOfNewspaper typeOfNewspaper);
};

#endif // !Newspaper_hpp
