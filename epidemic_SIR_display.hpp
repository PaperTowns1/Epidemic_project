#ifndef EPIDEMIC_SIR_DISPLAY_HPP
#define EPIDEMIC_SIR_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "epidemic_SIR.hpp"

class Display {
  sf::RenderWindow& m_window;
  sf::Font m_font;
  int m_display_size;

 public:
  Display(sf::RenderWindow& window, int display_size)
      : m_window{window}, m_display_size{display_size} {
    if (!m_font.loadFromFile("Roboto.ttf")) {
      throw std::runtime_error{"cannot load font"};
    }
  }

  void draw_canvas(double days, std::vector<State> const& data) {
    // declare x-axis as line bewteen two extremes
    sf::VertexArray x_axis(sf::Lines, 2);

    // set x-axis extremes
    x_axis[0].position =
        sf::Vector2f(m_display_size * 0.15, m_display_size * 0.9);
    x_axis[1].position =
        sf::Vector2f(m_display_size * 0.85, m_display_size * 0.9);

    // color x-axis
    x_axis[0].color = sf::Color::Black;
    x_axis[1].color = sf::Color::Black;

    // declare y-axis as line bewteen two extremes
    m_window.draw(x_axis);

    // y-axis line
    sf::VertexArray y_axis(sf::Lines, 2);

    // set y-axis extremes
    y_axis[0].position =
        sf::Vector2f(m_display_size * 0.15, m_display_size * 0.2);
    y_axis[1].position =
        sf::Vector2f(m_display_size * 0.15, m_display_size * 0.9);

    // color y-axis
    y_axis[0].color = sf::Color::Black;
    y_axis[1].color = sf::Color::Black;

    // draw y-axis
    m_window.draw(y_axis);

    // declare x-axis notches as line bewteen two extremes
    sf::VertexArray x_axis_notches(sf::Lines, 22);

    int const distance_notches =
        m_display_size * 0.7 / 20;  // distance between notches

    // set x-axis notches extremes
    for (int i = 0; i != 22; i = i + 2) {
      x_axis_notches[i].position =
          sf::Vector2f(m_display_size * 0.15 + distance_notches * i,
                       m_display_size * 0.9 - m_display_size * 0.01);
      x_axis_notches[i + 1].position =
          sf::Vector2f(m_display_size * 0.15 + distance_notches * i,
                       m_display_size * 0.9 + m_display_size * 0.01);
    }

    // color x-axis notches
    for (int i = 0; i != 22; ++i) {
      x_axis_notches[i].color = sf::Color::Black;
    }

    // draw x-axis notches
    m_window.draw(x_axis_notches);

    // declare y-axis notches as line bewteen two extremes
    sf::VertexArray y_axis_notches(sf::Lines, 22);

    // set y-axis notches extremes
    for (int i = 0; i != 22; i = i + 2) {
      y_axis_notches[i].position =
          sf::Vector2f(m_display_size * 0.15 - m_display_size * 0.01,
                       m_display_size * 0.2 + i * distance_notches);
      y_axis_notches[i + 1].position =
          sf::Vector2f(m_display_size * 0.15 + m_display_size * 0.01,
                       m_display_size * 0.2 + i * distance_notches);
    }
    // color y-axis notches
    for (int i = 0; i != 22; ++i) {
      y_axis_notches[i].color = sf::Color::Black;
    }

    // draw y-axis notches
    m_window.draw(y_axis_notches);

    // declare x-axis name as text
    sf::Text x_axis_name;

    // costumize x-axis name
    x_axis_name.setFont(m_font);
    x_axis_name.setString("Days");
    x_axis_name.setCharacterSize(m_display_size / 40);
    x_axis_name.setFillColor(sf::Color::Black);

    // set position x-axis name
    x_axis_name.setPosition(
        sf::Vector2f(m_display_size * 0.9, m_display_size * 0.9));

    // draw x-axis name as text
    m_window.draw(x_axis_name);

    // declare y-axis name
    sf::Text y_axis_name;

    // costumize y-axis name
    y_axis_name.setFont(m_font);
    y_axis_name.setString("Population");
    y_axis_name.setCharacterSize(m_display_size / 40);
    y_axis_name.setFillColor(sf::Color::Black);

    // set position y-axis name
    y_axis_name.setPosition(
        sf::Vector2f(m_display_size * 0.15, m_display_size * 0.15));

    // draw y-axis name
    m_window.draw(y_axis_name);

    int const distance_values = m_display_size * 0.7 / 10;

    // values x-axis
    for (int i = 0; i != 10; ++i) {
      sf::Text x_axis_value;
      x_axis_value.setFont(m_font);

      // set x-axis value of one notches in int
      int a = days / 10 * (i + 1);

      // put int x-axis value into string
      std::string s = std::to_string(a);
      x_axis_value.setString(s);

      // costumize x-axis value
      x_axis_value.setCharacterSize(m_display_size / 60);
      x_axis_value.setFillColor(sf::Color::Black);

      // set positions x-axis value
      x_axis_value.setPosition(
          sf::Vector2f(distance_values * (i + 1) + m_display_size * 0.15,
                       m_display_size * 0.915));

      // draw x-axis value
      m_window.draw(x_axis_value);
    }

    // values y-axis
    for (int i = 0; i != 10; ++i) {
      sf::Text y_axis_value;
      y_axis_value.setFont(m_font);

      int a = data[0].s / 10 * (10 - i);

      int b = count_digits(a) - 1;

      std::string u = std::to_string(a);
      char digit0 = u[0];
      char digit1 = u[1];

      std::string c{};
      c.push_back(digit0);
      c = c + ".";
      c.push_back(digit1);
      c = c + "*10^" + std::to_string(b);

      y_axis_value.setString(c);

      // costumize y-axis value
      y_axis_value.setCharacterSize(m_display_size / 60);
      y_axis_value.setFillColor(sf::Color::Black);

      // set positions y-axis value
      y_axis_value.setPosition(sf::Vector2f(
          m_display_size * 0.06, m_display_size * 0.2 + i * distance_values));

      // draw y-axis value
      m_window.draw(y_axis_value);
    }

    // declare legend borders as strip lines
    sf::VertexArray legend(sf::LineStrip, 5);

    // set position legend borders
    legend[0].position =
        sf::Vector2f(m_display_size * 0.55, m_display_size * 0.05);
    legend[1].position =
        sf::Vector2f(m_display_size * 0.95, m_display_size * 0.05);
    legend[2].position =
        sf::Vector2f(m_display_size * 0.95, m_display_size * 0.15);
    legend[3].position =
        sf::Vector2f(m_display_size * 0.55, m_display_size * 0.15);
    legend[4].position =
        sf::Vector2f(m_display_size * 0.55, m_display_size * 0.05);

    // color legend borders
    legend[0].color = sf::Color::Black;
    legend[1].color = sf::Color::Black;
    legend[2].color = sf::Color::Black;
    legend[3].color = sf::Color::Black;
    legend[4].color = sf::Color::Black;

    // draw legend borders
    m_window.draw(legend);

    // declare legend names
    sf::Text susceptible, infectious, recovered;

    // costumize legend names
    susceptible.setFont(m_font);
    infectious.setFont(m_font);
    recovered.setFont(m_font);
    susceptible.setString("S");
    infectious.setString("I");
    recovered.setString("R");
    susceptible.setCharacterSize(m_display_size / 40);
    infectious.setCharacterSize(m_display_size / 40);
    recovered.setCharacterSize(m_display_size / 40);
    susceptible.setFillColor(sf::Color::Black);
    infectious.setFillColor(sf::Color::Black);
    recovered.setFillColor(sf::Color::Black);

    // set position legend names
    susceptible.setPosition(
        sf::Vector2f(m_display_size * 0.57, m_display_size * 0.05));
    infectious.setPosition(
        sf::Vector2f(m_display_size * 0.57, m_display_size * 0.085));
    recovered.setPosition(
        sf::Vector2f(m_display_size * 0.57, m_display_size * 0.12));

    // draw legend names
    m_window.draw(susceptible);
    m_window.draw(infectious);
    m_window.draw(recovered);

    // declare legend color lines
    sf::VertexArray color(sf::Lines, 6);

    // set position legend color lines
    color[0].position =
        sf::Vector2f(m_display_size * 0.6, m_display_size * 0.065);
    color[1].position =
        sf::Vector2f(m_display_size * 0.7, m_display_size * 0.065);
    color[2].position =
        sf::Vector2f(m_display_size * 0.6, m_display_size * 0.10);
    color[3].position =
        sf::Vector2f(m_display_size * 0.7, m_display_size * 0.10);
    color[4].position =
        sf::Vector2f(m_display_size * 0.6, m_display_size * 0.135);
    color[5].position =
        sf::Vector2f(m_display_size * 0.7, m_display_size * 0.135);

    // color legend color lines
    color[0].color = sf::Color::Blue;
    color[1].color = sf::Color::Blue;
    color[2].color = sf::Color::Red;
    color[3].color = sf::Color::Red;
    color[4].color = sf::Color::Green;
    color[5].color = sf::Color::Green;

    // draw legend color lines
    m_window.draw(color);
  }

