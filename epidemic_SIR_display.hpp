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
      : m_window{window}, m_display_size{display_size} {
    if (!m_font.loadFromFile("Roboto.ttf")) {
      throw std::runtime_error{"cannot load font"};
    }
  }

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

    // name x_axis
    sf::Text x_axis_name;

    x_axis_name.setFont(m_font);
    x_axis_name.setString("Days");

    x_axis_name.setCharacterSize(15);
    x_axis_name.setFillColor(sf::Color::Black);

    x_axis_name.setPosition(sf::Vector2f(520, 490));

    m_window.draw(x_axis_name);

    // name y_axis
    sf::Text y_axis_name;

    y_axis_name.setFont(m_font);
    y_axis_name.setString("Population");

    y_axis_name.setCharacterSize(15);
    y_axis_name.setFillColor(sf::Color::Black);

    y_axis_name.setPosition(sf::Vector2f(50, 65));

    m_window.draw(y_axis_name);
  }

  void draw_axes_values(double days, std::vector<State> const& data) {
    // values x_axis
    for (int i = 0; i != 10; ++i) {
      sf::Text value;
      value.setFont(m_font);
      std::string s;
      int a = days / 10 * (i + 1);
      s = std::to_string(a);
      value.setString(s);
      value.setCharacterSize(10);
      value.setFillColor(sf::Color::Black);
      value.setPosition(sf::Vector2f(40 * i + 125, 510));
      m_window.draw(value);
    }

    // values y_axis
    for (int i = 0; i != 10; ++i) {
      sf::Text value;
      value.setFont(m_font);
      std::string s;
      int a = data[0].s / 10 * (10 - i);
      s = std::to_string(a);
      value.setString(s);
      value.setCharacterSize(10);
      value.setFillColor(sf::Color::Black);
      value.setPosition(sf::Vector2f(55, 40 * i + 95));
      m_window.draw(value);
    }
  }

  void draw_label() {
    // label
    sf::VertexArray label(sf::LineStrip, 5);

    label[0].position = sf::Vector2f(350, 20);
    label[1].position = sf::Vector2f(550, 20);
    label[2].position = sf::Vector2f(550, 95);
    label[3].position = sf::Vector2f(350, 95);
    label[4].position = sf::Vector2f(350, 20);

    label[0].color = sf::Color::Black;
    label[1].color = sf::Color::Black;
    label[2].color = sf::Color::Black;
    label[3].color = sf::Color::Black;
    label[4].color = sf::Color::Black;

    m_window.draw(label);

    // names label
    sf::Text susceptible, infectious, recovered;

    susceptible.setFont(m_font);
    infectious.setFont(m_font);
    recovered.setFont(m_font);

    susceptible.setString("Susceptible");
    infectious.setString("Infectious");
    recovered.setString("Recovered");

    susceptible.setCharacterSize(15);
    infectious.setCharacterSize(15);
    recovered.setCharacterSize(15);
    susceptible.setFillColor(sf::Color::Black);
    infectious.setFillColor(sf::Color::Black);
    recovered.setFillColor(sf::Color::Black);

    susceptible.setPosition(sf::Vector2f(355, 25));
    infectious.setPosition(sf::Vector2f(355, 50));
    recovered.setPosition(sf::Vector2f(355, 75));

    m_window.draw(susceptible);
    m_window.draw(infectious);
    m_window.draw(recovered);

    //color lines label
    sf::VertexArray color(sf::Lines, 6);

    color[0].position = sf::Vector2f(485, 35);
    color[1].position = sf::Vector2f(525, 35);
    color[2].position = sf::Vector2f(485, 60);
    color[3].position = sf::Vector2f(525, 60);
    color[4].position = sf::Vector2f(485, 85);
    color[5].position = sf::Vector2f(525, 85);


    color[0].color = sf::Color::Blue;
    color[1].color = sf::Color::Blue;
    color[2].color = sf::Color::Red;
    color[3].color = sf::Color::Red;
    color[4].color = sf::Color::Green;
    color[5].color = sf::Color::Green;

    m_window.draw(color);

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
