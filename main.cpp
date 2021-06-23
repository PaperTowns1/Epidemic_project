#include "SIR.hpp"
#include "SIR_automa.hpp"
#include "SIR_automa_display.hpp"
#include "SIR_display.hpp"
#include "input.hpp"

int main() {
  try {
    std::cout << "Hi, which epidemiological model?" << '\n'
              << "1. SIR model (differential equations)" << '\n'
              << "2. SIR model (automata cellular)" << '\n';

    auto choice_1 = input_choice(1, 2);

    switch (choice_1) {
      case 1: {
        auto initial_population = epidemic_SIR::input_initial_population();
        auto parameter = epidemic_SIR::input_parameters();

        epidemic_SIR::Virus covid{initial_population};

        int choice_2 = 0;

        do {
          auto days = input_days();

          int choice_3 = 0;

          covid = epidemic_SIR::evolve(covid, parameter, days);
          auto data = covid.get_data();

          do {
            std::cout << "Which output?" << '\n'
                      << "1. Table with values (standard output)" << '\n'
                      << "2. Table with round off values (standard output)" << '\n'
                      << "3. Dinamic graph (evolving form day 0)" << '\n'
                      << "4. Static graph (already simulated all days)" << '\n'
                      << "0. Exit" << '\n';

            choice_3 = input_choice(0, 4);

            switch (choice_3) {
              case 0: {
              } break;

              case 1: {
                epidemic_SIR::print(data, parameter);
              } break;

              case 2: {
                epidemic_SIR::print_round_off(data, parameter);
              } break;

              case 3: {
                auto const display_side = 600;

                std::cout << "Which graph?" << '\n'
                          << "1. Graph with S" << '\n'
                          << "2. Graph with I" << '\n'
                          << "3. Graph with R" << '\n'
                          << "4. Graph with S, I" << '\n'
                          << "5. Graph with I, R" << '\n'
                          << "6. Graph with S, R" << '\n'
                          << "7. Graph with S, I, R" << '\n';

                auto choice_4 = input_choice(1, 7);

                sf::RenderWindow window(sf::VideoMode(display_side, display_side),
                                        "SIR model (differential equations)");

                window.setFramerateLimit(10);

                epidemic_SIR::Display_graph display{window, display_side};

                int duration = 0;
                bool running = true;

                std::vector<epidemic_SIR::Population> temporary_data{};

                while (running) {
                  window.clear(sf::Color::Black);

                  if (duration < static_cast<int>(data.size())) {
                    temporary_data.push_back(data[duration]);
                  }

                  display.draw_axes();
                  display.draw_axes_notches();
                  display.draw_axes_values(temporary_data);
                  display.draw_legend();

                  if (choice_4 == 1 || choice_4 == 4 || choice_4 == 6 || choice_4 == 7) {
                    display.draw_susceptible(temporary_data);
                    display.draw_legend_susceptible();
                  }

                  if (choice_4 == 2 || choice_4 == 4 || choice_4 == 5 || choice_4 == 7) {
                    display.draw_infectious(temporary_data);
                    display.draw_legend_infectious();
                  }

                  if (choice_4 == 3 || choice_4 == 5 || choice_4 == 6 || choice_4 == 7) {
                    display.draw_recovered(temporary_data);
                    display.draw_legend_recovered();
                  }

                  window.display();

                  sf::Event event;
                  while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed) {
                      running = !running;
                    }
                  }

                  ++duration;
                }

                window.close();

              } break;

              case 4: {
                auto const display_side = 600;

                std::cout << "Which graph?" << '\n'
                          << "1. Graph with S" << '\n'
                          << "2. Graph with I" << '\n'
                          << "3. Graph with R" << '\n'
                          << "4. Graph with S, I" << '\n'
                          << "5. Graph with I, R" << '\n'
                          << "6. Graph with S, R" << '\n'
                          << "7. Graph with S, I, R" << '\n';

                auto choice_4 = input_choice(1, 7);

                sf::RenderWindow window(sf::VideoMode(display_side, display_side),
                                        "SIR model (differential equations)");

                epidemic_SIR::Display_graph display{window, display_side};

                window.clear(sf::Color::Black);

                display.draw_axes();
                display.draw_axes_notches();
                display.draw_axes_values(data);
                display.draw_legend();

                if (choice_4 == 1 || choice_4 == 4 || choice_4 == 6 || choice_4 == 7) {
                  display.draw_susceptible(data);
                  display.draw_legend_susceptible();
                }

                if (choice_4 == 2 || choice_4 == 4 || choice_4 == 5 || choice_4 == 7) {
                  display.draw_infectious(data);
                  display.draw_legend_infectious();
                }

                if (choice_4 == 3 || choice_4 == 5 || choice_4 == 6 || choice_4 == 7) {
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
        std::cout << "Which grid?" << '\n'
                  << "1. 120 x 120 with 5 x 5 cells" << '\n'
                  << "2. 60 x 60 with 10 x 10 cell" << '\n'
                  << "3. 30 x 30 with 20 x 20 cell" << '\n';

        auto choice_5 = input_choice(1, 3);
        int grid_side = 0;

        if (choice_5 == 1) {
          grid_side = 120;
        }

        if (choice_5 == 2) {
          grid_side = 60;
        }

        if (choice_5 == 3) {
          grid_side = 30;
        }

        std::cout << "Which speed?" << '\n'
                  << "1. 5 frame per rate" << '\n'
                  << "2. 10 frame per rate" << '\n'
                  << "3. 50 frame per rate" << '\n'
                  << "4. 100 frame per rate" << '\n';

        auto choice_6 = input_choice(1, 4);
        int frame_per_rate = 0;

        if (choice_6 == 1) {
          frame_per_rate = 5;
        }

        if (choice_6 == 2) {
          frame_per_rate = 10;
        }

        if (choice_6 == 3) {
          frame_per_rate = 50;
        }

        if (choice_6 == 4) {
          frame_per_rate = 100;
        }

        int const display_side = 600;

        auto initial_population = epidemic_SIR::input_initial_population();
        auto parameter = epidemic_SIR::input_parameters();

        sf::RenderWindow window{sf::VideoMode(display_side * 2, display_side),
                                "SIR model (cellular automata)"};

        window.setFramerateLimit(frame_per_rate);

        epidemic_SIR::Display_automa display{window, display_side};
        epidemic_SIR::World world(grid_side);

        world = generate(world, initial_population.s, epidemic_SIR::Cell::Susceptible);
        world = generate(world, initial_population.i, epidemic_SIR::Cell::Infectious);
        world = generate(world, initial_population.r, epidemic_SIR::Cell::Recovered);

        world = update_data(world);

        int duration = 0;
        bool running = true;

        while (running) {
          window.clear(sf::Color::Black);

          world = evolve(world, duration, parameter);
          auto data = world.get_data();

          display.draw_grid(world);
          display.draw_legend(data);
          display.draw_axes();
          display.draw_axes_notches();
          display.draw_axes_values(data);

          display.draw_graph(data);
          ++duration;

          window.display();

          sf::Event event;
          while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
              running = !running;
            }
          }

          ++duration;
        }

        window.close();
      } break;
    }

    std::cout << "Goodbye" << '\n';
  } catch (std::exception const& exception) {
    std::cerr << exception.what() << '\n';
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
