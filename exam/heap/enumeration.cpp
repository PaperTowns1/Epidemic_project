#include <iostream>

enum class Operator { Plus, Minus, Multiplies, Divides };
enum class Months {
  Jan = 1,
  Feb,
  Mar,
  Apr,
  May,
  Jun,
  Jul,
  Aug,
  Sep,
  Oct,
  Nov,
  Dec
};
enum Operator_ { Plus, Minus, Multiplies, Divides };

int main() {
  Operator op = Operator::Plus;
  switch (op) {
    case Operator::Plus: {
      std::cout << "+" << '\n';
    }
  }

  Months m{Months::Oct};
  //int i = m; no
  int i = static_cast<int>(m);
  ++i;
  Months n = static_cast<Months>(i);

  std::cout << i << '\n';

  Operator_ o{Operator_::Divides};
  int k = o;

  std::cout << k << '\n';
}