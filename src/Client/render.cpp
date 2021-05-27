#include <iostream>
#include "SFML/Graphics.hpp"
#include "render.h"
#include "button.h"

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
		}
		_mousePos = sf::Mouse::getPosition(_window);
	}
}

void Render::render(){

	// check all the window's events that were triggered since the last iteration of the loop
	


	// clear the window with white color
	_window.clear(sf::Color::White);


	drawButtons();
	// draw everything here...
	// _window.draw(...);
	// set the shape color to green

	// end the current frame
	_window.display();
}

int Render::getButtonClicked(){
	for(Button b : _buttons){
		if(b.clicked(_mousePos.x, _mousePos.y)){
			return b.id();
		}
	}
	return -1;
}

void Render::drawButtons(){
	for(Button b : _buttons){
		b.draw(_window);
	}
}