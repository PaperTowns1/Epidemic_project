#include "SIR_display.hpp"

namespace epidemic_SIR {

void Display_graph::draw_canvas() {
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

  sf::Text susceptible, infectious, recovered;

  susceptible.setFont(m_font);
  infectious.setFont(m_font);
  recovered.setFont(m_font);
  susceptible.setString("S");
  infectious.setString("I");
  recovered.setString("R");
  susceptible.setCharacterSize(m_display_size / 40);
  infectious.setCharacterSize(m_display_size / 40);
  recovered.setCharacterSize(m_display_size / 40);
  susceptible.setFillColor(sf::Color::Black);
  infectious.setFillColor(sf::Color::Black);
  recovered.setFillColor(sf::Color::Black);

  susceptible.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.055));
  infectious.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.085));
  recovered.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.115));

  m_window.draw(susceptible);
  m_window.draw(infectious);
  m_window.draw(recovered);

  sf::VertexArray color(sf::Lines, 6);

  color[0].position =
      sf::Vector2f(m_display_size * 0.6, m_display_size * 0.066);
  color[1].position =
      sf::Vector2f(m_display_size * 0.7, m_display_size * 0.066);
  color[2].position = sf::Vector2f(m_display_size * 0.6, m_display_size * 0.10);
  color[3].position = sf::Vector2f(m_display_size * 0.7, m_display_size * 0.10);
  color[4].position =
      sf::Vector2f(m_display_size * 0.6, m_display_size * 0.134);
  color[5].position =
      sf::Vector2f(m_display_size * 0.7, m_display_size * 0.134);

  color[0].color = sf::Color::Blue;
  color[1].color = sf::Color::Blue;
  color[2].color = sf::Color::Red;
  color[3].color = sf::Color::Red;
  color[4].color = sf::Color::Green;
  color[5].color = sf::Color::Green;

  m_window.draw(color);
}

void Display_graph::draw_more(std::vector<Population> const& data) {
  int const distance_values = m_display_size * 0.7 / 10;
  int const N = data[0].s + data[0].i + data[0].r;
  int const days = data.size();

  for (int i = 0; i != 10; ++i) {
    sf::Text x_axis_value;
    x_axis_value.setFont(m_font);

    long int a = days / 10 * (i + 1);

    int b = count_digits(a) - 1;

    std::string u = std::to_string(a);
    char digit0 = u[0];
    char digit1 = u[1];

    std::string c{};
    c.push_back(digit0);

    if (b != 0) {
      c = c + ".";
      c.push_back(digit1);
    } else {
      c = c + ".0";
    }

    c = c + "*10^" + std::to_string(b);

    x_axis_value.setString(c);

    x_axis_value.setCharacterSize(m_display_size / 60);
    x_axis_value.setFillColor(sf::Color::Black);

    if ((i + 1) % 2 == 0) {
      x_axis_value.setPosition(
          sf::Vector2f(distance_values * (i + 1) + m_display_size * 0.11,
                       m_display_size * 0.935));
    } else {
      x_axis_value.setPosition(
          sf::Vector2f(distance_values * (i + 1) + m_display_size * 0.11,
                       m_display_size * 0.915));
    }

    m_window.draw(x_axis_value);
  }

  for (int i = 0; i != 10; ++i) {
    sf::Text y_axis_value;
    y_axis_value.setFont(m_font);

    long int a = N / 10 * (10 - i);

    int b = count_digits(a) - 1;

    std::string u = std::to_string(a);
    char digit0 = u[0];
    char digit1 = u[1];

    std::string c{};
    c.push_back(digit0);

    if (b != 0) {
      c = c + ".";
      c.push_back(digit1);
    } else {
      c = c + ".0";
    }

    c = c + "*10^" + std::to_string(b);

    y_axis_value.setString(c);

    y_axis_value.setCharacterSize(m_display_size / 60);
    y_axis_value.setFillColor(sf::Color::Black);

    y_axis_value.setPosition(sf::Vector2f(
        m_display_size * 0.06, m_display_size * 0.2 + i * distance_values));

    m_window.draw(y_axis_value);
  }

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

  sf::Text susceptible, infectious, recovered;

  susceptible.setFont(m_font);
  infectious.setFont(m_font);
  recovered.setFont(m_font);
  susceptible.setString("S");
  infectious.setString("I");
  recovered.setString("R");
  susceptible.setCharacterSize(m_display_size / 40);
  infectious.setCharacterSize(m_display_size / 40);
  recovered.setCharacterSize(m_display_size / 40);
  susceptible.setFillColor(sf::Color::Black);
  infectious.setFillColor(sf::Color::Black);
  recovered.setFillColor(sf::Color::Black);

  susceptible.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.055));
  infectious.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.085));
  recovered.setPosition(
      sf::Vector2f(m_display_size * 0.57, m_display_size * 0.115));

  m_window.draw(susceptible);
  m_window.draw(infectious);
  m_window.draw(recovered);

  sf::VertexArray color(sf::Lines, 6);

  color[0].position =
      sf::Vector2f(m_display_size * 0.6, m_display_size * 0.066);
  color[1].position =
      sf::Vector2f(m_display_size * 0.7, m_display_size * 0.066);
  color[2].position = sf::Vector2f(m_display_size * 0.6, m_display_size * 0.10);
  color[3].position = sf::Vector2f(m_display_size * 0.7, m_display_size * 0.10);
  color[4].position =
      sf::Vector2f(m_display_size * 0.6, m_display_size * 0.134);
  color[5].position =
      sf::Vector2f(m_display_size * 0.7, m_display_size * 0.134);

  color[0].color = sf::Color::Blue;
  color[1].color = sf::Color::Blue;
  color[2].color = sf::Color::Red;
  color[3].color = sf::Color::Red;
  color[4].color = sf::Color::Green;
  color[5].color = sf::Color::Green;

  m_window.draw(color);
}

int Display_graph::count_digits(long int n) {
  int num = 0;
  while (n != 0) {
    n = n / 10;
    num++;
  }
  return num;
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

  for (int i{0}; i != n; ++i) {
    points_s[i].position = sf::Vector2f(
        i * m_display_size * 0.7 / n + m_display_size * 0.15,
        data[i].s / N * m_display_size * 0.7 + m_display_size * 0.1);
  }

  for (int i{0}; i != n; ++i) {
    points_s[i].color = sf::Color::Blue;
  }

  m_window.draw(points_s, transform());
}

void Display_graph::draw_infectious(std::vector<Population> const& data) {
  sf::VertexArray points_i(sf::LineStrip, data.size());

  int const n = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  for (int i{0}; i != n; ++i) {
    points_i[i].position = sf::Vector2f(
        i * m_display_size * 0.7 / n + m_display_size * 0.15,
        data[i].i / N * m_display_size * 0.7 + m_display_size * 0.1);
  }

  for (int i{0}; i != n; ++i) {
    points_i[i].color = sf::Color::Red;
  }

  m_window.draw(points_i, transform());
}

void Display_graph::draw_recovered(std::vector<Population> const& data) {
  sf::VertexArray points_r(sf::LineStrip, data.size());

  int const n = static_cast<int>(data.size());
  int const N = data[0].s + data[0].i + data[0].r;

  for (int i{0}; i != n; ++i) {
    points_r[i].position = sf::Vector2f(
        i * m_display_size * 0.7 / n + m_display_size * 0.15,
        data[i].r / N * m_display_size * 0.7 + m_display_size * 0.1);
  }

  for (int i{0}; i != n; ++i) {
    points_r[i].color = sf::Color::Green;
  }

  m_window.draw(points_r, transform());
}

}  // namespace epidemic_SIR