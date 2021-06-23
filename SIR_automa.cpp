#include "SIR_automa.hpp"

namespace epidemic_SIR {

int World::get_side() const {
  return m_side;
}

std::vector<Cell> World::get_grid() const {
  return m_grid;
}

std::vector<Population> World::get_data() const {
  return m_data;
}

void World::update_grid(std::vector<Cell> const& grid_to_update) {
  m_grid = grid_to_update;
}

void World::add_data(Population const& data_to_add) {
  m_data.push_back(data_to_add);
}

int find_index(Point const& point, int side) {
  auto const i = (point.row + side) % side;
  auto const j = (point.column + side) % side;
  assert(i >= 0 && i < side);
  assert(j >= 0 && j < side);
  auto const index = i * side + j;
  assert(index >= 0 && index < side * side);
  return index;
}

int random_int_generator(int inf, int sup) {
  std::default_random_engine engine{std::random_device{}()};
  std::uniform_int_distribution<int> uniform_distribution{inf, sup};
  return uniform_distribution(engine);
}

double random_real_generator(double inf, double sup) {
  std::default_random_engine engine{std::random_device{}()};
  std::uniform_real_distribution<double> real_distribution{inf, sup};
  return real_distribution(engine);
}

bool probability(double probability) {
  double random_number = random_real_generator(0, 1);
  return (random_number < probability);
}

World generate(World const& world_to_generate, int number_of_people, Cell const& cell_type) {
  World world = world_to_generate;
  std::vector<Cell> grid = world.get_grid();
  int const side = world.get_side();

  for (int i = 0; i != number_of_people; i++) {
    Point point{0, 0};
    point.row = random_int_generator(0, side - 1);
    point.column = random_int_generator(0, side - 1);

    int index = find_index(point, side);

    if (grid[index] == Cell::Empty) {
      grid[index] = cell_type;
    } else {
      --i;
    }
  }

  world.update_grid(grid);
  return world;
}

World update_data(World const& world_to_update_data) {
  World world = world_to_update_data;
  std::vector<Cell> grid = world.get_grid();
  std::vector<Population> data = world.get_data();
  int const side = world.get_side();

  double susceptible_count = 0;
  double infectious_count = 0;
  double recovered_count = 0;

  for (int row = 0; row != side; ++row) {
    for (int column = 0; column != side; ++column) {
      Point const point{row, column};
      int const index = find_index(point, side);

      if (grid[index] == Cell::Susceptible) {
        susceptible_count++;
      }
      if (grid[index] == Cell::Infectious) {
        infectious_count++;
      }
      if (grid[index] == Cell::Recovered) {
        recovered_count++;
      }
    }
  }
  world.add_data({susceptible_count, infectious_count, recovered_count});
  return world;
}

Point find_direction(Point const& point_to_move) {
  int random_direction_x = random_int_generator(-1, 1);
  int random_direction_y = random_int_generator(-1, 1);
  Point point = point_to_move;

  point.row = point.row + random_direction_x;
  point.column = point.column + random_direction_y;

  return point;
}

World move(World const& world_to_move, double travel_probability) {
  World world = world_to_move;
  std::vector<Cell> grid = world.get_grid();
  int const side = world.get_side();

  for (int row = 0; row != side; ++row) {
    for (int column = 0; column != side; ++column) {
      Point const point{row, column};
      int const index = find_index(point, side);

      if (grid[index] != Cell::Empty && (probability(travel_probability) == true)) {
        Point const new_point = find_direction(point);
        int const new_index = find_index(new_point, side);

        if (grid[new_index] == Cell::Empty) {
          grid[new_index] = grid[index];
          grid[index] = Cell::Empty;
        }
      }
    }
  }

  world.update_grid(grid);
  return world;
}

int neighbours(World const& world_to_count, Point const& point, Cell const& cell_type) {
  World world = world_to_count;
  std::vector<Cell> grid = world.get_grid();
  int const side = world.get_side();
  int count = 0;
  int const index = find_index(point, side);

  if (grid[index] == cell_type) {
    --count;
  }

  for (int i = -1; i != 2; i++) {
    for (int j = -1; j != 2; j++) {
      int const new_index = find_index({point.row + i, point.column + j}, side);
      if (grid[new_index] == cell_type) {
        ++count;
      }
    }
  }

  return count;
}

World spread(World const& world_to_spread, double probability_to_spread) {
  World world = world_to_spread;
  std::vector<Cell> grid = world.get_grid();
  int const side = world.get_side();

  std::vector<Cell> next_grid = grid;

  for (int row = 0; row != side; row++) {
    for (int column = 0; column != side; column++) {
      Point const point{row, column};
      int const index = find_index(point, side);
      if (grid[index] == Cell::Susceptible) {
        int const c = neighbours(world, point, Cell::Infectious);

        if ((probability(probability_to_spread * c) == true) && c > 0) {
          next_grid[index] = Cell::Infectious;
        }
      }
    }
  }

  world.update_grid(next_grid);
  return world;
}

World recover(World const& world_to_recover, double probability_gamma) {
  World world = world_to_recover;
  std::vector<Cell> grid = world.get_grid();
  int const side = world.get_side();

  std::vector<Cell> next_grid = grid;

  for (int row = 0; row != side; row++) {
    for (int column = 0; column != side; column++) {
      Point const point{row, column};
      int const index = find_index(point, side);
      if (grid[index] == Cell::Infectious && (probability(probability_gamma / 24) == true)) {
        next_grid[index] = Cell::Recovered;
      }
    }
  }

  world.update_grid(next_grid);
  return world;
}

World evolve(World const& current, int duration, Parameter const& parameter_to_evolve) {
  Parameter parameter = parameter_to_evolve;
  World next = current;

  next = spread(next, parameter.beta);

  next = recover(next, parameter.gamma);

  if ((duration % 24) > 6 && (duration % 24) < 22) {
    next = move(next, 0.5);
  } else {
    next = move(next, 0.1);
  }

  next = update_data(next);
  return next;
}

}  // namespace epidemic_SIR
