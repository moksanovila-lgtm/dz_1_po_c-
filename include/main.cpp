#include <iostream>
#include <memory>
#include "unique_ptr.hpp"

int main(){
    std::unique_ptr<int> ptr;
    std::unique_ptr<int> ptr2 {};
    std::unique_ptr<int> ptr_3 {nullptr};
    
    if(!ptr) ptr = std::make_unique<int>(10);
    *ptr = 7;
    std::cout << *ptr << std::endl;

    return 0;
}

    std::shared_ptr<int> ptr {std::make_shared<int>(3)};
    std::shared_ptr<int> ptr2 {};
    std::shared_ptr<int> ptr3 {nullptr};
    std::shared_ptr<int> ptr4 {ptr};
    UniquePtr<int> p = new int(10);



    UniquePtr<int> p(new int(10));
    
    struct Animal {virtual ~Animal() = default;};
    struct Cat : Animal {};
    UniquePtr<Cat> cat(new Cat);
    UniquePtr<Animal> animal(std::move(cat));

    struct Dog : Animal {};
    UniquePtr<Animal> animal(new Dog);
    UniquePtr<Cat> cat(new Cat);

    animal = std::move(cat);




    UniquePtr<int> p(new int(42));
    p.reset()
    int* raw = p.release();
    
    