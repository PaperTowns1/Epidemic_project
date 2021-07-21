struct Base {
  virtual ~Base() = 0;
  virtual void f(int);
};

inline Base::~Base() = default;

struct Derived : Base {
  void f(int) override {} //override
};

struct Base1 {
  virtual void f(int);
};

struct Derived1 : Base1 {
  void f(long int); //overload, diversa funzione
};

struct Base2 {
  virtual void f(int) const;
};

struct Derived2 : Base2 {
  void f(int); //overload, diversa funzione
};

int main() {
  Derived d;
  auto b = d;
  b.f(1);

//slicing

Derived rect{};
Base s = rect; //lost information, keep abstract (declare pure destructor)
}