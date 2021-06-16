#ifndef INPUT_HPP
#define INPUT_HPP

#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>

#include "SIR.hpp"

int input_choice(int inf, int sup);

int input_days();

namespace epidemic_SIR {

Population input_initial_population();

Parameter input_parameter();

}  // namespace epidemic_SIR

#endif