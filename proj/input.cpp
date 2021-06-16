#include "input.hpp"

int input_choice(int inf, int sup) {
  double choice;

  std::cout << "Choice: ";
  std::cin >> choice;
  std::cout << '\n';

  if (std::cin.fail() || choice < inf || choice > sup ||
      choice - std::floor(choice) != 0) {
    throw std::runtime_error{"Invalid choice input"};
  }

  return static_cast<int>(choice);
}

int input_days() {
  double days;

  std::cout << "Days: ";
  std::cin >> days;
  std::cout << '\n';

  if (std::cin.fail() || days < 0 || days - std::floor(days) != 0) {
    throw std::runtime_error{"Invalid days input"};
  }

  return static_cast<int>(days);
}

namespace epidemic_SIR {

Population input_initial_population() {
  Population initial_population{};

  std::cout << "Susceptible: ";
  std::cin >> initial_population.s;
  std::cout << '\n';

  if (std::cin.fail() || initial_population.s < 0 ||
      initial_population.s - std::floor(initial_population.s) != 0) {
    throw std::runtime_error{"Invalid susceptible input"};
  }

  std::cout << "Infectious: ";
  std::cin >> initial_population.i;
  std::cout << '\n';

  if (std::cin.fail() || initial_population.i < 0 ||
      initial_population.i - std::floor(initial_population.i) != 0) {
    throw std::runtime_error{"Invalid infectious input"};
  }

  std::cout << "Recovered: ";
  std::cin >> initial_population.r;
  std::cout << '\n';

  if (std::cin.fail() || initial_population.r < 0 ||
      initial_population.r - std::floor(initial_population.r) != 0) {
    throw std::runtime_error{"Invalid recovered input"};
  }

  return initial_population;
}

Parameter input_parameter() {
  epidemic_SIR::Parameter parameter{};

  std::cout << "Beta: ";
  std::cin >> parameter.beta;
  std::cout << '\n';

  if (std::cin.fail() || parameter.beta < 0 || parameter.beta > 1) {
    throw std::runtime_error{"Invalid beta input"};
  }

  std::cout << "Gamma: ";
  std::cin >> parameter.gamma;
  std::cout << '\n';

  if (std::cin.fail() || parameter.gamma < 0 || parameter.gamma > 1) {
    throw std::runtime_error{"Invalid gamma input"};
  }

  if (parameter.beta / parameter.gamma < 1) {
    throw std::runtime_error{"R0 is less than 1, epidemic will not start"};
  }

  return parameter;
}

}  // namespace epidemic_SIR