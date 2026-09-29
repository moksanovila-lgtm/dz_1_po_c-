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


TEST(SharedPtr, DefaultIsNull) {
    SharedPtr<int> p;
    EXPECT_FALSE(p);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_EQ(p.use_count(), 0);
}

TEST(SharedPtr, CreateFromPointer) {
    SharedPtr<int> p(new int(42));
    EXPECT_TRUE(p);
    EXPECT_EQ(*p, 42);
    EXPECT_EQ(p.use_count(), 1);
    EXPECT_TRUE(p.unique());
}

TEST(SharedPtr, CopyConstructor) {
    SharedPtr<int> p(new int(42));
    SharedPtr<int> q = p;
    EXPECT_EQ(p.use_count(), 2);
    EXPECT_EQ(q.use_count(), 2);
    EXPECT_EQ(*p, 42);
    EXPECT_EQ(*q, 42);
    EXPECT_FALSE(p.unique());
    EXPECT_FALSE(q.unique());
}

TEST(SharedPtr, CopyAssignment) {
    SharedPtr<int> p(new int(1));
    SharedPtr<int> q(new int(2));
    q = p;
    EXPECT_EQ(p.use_count(), 2);
    EXPECT_EQ(q.use_count(), 2);
    EXPECT_EQ(*q, 1);   
}

TEST(SharedPtr, CopyThenReset) {
    SharedPtr<int> p(new int(42));
    SharedPtr<int> q = p;
    EXPECT_EQ(p.use_count(), 2);
    q.reset();
    EXPECT_EQ(p.use_count(), 1);
    EXPECT_TRUE(p.unique());
    EXPECT_FALSE(q);
}

TEST(SharedPtr, MoveConstructor) {
    SharedPtr<int> p(new int(7));
    SharedPtr<int> q(std::move(p));
    EXPECT_FALSE(p);
    EXPECT_EQ(p.use_count(), 0);
    EXPECT_TRUE(q);
    EXPECT_EQ(*q, 7);
    EXPECT_EQ(q.use_count(), 1);   
}

TEST(SharedPtr, MoveAssignment) {
    SharedPtr<int> p(new int(1));
    SharedPtr<int> q(new int(2));
    q = std::move(p);
    EXPECT_FALSE(p);
    EXPECT_EQ(q.use_count(), 1);
    EXPECT_EQ(*q, 1);
}

TEST(SharedPtr, UseCountMultiple) {
    SharedPtr<int> p(new int(42));
    EXPECT_EQ(p.use_count(), 1);
    SharedPtr<int> q = p;
    EXPECT_EQ(p.use_count(), 2);
    SharedPtr<int> r = q;
    EXPECT_EQ(p.use_count(), 3);
    r.reset();
    EXPECT_EQ(p.use_count(), 2);
    q.reset();
    EXPECT_EQ(p.use_count(), 1);
    EXPECT_TRUE(p.unique());
}

TEST(SharedPtr, UseCountAfterReset) {
    SharedPtr<int> p(new int(42));
    SharedPtr<int> q = p;
    p.reset();
    EXPECT_EQ(p.use_count(), 0);
    EXPECT_EQ(q.use_count(), 1);
}

TEST(SharedPtr, ResetShared) {
    SharedPtr<int> p(new int(42));
    SharedPtr<int> q = p;
    p.reset();
    EXPECT_FALSE(p);
    EXPECT_EQ(p.use_count(), 0);
    EXPECT_EQ(q.use_count(), 1);   
}

TEST(SharedPtr, SubtypingCopyConstructor) {
    SharedPtr<Cat> cat(new Cat);
    SharedPtr<Animal> animal = cat;
    EXPECT_EQ(cat.use_count(), 2);
    EXPECT_EQ(animal.use_count(), 2);
    EXPECT_EQ(animal->name(), "Cat");
}

TEST(SharedPtr, SubtypingMoveConstructor) {
    SharedPtr<Cat> cat(new Cat);
    SharedPtr<Animal> animal = std::move(cat);
    EXPECT_FALSE(cat);
    EXPECT_EQ(animal.use_count(), 1);
    EXPECT_EQ(animal->name(), "Cat");
}

TEST(SharedPtr, SubtypingCopyAssignment) {
    SharedPtr<Animal> animal(new Dog);
    SharedPtr<Cat> cat(new Cat);
    animal = cat;
    EXPECT_EQ(cat.use_count(), 2);
    EXPECT_EQ(animal.use_count(), 2);
    EXPECT_EQ(animal->name(), "Cat");   
}

TEST(SharedPtr, SubtypingMoveAssignment) {
    SharedPtr<Animal> animal(new Dog);
    SharedPtr<Cat> cat(new Cat);
    animal = std::move(cat);
    EXPECT_FALSE(cat);
    EXPECT_EQ(animal.use_count(), 1);
    EXPECT_EQ(animal->name(), "Cat");
}

struct Tracker {
    static int alive;
    Tracker() { ++alive; }
    ~Tracker() { --alive; }
};

int Tracker::alive = 0;

TEST(SharedPtr, DestructorCalledWhenCountZero) {
    Tracker::alive = 0;
    {
        SharedPtr<Tracker> p(new Tracker);
        EXPECT_EQ(Tracker::alive, 1);
        SharedPtr<Tracker> q = p;
        EXPECT_EQ(Tracker::alive, 1);   
        q.reset();
        EXPECT_EQ(Tracker::alive, 1);   
    }
    EXPECT_EQ(Tracker::alive, 0);
}   

TEST(SharedPtr, SelfCopyAssignment) {
    SharedPtr<int> p(new int(42));
    p = p;   
    EXPECT_EQ(*p, 42);
    EXPECT_EQ(p.use_count(), 1);
}

TEST(SharedPtr, SelfMoveAssignment) {
    SharedPtr<int> p(new int(42));
    p = std::move(p);   
}