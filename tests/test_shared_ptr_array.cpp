#include <gtest/gtest.h>
#include "shared_ptr.hpp"
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

TEST(SharedPtrArr, DefaultIsNull) {
    SharedPtr<int[]> arr;
    EXPECT_FALSE(arr);
    EXPECT_EQ(arr.get(), nullptr);
    EXPECT_EQ(arr.use_count(), 0);
}

TEST(SharedPtrArr, CreateFromPointer) {
    SharedPtr<int[]> arr(new int[3]{10, 20, 30});
    EXPECT_TRUE(arr);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr.use_count(), 1);
    EXPECT_TRUE(arr.unique());
}

TEST(SharedPtrArr, ModifyElements) {
    SharedPtr<int[]> arr(new int[3]{1, 2, 3});
    arr[0] = 100;
    arr[1] = 200;
    EXPECT_EQ(arr[0], 100);
    EXPECT_EQ(arr[1], 200);
}

TEST(SharedPtrArr, ConstAccess) {
    const SharedPtr<int[]> arr(new int[3]{10, 20, 30});
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[2], 30);
}

TEST(SharedPtrArr, CopyConstructor) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    SharedPtr<int[]> b = a;
    EXPECT_EQ(a.use_count(), 2);
    EXPECT_EQ(b.use_count(), 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_FALSE(a.unique());
}

TEST(SharedPtrArr, CopyAssignment) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    SharedPtr<int[]> b(new int[3]{5, 6, 7});
    b = a;
    EXPECT_EQ(a.use_count(), 2);
    EXPECT_EQ(b[0], 1);
}

TEST(SharedPtrArr, CopyThenReset) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    SharedPtr<int[]> b = a;
    b.reset();
    EXPECT_EQ(a.use_count(), 1);
    EXPECT_TRUE(a.unique());
    EXPECT_FALSE(b);
}

TEST(SharedPtrArr, MoveConstructor) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    SharedPtr<int[]> b(std::move(a));
    EXPECT_FALSE(a);
    EXPECT_EQ(a.use_count(), 0);
    EXPECT_EQ(b.use_count(), 1);
    EXPECT_EQ(b[0], 1);
}

TEST(SharedPtrArr, MoveAssignment) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    SharedPtr<int[]> b(new int[3]{5, 6, 7});
    b = std::move(a);
    EXPECT_FALSE(a);
    EXPECT_EQ(b.use_count(), 1);
    EXPECT_EQ(b[0], 1);
}

TEST(SharedPtrArr, UseCountMultiple) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    EXPECT_EQ(a.use_count(), 1);
    SharedPtr<int[]> b = a;
    EXPECT_EQ(a.use_count(), 2);
    SharedPtr<int[]> c = b;
    EXPECT_EQ(a.use_count(), 3);
    c.reset();
    EXPECT_EQ(a.use_count(), 2);
    b.reset();
    EXPECT_EQ(a.use_count(), 1);
    EXPECT_TRUE(a.unique());
}

TEST(SharedPtrArr, Reset) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    a.reset();
    EXPECT_FALSE(a);
    EXPECT_EQ(a.use_count(), 0);
}

TEST(SharedPtrArr, ResetShared) {
    SharedPtr<int[]> a(new int[2]{1, 2});
    SharedPtr<int[]> b = a;
    a.reset();
    EXPECT_FALSE(a);
    EXPECT_EQ(b.use_count(), 1);
    EXPECT_EQ(b[0], 1);
}


struct ArrayTracker {
    static int alive;
    ArrayTracker() { ++alive; }
    ~ArrayTracker() { --alive; }
};

int ArrayTracker::alive = 0;

TEST(SharedPtrArr, DestructorCalledForEachElementWhenCountZero) {
    ArrayTracker::alive = 0;
    {
        SharedPtr<ArrayTracker[]> a(new ArrayTracker[3]);
        EXPECT_EQ(ArrayTracker::alive, 3);
        SharedPtr<ArrayTracker[]> b = a;
        EXPECT_EQ(ArrayTracker::alive, 3);
        b.reset();
        EXPECT_EQ(ArrayTracker::alive, 3);
    }
    EXPECT_EQ(ArrayTracker::alive, 0);
}