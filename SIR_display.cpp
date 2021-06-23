#include "SIR_display.hpp"

namespace epidemic_SIR {

void Display_graph::draw_axes() {
  sf::VertexArray x_axis(sf::Lines, 2);

  x_axis[0].position = sf::Vector2f(m_display_side * 0.15, m_display_side * 0.9);
  x_axis[1].position = sf::Vector2f(m_display_side * 0.85, m_display_side * 0.9);
  x_axis[0].color = sf::Color::White;
  x_axis[1].color = sf::Color::White;

  m_window.draw(x_axis);

  sf::VertexArray y_axis(sf::Lines, 2);

  y_axis[0].position = sf::Vector2f(m_display_side * 0.15, m_display_side * 0.2);
  y_axis[1].position = sf::Vector2f(m_display_side * 0.15, m_display_side * 0.9);
  y_axis[0].color = sf::Color::White;
  y_axis[1].color = sf::Color::White;

  m_window.draw(y_axis);
}

void Display_graph::draw_axes_notches() {
  int const half_distance_notches = m_display_side * 0.7 / 20;

  sf::VertexArray x_axis_notches(sf::Lines, 22);
  for (int i = 0; i != 22; i = i + 2) {
    x_axis_notches[i].position = sf::Vector2f(m_display_side * 0.15 + half_distance_notches * i,
                                              m_display_side * 0.9 - m_display_side * 0.01);
    if ((i + 1) / 2 % 2 == 0) {
      x_axis_notches[i + 1].position =
          sf::Vector2f(m_display_side * 0.15 + half_distance_notches * i,
                       m_display_side * 0.9 + m_display_side * 0.025);
    } else {
      x_axis_notches[i + 1].position =
          sf::Vector2f(m_display_side * 0.15 + half_distance_notches * i,
                       m_display_side * 0.9 + m_display_side * 0.01);
    }
    x_axis_notches[i].color = sf::Color::White;
    x_axis_notches[i + 1].color = sf::Color::White;
  }

  m_window.draw(x_axis_notches);

  sf::VertexArray y_axis_notches(sf::Lines, 22);

  for (int i = 0; i != 22; i = i + 2) {
    y_axis_notches[i].position = sf::Vector2f(m_display_side * 0.15 - m_display_side * 0.01,
                                              m_display_side * 0.2 + i * half_distance_notches);
    y_axis_notches[i + 1].position = sf::Vector2f(m_display_side * 0.15 + m_display_side * 0.01,
                                                  m_display_side * 0.2 + i * half_distance_notches);
    y_axis_notches[i].color = sf::Color::White;
    y_axis_notches[i + 1].color = sf::Color::White;
  }

  m_window.draw(y_axis_notches);
}

int Display_graph::count_digits(int n) {
  int result = 0;

  while (n != 0) {
    n = std::floor(n / 10);
    result++;
  }

  return result;
}

void Display_graph::draw_axes_values(std::vector<Population> const& data) {
  sf::Text x_axis_name;

  x_axis_name.setFont(m_font);
  x_axis_name.setString("Days");
  x_axis_name.setCharacterSize(m_display_side / 40);
  x_axis_name.setFillColor(sf::Color::White);
  x_axis_name.setPosition(sf::Vector2f(m_display_side * 0.9, m_display_side * 0.9));

  m_window.draw(x_axis_name);

  sf::Text y_axis_name;

  y_axis_name.setFont(m_font);
  y_axis_name.setString("Population");
  y_axis_name.setCharacterSize(m_display_side / 40);
  y_axis_name.setFillColor(sf::Color::White);
  y_axis_name.setPosition(sf::Vector2f(m_display_side * 0.06, m_display_side * 0.15));

  m_window.draw(y_axis_name);

  int const distance_notches = m_display_side * 0.7 / 10;
  int const N = data[0].s + data[0].i + data[0].r;
  double const days = static_cast<double>(data.size()) - 1;
  double const days_range = days / 10;
  double const N_range = N / 10;

  for (int i = 0; i != 10; ++i) {
    sf::Text x_axis_notch_value;
    x_axis_notch_value.setFont(m_font);

    auto digits_number = count_digits(days_range * (i + 1));
    std::string days_notch_with_all_digit = std::to_string(days_range * (i + 1));
    std::string approximated_days_notch{};

    if (days < 1000) {
      for (int j = 0; j < digits_number + 4; ++j) {
        char const digit = days_notch_with_all_digit[j];
        approximated_days_notch += digit;
      }
    } else {
      char digit0 = days_notch_with_all_digit[0];
      approximated_days_notch.push_back(digit0);
      approximated_days_notch += ".";
      char digit1 = days_notch_with_all_digit[1];
      approximated_days_notch.push_back(digit1);
      approximated_days_notch += "*10^" + std::to_string(digits_number - 1);
    }

    x_axis_notch_value.setString(approximated_days_notch);
    x_axis_notch_value.setCharacterSize(m_display_side / 60);
    x_axis_notch_value.setFillColor(sf::Color::White);
    if ((i + 1) % 2 == 0) {
      x_axis_notch_value.setPosition(
          sf::Vector2f(distance_notches * (i + 1) + m_display_side * 0.14, m_display_side * 0.935));
    } else {
      x_axis_notch_value.setPosition(
          sf::Vector2f(distance_notches * (i + 1) + m_display_side * 0.14, m_display_side * 0.915));
    }

    m_window.draw(x_axis_notch_value);
  }

  for (int i = 0; i != 10; ++i) {
    sf::Text y_axis_notch_value;
    y_axis_notch_value.setFont(m_font);

    auto digits_number = count_digits(N_range * (10 - i));
    std::string population_notch_with_all_digit = std::to_string(N_range * (10 - i));
    std::string approximated_population_notch{};

    if (N < 1000) {
      for (int j = 0; j < digits_number + 4; ++j) {
        char const digit = population_notch_with_all_digit[j];
        approximated_population_notch += digit;
      }

      y_axis_notch_value.setPosition(
          sf::Vector2f(m_display_side * 0.08, m_display_side * 0.2 + i * distance_notches));

    } else {
      char digit0 = population_notch_with_all_digit[0];
      approximated_population_notch.push_back(digit0);
      approximated_population_notch += ".";
      char digit1 = population_notch_with_all_digit[1];
      approximated_population_notch.push_back(digit1);
      approximated_population_notch += "*10^" + std::to_string(digits_number - 1);

      y_axis_notch_value.setPosition(
          sf::Vector2f(m_display_side * 0.06, m_display_side * 0.2 + i * distance_notches));
    }

    y_axis_notch_value.setString(approximated_population_notch);
    y_axis_notch_value.setCharacterSize(m_display_side / 60);
    y_axis_notch_value.setFillColor(sf::Color::White);

    m_window.draw(y_axis_notch_value);
  }
}

void Display_graph::draw_legend() {
  sf::VertexArray legend(sf::LineStrip, 5);

  legend[0].position = sf::Vector2f(m_display_side * 0.55, m_display_side * 0.05);
  legend[1].position = sf::Vector2f(m_display_side * 0.75, m_display_side * 0.05);
  legend[2].position = sf::Vector2f(m_display_side * 0.75, m_display_side * 0.15);
  legend[3].position = sf::Vector2f(m_display_side * 0.55, m_display_side * 0.15);
  legend[4].position = sf::Vector2f(m_display_side * 0.55, m_display_side * 0.05);

  legend[0].color = sf::Color::White;
  legend[1].color = sf::Color::White;
  legend[2].color = sf::Color::White;
  legend[3].color = sf::Color::White;
  legend[4].color = sf::Color::White;

  m_window.draw(legend);
}

sf::Transform Display_graph::transform() {
  sf::Transformable transformation;
  transformation.setOrigin(0, m_display_side);
  transformation.setScale(1.f, -1.f);
  return transformation.getTransform();
}

void Display_graph::draw_susceptible(std::vector<Population> const& data) {
  sf::VertexArray points_s(sf::LineStrip, data.size());

  int const data_size = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  double const points_distance = m_display_side * 0.7 / (data_size - 1);

  for (int i = 0; i != data_size; ++i) {
    points_s[i].position =
        sf::Vector2f(i * points_distance + m_display_side * 0.15,
                     data[i].s / N * m_display_side * 0.7 + m_display_side * 0.1);
  }

  for (int i = 0; i != data_size; ++i) {
    points_s[i].color = sf::Color::Blue;
  }

  m_window.draw(points_s, transform());
}

void Display_graph::draw_legend_susceptible() {
  sf::Text susceptible;

  susceptible.setFont(m_font);
  susceptible.setString("S");
  susceptible.setCharacterSize(m_display_side / 40);
  susceptible.setFillColor(sf::Color::White);
  susceptible.setPosition(sf::Vector2f(m_display_side * 0.57, m_display_side * 0.055));

  m_window.draw(susceptible);

  sf::VertexArray color(sf::Lines, 2);

  color[0].position = sf::Vector2f(m_display_side * 0.6, m_display_side * 0.066);
  color[1].position = sf::Vector2f(m_display_side * 0.7, m_display_side * 0.066);
  color[0].color = sf::Color::Blue;
  color[1].color = sf::Color::Blue;

  m_window.draw(color);
}

void Display_graph::draw_infectious(std::vector<Population> const& data) {
  sf::VertexArray points_i(sf::LineStrip, data.size());

  int const data_size = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  double const points_distance = m_display_side * 0.7 / (data_size - 1);

  for (int i{0}; i != data_size; ++i) {
    points_i[i].position =
        sf::Vector2f(i * points_distance + m_display_side * 0.15,
                     data[i].i / N * m_display_side * 0.7 + m_display_side * 0.1);
  }

  for (int i{0}; i != data_size; ++i) {
    points_i[i].color = sf::Color::Red;
  }

  m_window.draw(points_i, transform());
}

void Display_graph::draw_legend_infectious() {
  sf::Text infectious;

  infectious.setFont(m_font);
  infectious.setString("I");
  infectious.setCharacterSize(m_display_side / 40);
  infectious.setFillColor(sf::Color::White);
  infectious.setPosition(sf::Vector2f(m_display_side * 0.57, m_display_side * 0.085));

  m_window.draw(infectious);

  sf::VertexArray color(sf::Lines, 2);

  color[0].position = sf::Vector2f(m_display_side * 0.6, m_display_side * 0.10);
  color[1].position = sf::Vector2f(m_display_side * 0.7, m_display_side * 0.10);
  color[0].color = sf::Color::Red;
  color[1].color = sf::Color::Red;

  m_window.draw(color);
}

void Display_graph::draw_recovered(std::vector<Population> const& data) {
  sf::VertexArray points_r(sf::LineStrip, data.size());

  int const data_size = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  double const points_distance = m_display_side * 0.7 / (data_size - 1);

  for (int i{0}; i != data_size; ++i) {
    points_r[i].position =
        sf::Vector2f(i * points_distance + m_display_side * 0.15,
                     data[i].r / N * m_display_side * 0.7 + m_display_side * 0.1);
  }

  for (int i{0}; i != data_size; ++i) {
    points_r[i].color = sf::Color::Green;
  }

  m_window.draw(points_r, transform());
}

void Display_graph::draw_legend_recovered() {
  sf::Text recovered;

  recovered.setFont(m_font);
  recovered.setString("R");
  recovered.setCharacterSize(m_display_side / 40);
  recovered.setFillColor(sf::Color::White);
  recovered.setPosition(sf::Vector2f(m_display_side * 0.57, m_display_side * 0.115));

  m_window.draw(recovered);

  sf::VertexArray color(sf::Lines, 2);

  color[0].position = sf::Vector2f(m_display_side * 0.6, m_display_side * 0.134);
  color[1].position = sf::Vector2f(m_display_side * 0.7, m_display_side * 0.134);
  color[0].color = sf::Color::Green;
  color[1].color = sf::Color::Green;

  m_window.draw(color);
}

}  // namespace epidemic_SIR
