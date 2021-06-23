#ifndef SIR_DISPLAY_HPP
#define SIR_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "SIR.hpp"

namespace epidemic_SIR {

class Display_graph {
  sf::RenderWindow& m_window;
  sf::Font m_font;
  int m_display_side;

 public:
  Display_graph(sf::RenderWindow& window, int display_side)
      : m_window{window}, m_display_side{display_side} {
    if (m_font.loadFromFile("Roboto.ttf") == false) {
      throw std::runtime_error{"cannot load font"};
    }
  }

  void draw_axes();

  void draw_axes_notches();

  int count_digits(int n);

  void draw_axes_values(std::vector<Population> const& data);

  void draw_legend();

  sf::Transform transform();

  void draw_susceptible(std::vector<Population> const& data);

  void draw_legend_susceptible();

  void draw_infectious(std::vector<Population> const& data);

  void draw_legend_infectious();

  void draw_recovered(std::vector<Population> const& data);

  void draw_legend_recovered();
};

}  // namespace epidemic_SIR

#endif
