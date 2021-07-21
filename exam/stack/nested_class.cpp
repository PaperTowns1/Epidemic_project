class Base {
  int a;
  int b;

 public:
  struct Nested {
    int c;
  };

  Nested fit() { Nested n{a + b}; }
};

int main() {
  Base b;
  Base::Nested n = b.fit();
}