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
  int m_display_size;

 public:
  Display_graph(sf::RenderWindow& window, int display_size)
      : m_window{window}, m_display_size{display_size} {
    if (m_font.loadFromFile("Roboto.ttf") == false) {
      throw std::runtime_error{"cannot load font"};
    }
  }

  void draw_canvas();

  void draw_more(std::vector<Population> const& data);

  int count_digits(long int n);

  sf::Transform transform();

  void draw_susceptible(std::vector<Population> const& data);

  void draw_infectious(std::vector<Population> const& data);

  void draw_recovered(std::vector<Population> const& data);
};



}  // namespace epidemic_SIR

#endif
