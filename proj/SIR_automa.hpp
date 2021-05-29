#ifndef SIR_AUTOMA_HPP
#define SIR_AUTOMA_HPP

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "SIR.hpp"

namespace epidemic_SIR {

enum class Cell : char { Empty, Susceptible, Infectious, Recovered };

struct Point {
  int row;
  int column;
};

class World {
  int m_side;
  std::vector<Cell> m_grid;
  std::vector<Population> m_data;

 public:
  World(int n) : m_side(n), m_grid(m_side * m_side, Cell::Empty), m_data() {}

  int get_side() const;

  std::vector<Cell> get_grid() const;

  std::vector<Population> get_data() const;

  void update_grid(std::vector<Cell> const& grid_to_update);

  void add_data(Population const& data_to_add);
};

int find_index(Point const& point, int side);

int random_int_generator(int inf, int sup);

double random_real_generator(double inf, double sup);

bool probability(double probability);

World generate(World const& world_to_generate, int number_of_people,
               Cell const& cell_type);

World update_data(World const& world_to_update_data);

Point find_direction(Point const& point_to_move);

World move(World const& world_to_move, double travel_probability);

int neighbours(World const& world_to_count, Point const& point,
               Cell const& cell_type);

World spread(World const& world_to_spread);

World recover(World const& world_to_spread);

World evolve(World const& current, int duration);

}  // namespace epidemic_SIR

#endif