#include "SFML/Graphics.hpp"
#include "button.h"
#include <vector>

//Handle window rendering and button presses
class Render{
public:
	
	Render(float width, float height): _height(height), _width(width), _window(sf::VideoMode(width, height), "Battleship") {};


	

	void serRenderButtons(std::vector<Button> b){_buttons = b;}
	void render();
	bool isOpen(){return _window.isOpen();}

	int getButtonClicked();
	bool mouseClicked(){return _mouseClicked;}
	void setMouseClicked(bool mc){_mouseClicked = mc;}


private:
	void drawButtons();

	float _height;
	float _width;

	sf::Vector2i _mousePos;
	bool _mouseClicked = false;

	std::vector<Button> _buttons;

	sf::RenderWindow _window;

};
