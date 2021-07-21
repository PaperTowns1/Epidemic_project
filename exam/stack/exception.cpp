#include <exception>
#include <iostream>

int main() {
  try {
    int a = 1;
    if (a == 0) throw std::runtime_error{"Invalid"};
  } catch (std::exception const& e) {
    std::cerr << e.what() << '\n';
  }
}