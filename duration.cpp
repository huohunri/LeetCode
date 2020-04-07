#include <iostream>
#include <chrono>
 
constexpr auto year = 31556952ll; // 格里高利历年的平均秒数
 
int main()
{
    using shakes = std::chrono::duration<int, std::ratio<1, 100000000>>;
    using jiffies = std::chrono::duration<int, std::centi>;
    using microfortnights = std::chrono::duration<float, std::ratio<14*24*60*60, 1000000>>;
    using nanocenturies = std::chrono::duration<float, std::ratio<100*year, 1000000000>>;
 
    std::chrono::seconds sec(1);
 
    std::cout << "1 second is:\n";
 
    // 无精度损失的整数尺度转换：无转型
    std::cout << std::chrono::microseconds(sec).count() << " microseconds\n"
              << shakes(sec).count() << " shakes\n"
              << jiffies(sec).count() << " jiffies\n";
 
    // 有精度损失的整数尺度转换：需要转型
    std::cout << std::chrono::duration_cast<std::chrono::minutes>(sec).count()
              << " minutes\n";
 
    // 浮点尺度转换：无转型
    std::cout << microfortnights(sec).count() << " microfortnights\n"
              << nanocenturies(sec).count() << " nanocenturies\n";
}