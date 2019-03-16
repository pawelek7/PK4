#ifndef Gui_hpp
#define Gui_hpp

#include <SFML/Graphics.hpp> //SFML library

enum class StateOfButton
{BTN_IDLE = 0, BTN_HOVER = 1, BTN_ACTIVE = 2};

namespace Gui
{
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
		float size = 0.0f;
		bool active = false;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;

	public:
		SelectTexture(float x, float y, float width, float height, float size, const sf::Texture *texture_sheet);
		~SelectTexture() = default;
		const sf::IntRect& getTextureRect() const;

		void Update(const sf::Vector2i & mousePosWindow);
		void Draw(sf::RenderTarget& target);
	};
}

#endif // !Gui_hpp