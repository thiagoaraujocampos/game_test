
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int main() {
  RenderWindow window(VideoMode(800, 600), "Coloring");
  Texture texture;
  if (!texture.loadFromFile("cute_image.jpg"))
    return EXIT_FAILURE;
  Sprite sprite(texture);

  Image img;
  img.loadFromFile("fem.png");
  img.createMaskFromColor(Color(255, 0, 255));
  Texture textureFem;
  if (!textureFem.loadFromImage(img))
    return EXIT_FAILURE;

  IntRect rectSourceSprite(0, 0, 1024, 1024);
  Sprite spriteFem(textureFem, rectSourceSprite);
  Clock clockSprite;

  Image img2;
  img2.loadFromFile("fem2.png");
  img2.createMaskFromColor(Color(255, 0, 255));
  Texture textureFem2;
  if (!textureFem2.loadFromImage(img2))
    return EXIT_FAILURE;

  IntRect rectSourceSprite2(0, 0, 1024, 1024);
  Sprite spriteFem2(textureFem2, rectSourceSprite2);
  Clock clockSprite2;

  RectangleShape quadrado[20][15];

  Font font;
  if (!font.loadFromFile("arial.ttf"))
    return EXIT_FAILURE;

  // Music music;
  // if (!music.openFromFile("nice_music.ogg"))
  //  return EXIT_FAILURE;
  // music.play();

  spriteFem.setScale(Vector2f(0.04, 0.04));
  spriteFem2.setScale(Vector2f(0.04, 0.04));

  Event event;
  float x = 0, y = 0, x2 = 800 - spriteFem2.getGlobalBounds().width,
        y2 = 600 - spriteFem2.getGlobalBounds().width;

  int posx = 0, posy = 0, xadrez;
  int matriz[15][20];

  int conta1 = 0, conta2 = 0, lado = 0, lado2 = 0;

  Clock clock;
  Clock expTime;
  Clock global;

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

    if (Keyboard::isKeyPressed(Keyboard::D)) {
      x += 0.2;
      lado = 0;
    } else if (Keyboard::isKeyPressed(Keyboard::A)) {
      x -= 0.2;
      lado = 1;
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
      y -= 0.2;
      lado = 2;
    } else if (Keyboard::isKeyPressed(Keyboard::S)) {
      y += 0.2;
      lado = 3;
    } else {
      lado = 4;
    }

    if (Keyboard::isKeyPressed(Keyboard::Right)) {
      x2 += 0.2;
      lado2 = 0;
    } else if (Keyboard::isKeyPressed(Keyboard::Left)) {
      x2 -= 0.2;
      lado2 = 1;
    } else if (Keyboard::isKeyPressed(Keyboard::Up)) {
      y2 -= 0.2;
      lado2 = 2;
    } else if (Keyboard::isKeyPressed(Keyboard::Down)) {
      y2 += 0.2;
      lado2 = 3;
    } else {
      lado2 = 4;
    }

    spriteFem.setPosition(x, y);
    spriteFem2.setPosition(x2, y2);

    window.clear();

    window.draw(sprite);

    for (int i = 0; i < 15; i++) {
      xadrez = (i % 2 == 0) ? 1 : 0;
      for (int j = 0; j < 20; j++) {
        quadrado[i][j].setSize(Vector2f(40, 40));
        quadrado[i][j].setPosition(posx, posy);

        if (xadrez) {
          if (j % 2 == 0) {
            quadrado[i][j].setFillColor(Color::Black);
          } else {
            quadrado[i][j].setFillColor(Color::White);
          }
        } else {
          if ((j + 1) % 2 == 0) {
            quadrado[i][j].setFillColor(Color::Black);
          } else {
            quadrado[i][j].setFillColor(Color::White);
          }
        }

        if (x + 20 >= posx &&
            x + 20 <= posx + spriteFem.getGlobalBounds().width &&
            y + 20 >= posy &&
            y + 20 <= posy + spriteFem.getGlobalBounds().height &&
            matriz[i][j] != 1) {
          if (matriz[i][j] == 2)
            conta2--;
          matriz[i][j] = 1;
          conta1++;
        }

        if (x2 + 20 >= posx &&
            x2 + 20 <= posx + spriteFem2.getGlobalBounds().width &&
            y2 + 20 >= posy &&
            y2 + 20 <= posy + spriteFem2.getGlobalBounds().height &&
            matriz[i][j] != 2) {
          if (matriz[i][j] == 1)
            conta1--;
          matriz[i][j] = 2;
          conta2++;
        }

        if (matriz[i][j] == 1)
          quadrado[i][j].setFillColor(Color::Red);
        if (matriz[i][j] == 2)
          quadrado[i][j].setFillColor(Color::Yellow);

        if (matriz[i][j] == 2 || matriz[i][j] == 1)
          window.draw(quadrado[i][j]);
        posx += 40;
      }
      posx = 0;
      posy += 40;
    }

    posx = 0;
    posy = 0;

    Text text1(to_string(conta1), font, 50);
    text1.setPosition(Vector2f(20, 0));
    text1.setFillColor(Color::Red);
    text1.setOutlineColor(Color::Black);
    text1.setOutlineThickness(1.5);

    Text text2(to_string(conta2), font, 50);
    text2.setPosition(
        Vector2f(800 - text2.getGlobalBounds().width / 2 - 50, 0));
    text2.setFillColor(Color::Yellow);
    text2.setOutlineColor(Color::Black);
    text2.setOutlineThickness(1.5);

    if (lado != 4)
      rectSourceSprite.top = 1024 * lado;
    if (clockSprite.getElapsedTime().asSeconds() > 0.1f) {
      if (rectSourceSprite.left >= 3072 || lado == 4)
        rectSourceSprite.left = 0;
      else
        rectSourceSprite.left += 1024;
      spriteFem.setTextureRect(rectSourceSprite);
      clockSprite.restart();
    }

    if (lado2 != 4)
      rectSourceSprite2.top = 1024 * lado2;
    if (clockSprite2.getElapsedTime().asSeconds() > 0.1f) {
      if (rectSourceSprite2.left >= 3072 || lado2 == 4)
        rectSourceSprite2.left = 0;
      else
        rectSourceSprite2.left += 1024;
      spriteFem2.setTextureRect(rectSourceSprite2);
      clockSprite2.restart();
    }

    Text textClock(
        (to_string(global.getElapsedTime().asSeconds())).substr(0, 4), font,
        50);
    textClock.setPosition(
        Vector2f(800 / 2 - textClock.getGlobalBounds().width / 2, 0));
    textClock.setOutlineColor(Color::Black);
    textClock.setOutlineThickness(1.5);

    window.draw(textClock);
    window.draw(spriteFem);
    window.draw(spriteFem2);
    window.draw(text1);
    window.draw(text2);

    if (global.getElapsedTime().asSeconds() > 25.0f) {
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

        Text ganhador("ganhador", font, 30);

        if (conta1 > conta2) {
          ganhador.setString("Jogador vermelho venceu");
        } else if (conta1 < conta2) {
          ganhador.setString("Jogador amarelo venceu");
        } else {
          ganhador.setString("Empate");
        }

        ganhador.setPosition(
            Vector2f(800 / 2 - ganhador.getGlobalBounds().width / 2,
                     600 / 2 - ganhador.getGlobalBounds().height));

        ganhador.setOutlineColor(Color::Black);
        ganhador.setOutlineThickness(1.8);

        window.clear();
        window.draw(sprite);

        for (int i = 0; i < 15; i++) {
          for (int j = 0; j < 20; j++) {
            quadrado[i][j].setPosition(posx, posy);
            if (matriz[i][j] == 1)
              quadrado[i][j].setFillColor(Color::Red);
            if (matriz[i][j] == 2)
              quadrado[i][j].setFillColor(Color::Yellow);
            if (matriz[i][j] == 2 || matriz[i][j] == 1)
              window.draw(quadrado[i][j]);
            posx += 40;
          }
          posx = 0;
          posy += 40;
        }
        posx = 0;
        posy = 0;

        window.draw(textClock);
        window.draw(spriteFem);
        window.draw(spriteFem2);
        window.draw(text1);
        window.draw(text2);
        window.draw(ganhador);
        window.display();
      }
    }

    window.display();
  }

  return EXIT_SUCCESS;
}