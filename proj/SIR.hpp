#ifndef SIR_HPP
#define SIR_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

namespace epidemic_SIR {

struct Population {
  double s;
  double i;
  double r;
};

struct Parameter {
  double beta;
  double gamma;
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

  std::vector<Population> get_data();

  void add_data(Population const& data_to_add);
};

Virus evolve(Virus const& virus_to_evolve, Parameter const& parameter,
             double duration);

void print(Virus const& virus_to_print, Parameter const& parameter);

std::vector<Population> round_off(std::vector<Population> const& data_to_round_off);

void print_round_off(Virus const& virus_to_print, Parameter const& parameter);

}  // namespace epidemic_SIR

#endif