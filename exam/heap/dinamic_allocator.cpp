#include <iostream>

struct Struct {
  int a;
  int b;

  void print() { std::cout << a + b << '\n'; }
};

int main() {
  auto n = new int{1};
  delete n;

  auto p = new Struct{1, 1};
  p->print();
  delete p;

  int a[3]{1, 2, 3};
  int* m = new int[3] {1,2,3};

  std::cout << *m  << '\t' << m << '\n';

  delete [] m;
}