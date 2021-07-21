#include <algorithm>
#include <cassert>
#include <numeric>
#include <stdexcept>

class Rational {
  int num;
  int den;

  void reduce() {
    auto const g = std::gcd(num, den);
    num /= g;
    den /= g;
  }

  void fix_sign() {
    if (den < 0) {
      num = -num;
      den = -den;
    }
  }

  bool invariant() { return std::gcd(num, den) == 1 && den > 0; }

 public:
  Rational(int n = 0, int d = 1) : num{n}, den{d} {
    if (den == 0) {
      throw std::runtime_error{"denominator is zero"};
    }
    reduce();
    fix_sign();
    assert(invariant());
  }

  int num() const { return num; }
  int den() const { return den; }

  Rational& operator*=(int n) {
    assert(invariant());

    auto g = std::gcd(n, den);
    num *= n / g;
    den /= g;

    assert(invariant());
    return *this;
  }

  Rational& operator/=(int n) {
    assert(n != 0);
    assert(invariant());

    auto g = std::gcd(n, num);
    num /= g;
    den *= n / g;
    fix_sign();

    assert(invariant());
    return *this;
  }
};

bool operator==(Rational const& l, Rational const& r) {
  assert(std::gcd(l.num(), l.den()) == 1 && std::gcd(r.num(), r.den()) == 1);
  return l.num() == r.num() && l.den() == r.den();
}

bool operator!=(Rational const& l, Rational const& r) { return !(l == r); }

Rational operator*(Rational const& l, int n) {
  Rational result{l};
  result *= n;
  return result;
}

Rational operator/(Rational const& l, int n) {
  Rational result{l};
  result /= n;
  return result;
}

Rational operator+(Rational const& r) { return r; }

Rational operator-(Rational const& r) { return {-r.num(), r.den()}; }
