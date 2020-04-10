#include <functional>
#include <thread>
#include <pthread.h>
#include<semaphore.h>
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

class FooBar {
private:
    int n;
    sem_t odd_sem,even_sem;
public:
    FooBar() {
        
    }
    FooBar(int n) {
        this->n = n;
        sem_init(&odd_sem,0,0);
        sem_init(&even_sem,0,1);
    }

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n; ++i) {
            sem_wait(&even_sem);
            printFoo();
            sem_post(&odd_sem);
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n; ++i) {
            sem_wait(&odd_sem);
        	printBar();
            sem_post(&even_sem);
        }
    }
};

int main()
{
    FooBar foobar(10);
    std::thread t1(&FooBar::foo,foobar,printFirst);
    std::thread t2(&FooBar::bar,foobar,printSecond);

    t1.join();
    t2.join();
  
    return 0;
}