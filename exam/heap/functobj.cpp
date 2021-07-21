#include <algorithm>
#include <iostream>
#include <vector>

auto negative(int n) { return n < 0; }

struct negative_ {
  auto operator()(int n) const { return n < 0; }
};

class negative__ {
  int m;

 public:
  negative__(int n) : m{n} {}
  auto operator()(int r) const { return r < 0; }
};

int main() {
  auto a = negative(-2);
  negative_ b1{};
  auto b = b1(-2);
  negative__ c1{0};
  auto c = c1(-2);

  std::cout << std::boolalpha << a << b << c << '\n';
}