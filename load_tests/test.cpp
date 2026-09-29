#include "unique_ptr.hpp"
#include "shared_ptr.hpp"

#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <functional>
#include <string>
#include <windows.h>

static std::size_t g_allocated = 0;
static std::size_t g_peak = 0;

void* operator new(std::size_t size) {
    g_allocated += size;
    if (g_allocated > g_peak) g_peak = g_allocated;
    void* p = std::malloc(size);
    if (!p) throw std::bad_alloc();
    return p;
}

void operator delete(void* p) noexcept {
    std::free(p);
}

void operator delete(void* p, std::size_t size) noexcept {
    g_allocated -= size;
    std::free(p);
}

void reset_memory_stats() {
    g_allocated = 0;
    g_peak = 0;
}


using Clock = std::chrono::high_resolution_clock;

double measure_us(std::function<void(std::size_t)> f, std::size_t n) {
    auto start = Clock::now();
    f(n);
    auto end = Clock::now();
    return std::chrono::duration<double, std::micro>(end - start).count();
}


void bench_unique_raw(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        int* p = new int(static_cast<int>(i));
        delete p;
    }
}

void bench_unique_my(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        UniquePtr<int> p(new int(static_cast<int>(i)));
    }
}

void bench_unique_stl(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        std::unique_ptr<int> p(new int(static_cast<int>(i)));
    }
}


void bench_shared_raw(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        int* p = new int(static_cast<int>(i));
        delete p;
    }
}

void bench_shared_my(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        SharedPtr<int> p(new int(static_cast<int>(i)));
        SharedPtr<int> q = p;
    }
}

void bench_shared_stl(std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        std::shared_ptr<int> p = std::make_shared<int>(static_cast<int>(i));
        std::shared_ptr<int> q = p;
    }
}


void bench_unique_arr_raw(std::size_t n) {
    int* arr = new int[n];
    delete[] arr;
}

void bench_unique_arr_my(std::size_t n) {
    UniquePtr<int[]> arr(new int[n]);  
}

void bench_unique_arr_stl(std::size_t n) {
    std::unique_ptr<int[]> arr(new int[n]);
}


void bench_shared_arr_raw(std::size_t n) {
    int* arr = new int[n];
    delete[] arr;
}

void bench_shared_arr_my(std::size_t n) {
    SharedPtr<int[]> arr(new int[n]);  
}

void bench_shared_arr_stl(std::size_t n) {
    std::shared_ptr<int[]> arr(new int[n]);
}


void run_case(const std::string& name, std::function<void(std::size_t)> fn, std::size_t n) {
    reset_memory_stats();
    double us = measure_us(fn, n);

    std::cout << name << ":\n"
              << "  Время:  " << us << " мкс\n"
              << "  Память: выделено " << g_peak << " байт\n\n";
}


std::size_t read_n() {
    constexpr long long MAX_N = 100000000LL;

    while (true) {
        std::cout << "Введите число объектов (1 - " << MAX_N << "): ";

        long long n_input;
        if (!(std::cin >> n_input)) {
            std::cerr << "Ошибка: введите целое число\n";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (n_input <= 0) {
            std::cerr << "Ошибка: N должно быть > 0\n";
            continue;
        }

        if (n_input > MAX_N) {
            std::cerr << "Ошибка: N слишком большое (максимум " << MAX_N << ")\n";
            continue;
        }

        return static_cast<std::size_t>(n_input);
    }
}


int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    std::size_t n = read_n();

    std::cout << "\n N = " << n << " \n\n";

    run_case("UniquePtr (сырые)",  bench_unique_raw, n);
    run_case("UniquePtr (мои)",    bench_unique_my,  n);
    run_case("UniquePtr (STL)",    bench_unique_stl, n);

    run_case("SharedPtr (сырые)",  bench_shared_raw, n);
    run_case("SharedPtr (мои)",    bench_shared_my,  n);
    run_case("SharedPtr (STL)",    bench_shared_stl, n);

    run_case("UniquePtr (сырые)",  bench_unique_arr_raw, n);
    run_case("UniquePtr (мои)",    bench_unique_arr_my,  n);
    run_case("UniquePtr (STL)",    bench_unique_arr_stl, n);

    run_case("SharedPtr (сырые)",  bench_shared_arr_raw, n);
    run_case("SharedPtr (мои)",    bench_shared_arr_my,  n);
    run_case("SharedPtr (STL)",    bench_shared_arr_stl, n);

    return 0;
}