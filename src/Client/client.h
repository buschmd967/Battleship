#include "render.h"
#include "button.h"
#include <vector>

class Client{
public:
	
	Client(float width, float height);

	inline int changeGameState(int gs);
	void updateGameState();
	void run();

private:

	bool _changeGameState = true; // need to update game state
	int _gameState = 0;
	//Game States:
	//0 - menu
	

	Render _r;

	std::vector<Button> _menuButtons;


};

inline int Client::changeGameState(int gs){
	int oldGameState = _gameState;
	_gameState = gs;
	_changeGameState = true;
	return oldGameState;
}
