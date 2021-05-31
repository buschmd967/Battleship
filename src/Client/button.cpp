#include "button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <cstring>
#include <iostream>
#include <algorithm>

Button::Button(int x, int y, int width, int height, int id): _x(x), _y(y), _width(width), _height(height), _id(id) {
	if(!_font.loadFromFile("../fonts/Roboto/Roboto-Black.ttf")){
		if(!_font.loadFromFile("../../fonts/Roboto/Roboto-Black.ttf")){
			std::cout << "Error loading default Roboto-Black font for button id '" << id << "', hopefully it doesn't require text!" << std::endl;
		}
	}
}
/*
Button::Button(int x, int y, int width, int height, int id, const char text[]): Button(x, y, width, height, id){
	//copy text
	int len;
	for(len = 0; text[len] != '\0'; len++);
	_text = new char[len];
	for(int i = 0; i <= len; i++){
		_text[i] = text[i];
	}
	
}

*/

bool Button::clicked(float x, float y){

	return (x >= _x && x <= _x + _width && y >= _y && y <= _y + _height );
}

void Button::draw(sf::RenderWindow & window){
	//draw rectangle shape
	sf::RectangleShape rect(sf::Vector2f(_width, _height));
	rect.setPosition(_x, _y);
	rect.setFillColor(_color);

	window.draw(rect);

	//std::cout << "text: " << _text[0] << _text[1] << _text[2] << std::endl;
	//Text centering thing is really hacky, but it works for now
	if(_text[0] != '\0'){ //draw text
		sf::Text text;
		text.setFont(_font);
		text.setString(_text);
		int charSize = std::min((int) _height / 2, (int) _width /  (int) (_text.size() * 1.3) );
		text.setCharacterSize(charSize);
		//text.setCharacterSize(std::min(_height, _width));
		text.setFillColor(_textColor);
		text.setPosition((_x - charSize / 3.0 * _text.size() + _width / 2.0), (_y + _height / 5));
		//text.setFillColor(sf::Color::Blue);
		window.draw(text);
	}



}
