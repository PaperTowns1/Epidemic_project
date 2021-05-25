#include <chrono>
#include <iostream>
#include <random>
#include <thread>

#include "b_SIR.hpp"
#include "b_display.hpp"

int main() {
  constexpr int grid_size = 64;
  constexpr int cell_size = 10;
  constexpr auto window_title{"SIR"};

  sf::RenderWindow window{
      sf::VideoMode(grid_size * cell_size + 400, grid_size * cell_size),
      window_title, sf::Style::Close};

  window.setFramerateLimit(5);

  Display display{window};

  World world(grid_size);

  world = generate(world);

  if (window.isOpen()) {
    window.clear(sf::Color::White);
    display.draw(world);
    window.display();

    sf::Event event;
    while (window.waitEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        break;
      } else if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
  }

  bool running = true;
  int duration = 0;

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::KeyPressed) {
        running = !running;
      } else if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);

    if (running) {
      world = evolve(world, duration);
      duration++;
    }

    display.draw(world);
    display.print(world, duration);

    window.display();
  }
}
