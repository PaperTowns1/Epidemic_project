#include "SIR.hpp"
#include "SIR_display.hpp"
#include "SIR_automa.hpp"
#include "SIR_automa_display.hpp"
#include "input.hpp"

int main() {
  std::cout << "Hi, which epidemiological model?" << '\n'
            << "1. SIR model (differential equations)" << '\n'
            << "2. SIR model (cellular automata)" << '\n';

  int choice_1 = input_choice(1, 2);

  switch (choice_1) {
    case 1: {
      epidemic_SIR::Population initial_population =
          epidemic_SIR::input_initial_population();
      epidemic_SIR::Parameter parameter = epidemic_SIR::input_parameter();

      epidemic_SIR::Virus covid{initial_population};

      int choice_2;

      do {
        int days = input_days();

        covid = epidemic_SIR::evolve(covid, parameter, days);
        std::vector<epidemic_SIR::Population> data = covid.get_data();

        int choice_3;

        do {
          std::cout << "Which output?" << '\n'
                    << "1. Table with values (standard output - double type)"
                    << '\n'
                    << "2. Table with approximate values (standard output - "
                       "int type)"
                    << '\n'
                    << "3. Graph" << '\n'
                    << "0. Exit" << '\n';

          choice_3 = input_choice(0, 3);

          switch (choice_3) {
            case 0: {
            } break;

            case 1: {
              epidemic_SIR::print(covid, parameter);
            } break;

            case 2: {
              epidemic_SIR::print_round_off(covid, parameter);
            } break;

            case 3: {
              std::cout << "Which graph?" << '\n'
                        << "1. Graph with S" << '\n'
                        << "2. Graph with I" << '\n'
                        << "3. Graph with R" << '\n'
                        << "5. Graph with S, I" << '\n'
                        << "6. Graph with I, R" << '\n'
                        << "7. Graph with S, R" << '\n'
                        << "8. Graph with S, I, R" << '\n';

              int choice_4 = input_choice(1, 8);

              auto const display_size = 600;

              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIR model");

              epidemic_SIR::Display_graph display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_axes();
              display.draw_axes_notches();
              display.draw_axes_values(data);
              display.draw_legend();

              if (choice_4 == 1 || choice_4 == 5 || choice_4 == 7 ||
                  choice_4 == 8) {
                display.draw_susceptible(data);
                display.draw_legend_susceptible();
              }

              if (choice_4 == 2 || choice_4 == 5 || choice_4 == 6 ||
                  choice_4 == 8) {
                display.draw_infectious(data);
                display.draw_legend_infectious();
              }

              if (choice_4 == 3 || choice_4 == 6 || choice_4 == 7 ||
                  choice_4 == 8) {
                display.draw_recovered(data);
                display.draw_legend_recovered();
              }

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;
          }

          std::cout << '\n';
        } while (choice_3 != 0);

        std::cout << "Do you want to simulate more days?" << '\n'
                  << "1. Yes" << '\n'
                  << "0. Exit" << '\n';

        choice_2 = input_choice(0, 1);
      } while (choice_2 != 0);
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

  std::cout << "Goodbye" << '\n';
}
