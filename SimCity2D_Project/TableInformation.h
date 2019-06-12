#ifndef TableInformation_hpp
#define TableInformation_hpp

#include <SFML/Graphics.hpp>

#include <utility>
#include <vector>

class TableLook
{
	friend class TableInformation;

	sf::Color tableColor, bolderColor, textColor, highLightColor;
	sf::Font *font;

	float tableSizeX = 0.0f;
	float tableSizeY = 0.0f;
	float characterSize = 0.0f;

public:
	TableLook() = default;
	TableLook(sf::Font* font, float tableSizeX, float tableSizeY, float characterSize,
		sf::Color tableColor, sf::Color textColor, sf::Color bolderColor, sf::Color highLightColor = sf::Color::Transparent);
	virtual ~TableLook() = default;
};

class GuiTableOption
{
	friend class TableInformation;

	std::string guiString = "unknown";

	sf::RectangleShape rectangleShape;
	sf::Text text;

public:
	GuiTableOption() = default;
	GuiTableOption(const std::string & guiString, sf::RectangleShape rectangleShape, sf::Text text);
	virtual ~GuiTableOption() = default;
};

class TableInformation : public sf::Transformable, public sf::Drawable
{
	bool hide = false;
	bool activated = false;

	TableLook tableLook;

	std::vector<GuiTableOption> textLines;

public:
	TableInformation() = default;
	TableInformation(std::vector<std::pair<std::string, std::string>> text, TableLook tableLook);
	virtual ~TableInformation() = default;

	virtual void draw(sf::RenderTarget & renderTarget, sf::RenderStates renderStates) const override;
	void GlowElement(int it);

	std::string ActivatedElement(int it);
	std::string ActivatedElement(const sf::Vector2f & mousePosition);

	void ShowTable();
	void Hidetable();

	//setters
	void SetTableText(int it, std::string text);

	//getters
	bool GetIsActivated();
	int GetOption(const sf::Vector2f & mousePosition);
};

#endif // !TableInformation_hpp