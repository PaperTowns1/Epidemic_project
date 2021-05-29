#include "SIR.hpp"
#include "SIR_automa.hpp"
#include "SIR_automa_display.hpp"
#include "SIR_display.hpp"

int input_choice(int inf, int sup) {
  int choice;

  std::cout << "Choice: ";
  std::cin >> choice;
  std::cout << '\n';

  while (choice < inf || choice > sup) {
    std::cout << "Invalid choice, try again " << '\n';
    std::cout << "Choice: ";
    std::cin >> choice;
    std::cout << '\n';
  }

  return choice;
}

int input_days() {
  int days;

  std::cout << "Days: ";
  std::cin >> days;
  std::cout << '\n';

  if (days < 0) {
    throw std::range_error{"Days are less than 0"};
  }

  return days;
}

void plot_graph(int choice_3, int choice_4, int choice_5,
                std::vector<epidemic_SIR::Population> const& data_to_draw) {
  std::vector<epidemic_SIR::Population> data = data_to_draw;
  auto const display_size = 600;

  sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                          "SIR model");

  epidemic_SIR::Display_graph display{window, display_size};

  window.clear(sf::Color::White);

  display.draw_canvas();
  display.draw_more(data);

  if (choice_3 == 1) {
    display.draw_susceptible(data);
  }

  if (choice_4 == 1) {
    display.draw_infectious(data);
  }

  if (choice_5 == 1) {
    display.draw_recovered(data);
  }

  window.display();

  sf::Event event;
  while (window.waitEvent(event)) {
    if (event.type == sf::Event::Closed) window.close();
  }
}

int main() {
  std::cout << "Which epidemiological model?" << '\n'
            << "1. SIR model (differential equations)" << '\n'
            << "2. SIR model (automa)" << '\n';

  int choice_1 = input_choice(1, 2);

  switch (choice_1) {
    case 1: {
      epidemic_SIR::Population initial_population =
          epidemic_SIR::input_initial_population();
      epidemic_SIR::Parameter parameter = epidemic_SIR::input_parameter();

      epidemic_SIR::Virus covid{initial_population};

      int days = input_days();

      do {
        covid = epidemic_SIR::evolve(covid, parameter, days);

        int choice_2;

        do {
          std::cout << "What output?" << '\n'
                    << "1. Table with values (standard output)" << '\n'
                    << "2. Graph" << '\n'
                    << "0. Exit" << '\n';

          choice_2 = input_choice(0, 2);

          switch (choice_2) {
            case 0: {
            } break;

            case 1: {
              epidemic_SIR::print(covid, parameter);
            } break;

            case 2: {
              std::vector<epidemic_SIR::Population> data = covid.get_data();
              std::cout << "Do you want susceptible (S) on your graph? (0 for "
                           "no and 1 for yes)"
                        << '\n';
              int choice_3 = input_choice(0, 1);

              std::cout << "Do you want infectious (I) on your graph? (0 for "
                           "no and 1 for yes)"
                        << '\n';
              int choice_4 = input_choice(0, 1);

              std::cout << "Do you want recovered (R) on your graph? (0 for no "
                           "and 1 for yes)"
                        << '\n';
              int choice_5 = input_choice(0, 1);

              plot_graph(choice_3, choice_4, choice_5, data);

            } break;

              std::cout << '\n';
          }
        } while (choice_2 != 0);

        std::cout << "To exit press 0, otherwise insert more days to simulate: "
                  << '\n';
        days = input_days();

      } while (days != 0);
    } break;

    case 2: {
      constexpr int grid_size = 128;
      constexpr int cell_size = 5;
      constexpr auto window_title{"SIR"};

      std::cout << "S: ";
      int S;
      std::cin >> S;

      std::cout << "I: ";
      int I;
      std::cin >> I;

      std::cout << "R: ";
      int R;
      std::cin >> R;

      sf::RenderWindow window{
          sf::VideoMode(grid_size * cell_size * 2, grid_size * cell_size),
          window_title, sf::Style::Close};

      window.setFramerateLimit(25);

      epidemic_SIR::Display_automa display{window};

      epidemic_SIR::World world(grid_size);

      world = generate(world, S, epidemic_SIR::Cell::Susceptible);
      world = generate(world, I, epidemic_SIR::Cell::Infectious);
      world = generate(world, R, epidemic_SIR::Cell::Recovered);

      world = update_data(world);

      if (window.isOpen()) {
        window.clear(sf::Color::White);
        display.draw_grid(world);
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

        display.draw_grid(world);
        display.draw_legend(world, duration);

        window.display();
      }
    } break;
  }

  return 0;
}
