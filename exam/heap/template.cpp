#include <cassert>
#include <iostream>

class Complex {
  double r;
  double i;

  Complex(double r_ = double{}, double i_ = double{}) : r{r_}, i{i_} {}

  double get_r() const { return r; }
  double get_i() const { return i; }
};

template <typename T>  // template <class T>
class Complex_t {
  static_assert(std::is_floating_point_v<T>);
  T r;
  T i;

 public:
  Complex_t(T r_ = T{}, T i_ = T{}) : r{r_}, i{i_} {}

  auto get_r() const { return r; }
  auto get_i() const { return i; }
};

template <typename T>
auto operator+(Complex_t<T> const& l, Complex_t<T> const& r) {
  return Complex_t<T>{l.get_r() + r.get_r(), l.get_i() + r.get_i()};
}

template <typename T>
auto norm2(Complex_t<T> const& l) {
  return l.get_r() * l.get_r() + l.get_i() * l.get_i();
}

template<typename from, typename to>
auto convert_C_to_K (from f) {
    return static_cast<to>(f);
}

int main() {
  Complex_t<double> d{};
  Complex_t<float> f{};

  Complex_t ded_d{2., 2.};
  Complex_t ded_f{2.f, 2.f};
  d + ded_d;
  f + ded_f;

  auto norm_d = norm2<double>(ded_d);
  auto norm_f = norm2<float>(ded_f);

  // d + ded_f; error

  float a = 2.f;
  auto c = convert_C_to_K<float, double>(a);

}