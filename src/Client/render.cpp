#include <iostream>
#include "SFML/Graphics.hpp"
#include "render.h"
#include "button.h"

Render::Render(float width, float height): _height(height), _width(width), _window(sf::VideoMode(width, height), "Battleship") {

	//Create menu buttons
	_menuButtons.push_back(Button(width/2.0 - 100, height / 3, 200, 70, 0, sf::Color::Black, ((std::string) "START").c_str(), sf::Color::White));
	_menuButtons.push_back(Button(width/2.0 - 100,  height * 10/11, 200, 70, 1, sf::Color::Black, ((std::string) "QUIT").c_str(), sf::Color::White));

	//Create cell buttons
	int i = 0;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
		_setupButtons.push_back(Button( (height/10.0) * (x+1) + 1, (height / 10.0) * (y+1), height/10.0 - 1, height/10.0 - 1, i, sf::Color(64, 64, 128)));
		i++;
		}

	}


}


void Render::handleEvents(){
	while (_window.pollEvent(_event))
	{
		// "close requested" event: we close the _window
		switch(_event.type){
			case sf::Event::Closed:
				_window.close();
				break;
			case sf::Event::MouseButtonPressed:
				_mouseClicked = true;
				break;
			case sf::Event::MouseButtonReleased:
				_mouseClicked = false;
				break;
			default:
				break;
		}
		_mousePos = sf::Mouse::getPosition(_window);
	}
}

void Render::render(int state){

	// check all the window's events that were triggered since the last iteration of the loop
	

	switch(state){
		case 0: // menu
			_window.clear(sf::Color(128, 128, 128));
			//_window.clear(sf::Color::White);
			_currentButtons = &_menuButtons;
			drawButtons();
			break;
		case 1: // setup
			_window.clear(sf::Color(128, 128, 128));
			_currentButtons = &_setupButtons;
			drawButtons();
			drawRect(1000, 100, 1500, 100 + 100 * _dockedCount, sf::Color(160, 160, 160));
			drawShips();
			break;
		default:
			break;

	}


	// clear the window with white color


	// draw everything here...
	// _window.draw(...);
	// set the shape color to green

	// end the current frame
	_window.display();
}

int Render::getButtonClicked(){
	for(Button b : *_currentButtons){
		if(b.clicked(_mousePos.x, _mousePos.y)){
			return b.id();
		}
	}
	return -1;
}

int Render::getShipClicked(){
	int x = _mousePos.x;
	int y = _mousePos.y;
	for(int i = 0; i < _ships.size(); i++){
		Ship s = * (_ships[i]);
		if(s.isVertical()){
		}
		else{
			//std::cout << x << " >= " << (s.x() - 5) << " && " << x << " <= " << (s.x() + _blockWidth * s.size() + 5) << " && " << std::endl;
			if(x >= s.x() - 5 && x <= (s.x() + _blockWidth * s.size() + 5) && y >= s.y() - 5 && y <= (s.y() + _blockHeight + 5))
				return i;
		}
	}
	return -1;
}

void Render::drawButtons(){
	for(Button b : *_currentButtons){
		b.draw(_window);
	}
}
