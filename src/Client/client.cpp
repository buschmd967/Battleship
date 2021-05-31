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
					int shipPressed = _r.getShipClicked();
					std::cout << "Ship Pressed: " << shipPressed << std::endl;;
					if(shipPressed != -1){
						_r.undock(shipPressed);
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
