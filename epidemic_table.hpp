#ifndef EPIDEMIC_TABLE_HPP
#define EPIDEMIC_TABLE_HPP

#include <cassert>
#include <vector>


struct State {
  double s;
  double i;
  double r;
};

class Virus {
 private:
  State m_initial_state;
  double m_duration;

 public:
  Virus(State const& initial_state, double duration)
      : m_initial_state{initial_state}, m_duration{duration} {}

  std::vector<State> evolve(double beta, double gamma) {
    if (beta / gamma < 1) {
      throw std::runtime_error{"r0 is less than 1"};
    }

    std::vector<State> data{m_initial_state};
    State state = data.back();

    double const N = state.s + state.i + state.r;

    for (int i = 0; i != m_duration; i++) {
      double const delta_i = beta * state.s / N * state.i;
      double const delta_r = gamma * state.i;

      state.s = state.s - delta_i;
      state.i = state.i + delta_i - delta_r;
      state.r = state.r + delta_r;

      assert(std::round(N) == std::round(state.s + state.i + state.r));
      assert(state.s >= 0 && state.i >= 0 && state.r >= 0);

      data.push_back(state);
    }
    return data;
  }
};

#endif