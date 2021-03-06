#include <string>
#include <SFML/Graphics.hpp>

#ifndef __BUTTON__
#define __BUTTON__

class Button{
public:
	Button(int x, int y, int width, int height, int id);
	Button(int x, int y, int width, int height, int id, sf::Color c): Button(x, y, width, height, id){_color = c;};
	Button(int x, int y, int width, int height, int id, const std::string text): Button(x, y, width, height, id){_text = text;};
	Button(int x, int y, int width, int height, int id, sf::Color c, const std::string text, sf::Color tc): Button(x, y, width, height, id, text){_color = c; _textColor = tc;}

	void draw(sf::RenderWindow & window);
	void setColor(sf::Color c){ _color = c;}
	void setTextColor(sf::Color tc){ _textColor = tc;}
	bool clicked(float x, float y, int lowerBias, int upperBias);
	int id(){return _id;}
	int width() {return _width;}
	int height() {return _height;}
	inline int getX() {return _x;}
	inline int getY() {return _y;}


	int _id;

private:
	int _x;
	int _y;
	int _width;
	int _height;


	
	std::string _text;

	sf::Color _color = sf::Color::Black;
	sf::Color _textColor = sf::Color::White;

	sf::Font _font;

};

#endif
