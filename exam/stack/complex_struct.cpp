struct Complex {
  double r;
  double i;
};

bool operator==(Complex const& l, Complex const& r) {
  return (l.r == r.r && l.i == r.i);
}

Complex operator+(Complex const& l, Complex const& r) {
  return Complex{l.r + r.r, l.i + r.i};
}

int main() {
  Complex uno{1., 1.};
  Complex due{1., 1.};
  bool equal = (uno == due);
  Complex tre = uno + due;
}