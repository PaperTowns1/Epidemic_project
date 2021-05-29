#include "SIR.hpp"

namespace epidemic_SIR {

void Virus::add_data(Population const& data_to_add) {
  m_data.push_back(data_to_add);
}

std::vector<Population> Virus::get_data() { return m_data; }

Population input_initial_population() {
  Population initial_population{997, 3, 0};

  /*std::cout << "Susceptible: ";
  std::cin >> initial_population.s;

  if (initial_population.s < 0) {
    throw std::range_error{"S are less than 0"};
  }

  std::cout << "Infectious: ";
  std::cin >> initial_population.i;

  if (initial_population.i < 0) {
    throw std::range_error{"I are less than 0"};
  }

  std::cout << "Recovered: ";
  std::cin >> initial_population.r;

  if (initial_population.r < 0) {
    throw std::runtime_error{"R are less than 0"};
  }*/

  return initial_population;
}

Parameter input_parameter() {
  epidemic_SIR::Parameter parameter{0.4, 0.04};

  /*std::cout << "Beta: ";
  std::cin >> parameter.beta;

  if (parameter.beta < 0 || parameter.beta > 1) {
    throw std::range_error{"Beta is not between 0 and 1"};
  }

  std::cout << "Gamma: ";
  std::cin >> parameter.gamma;

  if (parameter.gamma < 0 || parameter.gamma > 1) {
    throw std::range_error{"Gamma is not between 0 and 1"};
  }

  if (parameter.beta / parameter.gamma < 1) {
    throw std::range_error{"R0 is less than 1, epidemic will not start"};
  }*/

  return parameter;
}

Virus evolve(Virus const& virus_to_evolve, Parameter const& parameter,
             double duration) {
  Virus virus = virus_to_evolve;
  std::vector<Population> data = virus.get_data();

  assert(!data.empty());

  std::vector<Population> data_to_add{};

  Population population = data.back();

  double const N = population.s + population.i + population.r;

  for (int i = 0; i != duration; ++i) {
    double const delta_i = parameter.beta * population.s / N * population.i;
    double const delta_r = parameter.gamma * population.i;

    assert(delta_i >= 0 && delta_r >= 0);

    population.s = population.s - delta_i;
    population.i = population.i + delta_i - delta_r;
    population.r = population.r + delta_r;

    assert(population.s >= 0 && population.i >= 0 && population.r >= 0);
    assert(std::round(N) ==
           std::round(population.s + population.i + population.r));

    virus.add_data(population);
  }

  return virus;
}

std::vector<Population> round(std::vector<Population> const& data_to_round) {
  std::vector<Population> data = data_to_round;
  int const length = static_cast<int>(data.size());

  for (int i = 1; i != length; ++i) {
    Population population = data[i];

    int s_int = std::floor(population.s);
    double s_fra = population.s - s_int;
    int i_int = std::floor(population.i);
    double i_fra = population.i - i_int;
    int r_int = std::floor(population.r);
    double r_fra = population.r - r_int;

    population.s = s_int;
    population.i = i_int;
    population.r = r_int;

    int sum = std::round(s_fra + i_fra + r_fra);

    if (sum == 1) {
      if (s_fra > 0.5) {
        population.s++;
      } else if (i_fra > 0.5) {
        population.i++;
      } else if (r_fra > 0.5) {
        population.r++;
      } else {
        population.s++;
      }
    }

    if (sum == 2) {
      if (s_fra > 0.5 && i_fra > 0.5) {
        population.s++;
        population.i++;
      } else if (s_fra > 0.5 && r_fra > 0.5) {
        population.s++;
        population.r++;
      } else {
        population.i++;
        population.r++;
      }
    }

    data[i] = population;

    /*if (i != 0) {
    assert(population.s >= 0 && population.i >= 0 && population.r >= 0);
      assert(data[i - 1].s >= data[i].s);
      assert(data[i - 1].r <= data[i].r);
    assert(N = somma s i r);

    }*/
  }

  return data;
}

void print(Virus const& virus_to_print, Parameter const& parameter) {
  Virus virus = virus_to_print;
  std::vector<Population> data = virus.get_data();

  int width = 8;

  std::cout << "R0: " << parameter.beta / parameter.gamma << '\n';

  std::cout << std::setw(width) << "Day" << '\t' << std::setw(width) << 'S'
            << '\t' << std::setw(width) << 'I' << '\t' << std::setw(width)
            << 'R' << '\t' << std::setw(width) << 'N' << '\t'
            << std::setw(width) << 'S' << '\t' << std::setw(width) << 'I'
            << '\t' << std::setw(width) << 'R' << '\t' << std::setw(width)
            << 'N' << '\n';

  int const size = static_cast<int>(data.size());

  std::vector<Population> round_data = round(data);

  for (int i = 0; i != size; ++i) {
    Population const popolation = data[i];
    Population const round_popolation = round_data[i];

    double const N = popolation.s + popolation.i + popolation.r;
    int const round_N =
        round_popolation.s + round_popolation.i + round_popolation.r;

    std::cout << std::setw(width) << i << '\t'             //
              << std::setw(width) << popolation.s << '\t'  //
              << std::setw(width) << popolation.i << '\t'  //
              << std::setw(width) << popolation.r << '\t'  //
              << std::setw(width) << N << '\t'             //
              << std::setw(width) << round_popolation.s << '\t'
              << std::setw(width) << round_popolation.i << '\t'
              << std::setw(width) << round_popolation.r << '\t'
              << std::setw(width) << round_N << '\n';
  }
}

}  // namespace epidemic_SIR
