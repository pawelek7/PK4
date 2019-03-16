#ifndef GameLoop_hpp
#define GameLoop_hpp

#include "MapTile.h"
#include "StateMachine.h"
#include "StateOfProgram.h"
#include "GameAssets.h"

class GameLoop : public StateOfProgram
{
	std::shared_ptr<GameAssets> ptrGame = nullptr;
	MapTile map;
	const float zoomAmount{ 1.1f };

	sf::Vector2i oldMousePos = sf::Vector2i(0, 0), newMousePos = sf::Vector2i(0, 0);

	sf::View camera;

public:
	GameLoop() = default;
	GameLoop(std::shared_ptr<GameAssets> ptrGame);

	void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow& window, float zoom);
	void UpdateObject(float elapsedTime);
	void DrawObject(float elapsedTime);
	void InitializeObject();
	void HoldInput();
};

#endif // !GameLoop_hpp