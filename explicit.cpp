struct S {
    explicit (S)(const S&);    // C++20 中错误，C++17 中 OK
    explicit (operator int)(); // C++20 中错误，C++17 中 OK
};

struct A
{
    A(int) { }      // 转换构造函数
    A(int, int) { } // 转换构造函数 (C++11)
    operator bool() const { return true; }
};
 
struct B
{
    explicit B(int) { }
    explicit B(int, int) { }
    explicit operator bool() const { return true; }
};
 
int main()
{
    A a1 = 1;      // OK：复制初始化选择 A::A(int)
    A a2(2);       // OK：直接初始化选择 A::A(int)
    A a3 {4, 5};   // OK：直接列表初始化选择 A::A(int, int)
    A a4 = {4, 5}; // OK：复制列表初始化选择 A::A(int, int)
    A a5 = (A)1;   // OK：显式转型进行 static_cast
    if (a1) ;      // OK：A::operator bool()
    bool na1 = a1; // OK：复制初始化选择 A::operator bool()
    bool na2 = static_cast<bool>(a1); // OK：static_cast 进行直接初始化
 
//  B b1 = 1;      // 错误：复制初始化不考虑 B::B(int)
    B b2(2);       // OK：直接初始化选择 B::B(int)
    B b3 {4, 5};   // OK：直接列表初始化选择 B::B(int, int)
//  B b4 = {4, 5}; // 错误：复制列表初始化不考虑 B::B(int,int)
    B b5 = (B)1;   // OK：显式转型进行 static_cast
    if (b2) ;      // OK：B::operator bool()
//  bool nb1 = b2; // 错误：复制初始化不考虑 B::operator bool()
    bool nb2 = static_cast<bool>(b2); // OK：static_cast 进行直接初始化

    B b4 = static_cast<B>(b3);

    return 0;
}