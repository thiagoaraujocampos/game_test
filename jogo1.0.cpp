
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
  // Create the main window
  RenderWindow window(VideoMode(800, 600), "SFML window");

  // VideoMode desktop = VideoMode::getDesktopMode();
  // RenderWindow window(VideoMode(1024, 768, desktop.bitsPerPixel),
  // "SFMLwindow");

  // Load a sprite to display
  Texture texture;
  if (!texture.loadFromFile("cute_image.jpg"))
    return EXIT_FAILURE;
  Sprite sprite(texture);

  // Circulo
  CircleShape circulo(20);
  circulo.setFillColor(Color::Red);

  CircleShape bomba(30);
  bomba.setFillColor(Color::Green);

  // Create a graphical text to display
  Font font;
  if (!font.loadFromFile("arial.ttf"))
    return EXIT_FAILURE;
  Text text("Hello SFML", font, 50);

  // Load a music to play
  Music music;
  if (!music.openFromFile("nice_music.ogg"))
    return EXIT_FAILURE;

  // Play the music
  //music.play();

  // Event var
  Event event;
  float x = 800/2, y = 600/2;

  // Start the game loop
  while (window.isOpen()) {
    // Process events
    while (window.pollEvent(event)) {
      // Close window: exit
      if (event.type == Event::Closed)
        window.close();
      // if (Keyboard::isKeyPressed(Keyboard::Escape))
      //  window.close();

      // Respond to key pressed events
      if (event.type == Event::EventType::KeyPressed) {
        if (event.key.code == Keyboard::Escape) {
          window.close();
        }
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::D)) {
      x += 0.2;
    } 

    if (Keyboard::isKeyPressed(Keyboard::A)) {
      x -= 0.2;
    } 

    if (Keyboard::isKeyPressed(Keyboard::W)) {
      y -= 0.2;
    } 

    if (Keyboard::isKeyPressed(Keyboard::S)) {
      y += 0.2;
    } 
    // Update circulo position
    circulo.setPosition(x,y);

    // Clear screen
    window.clear();
    // Draw the sprite
    window.draw(sprite);
    window.draw(circulo);
    if (Keyboard::isKeyPressed(Keyboard::Space)) {
      window.draw(bomba);
    } 
    // Draw the string
    //window.draw(text);
    // Update the window
    window.display();
  }

  return EXIT_SUCCESS;
}

/*
#include "SFML/Graphics.hpp"
#include <iostream>
#include <random>

int main(int argc, char **argv) {
  sf::RenderWindow renderWindow(sf::VideoMode(640, 480), "SFML Demo");

  sf::Event event;

  // A Clock starts counting as soon as it's created
  sf::Color color(sf::Color::Red);

  // C++ 11 way of generating a random between 0 - 255
  // mt19937 is an implementation of the Mersenne Twister pseudo random number
  // generator random_device() returns a random number to use as a seed for the
  // mt algorithm... slow however so that's why we dont just use it for all
  // randoms if you were wondering mt results arent in a human friendly format,
  // so we use uniform_int_distribution to "shape" the results to our range and
  // type uniform_int_distribution is a fairly "light" object.  random_device
  // and mt19937 aren't.
  std::uniform_int_distribution<int> randomColorRange(0, 255);
  std::random_device rd;
  std::mt19937 randomNumbers(rd());

  // Pre-C++ 11 but more common way (*with issues, see:
  //
https://www.reddit.com/r/programming/comments/1rnudl/quite_interesting_why_cs_rand_is_considered/
  // Mostly doesn't apply to game devs if not using rand for say... security.

  while (renderWindow.isOpen()) {
    // Check for all the events that occured since the last frame.
    while (renderWindow.pollEvent(event)) {
      // Handle events here
      if (event.type == sf::Event::EventType::Closed)
        renderWindow.close();

      // Respond to key pressed events
      if (event.type == sf::Event::EventType::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) {
          color.r = randomColorRange(randomNumbers);
        }
      }
    }

    // Now demonstrate input via polling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        color.r = 0;
      else
        color.r = randomColorRange(randomNumbers);

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        color.g = 0;
      else
        color.g = randomColorRange(randomNumbers);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
          sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
        color.b = 0;
      else
        color.b = randomColorRange(randomNumbers);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      color.r = 0;
      color.b = 0;
      color.g = 0;
    }

    renderWindow.clear(color);
    renderWindow.display();
  }
}
*/