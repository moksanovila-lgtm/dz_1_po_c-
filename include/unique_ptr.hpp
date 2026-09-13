#pragma once 

#include <type_traits>

template <typename T>
class UniquePtr{
private:
    T* ptr;
public:
    UniquePtr(T* p = nullptr) : ptr(p) {}
    ~UniquePtr() {delete ptr;}

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;

    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    UniquePtr(UniquePtr<U>&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    UniquePtr& operator=(UniquePtr<U>&& other) noexcept;

    T& operator*() const {return *ptr;}
    T* operator->() const {return ptr;}
    T*get() const {return ptr;}

    explicit operator bool() const { return ptr != nullptr; }

    T* release();

    void reset(T* p = nullptr);
};





template <typename T>
UniquePtr<T>::UniquePtr(UniquePtr&& other) noexcept :ptr(other.ptr) {
    other.ptr = nullptr;
}

template <typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr&& other) noexcept {
    if(this != &other){
        delete ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
T* UniquePtr<T>::release(){
    T* tmp = ptr;
    ptr = nullptr;
    return tmp;
}

template <typename T>
void UniquePtr<T>::reset(T* p){
    if(ptr != p){
        delete ptr;
        ptr = p;
    }
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
UniquePtr<T>::UniquePtr(UniquePtr<U>&& other) noexcept : ptr(other.release()) {}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<U>&& other) noexcept {
    if (static_cast<void*>(this) != static_cast<void*>(&other)) {
        delete ptr;
        ptr = other.release();
    }
    return *this;
}
