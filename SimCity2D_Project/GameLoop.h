#ifndef GameLoop_hpp
#define GameLoop_hpp

#include "defines.h"
#include "HudLeft.h"
#include "HudUp.h"
#include "StateOfProgram.h"
#include "LoadData.h"
#include "HoldGameplay.h"
#include "TableInformation.h"
#include "LoadGame.h"
#include "Options.h"

class GameLoop : public IStateOfProgram
{
public:
	enum class MouseAction
	{
		VOID = 0, MOVEVIEW = 1, SELECTMAP = 2, GUI_SELECTING = 3, TABLE_ACTIVATED = 4
	};

private:
	MouseAction mouseAction = MouseAction::VOID;

	HudLeft *hudLeft = nullptr;
	HudUp *hudUp = nullptr;
	LoadData *loadData = nullptr;
	HoldGameplay *holdGameplay = nullptr;

	std::shared_ptr<AssetsOfGame> ptrGame = nullptr;

	std::map<std::string, TableInformation> tableInfSystem;
	SmallTile::TileSpecialise tileSpecialise;

	const float zoomAmount = 1.3f;
	int zoomSize = 0;
	int sizeMap = 0;

	bool stopDrawing = false;
	bool special_building = false;

	sf::Font font;
	sf::Texture texture;

	sf::Vector2f movingDistance = sf::Vector2f(0, 0);
	sf::Vector2i selectFROM = sf::Vector2i(0, 0), selectTO = sf::Vector2i(0, 0);
	sf::Vector2f centre = sf::Vector2f(0, 0);
	sf::RectangleShape background;

	void SetCameraPosition();
	void UpdateHud(float elapsedTime);
	void UpdateGameplay(float elapsedTime);
	void DrawHud(float elapsedTime);
	void DrawMap(float elapsedTime);
	void DrawBackground();
	void UpdateHudUpOptions();
	void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);

public:
	GameLoop() = default;
	GameLoop(std::shared_ptr<AssetsOfGame> ptrGameconst, const std::string & mapName, uint64_t seedMap, int sizeMap, bool loadGame);
	virtual ~GameLoop();

	void UpdateObject(float elapsedTime) override;
	void DrawObject(float elapsedTime) override;
	void InitializeObject() override;
	void HoldInput() override;

	void GetBuildingOption(const std::string & buildingOption);
	bool IsTileUpdate(const std::string & tileName);
	unsigned long int CalculateCostOfAllTiles();
	unsigned long int GetTileCost(SmallTile::TileSpecialise tileSpecialise) const;
};

#endif // !GameLoop_hpp