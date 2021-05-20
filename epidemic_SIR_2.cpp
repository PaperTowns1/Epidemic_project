#include <iostream>

#include "epidemic_SIR_2_display.hpp"

int main() {
  std::cout << "S: ";
  int s;
  std::cin >> s;

  if (s < 0) {
    throw std::runtime_error{"S are less than 0"};
  }

  std::cout << "I: ";
  int i;
  std::cin >> i;

  if (i < 0) {
    throw std::runtime_error{"I are less than 0"};
  }

  std::cout << "R: ";
  int r;
  std::cin >> r;

  if (r < 0) {
    throw std::runtime_error{"R are less than 0"};
  }

  std::cout << "Days: ";
  int days;
  std::cin >> days;

  if (days < 0) {
    throw std::runtime_error{"Days are less than 0"};
  }

  std::cout << "Beta: ";
  double b;
  std::cin >> b;

  if (b < 0 || b > 1) {
    throw std::runtime_error{"Beta is not between 0 and 1"};
  }

  std::cout << "Gamma: ";
  double g;
  std::cin >> g;

  if (b < 0 || g > 1) {
    throw std::runtime_error{"Gamma is not between 0 and 1"};
  }

  if (b / g < 1) {
    throw std::runtime_error{"R0 is less than 1"};
  }

  Population initial_state{
      static_cast<double>(s),
      static_cast<double>(i),
      static_cast<double>(r),
  };
  Virus Covid{initial_state, days};

  std::vector<Population> data = Covid.evolve(b, g);

  std::cout << "r0: " << b / g << '\n';

  std::cout << 'S' << '\t' << 'I' << '\t' << 'R' << '\t' << 'N' << '\n';

  for (int i = 0; i != days; ++i) {
    Population data_round{data[i].s, data[i].i, data[i].r};
    data_round = approx(data_round);
    std::cout << data_round.s << '\t' << data_round.i << '\t' << data_round.r
              << '\t' << data_round.s + data_round.i + data_round.r << '\n';
  }

  auto const display_size{600};

  sf::RenderWindow window(sf::VideoMode(display_size, display_size), "SIR");
  Display display{window, display_size};

  window.clear(sf::Color::White);
  display.draw_canvas(days, data);

  display.draw_susceptible(data);
  display.draw_infectious(data);
  display.draw_recovered(data);

  window.display();

  sf::Event event;
  while (window.waitEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }
}
