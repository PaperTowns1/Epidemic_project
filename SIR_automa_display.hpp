#ifndef SIR_AUTOMA_DISPLAY_HPP
#define SIR_AUTOMA_DISPLAY_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>

#include "SIR_automa.hpp"

namespace epidemic_SIR {

class Display_automa {
  sf::RenderWindow& m_window;
  sf::Font m_font;
  std::vector<Population> m_data;
  int m_display_side;

 public:
  Display_automa(sf::RenderWindow& window, int display_side)
      : m_window{window}, m_display_side{display_side} {
    if (!m_font.loadFromFile("Roboto.ttf")) {
      throw std::runtime_error{"cannot load font"};
    }
  }

  void draw_grid(World const& world_to_draw);

  void draw_legend(std::vector<Population> const& data);

  void draw_axes();

  void draw_axes_notches();

  int count_digits(int n);

  void draw_axes_values(std::vector<Population> const& data);

  void draw_graph(std::vector<Population> const data);


  sf::Transform transform();
};

}  // namespace epidemic_SIR

#endif
