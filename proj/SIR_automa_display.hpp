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
  std::vector<Population> plot;

 public:
  Display_automa(sf::RenderWindow& window) : m_window{window} {
    if (!m_font.loadFromFile("Roboto.ttf")) {
      throw std::runtime_error{"cannot load font"};
    }
  }

  void draw_grid(World const& world_to_draw);

  void draw_legend(World const& world_to_draw, int duration);

  int count_digits(long int n);

  sf::Transform transform();
};

}  // namespace epidemic_SIR

#endif
