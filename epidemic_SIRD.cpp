#include <iostream>

#include "epidemic_SIRD_display.hpp"

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

  std::cout << "D: ";
  double d;
  std::cin >> d;

  std::cout << "Days: ";
  double days;
  std::cin >> days;

  std::cout << "Beta: ";
  double b;
  std::cin >> b;

  std::cout << "Gamma: ";
  double g;
  std::cin >> g;

  std::cout << "Mu: ";
  double m;
  std::cin >> m;


  State initial_state{s, i, r, d};
  Virus Covid{initial_state, days};

  std::vector<State> data = Covid.evolve(b, g, m);

  std::cout << "S"
            << "\t"
            << "I"
            << "\t"
            << "R"
            << "\t"
            << "D"
            << "\t"
            << "Live"
            << "\t"
            << "N" << '\n';
  for (auto first = data.begin(), last = data.end(); first != last; ++first) {
    std::cout << first->s << "\t" << first->i << "\t" << first->r << '\t'
              << first->d << '\t' << first->s + first->i + first->r << '\t'
              << first->s + first->i + first->r + first->d << std::endl;
  }

  auto const display_size{600};

  sf::RenderWindow window(sf::VideoMode(display_size, display_size), "Virus");
  Display display{window, display_size};

  window.clear(sf::Color::White);
  display.draw_axes();
  display.draw_axes_values(days, data);

  display.draw_susceptible(data);
  display.draw_infectious(data);
  display.draw_recovered(data);
  display.draw_deceased(data);

  window.display();

  sf::Event event;
  while (window.waitEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }
}
