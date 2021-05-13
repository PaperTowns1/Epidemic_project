#ifndef EPIDEMIC_TABLE_DISPLAY_HPP
#define EPIDEMIC_TABLE_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>

#include "epidemic_table.hpp"

class Display {
  sf::RenderWindow& m_window;
  sf::Font m_font;
  int m_display_size;

 public:
  Display(sf::RenderWindow& window, int display_size)
      : m_window{window}, m_display_size{display_size} {}

  void draw_axes() {
    // line x-axis
    sf::VertexArray x_axis(sf::Lines, 2);

    x_axis[0].position = sf::Vector2f(100, 500);
    x_axis[1].position = sf::Vector2f(500, 500);

    x_axis[0].color = sf::Color::Black;
    x_axis[1].color = sf::Color::Black;

    m_window.draw(x_axis);

    // notches x-axis
    sf::VertexArray x_axis_notches(sf::Lines, 22);

    for (int i = 0; i != 22; i = i + 2) {
      x_axis_notches[i].position = sf::Vector2f(95, 100 + i * 20);
      x_axis_notches[i + 1].position = sf::Vector2f(105, 100 + i * 20);
    }

    for (int i = 0; i != 22; ++i) {
      x_axis_notches[i].color = sf::Color::Black;
    }

    m_window.draw(x_axis_notches);

    // line y-axis
    sf::VertexArray y_axis(sf::Lines, 2);

    y_axis[0].position = sf::Vector2f(100, 100);
    y_axis[1].position = sf::Vector2f(100, 500);

    y_axis[0].color = sf::Color::Black;
    y_axis[1].color = sf::Color::Black;

    m_window.draw(y_axis);

    // notches y-axis
    sf::VertexArray y_axis_notches(sf::Lines, 44);

    for (int i = 0; i != 22; i = i + 2) {
      y_axis_notches[i].position = sf::Vector2f(100 + i * 20, 495);
      y_axis_notches[i + 1].position = sf::Vector2f(100 + i * 20, 505);
    }

    for (int i = 0; i != 22; ++i) {
      y_axis_notches[i].color = sf::Color::Black;
    }

    m_window.draw(y_axis_notches);
  }

  void draw_susceptible(std::vector<State> const& data) {
    sf::VertexArray points_s(sf::LineStrip, data.size());

    int n = static_cast<int>(data.size());

    for (int i{0}; i != n; ++i) {
      points_s[i].position =
          sf::Vector2f(i * 400 / n + 100, data[i].s / data[0].s * 400 + 100);
    }

    for (int i{0}; i != n; ++i) {
      points_s[i].color = sf::Color::Blue;
    }

    m_window.draw(points_s, transform());
  }

  void draw_infectious(std::vector<State> const& data) {
    sf::VertexArray points_i(sf::LineStrip, data.size());

    int n = static_cast<int>(data.size());

    for (int i{0}; i != n; ++i) {
      points_i[i].position =
          sf::Vector2f(i * 400 / n + 100, data[i].i / data[0].s * 400 + 100);
    }

    for (int i{0}; i != n; ++i) {
      points_i[i].color = sf::Color::Red;
    }

    m_window.draw(points_i, transform());
  }

  void draw_recovered(std::vector<State> const& data) {
    sf::VertexArray points_r(sf::LineStrip, data.size());

    int n = static_cast<int>(data.size());

    for (int i{0}; i != n; ++i) {
      points_r[i].position =
          sf::Vector2f(i * 400 / n + 100, data[i].r / data[0].s * 400 + 100);
    }

    for (int i{0}; i != n; ++i) {
      points_r[i].color = sf::Color::Green;
    }

    m_window.draw(points_r, transform());
  }

  sf::Transform transform() {
    sf::Transformable transformation;
    transformation.setOrigin(0, m_display_size);
    transformation.setScale(1.f, -1.f);
    return transformation.getTransform();
  }
};

#endif
