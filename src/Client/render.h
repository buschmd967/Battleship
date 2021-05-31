#include "SFML/Graphics.hpp"
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

	int getButtonClicked();
	int getShipClicked();
	bool mouseClicked(){return _mouseClicked;}
	inline void setMouseClicked(bool mc){_mouseClicked = mc;}
	void quit(){_window.close();}

	inline void setShips(std::vector<Ship> & ships);
	inline void undock(int index) {_ships[index]->docked(false); _dockedCount--;}
	inline void dock(int index) {_ships[index]->docked(true); _dockedCount++;}
	inline void drawRect(int x1, int y1, int x2, int y2, sf::Color c);
	inline void drawShips();
	inline void updateDockedCount();

private:
	void drawButtons();
	sf::Event _event;

	void drawEdit();

	float _height;
	float _width;

	sf::Vector2i _mousePos;
	bool _mouseClicked = false;

	//std::vector<Button> _buttons;
	std::vector<Button> * _currentButtons = nullptr;

	sf::RenderWindow _window;
	
	std::vector<Button> _menuButtons;
	std::vector<Button> _setupButtons;

	std::vector<Ship *> _ships = std::vector<Ship *>();
	std::vector<Ship *> _dockShips = std::vector<Ship *>();

	int _blockWidth;
	int _blockHeight;
	int _dockedCount;

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



inline void Render::drawShips(){
	//DockShips
	int startHeight = 105;
	int startWidth = 1010;
	int size = _dockedCount;
	int offset = 0;

	for(int i = 0; i < size; i++){
		std::cout << "size : " << size << std::endl;
		std::cout << "offset: " << offset << std::endl;
		std::cout << "i: " << i << std::endl;
		Ship s = *(_ships[i]);
		if(s.docked()){
			for(int block = 0; block < s.size(); block++){

				drawRect(startWidth + block * _blockWidth, (startHeight + 100 * (i - offset)), startWidth + (block + 1) * _blockWidth - 1, (startHeight + 100 * (i - offset)) + _blockHeight, sf::Color::Black); 
			}	
		}
		else{
			offset++;
			size++;

		}

	}
}

