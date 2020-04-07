#include <functional>
#include <thread>
#include <pthread.h>
#include <mutex>
using namespace std;
void printFirst()
{
    printf("%d\n",1);
}
void printSecond()
{
    printf("%d\n",2);
}
void printThird()
{
    printf("%d\n",3);
}
class  Foo
{
// User defined data may be declared here.
public:
    Foo()
    {
        pthread_barrier_init(&barr_second, NULL,2);
        pthread_barrier_init(&barr_third, NULL,3);
    }
    ~Foo()
    {
        pthread_barrier_destroy(&barr_second);
        pthread_barrier_destroy(&barr_third);
    }
    pthread_barrier_t barr_second;
    pthread_barrier_t barr_third;

    void third(function<void()> printThird) 
    {
        // printThird() outputs "third". Do not change or remove this line.
        pthread_barrier_wait(&barr_third);
        printThird();
    }

    void second(function<void()> printSecond) 
    {
        // printSecond() outputs "second". Do not change or remove this line.
        pthread_barrier_wait(&barr_second);
        printSecond();
        pthread_barrier_wait(&barr_third);
    }

    void first(function<void()> printFirst) 
    {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        pthread_barrier_wait(&barr_second);
        pthread_barrier_wait(&barr_third);
    }
};

int main()
{
    Foo foo;
    std::thread t1(&Foo::first,foo,printFirst);
    std::thread t2(&Foo::second,foo,printSecond);
    std::thread t3(&Foo::third,foo,printThird);
    t1.join();
    t2.join();
    t3.join();

    return 0;
}