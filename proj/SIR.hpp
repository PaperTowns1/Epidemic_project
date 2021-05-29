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

Population input_initial_population();

Parameter input_parameter();

Virus evolve(Virus const& virus_to_evolve, Parameter const& parameter,
             double duration);

std::vector<Population> round(std::vector<Population> const& data_to_round);

void print(Virus const& virus_to_print, Parameter const& parameter);

}  // namespace epidemic_SIR

#endif