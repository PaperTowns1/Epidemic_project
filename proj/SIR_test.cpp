#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "SIR.hpp"
#include "doctest.h"

TEST_CASE("Testing SIR model (equations) 1") {
  epidemic_SIR::Population initial_population{9999, 1, 0}];
  epidemic_SIR::Parameter parameter{0.4, 0.04}];
  int days = 10

      std::vector<epidemic_SIR::Population>
          data{initial_population};

  epidemic_SIR::Virus Covid{initial_population};

  data_to_add = Covid.evolve(parameter, days);

  auto it = data.end();
  data.insert(it, data_to_add.begin(), data_to_add.end());

  CHECK(block.cell(1, 1) == life::Cell::Dead);
}

int main() {
  epidemic_SIR::Population initial_population{999, 1, 0}];
  epidemic_SIR::Parameter parameter = epidemic_SIR::input_parameter();

  std::cout << "Days: ";
  int days;
  std::cin >> days;
  std::cout << '\n';

  std::vector<epidemic_SIR::Population> data_to_add{};

  epidemic_SIR::print(data, parameter);
}
