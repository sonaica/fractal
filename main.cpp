#include <SFML/Graphics.hpp>

#include "header.hpp"

double scale = 2;
int n = 100;

std::vector<sf::Color> color(11);

void DrawPoint(sf::RenderWindow& window, double x, double y, int num_color) {
  sf::RectangleShape point;
  point.setFillColor(color[num_color]);
  point.setSize(sf::Vector2f(1.0, 1.0));
  point.setPosition(x, y);
  window.draw(point);
  return;
}

void Draw(sf::RenderWindow& window, double size, double dx, double dy) {
  Complex c(-0.4, 0.6);
  for (int x = -size + dx; x < size + dx; ++x) {
    for (int y = -size + dy; y < size + dy; ++y) {
      bool f = true;
      double a = x / size * scale;
      double b = y / size * scale;
      Complex z(a, b);
      for (int i = 0; i < 100; ++i) {
        z = z * z;
        z = z + c;
        if (z.mod() > 2) {
          f = false;
          DrawPoint(window, x + size - dx, y + size - dy, i / 10 + 1);
          break;
        }
      }
      if (f) DrawPoint(window, x + size - dx, y + size - dy, 0);
    }
  }
}

int main() {
  double dx = 0, dy = 0;

  color[0] = sf::Color::Black;
  color[1] = sf::Color(148, 246, 147);
  color[2] = sf::Color(131, 231, 131);
  color[3] = sf::Color(73, 196, 116);
  color[4] = sf::Color(1, 166, 104);
  color[5] = sf::Color(61, 168, 55);
  color[6] = sf::Color(11, 216, 76);
  color[7] = sf::Color(47, 196, 34);
  color[8] = sf::Color(0, 245, 0);
  color[9] = sf::Color(101, 248, 0);
  color[10] = sf::Color(203, 251, 3);

  double size = 800;
  sf::RenderWindow window(sf::VideoMode(size, size), "Julia set");

  bool zoom1 = false, zoom2 = false;
  double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
  while (window.isOpen()) {
    window.clear(sf::Color::White);
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
      if (event.type == sf::Event::MouseButtonPressed) {
        if (!zoom1) {
          x1 = event.mouseButton.x;
          y1 = event.mouseButton.y;
          zoom1 = true;
        } else if (zoom1 && !zoom2) {
          x2 = event.mouseButton.x;
          y2 = event.mouseButton.y;
          zoom2 = true;
        }
      }
    }
    Draw(window, 400.0, dx, dy);
    if (zoom1 && zoom2) {
      if (x1 > x2) std::swap(x1, x2);
      if (y1 > y2) std::swap(y1, y2);
      sf::RectangleShape shape;
      shape.setPosition(x1, y1);
      shape.setSize(sf::Vector2f(x2 - x1, y2 - y1));
      shape.setFillColor(sf::Color(128, 128, 128, 100));
      shape.setOutlineThickness(1);
      shape.setOutlineColor(sf::Color(128, 128, 128));
      window.draw(shape);
      y2 = y1 + (x2 - x1);
      x1 -= 400.0;
      x2 -= 400.0;
      y1 -= 400.0;
      y2 -= 400.0;

      x1 += dx;
      x2 += dx;
      y1 += dy;
      y2 += dy;

      double a = x1 / 400.0 * scale;
      double b = x2 / 400.0 * scale;
      double c = y1 / 400.0 * scale;
      double d = y2 / 400.0 * scale;
      scale = (b - a) / 2.0;

      double x = a / scale * 400.0;
      double xx = b / scale * 400.0;
      double y = c / scale * 400.0;
      double yy = d / scale * 400.0;

      dx = (x + xx) / 2.0;
      dy = (y + yy) / 2.0;

      zoom1 = false;
      zoom2 = false;
    }
    window.display();
  }

  return 0;
}
