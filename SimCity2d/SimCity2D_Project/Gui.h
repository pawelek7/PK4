#ifndef Gui_hpp
#define Gui_hpp
#include <utility>
#include <SFML/Graphics.hpp> //SFML library
#include <string>
#include <vector>
enum class StateOfButton
{BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE = 2};

namespace Gui
{
	class GameGuiBase
	{
	public:
		sf::Color bodyCol;
		sf::Color bodyHighCol;
		sf::Color borderCol;
		sf::Color borderHighlightCol;
		sf::Font * font;
		sf::Color bodyHighlightCol;
		sf::Color textCol;
		sf::Color textHighlightCol;
		float borderSize = 0.0f;


		GameGuiBase() = default;
		GameGuiBase(sf::Font * font, float borderSize, sf::Color bodyCol, sf::Color borderCol, sf::Color textCol, sf::Color bodyHighlightCol, sf::Color borderHighlightCol, sf::Color textHighlightCol)
		{
			this->bodyCol = bodyCol;
			this->borderCol = borderCol;
			this->textCol = textCol;
			this->bodyHighlightCol = bodyHighlightCol;
			this->borderHighlightCol = borderHighlightCol;
			this->textHighlightCol = textHighlightCol;
			this->font = font;
			this->borderSize = borderSize;
		}
	};

	class GuiEntry
	{
	public:
		sf::RectangleShape shape;
		std::string message = "";
		sf::Text text;


		GuiEntry(const std::string& message, sf::RectangleShape shape, sf::Text text)
		{
			this->message = message;
			this->shape = shape;
			this->text = text;
		}
	};

	class GameGui : public sf::Transformable, public sf::Drawable
	{
	public:
		GameGuiBase style;
		sf::Vector2f dimensions;
		int padding;

	
		std::vector<GuiEntry> entries;

		bool visible;

		GameGui(sf::Vector2f dimensions, int padding, bool horizontal, GameGuiBase& style, std::vector<std::pair<std::string, std::string>> entries)
		{
			visible = false;
			this->style = style;
			this->dimensions = dimensions;
			this->padding = padding;

			sf::RectangleShape shape;
			shape.setSize(dimensions);
			shape.setFillColor(style.bodyCol);
			shape.setOutlineThickness(-style.borderSize);
			shape.setOutlineColor(style.borderCol);

			for (auto entry : entries)
			{
				sf::Text text;
				text.setString(entry.first);
				text.setFont(*style.font);
				text.setFillColor(style.textCol);
				text.setCharacterSize(dimensions.y - style.borderSize - padding);

				this->entries.push_back(GuiEntry(entry.second, shape, text));
			}
		}

		sf::Vector2f getSize();

		int getEntry(const sf::Vector2f mousePos);

		void setEntryText(int entry, std::string text);

		void setDimenstions(sf::Vector2f dimenstions);

		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

		void schow();

		void hide();

		void highlight(const int entry);

		std::string activate(const int entry);

		std::string activate(const sf::Vector2f mousePos);

	};

	class Button
	{
		StateOfButton buttonState = StateOfButton::BTN_IDLE;
		short unsigned buttonID = 0;

		sf::RectangleShape shape;
		sf::Font *font;
		sf::Text text;

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor;
		sf::Color hoverColor;
		sf::Color activeColor;

		sf::Color outlineIdleColor;
		sf::Color outlineHoverColor;
		sf::Color outlineActiveColor;

	public:
		Button(float x, float y, float width, float height, sf::Font *font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_color, sf::Color hover_color, sf::Color active_color, sf::Color outline_idle_color = sf::Color::Transparent,
			sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
			short unsigned id = 0);
		~Button() = default;

		const bool isPressed() const;
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned id);
		void ChangePosition(float x, float y);

		//Functions
		void update(const sf::Vector2f& mousePos);
		void render(sf::RenderTarget& target);
	};

	class DropDownList
	{
	private:
		float keytime = 0.0f;
		float keytimeMax = 0.0f;
		bool showList = false;
		Gui::Button* activeElement;
		std::vector<Gui::Button*> list;

		sf::Font& font;
		
	public:
		DropDownList(float x, float y, float width, float height,
			sf::Font& font, std::string list[],
			unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		void UpdateKeytime(const float& dt);
		void Update(const sf::Vector2f& mousePos, const float& dt);
		void Draw(sf::RenderTarget& target);

		const unsigned short& getActiveElementId() const;
		const bool getKeytime();
	};

	class SelectTexture
	{
		float keyTime = 0.0f;
		float keyTimeMax = 1.0f;
		float sizeX = 0.0f, sizeY = 0.0f;
		bool active = false;
		bool hidden = false;
		Gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		SelectTexture(float x, float y, float width, float height, float sizeX, float sizeY, const sf::Texture *texture_sheet,
			sf::Font& font, std::string text);
		~SelectTexture();
		const sf::IntRect& getTextureRect() const;
		const bool& getActive() const;

		void Update(const sf::Vector2i & mousePosWindow, const float & dt);
		void Draw(sf::RenderTarget& target);
		const bool getKeyTime();
		void UpdateKeyTime(const float & dt);
	};
}

#endif // !Gui_hpp