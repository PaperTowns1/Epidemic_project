#include <iostream>
struct Struct {
  int a;
  Struct& f() {
      return *this;
  };
};

int main() {
  int i = 3;
  int* p = &i;

  std::cout << *p << '\t' << p << '\t' << i << '\t' << '\n';

  p = nullptr;

  Struct s{2};
  Struct* q = &s;

  std::cout << (*q).a << '\t' << q << '\t' << q->a << '\t' << '\n';

}