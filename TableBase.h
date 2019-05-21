#ifndef TableBase_hpp
#define TableBase_hpp

#include "AssetsOfGame.h"
#include "defines.h"

class TableBase
{
protected:
	bool tableOpen = false;

	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;
	sf::Vector2f centre;
	sf::RectangleShape background;

	virtual void InitializeFont() = 0;
	virtual void InitializeButtons() = 0;
	virtual void InitializeText() = 0;
	virtual void InitializeBackground() = 0;

public:
	TableBase() = default;
	TableBase(std::shared_ptr<AssetsOfGame> ptrGame, int sizeMap = 0);

	virtual void UpdateTable(float elapsedTime) = 0;
	virtual void DrawTable() = 0;

	void SetIsTableOpen(bool tableOpen);
	bool GetIsTableOpnen() const;
};

#endif