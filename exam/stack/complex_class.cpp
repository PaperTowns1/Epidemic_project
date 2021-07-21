#include <iostream>

class Complex {
 private:
  double r;
  double i;

 public:
  Complex(double a = 0., double b = 0.) : r{a}, i{b} {}

  double get_real() const { return r; }
  double get_imag() const { return i; }

  friend bool operator==(Complex const& l, Complex const& r) {
    return (l.r == r.r && l.i == r.i);
  }

  friend Complex operator+(Complex const& l, Complex const& r) {
    return Complex{l.r + r.r, l.i + r.i};
  }
};

double norm2(Complex const& c) {
  return c.get_real() * c.get_real() + c.get_imag() * c.get_imag();
}

int main() {
  Complex uno{1, 1};
  Complex due{1, 1};
  bool equal = (uno == due);
  Complex tre = uno + due;
  double norm2_tre = norm2(tre);

  std::cout << std::boolalpha << equal << tre.get_real() << tre.get_imag()
            << norm2_tre << '\n';
}