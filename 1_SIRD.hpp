#ifndef SIRD_HPP
#define SIRD_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

namespace epidemic_SIRD {

struct Population {
  double s;
  double i;
  double r;
  double d;
};

struct Parameter {
  double beta;
  double gamma;
  double mu;
};

class Virus {
 private:
  Population m_initial_population;
  std::vector<Population> m_data;

 public:
  Virus(Population const& initial_population)
      : m_initial_population{initial_population} {
    m_data.push_back(m_initial_population);
  }

  std::vector<Population> evolve(Parameter const& parameter, double duration) {
    assert(!m_data.empty());

    std::vector<Population> data_to_add{};

    Population population = m_data.back();

    int const N = population.s + population.i + population.r;

    for (int i = 0; i != duration; ++i) {
      double const delta_i = parameter.beta * population.s / N * population.i;
      double const delta_r =
          parameter.gamma * (1 - parameter.mu) * population.i;
      double const delta_d = parameter.gamma * parameter.mu * population.i;

      assert(delta_i > 0 && delta_r > 0 && delta_d > 0);

      population.s = population.s - delta_i;
      population.i = population.i + delta_i - delta_r - delta_d;
      population.r = population.r + delta_r;
      population.d = population.d + delta_d;

      assert(population.s >= 0 && population.i >= 0 && population.r >= 0 &&
             population.d >= 0);
      // assert(N == std::round(population.s + population.i + population.r +
      // population.d));

      data_to_add.push_back(population);
    }

    auto it = m_data.end();
    m_data.insert(it, data_to_add.begin(), data_to_add.end());

    return data_to_add;
  }
};

inline void print(std::vector<Population> const& data) {
  int a = 8;
  std::cout << std::setw(a) << "Day" << '\t' << std::setw(a) << 'S' << '\t'
            << std::setw(a) << 'I' << '\t' << std::setw(a) << 'R' << '\t'
            << std::setw(a) << 'D' << '\t' << std::setw(a) << 'N' << '\n';

  for (int i = 0; i != static_cast<int>(data.size()); ++i) {
    std::cout << std::setw(a) << i << '\t' << std::setw(a) << data[i].s << '\t'
              << std::setw(a) << data[i].i << '\t' << std::setw(a) << data[i].r
              << '\t' << std::setw(a) << data[i].d << '\t' << std::setw(a)
              << data[i].s + data[i].i + data[i].r + data[i].d << '\n';
  }
}

}  // namespace epidemic_SIRD

#endif