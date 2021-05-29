#include "SIR_automa_display.hpp"

namespace epidemic_SIR {

void Display_automa::draw_grid(World const& world_to_draw) {
  World world = world_to_draw;
  int const side = world.get_side();
  std::vector<Cell> grid = world.get_grid();

  double const world_border = 640 / side;

  sf::Vector2f const cell_size{sf::Vector2f(world_border, world_border)};

  sf::RectangleShape Susceptible_cell(cell_size);
  Susceptible_cell.setFillColor(sf::Color::Blue);
  Susceptible_cell.setOutlineThickness(1.f);
  Susceptible_cell.setOutlineColor(sf::Color::White);

  sf::RectangleShape Infectious_cell(cell_size);
  Infectious_cell.setFillColor(sf::Color::Red);
  Infectious_cell.setOutlineThickness(1.f);
  Infectious_cell.setOutlineColor(sf::Color::White);

  sf::RectangleShape Recovered_cell(cell_size);
  Recovered_cell.setFillColor(sf::Color::Green);
  Recovered_cell.setOutlineThickness(1.f);
  Recovered_cell.setOutlineColor(sf::Color::White);

  for (int row = 0; row != side; ++row) {
    for (int column = 0; column != side; ++column) {
      int const index = find_index({row, column}, side);

      if (grid[index] == Cell::Susceptible) {
        Susceptible_cell.setPosition(row * cell_size.y, column * cell_size.x);
        m_window.draw(Susceptible_cell);
      }

      if (grid[index] == Cell::Infectious) {
        Infectious_cell.setPosition(row * cell_size.y, column * cell_size.x);
        m_window.draw(Infectious_cell);
      }

      if (grid[index] == Cell::Recovered) {
        Recovered_cell.setPosition(row * cell_size.y, column * cell_size.x);
        m_window.draw(Recovered_cell);
      }
    }
  }
}

void Display_automa::draw_legend(World const& world_to_draw, int duration) {
  sf::VertexArray separator(sf::LineStrip, 2);

  separator[0].position = sf::Vector2f(640, 0);
  separator[1].position = sf::Vector2f(640, 640);

  separator[0].color = sf::Color::Black;
  separator[1].color = sf::Color::Black;

  m_window.draw(separator);

  sf::VertexArray legend(sf::LineStrip, 5);

  legend[0].position = sf::Vector2f(650, 10);
  legend[1].position = sf::Vector2f(650, 170);
  legend[2].position = sf::Vector2f(1030, 170);
  legend[3].position = sf::Vector2f(1030, 10);
  legend[4].position = sf::Vector2f(650, 10);

  legend[0].color = sf::Color::Black;
  legend[1].color = sf::Color::Black;
  legend[2].color = sf::Color::Black;
  legend[3].color = sf::Color::Black;
  legend[4].color = sf::Color::Black;

  m_window.draw(legend);

  sf::Text susceptible, infectious, recovered, n;

  susceptible.setFont(m_font);
  infectious.setFont(m_font);
  recovered.setFont(m_font);
  n.setFont(m_font);
  susceptible.setString("S");
  infectious.setString("I");
  recovered.setString("R");
  n.setString("N");
  susceptible.setCharacterSize(20);
  infectious.setCharacterSize(20);
  recovered.setCharacterSize(20);
  n.setCharacterSize(20);
  susceptible.setFillColor(sf::Color::Black);
  infectious.setFillColor(sf::Color::Black);
  recovered.setFillColor(sf::Color::Black);
  n.setFillColor(sf::Color::Black);

  susceptible.setPosition(sf::Vector2f(660, 30));
  infectious.setPosition(sf::Vector2f(660, 60));
  recovered.setPosition(sf::Vector2f(660, 90));
  n.setPosition(sf::Vector2f(660, 120));

  m_window.draw(susceptible);
  m_window.draw(infectious);
  m_window.draw(recovered);
  m_window.draw(n);

  World world = world_to_draw;
  std::vector<Population> data = world.get_data();
  int size = data.size() - 1;

  sf::Text s_value, i_value, r_value, n_value;

  s_value.setFont(m_font);
  i_value.setFont(m_font);
  r_value.setFont(m_font);
  n_value.setFont(m_font);

  std::string s = std::to_string(data[size].s);
  std::string i = std::to_string(data[size].i);
  std::string r = std::to_string(data[size].r);
  std::string num = std::to_string(data[size].s + data[size].i + data[size].r);

  s_value.setString(s);
  i_value.setString(i);
  r_value.setString(r);
  n_value.setString(num);

  s_value.setCharacterSize(20);
  i_value.setCharacterSize(20);
  r_value.setCharacterSize(20);
  n_value.setCharacterSize(20);
  s_value.setFillColor(sf::Color::Black);
  i_value.setFillColor(sf::Color::Black);
  r_value.setFillColor(sf::Color::Black);
  n_value.setFillColor(sf::Color::Black);

  s_value.setPosition(sf::Vector2f(700, 30));
  i_value.setPosition(sf::Vector2f(700, 60));
  r_value.setPosition(sf::Vector2f(700, 90));
  n_value.setPosition(sf::Vector2f(700, 120));

  m_window.draw(s_value);
  m_window.draw(i_value);
  m_window.draw(r_value);
  m_window.draw(n_value);

  sf::Text days, hours;

  days.setFont(m_font);
  hours.setFont(m_font);

  days.setString("Days");
  hours.setString("Hours");

  days.setCharacterSize(20);
  hours.setCharacterSize(20);

  days.setFillColor(sf::Color::Black);
  hours.setFillColor(sf::Color::Black);

  days.setPosition(sf::Vector2f(750, 30));
  hours.setPosition(sf::Vector2f(750, 60));

  m_window.draw(days);
  m_window.draw(hours);

  sf::Text days_value, hours_value;

  days_value.setFont(m_font);
  hours_value.setFont(m_font);

  int da = std::floor(duration / 24);
  int ho = duration % 24;

  std::string d = std::to_string(da);
  std::string h = std::to_string(ho);

  days_value.setString(d);
  hours_value.setString(h);

  days_value.setCharacterSize(20);
  hours_value.setCharacterSize(20);

  days_value.setFillColor(sf::Color::Black);
  hours_value.setFillColor(sf::Color::Black);

  days_value.setPosition(sf::Vector2f(850, 30));
  hours_value.setPosition(sf::Vector2f(850, 60));

  m_window.draw(days_value);
  m_window.draw(hours_value);

  // axis

  sf::VertexArray x_axis(sf::Lines, 2);

  x_axis[0].position = sf::Vector2f(700, 600);
  x_axis[1].position = sf::Vector2f(1200, 600);

  x_axis[0].color = sf::Color::Black;
  x_axis[1].color = sf::Color::Black;

  m_window.draw(x_axis);

  sf::VertexArray y_axis(sf::Lines, 2);

  y_axis[0].position = sf::Vector2f(700, 200);
  y_axis[1].position = sf::Vector2f(700, 600);

  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;

  m_window.draw(y_axis);

  sf::VertexArray x_axis_notches(sf::Lines, 22);

  int const distance_notches = 500 / 20;

  for (int i = 0; i != 22; i = i + 2) {
    x_axis_notches[i].position =
        sf::Vector2f(700 + distance_notches * i, 600 - 4);
    x_axis_notches[i + 1].position =
        sf::Vector2f(700 + distance_notches * i, 600 + 4);
  }

  for (int i = 0; i != 22; ++i) {
    x_axis_notches[i].color = sf::Color::Black;
  }

  m_window.draw(x_axis_notches);

  sf::VertexArray y_axis_notches(sf::Lines, 22);

  int const distance_notches_ = 400 / 20;

  for (int i = 0; i != 22; i = i + 2) {
    y_axis_notches[i].position =
        sf::Vector2f(700 - 4, 200 + i * distance_notches_);
    y_axis_notches[i + 1].position =
        sf::Vector2f(700 + 4, 200 + i * distance_notches_);
  }

  for (int i = 0; i != 22; ++i) {
    y_axis_notches[i].color = sf::Color::Black;
  }

  m_window.draw(y_axis_notches);

  sf::Text x_axis_name;

  x_axis_name.setFont(m_font);
  x_axis_name.setString("Hours");
  x_axis_name.setCharacterSize(15);
  x_axis_name.setFillColor(sf::Color::Black);

  x_axis_name.setPosition(sf::Vector2f(1215, 585));

  m_window.draw(x_axis_name);

  sf::Text y_axis_name;

  y_axis_name.setFont(m_font);
  y_axis_name.setString("Population");
  y_axis_name.setCharacterSize(15);
  y_axis_name.setFillColor(sf::Color::Black);

  y_axis_name.setPosition(sf::Vector2f(700, 180));

  m_window.draw(y_axis_name);

  if ((size - 1) >= 0) {
    plot.push_back({data[size - 1].s, data[size - 1].i, data[size - 1].r});

    sf::VertexArray points_s(sf::LineStrip, duration - 1);
    sf::VertexArray points_i(sf::LineStrip, duration - 1);
    sf::VertexArray points_r(sf::LineStrip, duration - 1);

    int const N = plot[0].s + plot[0].i + plot[0].r;
    int const length = static_cast<int>(plot.size()) - 1;

    for (int i = 0; i != length; ++i) {
      points_s[i].position =
          sf::Vector2f(i * 500 / duration + 700, plot[i].s * 400 / N + 40);
      points_i[i].position =
          sf::Vector2f(i * 500 / duration + 700, plot[i].i * 400 / N + 40);
      points_r[i].position =
          sf::Vector2f(i * 500 / duration + 700, plot[i].r * 400 / N + 40);
    }

    for (int i = 0; i != length; ++i) {
      points_s[i].color = sf::Color::Blue;
      points_i[i].color = sf::Color::Red;
      points_r[i].color = sf::Color::Green;
    }

    m_window.draw(points_s, transform());
    m_window.draw(points_i, transform());
    m_window.draw(points_r, transform());

    for (int i = 0; i != 10; ++i) {
      sf::Text x_axis_value;
      x_axis_value.setFont(m_font);

      long int a = duration / 10 * (i + 1);

      int b = count_digits(a) - 1;

      std::string u = std::to_string(a);
      char digit0 = u[0];
      char digit1 = u[1];

      std::string c{};
      c.push_back(digit0);
      c = c + '.';
      c.push_back(digit1);

      c = c + "*10^" + std::to_string(b);

      x_axis_value.setString(c);

      x_axis_value.setCharacterSize(10);
      x_axis_value.setFillColor(sf::Color::Black);

      x_axis_value.setPosition(sf::Vector2f(50 * (i + 1) + 700 - 15, 610));

      m_window.draw(x_axis_value);
    }

    for (int i = 0; i != 10; ++i) {
      sf::Text y_axis_value;
      y_axis_value.setFont(m_font);

      long int a = N / 10 * (i + 1);

      int b = count_digits(a) - 1;

      std::string u = std::to_string(a);
      char digit0 = u[0];
      char digit1 = u[1];

      std::string c{};
      c.push_back(digit0);
      c = c + '.';
      c.push_back(digit1);

      c = c + "*10^" + std::to_string(b);

      y_axis_value.setString(c);

      y_axis_value.setCharacterSize(10);
      y_axis_value.setFillColor(sf::Color::Black);

      y_axis_value.setPosition(sf::Vector2f(650, 40 * (i + 1) + 160));

      m_window.draw(y_axis_value);
    }
  }
}

int Display_automa::count_digits(long int n) {
  int num = 0;
  while (n != 0) {
    n = n / 10;
    num++;
  }
  return num;
}

sf::Transform Display_automa::transform() {
  sf::Transformable transformation;
  transformation.setOrigin(0, 640);
  transformation.setScale(1.f, -1.f);
  return transformation.getTransform();
}

}  // namespace epidemic_SIR
