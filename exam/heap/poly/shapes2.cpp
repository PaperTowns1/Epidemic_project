#include <memory>

struct Point {
  int x;
  int y;
};

struct Shape {
  Point p;
  Shape(Point p) : p{p} {}

  virtual Point where() const { return p; };
  virtual ~Shape();
};

struct Circle : Shape {
  // Point center;
  int radius;

  Circle(Point p, double d) : Shape{p}, radius{d} {}
  ~Circle();
  // Point where() const override {return p;}
};

struct Rectangle : Shape {
  // Point up_left;
  Point bottom_right;

  Rectangle(Point p1, Point p2) : Shape{p1}, bottom_right{p2} {}
  ~Rectangle();
  // Point where() const override {return p;}
};

int main() {
  std::unique_ptr<Shape> s;
  s->where();
}