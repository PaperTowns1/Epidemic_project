#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

#include "SIR.hpp"
#include "SIRD.hpp"
#include "display.hpp"

int main() {
  auto const display_size{600};

  std::cout << "Which epidemiological model?" << '\n'
            << "1. SIR model" << '\n'
            << "2. SIRD model" << '\n';

  int choice;
  std::cout << "Choice: ";
  std::cin >> choice;

  switch (choice) {
    case 1: {
      epidemic_SIR::Population initial_population{997, 3, 0};
      epidemic_SIR::Parameter parameter{0.4, 0.04};

      /*std::cout << "S: ";
      std::cin >> initial_population.s;

      if (initial_population.s < 0) {
        throw std::runtime_error{"S are less than 0"};
      }

      std::cout << "I: ";
      std::cin >> initial_population.i;

      if (initial_population.i < 0) {
        throw std::runtime_error{"I are less than 0"};
      }

      std::cout << "R: ";
      std::cin >> initial_population.r;

      if (initial_population.r < 0) {
        throw std::runtime_error{"R are less than 0"};
      }

      std::cout << "Beta: ";
      std::cin >> parameter.beta;

      if (parameter.beta < 0 || parameter.beta > 1) {
        throw std::runtime_error{"Beta is not between 0 and 1"};
      }

      std::cout << "Gamma: ";
      std::cin >> parameter.gamma;

      if (parameter.gamma < 0 || parameter.gamma > 1) {
        throw std::runtime_error{"Gamma is not between 0 and 1"};
      }

      if (parameter.beta / parameter.gamma < 1) {
        throw std::runtime_error{"R0 is less than 1"};
      }*/

      std::vector<epidemic_SIR::Population> data{initial_population};
      epidemic_SIR::Virus Covid{initial_population};

      std::cout << "Days: ";
      int days;
      std::cin >> days;

      do {
        if (days < 0) {
          throw std::runtime_error{"Days are less than 0"};
        }

        std::vector<epidemic_SIR::Population> data_to_add{};

        data_to_add = Covid.evolve(parameter, days);

        auto it = data.end();
        data.insert(it, data_to_add.begin(), data_to_add.end());

        std::cout << "Which output?" << '\n'
                  << "1. Table with values (with cout)" << '\n'
                  << "2. Table with values (on file)" << '\n'
                  << "3. Plot only S" << '\n'
                  << "4. Plot only I" << '\n'
                  << "5. Plot only R" << '\n'
                  << "6. Plot all S, I and R" << '\n';

        int choice_2;
        std::cin >> choice_2;

        do {
          switch (choice_2) {
            case 1: {
              epidemic_SIR::print(data);

            } break;

            case 2: {
              // epidemic_SIR::print_file(data);

            } break;

            case 3: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_susceptible(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 4: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_infectious(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 5: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_recovered(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 6: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_susceptible(data);
              display.draw_infectious(data);
              display.draw_recovered(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            default: {
              throw std::runtime_error{"Invalid input"};
            } break;
          }

          std::cout << "To exit press 0, otherwise choose output: " << '\n';
          std::cin >> choice_2;

        } while (choice_2 != 0);

        std::cout << "To exit press 0, otherwise insert more days: " << '\n';
        std::cin >> days;

      } while (days != 0);

    } break;

    case 2: {
      epidemic_SIRD::Population initial_population{997, 3, 0, 0};
      epidemic_SIRD::Parameter parameter{0.4, 0.04, 0.02};

      /*std::cout << "S: ";
      std::cin >> initial_population.s;

      if (initial_population.s < 0) {
        throw std::runtime_error{"S are less than 0"};
      }

      std::cout << "E: ";
      std::cin >> initial_population.e;

      if (initial_population.e < 0) {
        throw std::runtime_error{"E are less than 0"};
      }

      std::cout << "I: ";
      std::cin >> initial_population.i;

      if (initial_population.i < 0) {
        throw std::runtime_error{"I are less than 0"};
      }

      std::cout << "R: ";
      std::cin >> initial_population.r;

      if (initial_population.r < 0) {
        throw std::runtime_error{"R are less than 0"};
      }

      std::cout << "Beta: ";
      std::cin >> parameter.beta;

      if (parameter.beta < 0 || parameter.beta > 1) {
        throw std::runtime_error{"Beta is not between 0 and 1"};
      }

      std::cout << "Gamma: ";
      std::cin >> parameter.gamma;

      if (parameter.gamma < 0 || parameter.gamma > 1) {
        throw std::runtime_error{"Gamma is not between 0 and 1"};
      }

      std::cout << "Mu: ";
      std::cin >> parameter.mu;

      if (parameter.mu < 0 || parameter.mu > 1) {
        throw std::runtime_error{"Mu is not between 0 and 1"};
      }

      if (parameter.beta / (parameter.gamma + parameter.mu) < 1) {
        throw std::runtime_error{"R0 is less than 1"};
      }*/

      std::vector<epidemic_SIRD::Population> data{initial_population};
      epidemic_SIRD::Virus Covid{initial_population};

      std::cout << "Days: ";
      int days;
      std::cin >> days;

      do {
        if (days < 0) {
          throw std::runtime_error{"Days are less than 0"};
        }

        std::vector<epidemic_SIRD::Population> data_to_add{};

        data_to_add = Covid.evolve(parameter, days);

        auto it = data.end();
        data.insert(it, data_to_add.begin(), data_to_add.end());

        std::cout << "Which output?" << '\n'
                  << "1. Table with values (with cout)" << '\n'
                  << "2. Table with values (on file)" << '\n'
                  << "3. Plot only S" << '\n'
                  << "4. Plot only I" << '\n'
                  << "5. Plot only R" << '\n'
                  << "6. Plot only D" << '\n'
                  << "7. Plot all S, I, R and D" << '\n';

        int choice_2;
        std::cin >> choice_2;

        do {
          switch (choice_2) {
            case 1: {
              epidemic_SIRD::print(data);

            } break;

            case 2: {
              // epidemic_SIR::print_file(data);

            } break;

            case 3: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_susceptible(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 4: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_infectious(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 5: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_recovered(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 6: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_deceased(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            case 7: {
              sf::RenderWindow window(sf::VideoMode(display_size, display_size),
                                      "SIRD");
              Display display{window, display_size};

              window.clear(sf::Color::White);

              display.draw_canvas();
              display.draw_more(data);
              display.draw_susceptible(data);
              display.draw_infectious(data);
              display.draw_recovered(data);

              window.display();

              sf::Event event;
              while (window.waitEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
              }

            } break;

            default: {
              throw std::runtime_error{"Invalid input"};
            } break;
          }

          std::cout << "To exit press 0, otherwise choose output: " << '\n';
          std::cin >> choice_2;

        } while (choice_2 != 0);

        std::cout << "To exit press 0, otherwise insert more days: " << '\n';
        std::cin >> days;

      } while (days != 0);

    } break;

    default:
      throw std::runtime_error{"Invalid input"};
      break;
  }

  return 0;
}
