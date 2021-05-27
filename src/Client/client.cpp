#include <string>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include "client.h"



Client::Client(float width, float height): _r(width, height){
	//Create menu buttons
	_menuButtons.push_back(Button(width/2.0 - 100, height / 3, 200, 70, 0, sf::Color::Black, ((std::string) "START").c_str(), sf::Color::White));
	_menuButtons.push_back(Button(width/2.0 - 100,  height * 10/11, 200, 70, 1, sf::Color::Black, ((std::string) "QUIT").c_str(), sf::Color::White));

}

void Client::updateGameState(){

	switch(_gameState){
		case 0: //Menu
			_r.serRenderButtons(_menuButtons);
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
	}

}

int main(){

	Client c(1600, 900);
	c.run();
	return 0;
}
