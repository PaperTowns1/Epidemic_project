#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  // expression
  std::vector<int> v{1, 2, 3, 4, -1};
  auto it1 = std::find_if(v.begin(), v.end(), [](int n) { return n < 0; });

  int m = 0;
  auto it2 = std::find_if(v.begin(), v.end(), [=](int n) { return n < m; });

  int l;
  auto it3 = std::find_if(v.begin(), v.end(), [l = 0](int n) { return n < l; });

  std::cout << *it1 << *it2 << *it3 << '\n';

  // closure
  int b;
  auto f = [b = 0](auto n) -> bool { return n < b; };
  auto it4 = std::find_if(v.begin(), v.end(), f);

  std::cout << *it4 << '\n';
}