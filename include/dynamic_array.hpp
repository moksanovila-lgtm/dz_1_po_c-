#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>
#include "unique_ptr.hpp"

template <typename T>
class DynamicArray {
private:
    UniquePtr<T[]> data;   
    std::size_t size;

public:
    DynamicArray() : size(0) {}
    ~DynamicArray() = default;

    DynamicArray(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;

    DynamicArray(DynamicArray&& other) noexcept;
    DynamicArray& operator=(DynamicArray&& other) noexcept;

    void Append(const T& value);
    void Prepend(const T& value);
    void InsertAt(std::size_t index, const T& value);

    T& Get(std::size_t i);
    const T& Get(std::size_t i) const;

    UniquePtr<T> Copy(std::size_t i) const;

    std::size_t Size() const { return size; }
    bool IsEmpty() const { return size == 0; }

    void RemoveAt(std::size_t i);
    void Clear();
};




template <typename T>
DynamicArray<T>::DynamicArray(DynamicArray&& other) noexcept
    : data(std::move(other.data)), size(other.size) {
    other.size = 0;
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray&& other) noexcept {
    if (this != &other) {
        data = std::move(other.data);
        size = other.size;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void DynamicArray<T>::Append(const T& value) {
    UniquePtr<T[]> newData(new T[size + 1]);
    for (std::size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }
    newData[size] = value;
    data = std::move(newData);
    ++size;
}

template <typename T>
void DynamicArray<T>::Prepend(const T& value) {
    UniquePtr<T[]> newData(new T[size + 1]);
    newData[0] = value;
    for (std::size_t i = 0; i < size; ++i) {
        newData[i + 1] = data[i];
    }
    data = std::move(newData);
    ++size;
}

template <typename T>
void DynamicArray<T>::InsertAt(std::size_t index, const T& value) {
    if (index > size) {
        throw std::out_of_range("InsertAt: index out of range");
    }
    UniquePtr<T[]> newData(new T[size + 1]);
    for (std::size_t i = 0; i < index; ++i) {
        newData[i] = data[i];
    }
    newData[index] = value;
    for (std::size_t i = index; i < size; ++i) {
        newData[i + 1] = data[i];
    }
    data = std::move(newData);
    ++size;
}

template <typename T>
T& DynamicArray<T>::Get(std::size_t i) {
    if (i >= size) {
        throw std::out_of_range("Get: index out of range");
    }
    return data[i];
}

template <typename T>
const T& DynamicArray<T>::Get(std::size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Get: index out of range");
    }
    return data[i];
}

template <typename T>
UniquePtr<T> DynamicArray<T>::Copy(std::size_t i) const {
    if (i >= size) {
        throw std::out_of_range("Copy: index out of range");
    }
    return UniquePtr<T>(new T(data[i]));
}

template <typename T>
void DynamicArray<T>::RemoveAt(std::size_t i) {
    if (i >= size) {
        throw std::out_of_range("RemoveAt: index out of range");
    }
    if (size == 1) {
        Clear();
        return;
    }
    UniquePtr<T[]> newData(new T[size - 1]);
    for (std::size_t j = 0; j < i; ++j) {
        newData[j] = data[j];
    }
    for (std::size_t j = i + 1; j < size; ++j) {
        newData[j - 1] = data[j];
    }
    data = std::move(newData);
    --size;
}

template <typename T>
void DynamicArray<T>::Clear() {
    data.reset();
    size = 0;
}