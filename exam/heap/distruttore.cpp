#include <iostream>

class Vector {
  int size = 0;
  int* data = nullptr;

 public:
  Vector(int n = 0, int v = int{})
      : size{n}, data{new int[size]} {  // costruttore
    std::fill(data, data + size, v);
  }
  ~Vector() { delete[] data; }  // distruttore

  Vector(Vector const& o)
      : size{o.size}, data{new int[size]} {  // copy costructor
    std::copy(o.data, o.data + size, data);
  }
  

  Vector& operator=(Vector const& o) {  // copy assignment
    if (this != &o) {
      delete[] data;
      size = o.size;
      data = new int[size];
      std::copy(o.data, o.data + size, data);
    }
    return *this;
  }

  int get_size() const { return size; }
};

int main() {
  Vector c{1, 2};
  Vector c2{};
  Vector c1 = c;
  c2 = c;

  std::cout << c.get_size() << '\t' << c1.get_size() << '\t' << c2.get_size()
            << '\n';
}