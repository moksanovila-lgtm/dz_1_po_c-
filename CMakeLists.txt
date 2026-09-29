cmake_minimum_required(VERSION 3.20)
project(dz_smart_pointers CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_SANITIZERS "Enable ASan and UBSan" OFF)

if(ENABLE_SANITIZERS)
    add_compile_options(-fsanitize=undefined -fsanitize-undefined-trap-on-error -g)
endif()

add_library(smart_ptr INTERFACE)
target_include_directories(smart_ptr INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_NAMES
    unique_ptr
    unique_ptr_array
    shared_ptr
    shared_ptr_array
    dynamic_array
)

foreach(TEST_NAME ${TEST_NAMES})
    set(TARGET_NAME test_${TEST_NAME})
    set(SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/tests/${TARGET_NAME}.cpp)

    add_executable(${TARGET_NAME} ${SOURCE_FILE})
    target_link_libraries(${TARGET_NAME} PRIVATE smart_ptr GTest::gtest_main)

    add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME})
endforeach()

option(BUILD_BENCHMARKS "Build benchmarks" OFF)

if(BUILD_BENCHMARKS)
    add_executable(bench_all load_tests/test.cpp)
    target_link_libraries(bench_all PRIVATE smart_ptr)
endif()