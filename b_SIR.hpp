#ifndef B_SIR_HPP
#define B_SIR_HPP

#include <cassert>
#include <vector>

enum class Cell : char { E, S, I, R };

struct Person {
  Cell status;
  int x;
  int y;
  int time_infected;
};

class World {
  int m_side;
  std::vector<Person> m_grid;

 public:
  World(int n) : m_side(n), m_grid(m_side * m_side, {Cell::E, -1, -1, -1}) {}

  int side() const { return m_side; }

  std::vector<Person> grid() { return m_grid; }

  void put(std::vector<Person> const& grid_to_put) { m_grid = grid_to_put; }
};

inline int index(int r, int c, int side) {
  auto const i = (r + side) % side;
  auto const j = (c + side) % side;
  assert(i >= 0 && i < side && j >= 0 && j < side);
  auto const index = i * side + j;
  assert(index >= 0 && index < side * side);
  return index;
}

inline World generate(World const& empty_world) {
  World world = empty_world;
  int const N = world.side();
  std::vector<Person> grid = world.grid();

  std::default_random_engine engine{std::random_device{}()};
  std::uniform_int_distribution<int> range{0, N - 1};

  for (int i = 0; i != 499; ++i) {
    int r = range(engine);
    int c = range(engine);

    if (grid[index(r, c, N)].status == Cell::E) {
      grid[index(r, c, N)].status = Cell::S;
      grid[index(r, c, N)].x = r;
      grid[index(r, c, N)].y = c;
    } else {
      --i;
    }
  }

  int cont = 0;

  while (cont == 0) {
    int r = range(engine);
    int c = range(engine);
    if (grid[index(r, c, N)].status == Cell::E) {
      grid[index(r, c, N)].status = Cell::I;
      grid[index(r, c, N)].x = r;
      grid[index(r, c, N)].y = c;
      grid[index(r, c, N)].time_infected = 0;
      cont++;
    }
  }

  world.put(grid);
  return world;
}

inline bool probability(int prob) {
  std::default_random_engine engine{std::random_device{}()};
  std::uniform_int_distribution<int> range_probability{0, 100};

  int casual = range_probability(engine);

  if (casual > prob) {
    return false;
  } else {
    return true;
  }
}

inline Person direction(Person const& travel_person) {
  Person person = travel_person;

  std::default_random_engine engine{std::random_device{}()};
  std::uniform_int_distribution<int> range_direction{0, 7};

  int direction = range_direction(engine);

  if (direction == 0) {
    person.x = travel_person.x - 1;
    person.y = travel_person.y - 1;
  } else if (direction == 1) {
    person.x = travel_person.x;
    person.y = travel_person.y - 1;
  } else if (direction == 2) {
    person.x = travel_person.x + 1;
    person.y = travel_person.y - 1;
  } else if (direction == 3) {
    person.x = travel_person.x - 1;
    person.y = travel_person.y;
  } else if (direction == 4) {
    person.x = travel_person.x + 1;
    person.y = travel_person.y;
  } else if (direction == 5) {
    person.x = travel_person.x - 1;
    person.y = travel_person.y + 1;
  } else if (direction == 6) {
    person.x = travel_person.x;
    person.y = travel_person.y + 1;
  } else if (direction == 7) {
    person.x = travel_person.x + 1;
    person.y = travel_person.y + 1;
  }
  return person;
}

inline World move(World const& world_to_move, int travel_prob) {
  World current_world = world_to_move;

  int const N = current_world.side();
  std::vector<Person> current_grid = current_world.grid();

  for (int i = 0; i != N; ++i) {
    for (int j = 0; j != N; ++j) {
      if (current_grid[index(i, j, N)].status != Cell::E) {
        if (probability(travel_prob) == true) {
          Person person = direction(current_grid[index(i, j, N)]);
          if (current_grid[index(person.x, person.y, N)].status == Cell::E) {
            current_grid[index(person.x, person.y, N)] = person;

            current_grid[index(i, j, N)].status = Cell::E;
            current_grid[index(i, j, N)].x = -1;
            current_grid[index(i, j, N)].y = -1;
            current_grid[index(i, j, N)].time_infected = -1;
          } else {
            current_grid[index(i, j, N)] = current_grid[index(i, j, N)];
          }
        } else {
          current_grid[index(i, j, N)] = current_grid[index(i, j, N)];
        }
      }
    }
  }
  current_world.put(current_grid);
  return current_world;
}

inline int neighbours(World const& world_to_count, int r, int c,
                      Cell const& cell_type) {
  World current_world = world_to_count;

  int const N = current_world.side();
  std::vector<Person> current_grid = current_world.grid();

  int result = 0;

  if (current_grid[index(r, c, N)].status == cell_type) {
    --result;
  }

  for (int i = -1; i != 2; i++) {
    for (int j = -1; j != 2; j++) {
      if (current_grid[index(r + i, c + j, N)].status == cell_type) {
        ++result;
      }
    }
  }

  return result;
}

inline World spread(World const& world_to_spread) {
  World current_world = world_to_spread;

  int const N = current_world.side();
  std::vector<Person> current_grid = current_world.grid();

  World next_world = current_world;
  std::vector<Person> next_grid = next_world.grid();

  for (int i = 0; i != N; ++i) {
    for (int j = 0; j != N; ++j) {
      if (current_grid[index(i, j, N)].status == Cell::S) {
        int const c = neighbours(current_world, i, j, Cell::I);
        if (probability(c * 40) == true && c > 0) {
          next_grid[index(i, j, N)].status = Cell::I;
          next_grid[index(i, j, N)].x = i;
          next_grid[index(i, j, N)].y = j;
          next_grid[index(i, j, N)].time_infected = 0;
        }
      }
    }
  }

  next_world.put(next_grid);
  return next_world;
}

inline World recover(World const& world_to_recover) {
  World current_world = world_to_recover;

  int const N = current_world.side();
  std::vector<Person> current_grid = current_world.grid();

  World next_world = current_world;
  std::vector<Person> next_grid = next_world.grid();

  for (int i = 0; i != N; ++i) {
    for (int j = 0; j != N; ++j) {
      if (current_grid[index(i, j, N)].status == Cell::I) {
        next_grid[index(i, j, N)].time_infected++;
      }

      if (next_grid[index(i, j, N)].time_infected == 24 * (1 / 0.04)) {
        next_grid[index(i, j, N)].status = Cell::R;
      }
    }
  }

  next_world.put(next_grid);
  return next_world;
}

inline World evolve(World const& current, int duration) {
  World next = current;

  next = spread(next);
  next = recover(next);

  if ((duration % 24) > 6 && (duration % 24) < 22) {
    next = move(next, 70);
  } else {
    next = move(next, 5);
  }

  return next;
}

#endif