  int count_digits(int n) {
    int num = 0;
    while (n != 0) {
      n = n / 10;
      num++;
    }
    return num;
  }

  void draw_susceptible(std::vector<State> const& data) {
    sf::VertexArray points_s(sf::LineStrip, data.size());

    int n = static_cast<int>(data.size());

    for (int i{0}; i != n; ++i) {
      points_s[i].position = sf::Vector2f(
          i * m_display_size * 0.7 / n + m_display_size * 0.15,
          data[i].s / data[0].s * m_display_size * 0.7 + m_display_size * 0.1);
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
      points_i[i].position = sf::Vector2f(
          i * m_display_size * 0.7 / n + m_display_size * 0.15,
          data[i].i / data[0].s * m_display_size * 0.7 + m_display_size * 0.1);
    }

    for (int i{0}; i != n; ++i) {
      points_i[i].color = sf::Color::Red;
    }

    m_window.draw(points_i, transform());
  }

  void draw_recovered(std::vector<State> const& data) {
    sf::VertexArray points_r(sf::LineStrip, data.size());

    int const n = static_cast<int>(data.size());

    for (int i{0}; i != n; ++i) {
      points_r[i].position = sf::Vector2f(
          i * m_display_size * 0.7 / n + m_display_size * 0.15,
          data[i].r / data[0].s * m_display_size * 0.7 + m_display_size * 0.1);
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
