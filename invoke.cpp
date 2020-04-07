#include <functional>
#include <iostream>
using namespace std;
struct Foo {
    Foo(int num) : num_(num) {}
    void print_add(int i) const { std::cout << num_+i << '\n'; }
    int num_;
};
 
void print_num(int i)
{
    std::cout << i << '\n';
}
 
struct PrintNum {
    void operator()(int i) const
    {
        std::cout << i << '\n';
    }
};
 
int main()
{
    // 调用自由函数
    std::invoke(print_num, -9);
 
    // 调用 lambda
    std::invoke([]() { print_num(42); });
 
    // 调用成员函数
    const Foo foo(314159);
    std::invoke(&Foo::print_add, foo, 1);
 
    // 调用（访问）数据成员
    std::cout << "num_: " << std::invoke(&Foo::num_, foo) << '\n';
 
    // 调用函数对象
    std::invoke(PrintNum(), 18);
}