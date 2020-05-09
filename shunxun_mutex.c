class Foo {
public:
    Foo() {
        m2.lock();
        m3.lock();
        
    }

    void first(function<void()> printFirst) {
        printFirst();
        m2.unlock();
    }

    void second(function<void()> printSecond) {
        m2.lock();
        printSecond();
        m3.unlock();
    }

    void third(function<void()> printThird) {
        m3.lock();
        printThird();
        m3.unlock();
    }
    
private:
    std::mutex m2, m3;
    
};

