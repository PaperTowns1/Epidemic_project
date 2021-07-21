#include <memory> 

struct Point {
  int x;
  int y;
};

struct Shape {
  virtual Point where() const = 0;
  virtual ~Shape();
};

struct Circle : Shape {
  Point center;
  int radius;

  ~Circle();
  Point where() const override {return center;}
};

struct Rectangle : Shape {
  Point up_left;
  Point bottom_right;

  ~Rectangle();
  Point where() const override {return up_left;}
};

int main() {
  std::unique_ptr<Shape> s;
  s->where();
}