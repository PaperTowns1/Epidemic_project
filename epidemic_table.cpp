#include <iostream>

#include "epidemic_table_display.hpp"

int main() {
  std::cout << "S: ";
  double s;
  std::cin >> s;

  std::cout << "I: ";
  double i;
  std::cin >> i;

  std::cout << "R: ";
  double r;
  std::cin >> r;

  std::cout << "Days: ";
  double days;
  std::cin >> days;

  std::cout << "Beta: ";
  double b;
  std::cin >> b;

  std::cout << "Gamma: ";
  double g;
  std::cin >> g;

  State initial_state{s, i, r};
  Virus Covid{initial_state, days};

  std::vector<State> data = Covid.evolve(b, g);

  std::cout << "S"
            << "\t"
            << "I"
            << "\t"
            << "R"
            << "\t"
            << "N" << '\n';
  for (auto first = data.begin(), last = data.end(); first != last; ++first) {
    std::cout << first->s << "\t" << first->i << "\t" << first->r << '\t'
              << first->s + first->i + first->r << std::endl;
  }

  auto const display_size{600};

  sf::RenderWindow window(sf::VideoMode(display_size, display_size), "Virus");
  Display display{window, display_size};

  window.clear(sf::Color::White);
  display.draw_axes();

  display.draw_susceptible(data);
  display.draw_infectious(data);
  display.draw_recovered(data);

  window.display();

  sf::Event event;
  while (window.waitEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }
}
