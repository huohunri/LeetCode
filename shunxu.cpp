
#include <semaphore.h>
#include <functional>
using namespace std;
class Foo {
public:
    sem_t sem_one;
    sem_t sem_two;
    sem_t sem_three;
 


    void first(function<void()> printFirst) {
        
        // printFirst() outputs "first". Do not change or remove this line.
        sem_wait(&sem_one);
        printFirst();
        sem_post(&sem_two);
    }

    void second(function<void()> printSecond) {
        
        // printSecond() outputs "second". Do not change or remove this line.
        sem_wait(&sem_two);
        printSecond();
        sem_post(&sem_three);
    }

    void third(function<void()> printThird) {
        
        // printThird() outputs "third". Do not change or remove this line.
        sem_wait(&sem_three);
        printThird();
    }
};

