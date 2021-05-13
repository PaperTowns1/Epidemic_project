#ifndef EPIDEMIC_SIRD_HPP
#define EPIDEMIC_SIRD_HPP

#include <cassert>
#include <vector>

struct State {
  double s;
  double i;
  double r;
  double d;
};

class Virus {
 private:
  State m_initial_state;
  double m_duration;

 public:
  Virus(State const& initial_state, double duration)
      : m_initial_state{initial_state}, m_duration{duration} {}

  std::vector<State> evolve(double beta, double gamma, double mu) {
    std::vector<State> data{m_initial_state};
    State state = data.back();

    double const N = state.s + state.i + state.r + state.d;

    for (int i = 0; i != m_duration; i++) {
      double const delta_i = beta * state.s / N * state.i;
      double const delta_r = gamma * state.i;
      double const delta_d = mu * state.i;


      state.s = state.s - delta_i;
      state.i = state.i + delta_i - delta_r - delta_d;
      state.r = state.r + delta_r;
      state.d = state.d + delta_d;

      assert(std::round(N) ==
             std::round(state.s + state.i + state.r + state.d));
      assert(state.s >= 0 && state.i >= 0 && state.r >= 0 && state.d >= 0);

      data.push_back(state);
    }
    return data;
  }
};

#endif