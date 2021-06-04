#include <iostream>
#include "SFML/Graphics.hpp"
#include "render.h"
#include "button.h"

#define SHIP_HIGHLIGHT_WIDTH 3

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
				switch(_event.key.code){
					case sf::Mouse::Left:
						std::cout << _event.MouseLeft << std::endl;
						_mouseClicked = true;
						_mouseDown = true;
						break;

					case sf::Mouse::Right:
						break;
				}
				
				break;
			case sf::Event::MouseButtonReleased:
				switch(_event.key.code){
					case sf::Mouse::Left:
						_mouseClicked = false;
						_mouseDown = false;
						break;

					case sf::Mouse::Right:
						break;	
				}
				
				break;
			default:
				break;
		}
		_mousePos = sf::Mouse::getPosition(_window);
	}
}

void Render::render(int state){
	//std::cout << "MousePressed: " << _mouseDown << std::endl;
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
			drawRect(1000, 100, 1500, 100 + 100 * (_dockedCount + _dockOffset + (int) (_selectedShip != nullptr) ), sf::Color(160, 160, 160));
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

int Render::getButtonClicked(int x, int y, int lowerBias, int upperBias){
	if(x == -1 && y == -1){
		x = _mousePos.x;
		y = _mousePos.y;
	}

	for(Button b : *_currentButtons){
		if(b.clicked(x, y, lowerBias, upperBias)){
			return b.id();
		}
	}
	return -1;
}

int Render::getShipClicked(){
	
	int x = _mousePos.x;
	int y = _mousePos.y;

	std::vector<int> backgroundShipsIndexes;

	for(int i = _ships.size() - 1; i >= 0; i--){ // check floating ships first
		if(!_ships[i]->isFloating()){
			backgroundShipsIndexes.push_back(i);
			continue;
		}
		Ship s = * (_ships[i]);
		if(s.isVertical()){
			if(x >= s.x() - 5 && x <= (s.x() + _blockWidth + 5) && y >= s.y() - 5 && y <= (s.y() + _blockHeight * s.size() + 5))
				return i;
		}
		else{
			//std::cout << "ship " << i << " size: " << s.size() << std::endl;
			//std::cout << x << " >= " << (s.x() - 5) << " && " << x << " <= " << (s.x() + _blockWidth * s.size() + 5) << " && " << std::endl;
			if(x >= s.x() - 5 && x <= (s.x() + _blockWidth * s.size() + 5) && y >= s.y() - 5 && y <= (s.y() + _blockHeight + 5))
				return i;
		}
	}

	for(int index : backgroundShipsIndexes){
		Ship s = * (_ships[index]);
		if(s.isVertical()){
			if(x >= s.x() - 5 && x <= (s.x() + _blockWidth + 5) && y >= s.y() - 5 && y <= (s.y() + _blockHeight * s.size() + 5))
				return index;
		}
		else{
			//std::cout << "ship " << i << " size: " << s.size() << std::endl;
			//std::cout << x << " >= " << (s.x() - 5) << " && " << x << " <= " << (s.x() + _blockWidth * s.size() + 5) << " && " << std::endl;
			if(x >= s.x() - 5 && x <= (s.x() + _blockWidth * s.size() + 5) && y >= s.y() - 5 && y <= (s.y() + _blockHeight + 5))
				return index;
		}
	}
	return -1;
}

void Render::drawButtons(){
	for(Button b : *_currentButtons){
		b.draw(_window);
	}
}

void Render::drawShips(){
	
	//dock starting values
	int startHeight = 105;
	int startWidth = 1010;

	//size of docked ships and offset if undocked ship is encountered
	int size = _ships.size();
	int offset = 0;

	//used to draw undocked ships
	int x;
	int y;

	std::vector<int> floatingShipIndexes;
	int selectedShipIndex = -1;

	for(int i = 0; i < size; i++){
		/*
		std::cout << "size : " << size << std::endl;
		std::cout << "offset: " << offset << std::endl;
		std::cout << "i: " << i << std::endl;
		*/
		
		if(_ships[i]->isFloating()){
			//std::cout << "Skipping selected ship of size " << _ships[i]->size() << std::endl;
			if(_ships[i] != _selectedShip){
				floatingShipIndexes.push_back(i);
			}
			else{	//Save for later so current selected ship is displayed above all others
				selectedShipIndex = i;
			}
			
			continue;
		}

		Ship s = *(_ships[i]);
		if(s.docked()){		//Docked Ships
			_ships[i]->setPos(startWidth, startHeight + 100 * (i - offset));
			/*
			for(int block = 0; block < s.size(); block++){
				

				drawRect(startWidth + block * _blockWidth, (startHeight + 100 * (i - offset)), startWidth + (block + 1) * _blockWidth - 1, (startHeight + 100 * (i - offset)) + _blockHeight, sf::Color::Black); 
			}	*/
			drawRect(startWidth, startHeight + 100 * (i - offset), startWidth + ((_blockWidth+2) * s.size()), startHeight+ + 100 * (i - offset) + (_blockHeight+2), sf::Color::Blue);
			drawRect(startWidth + SHIP_HIGHLIGHT_WIDTH, startHeight + 100 * (i - offset) + SHIP_HIGHLIGHT_WIDTH, startWidth + ((_blockWidth+2) * s.size()) - SHIP_HIGHLIGHT_WIDTH, startHeight + 100 * (i - offset) + (_blockHeight+2) - SHIP_HIGHLIGHT_WIDTH, sf::Color::Black);
		}
		else{				//Undocked Ships
			//Fix problems for docked ships
			offset++;

			x = s.x();
			y = s.y();
			//draw undocked ship
			if(s.isVertical()){ //Vertical Ship
				for(int block = 0; block < s.size(); block++){
					//drawRect(x, y + block + block * _blockHeight, x + _blockHeight - 1, y + block + (block + 1) * _blockHeight - 1, s.color());
					//drawRect(x, y, x + (_blockWidth), y + (_blockHeight) * s.size(), sf::Color::Blue);
					drawRect(x, y, x + (_blockWidth), y + (_blockHeight+1) * s.size() - 1, sf::Color::Blue);
					drawRect(x + SHIP_HIGHLIGHT_WIDTH, y + SHIP_HIGHLIGHT_WIDTH, x + _blockWidth - SHIP_HIGHLIGHT_WIDTH, y + (_blockHeight+1) * s.size() - 1 - SHIP_HIGHLIGHT_WIDTH, sf::Color::Black);

				}

			}
			else{ 				//Horizontal Ship
				for(int block = 0; block < s.size(); block++){
					//drawRect(x + block + block * _blockWidth, y, x + block + (block + 1) * _blockWidth - 1, y + _blockHeight - 1, s.color());
					drawRect(x, y, x + (_blockWidth+1) * s.size()-1, y + _blockHeight, sf::Color::Blue);
					drawRect(x + SHIP_HIGHLIGHT_WIDTH, y + SHIP_HIGHLIGHT_WIDTH, x + (_blockWidth+1) * s.size() - 1 - SHIP_HIGHLIGHT_WIDTH, y + _blockHeight - SHIP_HIGHLIGHT_WIDTH, sf::Color::Black);

				}
			}
			
		}

	}

	if(selectedShipIndex != -1){
		floatingShipIndexes.push_back(selectedShipIndex);
	}
	//Draw currently selected ship over all other ships (draw last)
	for(int index : floatingShipIndexes){

		Ship s = * _ships[index];
		x = s.x();
		y = s.y();
		if(s.isVertical()){ //Vertical Ship
			for(int block = 0; block < s.size(); block++){
				drawRect(x, y, x + _blockWidth, y + _blockHeight * s.size(), sf::Color::Red);
				drawRect(x + SHIP_HIGHLIGHT_WIDTH, y + SHIP_HIGHLIGHT_WIDTH, x + _blockWidth - SHIP_HIGHLIGHT_WIDTH, y + _blockHeight * s.size() - SHIP_HIGHLIGHT_WIDTH, sf::Color::Black);
			}

		}
		else{ 				//Horizontal Ship
			//std::cout << "drawing ship of size " << s.size() << std::endl;
			for(int block = 0; block < s.size(); block++){
				drawRect(x, y, x + _blockWidth * s.size(), y + _blockHeight, sf::Color::Red);
				drawRect(x + SHIP_HIGHLIGHT_WIDTH, y + SHIP_HIGHLIGHT_WIDTH, x + _blockWidth * s.size() - SHIP_HIGHLIGHT_WIDTH, y + _blockHeight - SHIP_HIGHLIGHT_WIDTH, sf::Color::Black);
			}
		}
	}
		
}
