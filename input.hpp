#ifndef INPUT_HPP
#define INPUT_HPP

#include <cassert>
#include <cmath>
#include <exception>
#include <iostream>

#include "SIR.hpp"

int input_choice(int inf, int sup);

int input_days();

namespace epidemic_SIR {

Population input_initial_population();

Parameter input_parameters();

}  // namespace epidemic_SIR

#endif