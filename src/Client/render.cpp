#include <iostream>
#include "SFML/Graphics.hpp"
#include "render.h"
#include "button.h"


void Render::drawButtons(){
	for(Button b : _buttons){
		b.draw(_window);
	}
}

void Render::render(){

	// check all the window's events that were triggered since the last iteration of the loop
	sf::Event event;
	while (_window.pollEvent(event))
	{
		// "close requested" event: we close the _window
		if (event.type == sf::Event::Closed)
			_window.close();
	}

	// clear the window with white color
	_window.clear(sf::Color::White);


	drawButtons();
	// draw everything here...
	// _window.draw(...);
	// set the shape color to green

	// end the current frame
	_window.display();
}
