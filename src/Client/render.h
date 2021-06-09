#include "SFML/Graphics.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "button.h"
#include "ship.h"
#include <vector>

//Handle window rendering and button presses
class Render{
public:
	
	Render(float width, float height);
	//Render(float width, float height): _height(height), _width(width), _window(sf::VideoMode(width, height), "Battleship") {};
	
	void handleEvents();
	//void setRenderButtons(std::vector<Button> b){_buttons = b;}
	void render(int state);
	bool isOpen(){return _window.isOpen();}

	int getButtonClicked(int x = -1, int y = -1, int lowerBias = 0, int upperBias = 0);
	int getShipClicked();
	inline bool mouseClicked(){return _mouseClicked;}
	inline bool mouseDown(){return _mouseDown;}
	inline void setMouseClicked(bool mc){_mouseClicked = mc;}
	void quit(){_window.close();}

	inline void setShips(std::vector<Ship> & ships);
	inline void undock(int index);
	inline void dock(int index);
	inline void drawRect(int x1, int y1, int x2, int y2, sf::Color c);
	void drawShips();
	inline void updateDockedCount();
	
	inline int mouseX(){return _mousePos.x;}
	inline int mouseY(){return _mousePos.y;}

	void setSelectedShip(Ship & s){_selectedShip = &s;}
	void clearSelectedShip(){_selectedShip = nullptr;}

	inline std::vector<Button> * getCurrentButtons(){return _currentButtons;}

private:
	void drawButtons();
	sf::Event _event;

	void drawEdit();

	float _height;
	float _width;

	sf::Vector2i _mousePos;
	bool _mouseClicked = false; //for button click detection
	bool _mouseDown = false; //for more raw stuff

	//std::vector<Button> _buttons;
	std::vector<Button> * _currentButtons = nullptr;

	sf::RenderWindow _window;
	
	//State 0
	std::vector<Button> _menuButtons;
	//State 1
	std::vector<Button> _setupButtons;
	//State 2
	std::vector<Button> _setupButtonsConnect;

	std::vector<Ship *> _ships = std::vector<Ship *>();
	std::vector<Ship *> _dockShips = std::vector<Ship *>();
	Ship * _selectedShip = nullptr;

	float _blockWidth;
	float _blockHeight;
	int _dockedCount;
	int _dockOffset = 0;

};

inline void Render::setShips(std::vector<Ship> & ships){
	_dockedCount = ships.size();
	for(int i = 0; i < _dockedCount; i++){
		_ships.push_back(& (ships[i]));
		_dockShips.push_back(& (ships[i]));
	}	
	_blockWidth = _setupButtons[0].width();
	_blockHeight = _setupButtons[0].height();
}

inline void Render::drawRect(int x1, int y1, int x2, int y2, sf::Color c){
	
	sf::RectangleShape rect(sf::Vector2f(x2 - x1, y2 - y1));
	rect.setPosition(x1, y1);
	rect.setFillColor(c);
	_window.draw(rect);
	
}

inline void Render::undock(int index) {
	if(_ships[index]->docked()){
		_ships[index]->docked(false); 
		_ships[index]->setFloating(true);
		_dockedCount--;
	}
	
}

inline void Render::dock(int index) {
	if(!_ships[index]->docked()){
		_ships[index]->docked(true); 
		_ships[index]->setVertical(false);
		_ships[index]->setFloating(false);
		_dockedCount++;
	}
}
