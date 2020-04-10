// // foo 是否声明为 noexcept 取决于 T() 是否抛任何异常
// template <class T>
//   void foo() noexcept(noexcept(T())) {}
 
// void bar() noexcept(true) {}
// void baz() noexcept { throw 42; }  // noexcept 等同于 noexcept(true)
 
//  class aaaa
//  {
     
//  };

// int main() 
// {
//     foo<int>();  // noexcept(noexcept(int())) => noexcept(true)，故这是可以的
 
//     bar();  // 可以
//     //baz();  // 能编译，但在运行时会调用 std::terminate

//     foo<aaaa>();

//     return 0;
// }

struct A {
  A(int = (A(5), 0)) noexcept;
  A(const A&) noexcept;
  A(A&&) noexcept;
  ~A();
};
struct B {
  B() throw();
  B(const B&) = default; // 隐式异常说明是 noexcept(true)
  B(B&&, int = (throw Y(), 0)) noexcept;
  ~B() noexcept(false);
};
int n = 7;
struct D : public A, public B {
  int * p = new int[n];
  // D::D() 潜在抛出，因为 new 运算符
  // D::D(const D&) 不抛出
  // D::D(D&&) 潜在抛出：因为 B 的构造函数的默认实参可能抛出
  // D::~D() 潜在抛出
 
  // 注意：若 A::~A() 为虚，则此程序将为非良构，因为不抛出虚函数的覆盖函数不能为潜在抛出
};


int main()
{
    return 0;
}