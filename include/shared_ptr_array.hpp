#pragma once

#include <cstddef>
#include <type_traits>

template <typename T>
class SharedPtrArray{
private:
    T* ptr;
    int* ref_count;

    void ReleaseOwnership() noexcept;
public:
    SharedPtrArray(T* p = nullptr) : ptr(p), ref_count(p ? new int(1) : nullptr) {}
    ~SharedPtrArray();


    SharedPtrArray(const SharedPtrArray& other);
    SharedPtrArray& operator=(const SharedPtrArray& other);

    SharedPtrArray(SharedPtrArray&& other) noexcept;
    SharedPtrArray& operator=(SharedPtrArray&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtrArray(const SharedPtrArray<U>& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtrArray(SharedPtrArray<U>&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtrArray& operator=(const SharedPtrArray<U>& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtrArray& operator=(SharedPtrArray<U>&& other) noexcept;

    T& operator[](std::size_t i) {return ptr[i];}
    const T& operator[](std::size_t i) {return ptr[i];}

    T* get() const {return ptr;}
    int use_count() const {return ref_count ? *ref_count : 0;}
    bool unique() const {return use_count() == 1;}

    void reset() noexcept;
};





template <typename T>
SharedPtrArray<T>::SharedPtrArray(const SharedPtrArray& other) 
    : ptr(other.ptr), ref_count(other.ref_count) {
    if (ref_count) ++(*ref_count);
}

template <typename T>
SharedPtrArray<T>& SharedPtrArray<T>::operator=(const SharedPtrArray& other) {
    if (this != &other) {
        ReleaseOwnership();
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) ++(*ref_count);
    }
    return *this;
}

template <typename T>
SharedPtrArray<T>::SharedPtrArray(SharedPtrArray&& other) noexcept
    : ptr(other.ptr), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
}

template <typename T>
SharedPtrArray<T>& SharedPtrArray<T>::operator=(SharedPtrArray&& other) noexcept {
    if (this != &other) {
        ReleaseOwnership();
        ptr = other.ptr;
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }
    return *this;
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
SharedPtrArray<T>::SharedPtrArray(const SharedPtrArray<U>& other) noexcept
    : ptr(other.get()), ref_count(other.ref_count) {
    if (ref_count) ++(*ref_count);
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
SharedPtrArray<T>::SharedPtrArray(SharedPtrArray<U>&& other) noexcept
    : ptr(other.get()), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
SharedPtrArray<T>& SharedPtrArray<T>::operator=(const SharedPtrArray<U>& other) noexcept {
    if (static_cast<void*>(this) != static_cast<void*>(&other)) {
        ReleaseOwnership();
        ptr = other.get();
        ref_count = other.ref_count;
        if (ref_count) ++(*ref_count);
    }
    return *this;
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
SharedPtrArray<T>& SharedPtrArray<T>::operator=(SharedPtrArray<U>&& other) noexcept {
    if (static_cast<void*>(this) != static_cast<void*>(&other)) {
        ReleaseOwnership();
        ptr = other.get();
        ref_count = other.ref_count;
        other.ptr = nullptr;
        other.ref_count = nullptr;
    }
    return *this;
}

template <typename T>
SharedPtrArray<T>::~SharedPtrArray() {
    ReleaseOwnership();
}

template <typename T>
void SharedPtrArray<T>::ReleaseOwnership() noexcept {
    if (ref_count && --(*ref_count) == 0) {
        delete[] ptr;       
        delete ref_count;    
    }
    ptr = nullptr;
    ref_count = nullptr;
}

template <typename T>
void SharedPtrArray<T>::reset() noexcept {
    ReleaseOwnership();
}

