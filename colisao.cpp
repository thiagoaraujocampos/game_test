
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
