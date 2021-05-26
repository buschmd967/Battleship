#include "SFML/Graphics.hpp"
#include "button.h"
#include <vector>

class Render{
public:
	
	Render(float width, float height): _height(height), _width(width), _window(sf::VideoMode(width, height), "Battleship") {};


	

	void serRenderButtons(std::vector<Button> b){_buttons = b;}
	void render();
	bool isOpen(){return _window.isOpen();}


private:
	void drawButtons();

	float _height;
	float _width;

	std::vector<Button> _buttons;

	sf::RenderWindow _window;

};
