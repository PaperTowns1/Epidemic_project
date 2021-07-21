struct Base {
  virtual void f(int) = 0;
};

struct Derived : Base {
  void f(int) override {}
};

int main() {
  // Base b; error
  auto b1 = new Derived;  // to delete
  Derived d;
  auto b2 = &d;  // to not delete
  b2->f(2);
  auto b3 = d;
  b3.f(2);
}