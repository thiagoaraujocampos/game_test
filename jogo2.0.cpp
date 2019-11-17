
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
  RenderWindow window(VideoMode(800, 600), "Bombs and Movimentation");

  Texture texture;
  if (!texture.loadFromFile("cute_image.jpg"))
    return EXIT_FAILURE;
  Sprite sprite(texture);

  CircleShape circulo(20);
  circulo.setFillColor(Color::Red);

  CircleShape bomba(15);
  bomba.setFillColor(Color::Green);

  RectangleShape retanguloDir(Vector2f(0, 0));
  RectangleShape retanguloEsq(Vector2f(0, 0));
  RectangleShape retanguloCima(Vector2f(0, 0));
  RectangleShape retanguloBaixo(Vector2f(0, 0));

  Font font;
  if (!font.loadFromFile("arial.ttf"))
    return EXIT_FAILURE;
  Text text("BOMBS TEST", font, 50);

  Music music;
  if (!music.openFromFile("nice_music.ogg"))
    return EXIT_FAILURE;
  // music.play();

  Event event;
  float x = 800 / 2, y = 600 / 2;
  float x2, y2, x3, y3;
  bool indicador = false, explosao = false;
  int xs = 0, ys = 0;

  Clock clock;
  Clock expTime;

  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();
      if (event.type == Event::EventType::KeyPressed) {
        if (event.key.code == Keyboard::Escape) {
          window.close();
        }
      }
    }

    if (Keyboard::isKeyPressed(Keyboard::D))
      x += 0.2;
    if (Keyboard::isKeyPressed(Keyboard::A))
      x -= 0.2;
    if (Keyboard::isKeyPressed(Keyboard::W))
      y -= 0.2;
    if (Keyboard::isKeyPressed(Keyboard::S))
      y += 0.2;

    circulo.setPosition(x, y);

    if (Keyboard::isKeyPressed(Keyboard::Space)) {
      if (!indicador) {
        x2 = x;
        y2 = y;
        bomba.setPosition(x2, y2);
        clock.restart();
      }
      indicador = true;
    }

    Time elapsed = clock.getElapsedTime();
    if (elapsed.asSeconds() >= 2 && indicador) {
      x3 = x2;
      y3 = y2;
      indicador = false;
      explosao = true;
      expTime.restart();
    }

    retanguloDir.setPosition(x3 + 15, y3);
    retanguloEsq.setPosition(x3 + 15, y3);
    retanguloCima.setPosition(x3, y3 + 15);
    retanguloBaixo.setPosition(x3, y3 + 15);

    window.clear();

    window.draw(sprite);
    window.draw(circulo);
    if (indicador) {
      window.draw(bomba);
    }
    Time boom = expTime.getElapsedTime();
    if (explosao) {
      if(xs <= 200) xs += 3;
      if(ys >= -200) ys -= 3;
      retanguloDir.setSize(Vector2f(xs, 30));
      retanguloEsq.setSize(Vector2f(ys, 30));
      retanguloCima.setSize(Vector2f(30, ys));
      retanguloBaixo.setSize(Vector2f(30, xs));
      window.draw(retanguloDir);
      window.draw(retanguloEsq);
      window.draw(retanguloCima);
      window.draw(retanguloBaixo);
      if (boom.asSeconds() >= 0.2) {
        explosao = false;
        xs = 0;
      }
    }
    window.draw(text);

    window.display();
  }

  return EXIT_SUCCESS;
}