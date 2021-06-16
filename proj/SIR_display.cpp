#include "SIR_display.hpp"

namespace epidemic_SIR {

void Display_graph::draw_axes() {
  sf::VertexArray x_axis(sf::Lines, 2);

  x_axis[0].position =
      sf::Vector2f(m_display_size * 0.15, m_display_size * 0.9);
  x_axis[1].position =
      sf::Vector2f(m_display_size * 0.85, m_display_size * 0.9);

  x_axis[0].color = sf::Color::Black;
  x_axis[1].color = sf::Color::Black;

  m_window.draw(x_axis);

  sf::VertexArray y_axis(sf::Lines, 2);

  y_axis[0].position =
      sf::Vector2f(m_display_size * 0.15, m_display_size * 0.2);
  y_axis[1].position =
      sf::Vector2f(m_display_size * 0.15, m_display_size * 0.9);

  y_axis[0].color = sf::Color::Black;
  y_axis[1].color = sf::Color::Black;

  m_window.draw(y_axis);
}

void Display_graph::draw_axes_notches() {
  sf::VertexArray x_axis_notches(sf::Lines, 22);

  int const distance_notches = m_display_size * 0.7 / 20;

  for (int i = 0; i != 22; i = i + 2) {
    x_axis_notches[i].position =
        sf::Vector2f(m_display_size * 0.15 + distance_notches * i,
                     m_display_size * 0.9 - m_display_size * 0.01);
    if ((i + 1) / 2 % 2 == 0) {
      x_axis_notches[i + 1].position =
          sf::Vector2f(m_display_size * 0.15 + distance_notches * i,
                       m_display_size * 0.9 + m_display_size * 0.025);
    } else {
      x_axis_notches[i + 1].position =
          sf::Vector2f(m_display_size * 0.15 + distance_notches * i,
                       m_display_size * 0.9 + m_display_size * 0.01);
    }
  }

  for (int i = 0; i != 22; ++i) {
    x_axis_notches[i].color = sf::Color::Black;
  }

  m_window.draw(x_axis_notches);

  sf::VertexArray y_axis_notches(sf::Lines, 22);

  for (int i = 0; i != 22; i = i + 2) {
    y_axis_notches[i].position =
        sf::Vector2f(m_display_size * 0.15 - m_display_size * 0.01,
                     m_display_size * 0.2 + i * distance_notches);
    y_axis_notches[i + 1].position =
        sf::Vector2f(m_display_size * 0.15 + m_display_size * 0.01,
                     m_display_size * 0.2 + i * distance_notches);
  }

  for (int i = 0; i != 22; ++i) {
    y_axis_notches[i].color = sf::Color::Black;
  }

  m_window.draw(y_axis_notches);
}

void Display_graph::draw_axes_values(std::vector<Population> const& data) {
  sf::Text x_axis_name;

  x_axis_name.setFont(m_font);
  x_axis_name.setString("Days");
  x_axis_name.setCharacterSize(m_display_size / 40);
  x_axis_name.setFillColor(sf::Color::Black);

  x_axis_name.setPosition(
      sf::Vector2f(m_display_size * 0.9, m_display_size * 0.9));

  m_window.draw(x_axis_name);

  sf::Text y_axis_name;

  y_axis_name.setFont(m_font);
  y_axis_name.setString("Population");
  y_axis_name.setCharacterSize(m_display_size / 40);
  y_axis_name.setFillColor(sf::Color::Black);

  y_axis_name.setPosition(
      sf::Vector2f(m_display_size * 0.06, m_display_size * 0.15));

  m_window.draw(y_axis_name);

  int const distance_values = m_display_size * 0.7 / 10;
  int const N = data[0].s + data[0].i + data[0].r;
  double const days = static_cast<double>(data.size()) - 1;
  double const days_range = days / 10;

  for (int i = 0; i != 10; ++i) {
    sf::Text x_axis_value;
    x_axis_value.setFont(m_font);

    int a = count_digits(days);

    std::string add = std::to_string(days_range * (i + 1));
    std::string add1;

    for (int j = 0; j < a + 2; ++j) {
      char digit = add[j];
      add1 += digit;
    }

    x_axis_value.setString(add1);

    x_axis_value.setCharacterSize(m_display_size / 60);
    x_axis_value.setFillColor(sf::Color::Black);

    if ((i + 1) % 2 == 0) {
      x_axis_value.setPosition(
          sf::Vector2f(distance_values * (i + 1) + m_display_size * 0.14,
                       m_display_size * 0.935));
    } else {
      x_axis_value.setPosition(
          sf::Vector2f(distance_values * (i + 1) + m_display_size * 0.14,
                       m_display_size * 0.915));
    }

    m_window.draw(x_axis_value);
  }

  for (int i = 0; i != 10; ++i) {
    sf::Text y_axis_value;
    y_axis_value.setFont(m_font);

    std::string c{};

    if (N > 10) {
      int a = N / 10 * (10 - i);

      int b = count_digits(a) - 1;

      std::string u = std::to_string(a);
      char digit0 = u[0];
      char digit1 = u[1];

      c.push_back(digit0);

      if (b != 0) {
        c = c + ".";
        c.push_back(digit1);
      } else {
        c = c + ".0";
      }

      c = c + "*10^" + std::to_string(b);
    } else {
      c = std::to_string(N / 10 * (10 - i));
    }

    y_axis_value.setString(c);

    y_axis_value.setCharacterSize(m_display_size / 60);
    y_axis_value.setFillColor(sf::Color::Black);

    y_axis_value.setPosition(sf::Vector2f(
        m_display_size * 0.06, m_display_size * 0.2 + i * distance_values));

    m_window.draw(y_axis_value);
  }
}

void Display_graph::draw_legend() {
  sf::VertexArray legend(sf::LineStrip, 5);

  legend[0].position =
      sf::Vector2f(m_display_size * 0.55, m_display_size * 0.05);
  legend[1].position =
      sf::Vector2f(m_display_size * 0.75, m_display_size * 0.05);
  legend[2].position =
      sf::Vector2f(m_display_size * 0.75, m_display_size * 0.15);
  legend[3].position =
      sf::Vector2f(m_display_size * 0.55, m_display_size * 0.15);
  legend[4].position =
      sf::Vector2f(m_display_size * 0.55, m_display_size * 0.05);

  legend[0].color = sf::Color::Black;
  legend[1].color = sf::Color::Black;
  legend[2].color = sf::Color::Black;
  legend[3].color = sf::Color::Black;
  legend[4].color = sf::Color::Black;

  m_window.draw(legend);
}

int Display_graph::count_digits(int n) {
  int result = 0;
  while (n != 0) {
    n = std::floor(n / 10);
    result++;
  }
  return result;
}

sf::Transform Display_graph::transform() {
  sf::Transformable transformation;
  transformation.setOrigin(0, m_display_size);
  transformation.setScale(1.f, -1.f);
  return transformation.getTransform();
}

void Display_graph::draw_susceptible(std::vector<Population> const& data) {
  sf::VertexArray points_s(sf::LineStrip, data.size());

  int const n = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  double const range = m_display_size * 0.7 / (n - 1);

  for (int i = 0; i != n; ++i) {
    points_s[i].position = sf::Vector2f(
        i * range + m_display_size * 0.15,
        data[i].s / N * m_display_size * 0.7 + m_display_size * 0.1);
  }

  for (int i = 0; i != n; ++i) {
    points_s[i].color = sf::Color::Blue;
  }

  m_window.draw(points_s, transform());
}

void Display_graph::draw_legend_susceptible() {
  sf::Text susceptible;

  susceptible.setFont(m_font);
  susceptible.setString("S");
  susceptible.setCharacterSize(m_display_size / 40);
  susceptible.setFillColor(sf::Color::Black);
  susceptible.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.055));

  m_window.draw(susceptible);

  sf::VertexArray color(sf::Lines, 2);

  color[0].position =
      sf::Vector2f(m_display_size * 0.6, m_display_size * 0.066);
  color[1].position =
      sf::Vector2f(m_display_size * 0.7, m_display_size * 0.066);

  color[0].color = sf::Color::Blue;
  color[1].color = sf::Color::Blue;

  m_window.draw(color);
}

