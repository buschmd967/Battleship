#include <iostream>



#ifndef __SHIP__
#define __SHIP__



class Ship{
public:
	Ship(int x, int y, int size): _x(x), _y(y), _size(size), _isVertical(false), _sunk(false), _xOrig(x), _yOrig(y), _docked(true){}

	bool sunk(){return _sunk;}
	bool isVertical(){return _isVertical;}
	int x(){return _x;}
	int y(){return _y;}
	int size(){return _size;}
	int docked() {return _docked;}
	void docked(bool b){_docked = b;}


private:
	bool _docked;
	int _size;
	bool _isVertical;
	bool _sunk;

	int _x;
	int _y;

	//Original x y positions in edit tray
	int _xOrig;
	int _yOrig;
};

#endif
