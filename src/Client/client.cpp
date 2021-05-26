#include <iostream>
#include "SFML/Graphics.hpp"

#define WIDTH 1600
#define HEIGHT 900


int main(int argc, char** argv){
  sf::RenderWindow renderWindow(sf::VideoMode(WIDTH, HEIGHT), "Hello Cruel World");
  // Create a font object and load it from file relative
  sf::Font font;
  if (!font.loadFromFile("../../fonts/Roboto/Roboto-Black.ttf")){
    return 42; // Robust error handling!
  }

  //Create Hello World text objecct using our font and size 128pt
  sf::Text text("Hello World", font, 128);
  //Set the text color to red 
  text.setColor(sf::Color::Red);
  //Get the text object's physical dimensions and use them to center the text to 
  //our render window
  //By default things are drawn relative to their top left corner and can be 
  //changed by calling setOrigin()
  sf::FloatRect bounds(text.getLocalBounds());
  text.setPosition(renderWindow.getSize().x/2 - (bounds.left + bounds.width/2), 
          renderWindow.getSize().y/2 - (bounds.top + bounds.height/2));
  while (renderWindow.isOpen()){
    sf::Event event;
    while (renderWindow.pollEvent(event)){
      if (event.type == sf::Event::EventType::Closed)
      {
        renderWindow.close();
      }
    } 
    renderWindow.clear(sf::Color::White);
    //Draw our text object to the window
    renderWindow.draw(text);
    renderWindow.display();
  }
}