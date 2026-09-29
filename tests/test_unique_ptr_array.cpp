#include <gtest/gtest.h>
#include "unique_ptr.hpp"
#include <string>
#include <utility>


struct Animal {
    virtual ~Animal() = default;
    virtual std::string name() const { return "Animal"; }
};

struct Cat : Animal {
    std::string name() const override { return "Cat"; }
};

struct Dog : Animal {
    std::string name() const override { return "Dog"; }
};

TEST(UniquePtrArr, DefaultIsNull) {
    UniquePtr<int[]> arr;
    EXPECT_FALSE(arr);
    EXPECT_EQ(arr.get(), nullptr);
}

TEST(UniquePtrArr, CreateAndIndex) {
    UniquePtr<int[]> arr(new int[3]{10, 20, 30});

    EXPECT_TRUE(arr);
    EXPECT_NE(arr.get(), nullptr);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
}

TEST(UniquePtrArr, ModifyElements) {
    UniquePtr<int[]> arr(new int[3]{1, 2, 3});
    arr[0] = 100;
    arr[1] = 200;
    arr[2] = 300;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
    EXPECT_EQ(arr[2], 300);
}

TEST(UniquePtrArr, MoveConstructor) {
    UniquePtr<int[]> arr(new int[2]{1, 2});
    UniquePtr<int[]> arr2(std::move(arr));
    EXPECT_FALSE(arr);
    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_TRUE(arr2);
    EXPECT_EQ(arr2[0], 1);
    EXPECT_EQ(arr2[1], 2);
}

TEST(UniquePtrArr, MoveAssignment) {
    UniquePtr<int[]> a(new int[2]{1, 2});
    UniquePtr<int[]> b(new int[3]{5, 6, 7});
    b = std::move(a);
    EXPECT_FALSE(a);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
}

TEST(UniquePtrArr, Release) {
    UniquePtr<int[]> arr(new int[2]{5, 10});
    int* raw = arr.release();
    EXPECT_FALSE(arr);
    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_NE(raw, nullptr);
    EXPECT_EQ(raw[0], 5);
    EXPECT_EQ(raw[1], 10);
    delete[] raw;
}

TEST(UniquePtrArr, Reset) {
    UniquePtr<int[]> arr(new int[2]{1, 2});
    arr.reset(new int[3]{10, 20, 30});
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[2], 30);
    arr.reset();
    EXPECT_FALSE(arr);
    EXPECT_EQ(arr.get(), nullptr);
}

struct ArrayTracker {
    static int alive;
    ArrayTracker() { ++alive; }
    ~ArrayTracker() { --alive; }
};

int ArrayTracker::alive = 0;

TEST(UniquePtrArr, DestructorCalledForEachElement) {
    ArrayTracker::alive = 0;
    {
        UniquePtr<ArrayTracker[]> arr(new ArrayTracker[3]);
        EXPECT_EQ(ArrayTracker::alive, 3);
    }
    EXPECT_EQ(ArrayTracker::alive, 0);
}