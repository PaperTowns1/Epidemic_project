#ifndef EPIDEMIC_SIR_2_HPP
#define EPIDEMIC_SIR_2_HPP

#include <cassert>
#include <cmath>
#include <vector>

struct Population {
  double s;
  double i;
  double r;
};

class Virus {
 private:
  Population m_initial_population;
  double m_duration;

 public:
  Virus(Population const& initial_population, double duration)
      : m_initial_population{initial_population}, m_duration{duration} {}

  std::vector<Population> evolve(double beta, double gamma) {
    std::vector<Population> data{m_initial_population};
    Population population = data.back();

    double const N = population.s + population.i + population.r;

    for (int i = 0; i != m_duration; i++) {
      double const delta_i = beta * population.s / N * population.i;
      double const delta_r = gamma * population.i;

      population.s = population.s - delta_i;
      population.i = population.i + delta_i - delta_r;
      population.r = population.r + delta_r;

      //assert(N == population.s + population.i + population.r);
      assert(population.s >= 0 && population.i >= 0 && population.r >= 0);

      data.push_back(population);
    }
    return data;
  }
};

inline Population approx(Population const& population_to_round) {
  Population population = population_to_round;

  int s_int = std::floor(population.s);
  double s_fra = population.s - s_int;
  int i_int = std::floor(population.i);
  double i_fra = population.i - i_int;
  int r_int = std::floor(population.r);
  double r_fra = population.r - r_int;

  population.s = s_int;
  population.i = i_int;
  population.r = r_int;

  int const sum = std::round(s_fra + i_fra + r_fra);
  double const max = std::max({s_fra, i_fra, r_fra});
  double const min = std::min({s_fra, i_fra, r_fra});

  if (sum == 2) {
    if (min == r_fra) {
      population.s++;
      population.i++;
    } else if (min == i_fra) {
      population.s++;
      population.r++;
    } else {
      population.i++;
      population.r++;
    }
  } else if (sum == 1) {
    if (max == s_fra) {
      population.s++;
    } else if (max == i_fra) {
      population.i++;
    } else {
      population.r++;
    }
  }

  return population;
}

#endif