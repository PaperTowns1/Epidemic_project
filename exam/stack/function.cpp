#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

int if_(int a) { return (a > 0) ? 1 : 0; }

void if_out() {
  auto b = if_(1);
  auto c = if_(-1);
  std::cout << b << c << '\n';
}

void ref_(int& a) { ++a; }

void ref_out() {
  auto a = 9;
  ref_(a);
  std::cout << a << '\n';
}

void for_(int& sum) {
  std::vector<int> v = {1, 1, 1, 1, 1, 1};
  for (auto& i : v) {
    sum += v[i];
  }
}

void for_out() {
  int sum = 0;
  for_(sum);
  std::cout << sum << '\n';
}

struct Struct {
  int a;
  int b;
};

Struct vst() {
  std::vector<Struct> v = {{1, 1}, {2, 2}, {3, 3}};
  Struct res{};

  int sum1 = std::accumulate(
      v.begin(), v.end(), 0,
      [](int sum, Struct const& current) { return sum + current.a; });

  int sum2 = 0;
  for (auto first = v.begin(), last = v.end(); first != last; ++first) {
    // sum2 += first->a;
    sum2 += (*first).a;
  }

  return {sum1, sum2};
}

void vst_out() {
  auto f = vst();
  std::cout << f.a << '\t' << f.b << '\n';
}

void stcrbind() {
  Struct s{1, 2};
  auto& [x, y] = s;
  ++x;
  ++y;
  std::cout << s.a << '\t' << s.b << '\n';
}

int main() {
  if_out();
  ref_out();
  for_out();
  vst_out();
  stcrbind();
}