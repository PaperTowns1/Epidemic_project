#ifndef B_DISPLAY_HPP
#define B_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdexcept>

#include "b_SIR.hpp"

class Display {
  sf::RenderWindow& m_window;
  sf::Font m_font;

 public:
  Display(sf::RenderWindow& window) : m_window{window} {
    if (!m_font.loadFromFile("Roboto.ttf")) {
      throw std::runtime_error{"cannot load font"};
    }
  }

  void draw(World const& world_to_draw) {
    World world = world_to_draw;
    int const N = world.side();
    std::vector<Person> grid = world.grid();

    sf::Vector2f const cell_size{sf::Vector2f(640.f / N, 640.f / N)};

    sf::RectangleShape S_cell(cell_size);
    S_cell.setFillColor(sf::Color::Blue);
    S_cell.setOutlineThickness(1.f);
    S_cell.setOutlineColor(sf::Color::White);

    sf::RectangleShape I_cell(cell_size);
    I_cell.setFillColor(sf::Color::Red);
    I_cell.setOutlineThickness(1.f);
    I_cell.setOutlineColor(sf::Color::White);

    sf::RectangleShape R_cell(cell_size);
    R_cell.setFillColor(sf::Color::Green);
    R_cell.setOutlineThickness(1.f);
    R_cell.setOutlineColor(sf::Color::White);

    for (int r = 0; r != N; ++r) {
      for (int c = 0; c != N; ++c) {
        if (grid[index(r, c, N)].status == Cell::S) {
          S_cell.setPosition(r * cell_size.y, c * cell_size.x);
          m_window.draw(S_cell);
        }

        if (grid[index(r, c, N)].status == Cell::I) {
          I_cell.setPosition(r * cell_size.y, c * cell_size.x);
          m_window.draw(I_cell);
        }

        if (grid[index(r, c, N)].status == Cell::R) {
          R_cell.setPosition(r * cell_size.y, c * cell_size.x);
          m_window.draw(R_cell);
        }
      }
    }
  }

