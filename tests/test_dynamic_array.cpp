#include <gtest/gtest.h>
#include "dynamic_array.hpp"
#include <string>
#include <utility>

struct Tracker {
    static int alive;
    Tracker() { ++alive; }
    ~Tracker() { --alive; }
};

int Tracker::alive = 0;


TEST(DynamicArray, DefaultIsEmpty) {
    DynamicArray<int> arr;
    EXPECT_TRUE(arr.IsEmpty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST(DynamicArray, AppendIncreasesSize) {
    DynamicArray<int> arr;
    arr.Append(10);
    EXPECT_EQ(arr.Size(), 1u);
    EXPECT_FALSE(arr.IsEmpty());
    arr.Append(20);
    EXPECT_EQ(arr.Size(), 2u);
}


TEST(DynamicArray, AppendAndGet) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 20);
    EXPECT_EQ(arr.Get(2), 30);
}

TEST(DynamicArray, GetModifiesInPlace) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Get(0) = 100;
    EXPECT_EQ(arr.Get(0), 100);
}

TEST(DynamicArray, GetOutOfRange) {
    DynamicArray<int> arr;
    arr.Append(10);
    EXPECT_THROW(arr.Get(1), std::out_of_range);
}


TEST(DynamicArray, Prepend) {
    DynamicArray<int> arr;
    arr.Append(20);
    arr.Append(30);
    arr.Prepend(10);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 20);
    EXPECT_EQ(arr.Get(2), 30);
}


TEST(DynamicArray, InsertAtMiddle) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(30);
    arr.InsertAt(1, 20);
    EXPECT_EQ(arr.Size(), 3u);
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 20);
    EXPECT_EQ(arr.Get(2), 30);
}

TEST(DynamicArray, InsertAtBeginning) {
    DynamicArray<int> arr;
    arr.Append(20);
    arr.InsertAt(0, 10);
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 20);
}

TEST(DynamicArray, InsertAtEnd) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.InsertAt(1, 20);
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 20);
}

TEST(DynamicArray, InsertAtOutOfRange) {
    DynamicArray<int> arr;
    arr.Append(10);
    EXPECT_THROW(arr.InsertAt(5, 99), std::out_of_range);
}


TEST(DynamicArray, CopyIsIndependent) {
    DynamicArray<int> arr;
    arr.Append(42);
    UniquePtr<int> p = arr.Copy(0);
    EXPECT_EQ(*p, 42);
    *p = 999;
    EXPECT_EQ(*p, 999);
    EXPECT_EQ(arr.Get(0), 42);
}

TEST(DynamicArray, CopyOutOfRange) {
    DynamicArray<int> arr;
    EXPECT_THROW(arr.Copy(0), std::out_of_range);
}


TEST(DynamicArray, RemoveAtMiddle) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);
    arr.RemoveAt(1);
    EXPECT_EQ(arr.Size(), 2u);
    EXPECT_EQ(arr.Get(0), 10);
    EXPECT_EQ(arr.Get(1), 30);
}

TEST(DynamicArray, RemoveAtBeginning) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.RemoveAt(0);
    EXPECT_EQ(arr.Get(0), 20);
}

TEST(DynamicArray, RemoveAtOnlyElement) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.RemoveAt(0);
    EXPECT_TRUE(arr.IsEmpty());
    EXPECT_EQ(arr.Size(), 0u);
}

TEST(DynamicArray, RemoveAtOutOfRange) {
    DynamicArray<int> arr;
    EXPECT_THROW(arr.RemoveAt(0), std::out_of_range);
}


TEST(DynamicArray, Clear) {
    DynamicArray<int> arr;
    arr.Append(10);
    arr.Append(20);
    arr.Append(30);
    arr.Clear();
    EXPECT_TRUE(arr.IsEmpty());
    EXPECT_EQ(arr.Size(), 0u);
}


TEST(DynamicArray, MoveConstructor) {
    DynamicArray<int> a;
    a.Append(10);
    a.Append(20);
    DynamicArray<int> b(std::move(a));
    EXPECT_TRUE(a.IsEmpty());
    EXPECT_EQ(b.Size(), 2u);
    EXPECT_EQ(b.Get(0), 10);
}

TEST(DynamicArray, MoveAssignment) {
    DynamicArray<int> a;
    a.Append(10);
    a.Append(20);
    DynamicArray<int> b;
    b.Append(99);
    b = std::move(a);
    EXPECT_TRUE(a.IsEmpty());
    EXPECT_EQ(b.Size(), 2u);
    EXPECT_EQ(b.Get(0), 10);
}


TEST(DynamicArray, DestructorCallsElementDestructors) {
    Tracker::alive = 0;
    {
        DynamicArray<Tracker> arr;
        arr.Append(Tracker{});
        arr.Append(Tracker{});
        arr.Append(Tracker{});
        EXPECT_EQ(Tracker::alive, 3);
    }
    EXPECT_EQ(Tracker::alive, 0);
}