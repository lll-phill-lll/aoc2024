#include <iostream>
#include <algorithm>

class MyClass {
public:
    MyClass(int val) {
        std::cout << (void*)this << "# MyClass constructor called with " << val << std::endl;
        this->val = val;
    }

    MyClass(const MyClass &other) {
        std::cout << (void*)this << "# Copy constructor called" << std::endl;
        this->val = other.val;
    }

    MyClass(MyClass &&other) {
        std::cout << (void*)this << "# Move constructor called" << std::endl;
        this->val = other.val;
        other.val = 0; // предотвращаем использование перемещённого объекта
    }

    MyClass &operator=(const MyClass &other) {
        std::cout << (void*)this << "# Assignment operator called" << std::endl;
        this->val = other.val;
        return *this;
    }

    int getVal() {
        return val;
    }
private:
    int val;
};

void Process(MyClass& a, MyClass& b) {
    std::cout << "[PROCESS] A: " << a.getVal() << ", B: " << b.getVal() << std::endl; 
    auto& c = (a.getVal() > b.getVal()) ? a : b;
    std::cout << "[PROCESS] A: " << a.getVal() << ", B: " << b.getVal() << std::endl; 

}

int main() {
    MyClass a(5);
    MyClass b(10);
    std::cout << "[MAIN] A: " << a.getVal() << ", B: " << b.getVal() << std::endl; 

    Process(a, b);

    std::cout << "[MAIN] A: " << a.getVal() << ", B: " << b.getVal() << std::endl; 


    return 0;
}
