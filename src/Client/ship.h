#include <iostream>



#ifndef __SHIP__
#define __SHIP__



class Ship{
public:
	Ship(int x, int y, int size): _x(x), _y(y), _size(size), _isVertical(false), _sunk(false), _xOrig(x), _yOrig(y), _docked(true){}

	inline bool sunk(){return _sunk;}
	inline bool isVertical(){return _isVertical;}
	inline int x(){return _x;}
	inline int y(){return _y;}
	inline int size(){return _size;}
	inline int docked() {return _docked;}
	inline void docked(bool b){_docked = b;}

	inline void setPos(int x, int y){_x = x; _y = y;}


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
