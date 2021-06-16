#include "SIR.hpp"

namespace epidemic_SIR {

void Virus::add_data(Population const& data_to_add) {
  m_data.push_back(data_to_add);
}

std::vector<Population> Virus::get_data() { return m_data; }

Virus evolve(Virus const& virus_to_evolve, Parameter const& parameter,
             double duration) {
  Virus virus = virus_to_evolve;
  std::vector<Population> data = virus.get_data();

  assert(!data.empty());

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

std::vector<Population> round_off(std::vector<Population> const& data_to_round_off) {
  std::vector<Population> data = data_to_round_off;
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

    while (sum > 0) {
      if (s_fra < 0.5) {
        i_fra = i_fra + s_fra;
        s_fra = 0;
      } else {
        i_fra -= 1 - s_fra;
        s_fra = 1;
      }

      if (i_fra < 0.5) {
        r_fra = r_fra + i_fra;
        i_fra = 0;
      } else {
        r_fra -= 1 - i_fra;
        i_fra = 1;
      }

      --sum;
    }

    population.s += std::round(s_fra);
    population.i += std::round(i_fra);
    population.r += std::round(r_fra);

    data[i] = population;

    assert(population.s >= 0 && population.i >= 0 && population.r >= 0);
    int const N = data[0].s + data[0].i + data[0].r;
    if (i != 0) {
      assert(data[i - 1].s >= data[i].s);
      assert(data[i - 1].r <= data[i].r);
      assert(data[i].s + data[i].i + data[i].r == N);
    }
  }

  return data;
}

void print(Virus const& virus_to_print, Parameter const& parameter) {
  Virus virus = virus_to_print;
  std::vector<Population> data = virus.get_data();

  int const width = 8;

  std::cout << "R0: " << parameter.beta / parameter.gamma << '\n';

  std::cout << std::setw(width) << "Day" << '\t'  //
            << std::setw(width) << 'S' << '\t'    //
            << std::setw(width) << 'I' << '\t'    //
            << std::setw(width) << 'R' << '\t'    //
            << std::setw(width) << 'N' << '\n';

  int const size = static_cast<int>(data.size());

  for (int i = 0; i != size; ++i) {
    Population const population = data[i];

    double const N = population.s + population.i + population.r;

    std::cout << std::setw(width) << i << '\t'             //
              << std::setw(width) << population.s << '\t'  //
              << std::setw(width) << population.i << '\t'  //
              << std::setw(width) << population.r << '\t'  //
              << std::setw(width) << N << '\n';
  }
}

void print_round_off(Virus const& virus_to_print,
                       Parameter const& parameter) {
  Virus virus = virus_to_print;
  std::vector<Population> data = virus.get_data();

  int const width = 8;

  std::cout << "R0: " << parameter.beta / parameter.gamma << '\n' << '\n';

  std::cout << std::setw(width) << "Day" << '\t'  //
            << std::setw(width) << 'S' << '\t'    //
            << std::setw(width) << 'I' << '\t'    //
            << std::setw(width) << 'R' << '\t'    //
            << std::setw(width) << 'N' << '\n';

  int const size = static_cast<int>(data.size());

  std::vector<Population> data_round = round_off(data);

  for (int i = 0; i != size; ++i) {
    Population const population = data_round[i];

    double const N = population.s + population.i + population.r;

    std::cout << std::setw(width) << i << '\t'             //
              << std::setw(width) << population.s << '\t'  //
              << std::setw(width) << population.i << '\t'  //
              << std::setw(width) << population.r << '\t'  //
              << std::setw(width) << N << '\n';
  }
}

}  // namespace epidemic_SIR