void Display_graph::draw_infectious(std::vector<Population> const& data) {
  sf::VertexArray points_i(sf::LineStrip, data.size());

  int const n = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  double const range = m_display_size * 0.7 / (n - 1);

  for (int i{0}; i != n; ++i) {
    points_i[i].position = sf::Vector2f(
        i * range + m_display_size * 0.15,
        data[i].i / N * m_display_size * 0.7 + m_display_size * 0.1);
  }

  for (int i{0}; i != n; ++i) {
    points_i[i].color = sf::Color::Red;
  }

  m_window.draw(points_i, transform());
}

void Display_graph::draw_legend_infectious() {
  sf::Text infectious;

  infectious.setFont(m_font);
  infectious.setString("I");
  infectious.setCharacterSize(m_display_size / 40);
  infectious.setFillColor(sf::Color::Black);

  infectious.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.085));

  m_window.draw(infectious);

  sf::VertexArray color(sf::Lines, 2);

  color[0].position = sf::Vector2f(m_display_size * 0.6, m_display_size * 0.10);
  color[1].position = sf::Vector2f(m_display_size * 0.7, m_display_size * 0.10);

  color[0].color = sf::Color::Red;
  color[1].color = sf::Color::Red;

  m_window.draw(color);
}

void Display_graph::draw_recovered(std::vector<Population> const& data) {
  sf::VertexArray points_r(sf::LineStrip, data.size());

  int const n = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  double const range = m_display_size * 0.7 / (n - 1);

  for (int i{0}; i != n; ++i) {
    points_r[i].position = sf::Vector2f(
        i * range + m_display_size * 0.15,
        data[i].r / N * m_display_size * 0.7 + m_display_size * 0.1);
  }

  for (int i{0}; i != n; ++i) {
    points_r[i].color = sf::Color::Green;
  }

  m_window.draw(points_r, transform());
}

void Display_graph::draw_legend_recovered() {
  sf::Text recovered;

  recovered.setFont(m_font);
  recovered.setString("R");
  recovered.setCharacterSize(m_display_size / 40);
  recovered.setFillColor(sf::Color::Black);

  recovered.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.115));

  m_window.draw(recovered);

  sf::VertexArray color(sf::Lines, 2);

  color[0].position =
      sf::Vector2f(m_display_size * 0.6, m_display_size * 0.134);
  color[1].position =
      sf::Vector2f(m_display_size * 0.7, m_display_size * 0.134);

  color[0].color = sf::Color::Green;
  color[1].color = sf::Color::Green;

  m_window.draw(color);
}

}  // namespace epidemic_SIR
