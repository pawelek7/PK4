#ifndef DropList_hpp
#define DropList_hpp

#include <vector>

#include "TextButton.h"

class DropList
{
	float keyTime = 0.0f;
	float keyTimeMax = 1.0f;

	bool showList = false;
	bool clickedElement = false;
	bool mouseOnList = false;

	TextButton* activatedElement = nullptr;
	std::vector<TextButton*> list;

	sf::Font & font;

public:
	DropList(float x, float y, float width, float height, int characterSize, std::string text,
		sf::Font& font, std::string list[], std::shared_ptr<AssetsOfGame> ptrGame,
		unsigned nrOfElements, unsigned default_index = 0);
	~DropList();

	void UpdateKeyTime(const float & elapsedTime);
	void Update(const sf::Vector2f& mousePosition, const float & elapsedTime);
	void Draw(sf::RenderTarget *renderTarget);

	void SetClickedElement(bool clicked);

	const unsigned short & getActiveElementID() const;
	bool GetShowList() const;
	const bool GetKeyTime();
	bool GetIsMouseOnList() const;
	bool GetIsClickedElement() const;
};

#endif // !DropList_hpp
