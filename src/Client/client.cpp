#include <string>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "client.h"
#include "ship.h"
#include <algorithm>



Client::Client(float width, float height): _r(width, height), _width(width), _height(height){

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

bool Client::shipPlacementAvailable(int startIndex, int stopIndex, bool isVertical){
	int offset;
	if(isVertical){
		offset = 8;
	}
	else{
		offset = 1;
	}

	for(int i = startIndex; i <= stopIndex; i+=offset){
		if(_shipGrid[i] != nullptr){
			return false;
		}

	}
	return true;

}

//Ship is deselected, try to place it in the grid
//If ship is not in the grid, dock it
void Client::handleShipEdit(){
	//int x = _ships[_currentShip].x();
	//int y = _ships[_currentShip].y();
	int x = _r.mouseX();
	int y = _r.mouseY();
	if(x > 805 || y < 85 || y > 805 || x < 85){ //in order of liklihood for lazy eval
	//if(x > 805 || y < 85 || y > 805){ //in order of liklihood for lazy eval
		_r.dock(_currentShip);
		
		
	}
	else{ //try to place it
		Ship s = _ships[_currentShip];
		
		//get starting button
		int startButton = _r.getButtonClicked(s.x() + _height/20.0, s.y() + _height/20.0, 0, 1);
		int endButton;
		if(s.isVertical()){
			endButton = _r.getButtonClicked(s.x() + _height/20.0, s.y() + (_height/10.0 * (s.size() - 1)) + _height/20.0);
		}
		else{
			endButton = _r.getButtonClicked(s.x() + (_height/10.0 * (s.size() - 1)) +_height/20.0, s.y() + _height/20.0);
		}

		std::cout << startButton << std::endl;
		std::cout << endButton << std::endl;
		if(endButton >= 0 && startButton >= 0){
			std::vector<Button> buttons = * (_r.getCurrentButtons());
			Button b = buttons[startButton];
			//test if button 
			if(shipPlacementAvailable(startButton, endButton, s.isVertical())){
				int offset;
				if(s.isVertical()){
					offset = 8;
				}
				else{
					offset = 1;
				}
				for(int i = startButton; i <= endButton; i += offset){
					_shipGrid[i] = & _ships[_currentShip];
					//FIX THIS LINE, WRITTEN AT 4:51 AM AND IS AWFUL
					_ships[_currentShip].addButton(& (_r.getCurrentButtons()->operator[](i)));
				}
				_ships[_currentShip].setPos(b.getX(), b.getY());
				_ships[_currentShip].setFloating(false);
			}
		}



	}
	_ships[_currentShip].setColor(sf::Color::Black);
	_r.clearSelectedShip();
	_currentShip = -1;

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
		case 2: //Setup + connect
			std::cout << "setup + connect" << std::endl;
			break;
		default:
			std::cout << "Error changing gamestates: GameState '" << _gameState << "' not recognized" << std::endl;
	}
	
}

void Client::handleShipRotate(){
	if( (sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Mouse::isButtonPressed(sf::Mouse::Right))  && !_rPressHandled){
		std::cout << "Handling R press" << std::endl;
		if(_currentShip != -1){
			_ships[_currentShip].rotate();

			std::swap(_mouseXOffset, _mouseYOffset);

		}
		_rPressHandled = true;
	}
	else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::R) && !sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		//std::cout << "resetting _rPressHandled" << std::endl;
		_rPressHandled = false;
	}

}

void Client::selectShip(){

	_ships[_currentShip].setFloating(true);
	Ship s = _ships[_currentShip];
	std::vector<Button *> shipButtons = _ships[_currentShip].getButtons();
	std::cout << "size: " << shipButtons.size() << std::endl;
	if(shipButtons.size() > 0){
		std::cout << "button id: " << (_ships[_currentShip].getButtons()[0])->id() << std::endl;
	}
	
	for(int i = 0; i < shipButtons.size(); i++){
		
		int id = shipButtons[i]->id();
		std::cout << "id: " << id << std::endl;
		_shipGrid[id] = nullptr;
	}
	_ships[_currentShip].clearButtons();

	_r.undock(_currentShip);
	_ships[_currentShip].setColor(sf::Color(100, 100, 100));
	_r.setSelectedShip(_ships[_currentShip]);

	_mouseXOffset = s.x() - _r.mouseX();
	_mouseYOffset = s.y() - _r.mouseY();
	//std::cout << "Set offset to: ( " << _mouseXOffset << ", " << _mouseYOffset << ")" << std::endl;
	//std::cout << "undocked ship " << _currentShip << std::endl;;

}

bool Client::allShipsPlaced(){

	for(Ship s : _ships){
		if(s.docked() || s.isFloating()){
			return false;
		}
	}

	return true;
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
			case 2: //Setup + connect

				handleShipRotate();
				
				if(_r.mouseClicked()){
					_r.setMouseClicked(false);
					int pressedButton = _r.getButtonClicked();
					std::cout << pressedButton << std::endl;
					_currentShip = _r.getShipClicked();
					//std::cout << "Ship Pressed: " << _currentShip << std::endl;;
					if(_currentShip != -1){
						selectShip();
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
					//std::cout << "Button Pressed: " << pressedButton << std::endl;
				}

				//Moving ship while holding mouse down
				if(_r.mouseDown()){
					if(_currentShip != -1){
						_ships[_currentShip].setPos(_r.mouseX() + _mouseXOffset , _r.mouseY() + _mouseYOffset);
						//std::cout << "moved ship " << _currentShip << " to (" << _r.mouseX() << ", " << _r.mouseY() << ")" << std::endl;
					}
				}
				//Mouse Up, deselect ship
				else{
					if(_currentShip != -1){
						handleShipEdit();
					}
					
				}

				//If all ships are placed, swap gamestate to 2 to show connect option
				//If ships are being edited after that, swap game state back to 1
				bool readyToConnect = allShipsPlaced();

				if(readyToConnect && _gameState != 2){
					changeGameState(2);
				}
				else if(!readyToConnect && _gameState != 1){
					changeGameState(1);
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
