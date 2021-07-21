#include <iostream>
#include <memory>

template <typename Pointee>
class UniquePtr {
  Pointee* m_p;

 public:
  explicit UniquePtr(Pointee* p) : m_p{p} {}
  ~UniquePtr() { delete m_p; }
  UniquePtr(UniquePtr const&) = delete;
  UniquePtr& operator=(UniquePtr const&) = delete;
  UniquePtr(UniquePtr&& o) noexcept
      : m_p{std::exchange(o.m_p, nullptr)} {}
  UniquePtr& operator=(UniquePtr&& o) noexcept {
    delete m_p;
    m_p = std::exchange(o.m_p, nullptr);
    return *this;
  }

  Pointee* operator->() { return m_p; }
  Pointee* operator*() { return *m_p; }
};

class C {
  int m_a;

 public:
  C(int a = 0) : m_a{a} {}
  void print() { std::cout << m_a << '\n'; }
};

void take(std::unique_ptr<C> q);
void take2(std::shared_ptr<C> q);

int main() {
  UniquePtr<C> p{new C{2}};
  p->print();

  // std::unique_ptr<C> p2{new C{1}};
  auto p2 = std::make_unique<C>();
  //take(p3) error
  take(std::move(p2));

  UniquePtr<int> a{new int{42}};
  auto b{std::move(a)};

  UniquePtr<int> c{new int{12}};
  UniquePtr<int> d{new int{32}};
  d = std::move(c);

  //std::shared_ptr<C> p3{new c{1}};
  auto p3 = std::make_shared<C>();
  take2(p3);
  take2(std::move(p3));
}