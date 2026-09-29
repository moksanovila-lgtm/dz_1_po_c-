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

TEST(UniquePtr, DefaultIsNull) {
    UniquePtr<int> p;
    EXPECT_FALSE(p);
    EXPECT_EQ(p.get(), nullptr);
}

TEST(UniquePtr, CreateAndDereference) {
    UniquePtr<int> p(new int(42));
    EXPECT_TRUE(p);
    EXPECT_NE(p.get(), nullptr);
    EXPECT_EQ(*p, 42);
}

TEST(UniquePtr, ArrowOperator) {   
    UniquePtr<std::string> p(new std::string("hello"));
    EXPECT_EQ(p->size(), 5u);
    EXPECT_EQ(*p, "hello");
}

TEST(UniquePtr, MoveConstructor) {
    UniquePtr<int> p(new int(7));
    UniquePtr<int> q(std::move(p));
    EXPECT_FALSE(p);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_TRUE(q);
    EXPECT_EQ(*q, 7);
}

TEST(UniquePtr, MoveAssignment) {   
    UniquePtr<int> p(new int(1));
    UniquePtr<int> q(new int(2));
    q = std::move(p);
    EXPECT_FALSE(p);
    EXPECT_EQ(*q, 1);
}

TEST(UniquePtr, Release) {
    UniquePtr<int> p(new int(5));
    int* raw = p.release();
    EXPECT_FALSE(p);
    EXPECT_EQ(p.get(), nullptr);
    EXPECT_NE(raw, nullptr);
    EXPECT_EQ(*raw, 5);
    delete raw;
}

TEST(UniquePtr, Reset) {
    UniquePtr<int> p(new int(5));
    p.reset(new int(10));
    EXPECT_EQ(*p, 10);
    p.reset();
    EXPECT_FALSE(p);
    EXPECT_EQ(p.get(), nullptr);
}

TEST(UniquePtr, SubtypingMoveConstructor) {
    UniquePtr<Cat> cat(new Cat);
    UniquePtr<Animal> animal(std::move(cat));
    EXPECT_FALSE(cat);
    EXPECT_TRUE(animal);
    EXPECT_EQ(animal->name(), "Cat");
}

TEST(UniquePtr, SubtypingMoveAssignment) {  
    UniquePtr<Animal> animal(new Dog);
    UniquePtr<Cat> cat(new Cat);
    animal = std::move(cat);
    EXPECT_FALSE(cat);
    EXPECT_EQ(animal->name(), "Cat");
}

struct Tracker {
    static int alive;
    Tracker() { ++alive; }
    ~Tracker() { --alive; }
};

int Tracker::alive = 0;

TEST(UniquePtr, DestructorCalled) {
    Tracker::alive = 0;
    {
        UniquePtr<Tracker> p(new Tracker);
        EXPECT_EQ(Tracker::alive, 1);
    }
    EXPECT_EQ(Tracker::alive, 0);
}