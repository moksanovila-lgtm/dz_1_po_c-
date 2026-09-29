#pragma once

#include <cstddef>
#include <type_traits>
#include <utility>



template <typename T>
class SharedPtr {
    template <typename> friend class SharedPtr;

    static_assert(!std::is_array_v<T>, "Use SharedPtr<T[]> for arrays");

private:
    T* ptr;
    int* ref_count;

    void ReleaseOwnership() noexcept;

public:
    SharedPtr() noexcept : ptr(nullptr), ref_count(nullptr) {}

    SharedPtr(T* p) : ptr(p), ref_count(p ? new int(1) : nullptr) {}

    SharedPtr(std::nullptr_t) noexcept : ptr(nullptr), ref_count(nullptr) {}

    SharedPtr(const SharedPtr& other) noexcept;
    SharedPtr& operator=(const SharedPtr& other) noexcept;

    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtr(const SharedPtr<U>& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtr(SharedPtr<U>&& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtr& operator=(const SharedPtr<U>& other) noexcept;

    template <typename U>
    requires std::is_base_of_v<T, U>
    SharedPtr& operator=(SharedPtr<U>&& other) noexcept;

    ~SharedPtr();

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* get() const { return ptr; }
    explicit operator bool() const { return ptr != nullptr; }

    int use_count() const { return ref_count ? *ref_count : 0; }
    bool unique() const { return use_count() == 1; }

    void reset() noexcept;
};




template <typename T>
class SharedPtr<T[]> {
    template <typename> friend class SharedPtr;

private:
    T* ptr;
    int* ref_count;

    void ReleaseOwnership() noexcept;

public:
    SharedPtr() noexcept : ptr(nullptr), ref_count(nullptr) {}

    SharedPtr(T* p) : ptr(p), ref_count(p ? new int(1) : nullptr) {}

    SharedPtr(std::nullptr_t) noexcept : ptr(nullptr), ref_count(nullptr) {}

    SharedPtr(const SharedPtr& other) noexcept;
    SharedPtr& operator=(const SharedPtr& other) noexcept;

    SharedPtr(SharedPtr&& other) noexcept;
    SharedPtr& operator=(SharedPtr&& other) noexcept;

    ~SharedPtr();

    T& operator[](std::size_t i) const { return ptr[i]; }   
    T* get() const { return ptr; }
    explicit operator bool() const { return ptr != nullptr; }

    int use_count() const { return ref_count ? *ref_count : 0; }
    bool unique() const { return use_count() == 1; }

    void reset() noexcept;
};




template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& other) noexcept
    : ptr(other.ptr), ref_count(other.ref_count) {
    if (ref_count) ++(*ref_count);
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other) noexcept {
    if (this != &other) {
        ReleaseOwnership();
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) ++(*ref_count);
    }
    return *this;
}

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept
    : ptr(other.ptr), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other) noexcept {
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
SharedPtr<T>::SharedPtr(const SharedPtr<U>& other) noexcept
    : ptr(other.get()), ref_count(other.ref_count) {
    if (ref_count) ++(*ref_count);
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
SharedPtr<T>::SharedPtr(SharedPtr<U>&& other) noexcept
    : ptr(other.get()), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
}

template <typename T>
template <typename U>
requires std::is_base_of_v<T, U>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<U>& other) noexcept {
    if (static_cast<const void*>(this) != static_cast<const void*>(&other)) {
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
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<U>&& other) noexcept {
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
SharedPtr<T>::~SharedPtr() {
    ReleaseOwnership();
}

template <typename T>
void SharedPtr<T>::ReleaseOwnership() noexcept {
    if (ref_count && --(*ref_count) == 0) {
        delete ptr;              
        delete ref_count;
    }
    ptr = nullptr;
    ref_count = nullptr;
}

template <typename T>
void SharedPtr<T>::reset() noexcept {
    ReleaseOwnership();
}

template <typename T>
SharedPtr<T[]>::SharedPtr(const SharedPtr& other) noexcept
    : ptr(other.ptr), ref_count(other.ref_count) {
    if (ref_count) ++(*ref_count);
}

template <typename T>
SharedPtr<T[]>& SharedPtr<T[]>::operator=(const SharedPtr& other) noexcept {
    if (this != &other) {
        ReleaseOwnership();
        ptr = other.ptr;
        ref_count = other.ref_count;
        if (ref_count) ++(*ref_count);
    }
    return *this;
}

template <typename T>
SharedPtr<T[]>::SharedPtr(SharedPtr&& other) noexcept
    : ptr(other.ptr), ref_count(other.ref_count) {
    other.ptr = nullptr;
    other.ref_count = nullptr;
}

template <typename T>
SharedPtr<T[]>& SharedPtr<T[]>::operator=(SharedPtr&& other) noexcept {
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
SharedPtr<T[]>::~SharedPtr() {
    ReleaseOwnership();
}

template <typename T>
void SharedPtr<T[]>::ReleaseOwnership() noexcept {
    if (ref_count && --(*ref_count) == 0) {
        delete[] ptr;            
        delete ref_count;
    }
    ptr = nullptr;
    ref_count = nullptr;
}

template <typename T>
void SharedPtr<T[]>::reset() noexcept {
    ReleaseOwnership();
}
