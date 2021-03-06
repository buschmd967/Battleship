#include "render.h"
#include "button.h"
#include "ship.h"
#include <vector>

class Client{
public:
	
	Client(float width, float height);

	inline int changeGameState(int gs);
	void updateGameState();
	void run();

private:

	//Editing Phase
	void handleShipEdit();
	void handleShipRotate();
	bool allShipsPlaced();
	bool shipPlacementAvailable(int startIndex, int stopIndex, bool isVertical);
	void selectShip();

	bool _changeGameState = true; // need to update game state
	int _gameState = 0;
	//Game States:
	//0 - menu
	//1 - setup board
	

	Render _r;
	float _width;
	float _height;


	std::vector<Ship> _ships;
	std::vector<Ship *> _shipGrid = std::vector<Ship *>(64, nullptr);
	int _currentShip = -1;
	int _mouseXOffset = 0;
	int _mouseYOffset = 0;

	bool _rPressHandled = false;
};

inline int Client::changeGameState(int gs){
	int oldGameState = _gameState;
	_gameState = gs;
	_changeGameState = true;
	return oldGameState;

}
