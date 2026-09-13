#pragma once

#include <type_traits>
#include <cstddef>

template <typename T>
class UniquePtrArray{
private:
    T* ptr;
public:
    UniquePtrArray(T* p = nullptr) : ptr(p) {}
    ~UniquePtrArray() {delete[] ptr;}

    UniquePtrArray(const UniquePtrArray&) = delete;
    UniquePtrArray& operator=(const UniquePtrArray&) = delete;

    UniquePtrArray(UniquePtrArray&& other) noexcept;
    UniquePtrArray& operator=(UniquePtrArray&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    UniquePtrArray(UniquePtrArray<U>&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    UniquePtrArray& operator=(UniquePtrArray<U>&& other) noexcept;

    T& operator[](std::size_t i) const { return ptr[i]; }
    const T& operator[](std::size_t i) const { return ptr[i]; }

    explicit operator bool() const { return ptr != nullptr; }

    T* get() const { return ptr; }
    T* release();

    void reset(T* p = nullptr);
};







template <typename T>
UniquePtrArray<T>::UniquePtrArray(UniquePtrArray&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

template <typename T>
UniquePtrArray<T>& UniquePtrArray<T>::operator=(UniquePtrArray&& other) noexcept {
    if (this != &other) {
        delete[] ptr;
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    return *this;
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
UniquePtrArray<T>::UniquePtrArray(UniquePtrArray<U>&& other) noexcept : ptr(other.release()) {}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
UniquePtrArray<T>& UniquePtrArray<T>::operator=(UniquePtrArray<U>&& other) noexcept {
    if (static_cast<void*>(this) != static_cast<void*>(&other)) {
        delete[] ptr;
        ptr = other.release();
    }
    return *this;
}

template <typename T>
T* UniquePtrArray<T>::release() {
    T* tmp = ptr;
    ptr = nullptr;
    return tmp;
}

template <typename T>
void UniquePtrArray<T>::reset(T* p) {
    if (ptr != p) {
        delete[] ptr;
        ptr = p;
    }
}