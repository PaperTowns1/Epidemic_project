#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
#include <vector>

struct s {
  int a;
  int b;
};

int main() {
  std::vector<int> v1{1, 2, 3, 4, 5};
  std::vector<s> v2{{1, 1}, {2, 2}};

  auto sum1 = std::accumulate(v1.begin(), v1.end(), 0);
  auto sum2 = std::accumulate(v2.begin(), v2.end(), 0,
                              [](int sum, s const& v) { return sum + v.a; });

  std::cout << sum1 << '\t' << sum2 << '\n';

  auto it = std::find(v1.begin(), v1.end(), 5);
  std::cout << *it << '\n';

  auto it1 = std::find_if(v1.begin(), v1.end(), [](int i){ return i < 0; });
  std::cout << *it1 << '\n';
}
