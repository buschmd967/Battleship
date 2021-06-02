#include <string>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "client.h"
#include "ship.h"



Client::Client(float width, float height): _r(width, height){

	//Create ships
	_ships.push_back(Ship(1010, 105, 2));
	_ships.push_back(Ship(1010, 205, 3));
	_ships.push_back(Ship(1010, 305, 3));
	_ships.push_back(Ship(1010, 405, 4));
	_ships.push_back(Ship(1010, 505, 5));
	//std::cout << "isVert:" << _ships[0].isVertical() << std::endl;


	//save ships to render
	_r.setShips(_ships);


}

void Client::updateGameState(){

	_changeGameState = false;
	switch(_gameState){
		case 0: //Menu
			std::cout << "menu" << std::endl;
			break;
		case 1: // Setup
			std::cout << "setup" << std::endl;
			break;
		default:
			std::cout << "Error changing gamestates: GameState '" << _gameState << "' not recognized" << std::endl;
	}
	
}

void Client::run(){

	while(_r.isOpen()){
		if(_changeGameState){
			updateGameState();
		}
		_r.handleEvents();
		

		switch(_gameState){
			case 0: // Menu
				if(_r.mouseClicked()){
					_r.setMouseClicked(false);
					int pressedButton = _r.getButtonClicked();
					switch(pressedButton){
						case 0: //Start
							changeGameState(1);
							break;
						case 1: //Quit
							_r.quit();
							break;

					}
					std::cout << "Button Pressed: " << pressedButton << std::endl;
				}
				break;
			case 1: // Setup
				if(_r.mouseClicked()){
					_r.setMouseClicked(false);
					int pressedButton = _r.getButtonClicked();
					_currentShip = _r.getShipClicked();
					std::cout << "Ship Pressed: " << _currentShip << std::endl;;
					if(_currentShip != -1){
						Ship s = _ships[_currentShip];
						_r.undock(_currentShip);
						_ships[_currentShip].setColor(sf::Color(100, 100, 100));
						_r.setSelectedShip(_ships[_currentShip]);

						_mouseXOffset = s.x() - _r.mouseX();
						_mouseYOffset = s.y() - _r.mouseY();
						std::cout << "Set offset to: ( " << _mouseXOffset << ", " << _mouseYOffset << ")" << std::endl;
						std::cout << "undocked ship " << _currentShip << std::endl;;
					}
					else{
						_r.clearSelectedShip();
						_mouseXOffset = _mouseYOffset = 0;
					}
					/*
					switch(pressedButton){
						case 0: //Start
							changeGameState(1);
							break;
						case 1: //Quit
							_r.quit();
							break;

					}
							*/
					std::cout << "Button Pressed: " << pressedButton << std::endl;
				}
				if(_r.mouseDown()){
					if(_currentShip != -1){
						_ships[_currentShip].setPos(_r.mouseX() + _mouseXOffset , _r.mouseY() + _mouseYOffset);
						//std::cout << "moved ship " << _currentShip << " to (" << _r.mouseX() << ", " << _r.mouseY() << ")" << std::endl;
					}
//90, 800
				}
				else{
					if(_currentShip != -1){
						int x = _ships[_currentShip].x();
						int y = _ships[_currentShip].y();
						if(x > 805 || y < 85 || y > 805 || x < 85){ //in order of liklihood for lazy eval
							_r.dock(_currentShip);
							
							
						}
						_ships[_currentShip].setColor(sf::Color::Black);
						_r.clearSelectedShip();
						_currentShip = -1;
					}
					
				}
				break;

		} //End Switch

		_r.render(_gameState);
	}

}

int main(){

	Client c(1600, 900);
	c.run();
	return 0;
}
