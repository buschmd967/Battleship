#include <string>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "client.h"



Client::Client(float width, float height): _r(width, height){
	//Create menu buttons
	_menuButtons.push_back(Button(width/2.0 - 100, height / 3, 200, 70, 0, sf::Color::Black, ((std::string) "START").c_str(), sf::Color::White));
	_menuButtons.push_back(Button(width/2.0 - 100,  height * 10/11, 200, 70, 1, sf::Color::Black, ((std::string) "QUIT").c_str(), sf::Color::White));

	//Create cell buttons
	int i = 0;
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
		_setupButtons.push_back(Button( (width/10.0) * (x+1) + 1, (height / 10.0) * (y+1), width/10.0 - 1, height/10.0 - 1, i));
		i++;
		}
	}

}

void Client::updateGameState(){

	switch(_gameState){
		case 0: //Menu
			_r.setRenderButtons(_menuButtons);
			break;
		case 1: // Setup
			_r.setRenderButtons(_setupButtons);
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
		_r.render();

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

		}
	}

}

int main(){

	Client c(1600, 900);
	c.run();
	return 0;
}
