#include <array>
#include <iostream>

int main() {
  // native array
  int a[3] = {1, 2, 3};
  std::cout << a[0] << a[1] << a[2] << '\n';

  auto b = a;

  std::cout << b << '\t' << *b << '\n';

  ++b;

  std::cout << b << '\t' << *b << '\n';

  *b = 5;

  std::cout << b << '\t' << *b << '\n';
  std::cout << a[0] << a[1] << a[2] << '\n';

  // std::array

  std::array<int, 2> a1;
  std::array<int, 2> a2{};
  std::array<int, 2> a3{1, 2};
  auto a4 = a3;

  std::cout << a4[0] << a4[1] << '\n';
}