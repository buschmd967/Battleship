#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "button.h"



#ifndef __SHIP__
#define __SHIP__



class Ship{
public:
	Ship(int x, int y, int size): _x(x), _y(y), _size(size), _isVertical(false), _sunk(false), _xOrig(x), _yOrig(y), _docked(true), _floating(false){}

	inline bool sunk(){return _sunk;}
	inline bool isVertical() const {return _isVertical;}
	inline void rotate(){_isVertical = !_isVertical;}
	inline int x() const {return _x;}
	inline int y() const {return _y;}

	inline int size() const {return _size;}
	inline int docked() const {return _docked;}
	inline void docked(bool b){_docked = b;}
	inline sf::Color color(){return _color;}
	inline void setColor(sf::Color c){_color = c;}
	inline void setVertical(bool v){_isVertical = v;}

	inline void setPos(int x, int y){_x = x; _y = y;}
	inline void addButton(Button * b){_buttons.push_back(b);}
	inline void clearButtons(){_buttons.clear();}
	const std::vector<Button *> & getButtons(){return _buttons;}
	bool isFloating(){return _floating;}
	bool setFloating(bool f){_floating = f;}


private:
	bool _docked; //Currently somewhere in the side pannel
	bool _floating; //Either being moved or is in an invalid spot

	int _size;
	bool _isVertical;
	bool _sunk;

	int _x;
	int _y;

	sf::Color _color = sf::Color::Black;

	//Original x y positions in edit tray
	int _xOrig;
	int _yOrig;

	std::vector<Button  *> _buttons; 
};

#endif