struct Point {
  int x;
  int y;
};

class Shape {
 protected:
  Point p;

 public:
  Shape(Point p) : p{p} {}

  virtual Point where() const { return p; };
  virtual ~Shape();
};

class Circle : Shape {
 private:
  int radius;

 public:
  Circle(Point p, double d) : Shape{p}, radius{d} {}
  ~Circle();
  // use p..., where...
};