  void print(World const& world_to_print, int duration) {
    sf::VertexArray separator(sf::LineStrip, 2);

    separator[0].position = sf::Vector2f(640, 0);
    separator[1].position = sf::Vector2f(640, 640);

    separator[0].color = sf::Color::Black;
    separator[1].color = sf::Color::Black;

    m_window.draw(separator);

    sf::VertexArray legend(sf::LineStrip, 5);

    legend[0].position = sf::Vector2f(650, 10);
    legend[1].position = sf::Vector2f(650, 170);
    legend[2].position = sf::Vector2f(1030, 170);
    legend[3].position = sf::Vector2f(1030, 10);
    legend[4].position = sf::Vector2f(650, 10);

    legend[0].color = sf::Color::Black;
    legend[1].color = sf::Color::Black;
    legend[2].color = sf::Color::Black;
    legend[3].color = sf::Color::Black;
    legend[4].color = sf::Color::Black;

    m_window.draw(legend);

    sf::Text susceptible, infectious, recovered, n;

    susceptible.setFont(m_font);
    infectious.setFont(m_font);
    recovered.setFont(m_font);
    n.setFont(m_font);
    susceptible.setString("S");
    infectious.setString("I");
    recovered.setString("R");
    n.setString("N");
    susceptible.setCharacterSize(20);
    infectious.setCharacterSize(20);
    recovered.setCharacterSize(20);
    n.setCharacterSize(20);
    susceptible.setFillColor(sf::Color::Black);
    infectious.setFillColor(sf::Color::Black);
    recovered.setFillColor(sf::Color::Black);
    n.setFillColor(sf::Color::Black);

    susceptible.setPosition(sf::Vector2f(660, 30));
    infectious.setPosition(sf::Vector2f(660, 60));
    recovered.setPosition(sf::Vector2f(660, 90));
    n.setPosition(sf::Vector2f(660, 120));

    m_window.draw(susceptible);
    m_window.draw(infectious);
    m_window.draw(recovered);
    m_window.draw(n);

    World current_world = world_to_print;

    int const N = current_world.side();
    std::vector<Person> current_grid = current_world.grid();

    int cont_s = 0, cont_i = 0, cont_r = 0;

    for (int i = 0; i != N * N; ++i) {
      if (current_grid[i].status == Cell::S) {
        cont_s++;
      }
      if (current_grid[i].status == Cell::I) {
        cont_i++;
      }
      if (current_grid[i].status == Cell::R) {
        cont_r++;
      }
    }

    sf::Text s_value, i_value, r_value, n_value;

    s_value.setFont(m_font);
    i_value.setFont(m_font);
    r_value.setFont(m_font);
    n_value.setFont(m_font);

    std::string s = std::to_string(cont_s);
    std::string i = std::to_string(cont_i);
    std::string r = std::to_string(cont_r);
    std::string num = std::to_string(cont_s + cont_i + cont_r);

    s_value.setString(s);
    i_value.setString(i);
    r_value.setString(r);
    n_value.setString(num);

    s_value.setCharacterSize(20);
    i_value.setCharacterSize(20);
    r_value.setCharacterSize(20);
    n_value.setCharacterSize(20);
    s_value.setFillColor(sf::Color::Black);
    i_value.setFillColor(sf::Color::Black);
    r_value.setFillColor(sf::Color::Black);
    n_value.setFillColor(sf::Color::Black);

    s_value.setPosition(sf::Vector2f(700, 30));
    i_value.setPosition(sf::Vector2f(700, 60));
    r_value.setPosition(sf::Vector2f(700, 90));
    n_value.setPosition(sf::Vector2f(700, 120));

    m_window.draw(s_value);
    m_window.draw(i_value);
    m_window.draw(r_value);
    m_window.draw(n_value);

    sf::Text days, hours;

    days.setFont(m_font);
    hours.setFont(m_font);

    days.setString("Days");
    hours.setString("Hours");

    days.setCharacterSize(20);
    hours.setCharacterSize(20);

    days.setFillColor(sf::Color::Black);
    hours.setFillColor(sf::Color::Black);

    days.setPosition(sf::Vector2f(750, 30));
    hours.setPosition(sf::Vector2f(750, 60));

    m_window.draw(days);
    m_window.draw(hours);

    sf::Text days_value, hours_value;

    days_value.setFont(m_font);
    hours_value.setFont(m_font);

    int da = std::floor(duration / 24);
    int ho = duration % 24;

    std::string d = std::to_string(da);
    std::string h = std::to_string(ho);

    days_value.setString(d);
    hours_value.setString(h);

    days_value.setCharacterSize(20);
    hours_value.setCharacterSize(20);

    days_value.setFillColor(sf::Color::Black);
    hours_value.setFillColor(sf::Color::Black);

    days_value.setPosition(sf::Vector2f(850, 30));
    hours_value.setPosition(sf::Vector2f(850, 60));

    m_window.draw(days_value);
    m_window.draw(hours_value);

    /*

    sf::VertexArray x_axis(sf::Lines, 2);

    x_axis[0].position = sf::Vector2f(700, 600);
    x_axis[1].position = sf::Vector2f(1000, 600);

    x_axis[0].color = sf::Color::Black;
    x_axis[1].color = sf::Color::Black;

    m_window.draw(x_axis);

    sf::VertexArray y_axis(sf::Lines, 2);

    y_axis[0].position = sf::Vector2f(700, 300);
    y_axis[1].position = sf::Vector2f(700, 600);

    y_axis[0].color = sf::Color::Black;
    y_axis[1].color = sf::Color::Black;

    m_window.draw(y_axis);

    sf::VertexArray x_axis_notches(sf::Lines, 22);

    int const distance_notches = 15;

    for (int i = 0; i != 22; i = i + 2) {
      x_axis_notches[i].position =
          sf::Vector2f(700 + distance_notches * i, 600 - 3);
      x_axis_notches[i + 1].position =
          sf::Vector2f(700 + distance_notches * i, 600 + 3);
    }

    for (int i = 0; i != 22; ++i) {
      x_axis_notches[i].color = sf::Color::Black;
    }

    m_window.draw(x_axis_notches);

    sf::VertexArray y_axis_notches(sf::Lines, 22);

    for (int i = 0; i != 22; i = i + 2) {
      y_axis_notches[i].position =
          sf::Vector2f(700 - 3, 300 + i * distance_notches);
      y_axis_notches[i + 1].position =
          sf::Vector2f(700 + 3, 300 + i * distance_notches);
    }

    for (int i = 0; i != 22; ++i) {
      y_axis_notches[i].color = sf::Color::Black;
    }

    m_window.draw(y_axis_notches);

    sf::Text x_axis_name;

    x_axis_name.setFont(m_font);
    x_axis_name.setString("Days");
    x_axis_name.setCharacterSize(10);
    x_axis_name.setFillColor(sf::Color::Black);

    x_axis_name.setPosition(sf::Vector2f(1005, 600));

    m_window.draw(x_axis_name);

    sf::Text y_axis_name;

    y_axis_name.setFont(m_font);
    y_axis_name.setString("Population");
    y_axis_name.setCharacterSize(10);
    y_axis_name.setFillColor(sf::Color::Black);

    y_axis_name.setPosition(sf::Vector2f(700, 285));

    m_window.draw(y_axis_name);*/
  }
};

#endif