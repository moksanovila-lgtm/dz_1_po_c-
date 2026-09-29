# Результаты нагрузочных тестов
```
n, category, implementation, time_us, memory_bytes
100, UniquePtr, raw, 32, 4
100, UniquePtr, my, 9, 4
100, UniquePtr, stl, 24, 4
100, UniquePtrArray, raw, 1, 400
100, UniquePtrArray, my, 1, 400
100, UniquePtrArray, stl, 3, 400
100, SharedPtr, raw, 11, 4
100, SharedPtr, my, 24, 8
100, SharedPtr, stl, 144, 24
100, SharedPtrArray, raw, 2, 400
100, SharedPtrArray, my, 3, 404
100, SharedPtrArray, stl, 7, 424
1000, UniquePtr, raw, 80, 4
1000, UniquePtr, my, 102, 4
1000, UniquePtr, stl, 214, 4
1000, UniquePtrArray, raw, 4, 4000
1000, UniquePtrArray, my, 3, 4000
1000, UniquePtrArray, stl, 5, 4000
1000, SharedPtr, raw, 98, 4
1000, SharedPtr, my, 217, 8
1000, SharedPtr, stl, 1950, 24
1000, SharedPtrArray, raw, 4, 4000
1000, SharedPtrArray, my, 4, 4004
1000, SharedPtrArray, stl, 8, 4024
10000, UniquePtr, raw, 537, 4
10000, UniquePtr, my, 570, 4
10000, UniquePtr, stl, 1608, 4
10000, UniquePtrArray, raw, 24, 40000
10000, UniquePtrArray, my, 3, 40000
10000, UniquePtrArray, stl, 4, 40000
10000, SharedPtr, raw, 638, 4
10000, SharedPtr, my, 2258, 8
10000, SharedPtr, stl, 3883, 24
10000, SharedPtrArray, raw, 4, 40000
10000, SharedPtrArray, my, 7, 40004
10000, SharedPtrArray, stl, 7, 40024
100000, UniquePtr, raw, 6640, 4
100000, UniquePtr, my, 9407, 4
100000, UniquePtr, stl, 19195, 4
100000, UniquePtrArray, raw, 20, 400000
100000, UniquePtrArray, my, 4, 400000
100000, UniquePtrArray, stl, 5, 400000
100000, SharedPtr, raw, 5820, 4
100000, SharedPtr, my, 17515, 8
100000, SharedPtr, stl, 33049, 24
100000, SharedPtrArray, raw, 4, 400000
100000, SharedPtrArray, my, 5, 400004
100000, SharedPtrArray, stl, 8, 400024
1000000, UniquePtr, raw, 58204, 4
1000000, UniquePtr, my, 64023, 4
1000000, UniquePtr, stl, 175006, 4
1000000, UniquePtrArray, raw, 162, 4000000
1000000, UniquePtrArray, my, 103, 4000000
1000000, UniquePtrArray, stl, 97, 4000000
1000000, SharedPtr, raw, 69536, 4
1000000, SharedPtr, my, 154241, 8
1000000, SharedPtr, stl, 280835, 24
1000000, SharedPtrArray, raw, 107, 4000000
1000000, SharedPtrArray, my, 65, 4000004
1000000, SharedPtrArray, stl, 74, 4000024
```



# Проверка утечек (Valgrind) unique_ptr
```
==3007== Command: ./test_unique_ptr
==3007==
Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 10 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 10 tests from UniquePtr
[ RUN      ] UniquePtr.DefaultIsNull
[       OK ] UniquePtr.DefaultIsNull (14 ms)
[ RUN      ] UniquePtr.CreateAndDereference
[       OK ] UniquePtr.CreateAndDereference (2 ms)
[ RUN      ] UniquePtr.ArrowOperator
[       OK ] UniquePtr.ArrowOperator (3 ms)
[ RUN      ] UniquePtr.MoveConstructor
[       OK ] UniquePtr.MoveConstructor (3 ms)
[ RUN      ] UniquePtr.MoveAssignment
[       OK ] UniquePtr.MoveAssignment (2 ms)
[ RUN      ] UniquePtr.Release
[       OK ] UniquePtr.Release (2 ms)
[ RUN      ] UniquePtr.Reset
[       OK ] UniquePtr.Reset (2 ms)
[ RUN      ] UniquePtr.SubtypingMoveConstructor
[       OK ] UniquePtr.SubtypingMoveConstructor (3 ms)
[ RUN      ] UniquePtr.SubtypingMoveAssignment
[       OK ] UniquePtr.SubtypingMoveAssignment (3 ms)
[ RUN      ] UniquePtr.DestructorCalled
[       OK ] UniquePtr.DestructorCalled (1 ms)
[----------] 10 tests from UniquePtr (50 ms total)

[----------] Global test environment tear-down
[==========] 10 tests from 1 test suite ran. (97 ms total)
[  PASSED  ] 10 tests.
==3007==
==3007== HEAP SUMMARY:
==3007==     in use at exit: 0 bytes in 0 blocks
==3007==   total heap usage: 286 allocs, 286 frees, 126,074 bytes allocated
==3007==
==3007== All heap blocks were freed -- no leaks are possible
==3007==
==3007== For lists of detected and suppressed errors, rerun with: -s
==3007== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```



# Проверка утечек (Valgrind) shared_ptr
```
==3017== Command: ./test_shared_ptr
==3017==
Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 17 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 17 tests from SharedPtr
[ RUN      ] SharedPtr.DefaultIsNull
[       OK ] SharedPtr.DefaultIsNull (15 ms)
[ RUN      ] SharedPtr.CreateFromPointer
[       OK ] SharedPtr.CreateFromPointer (3 ms)
[ RUN      ] SharedPtr.CopyConstructor
[       OK ] SharedPtr.CopyConstructor (3 ms)
[ RUN      ] SharedPtr.CopyAssignment
[       OK ] SharedPtr.CopyAssignment (3 ms)
[ RUN      ] SharedPtr.CopyThenReset
[       OK ] SharedPtr.CopyThenReset (4 ms)
[ RUN      ] SharedPtr.MoveConstructor
[       OK ] SharedPtr.MoveConstructor (3 ms)
[ RUN      ] SharedPtr.MoveAssignment
[       OK ] SharedPtr.MoveAssignment (2 ms)
[ RUN      ] SharedPtr.UseCountMultiple
[       OK ] SharedPtr.UseCountMultiple (3 ms)
[ RUN      ] SharedPtr.UseCountAfterReset
[       OK ] SharedPtr.UseCountAfterReset (2 ms)
[ RUN      ] SharedPtr.ResetShared
[       OK ] SharedPtr.ResetShared (2 ms)
[ RUN      ] SharedPtr.SubtypingCopyConstructor
[       OK ] SharedPtr.SubtypingCopyConstructor (5 ms)
[ RUN      ] SharedPtr.SubtypingMoveConstructor
[       OK ] SharedPtr.SubtypingMoveConstructor (3 ms)
[ RUN      ] SharedPtr.SubtypingCopyAssignment
[       OK ] SharedPtr.SubtypingCopyAssignment (4 ms)
[ RUN      ] SharedPtr.SubtypingMoveAssignment
[       OK ] SharedPtr.SubtypingMoveAssignment (5 ms)
[ RUN      ] SharedPtr.DestructorCalledWhenCountZero
[       OK ] SharedPtr.DestructorCalledWhenCountZero (3 ms)
[ RUN      ] SharedPtr.SelfCopyAssignment
[       OK ] SharedPtr.SelfCopyAssignment (2 ms)
[ RUN      ] SharedPtr.SelfMoveAssignment
[       OK ] SharedPtr.SelfMoveAssignment (1 ms)
[----------] 17 tests from SharedPtr (82 ms total)

[----------] Global test environment tear-down
[==========] 17 tests from 1 test suite ran. (132 ms total)
[  PASSED  ] 17 tests.
==3017==
==3017== HEAP SUMMARY:
==3017==     in use at exit: 0 bytes in 0 blocks
==3017==   total heap usage: 372 allocs, 372 frees, 133,717 bytes allocated
==3017==
==3017== All heap blocks were freed -- no leaks are possible
==3017==
==3017== For lists of detected and suppressed errors, rerun with: -s
==3017== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```




# Проверка утечек (Valgrind) unique_ptr with array
```
==3027== Command: ./test_unique_ptr_array
==3027==
Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 8 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 8 tests from UniquePtrArr
[ RUN      ] UniquePtrArr.DefaultIsNull
[       OK ] UniquePtrArr.DefaultIsNull (15 ms)
[ RUN      ] UniquePtrArr.CreateAndIndex
[       OK ] UniquePtrArr.CreateAndIndex (4 ms)
[ RUN      ] UniquePtrArr.ModifyElements
[       OK ] UniquePtrArr.ModifyElements (2 ms)
[ RUN      ] UniquePtrArr.MoveConstructor
[       OK ] UniquePtrArr.MoveConstructor (3 ms)
[ RUN      ] UniquePtrArr.MoveAssignment
[       OK ] UniquePtrArr.MoveAssignment (3 ms)
[ RUN      ] UniquePtrArr.Release
[       OK ] UniquePtrArr.Release (4 ms)
[ RUN      ] UniquePtrArr.Reset
[       OK ] UniquePtrArr.Reset (5 ms)
[ RUN      ] UniquePtrArr.DestructorCalledForEachElement
[       OK ] UniquePtrArr.DestructorCalledForEachElement (3 ms)
[----------] 8 tests from UniquePtrArr (52 ms total)

[----------] Global test environment tear-down
[==========] 8 tests from 1 test suite ran. (103 ms total)
[  PASSED  ] 8 tests.
==3027==
==3027== HEAP SUMMARY:
==3027==     in use at exit: 0 bytes in 0 blocks
==3027==   total heap usage: 265 allocs, 265 frees, 123,941 bytes allocated
==3027==
==3027== All heap blocks were freed -- no leaks are possible
==3027==
==3027== For lists of detected and suppressed errors, rerun with: -s
==3027== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```


# Проверка утечек (Valgrind) shared_ptr with array
```
==3039== Command: ./test_shared_ptr_array
==3039==
Running main() from /usr/src/googletest/googletest/src/gtest_main.cc
[==========] Running 13 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 13 tests from SharedPtrArr
[ RUN      ] SharedPtrArr.DefaultIsNull
[       OK ] SharedPtrArr.DefaultIsNull (13 ms)
[ RUN      ] SharedPtrArr.CreateFromPointer
[       OK ] SharedPtrArr.CreateFromPointer (5 ms)
[ RUN      ] SharedPtrArr.ModifyElements
[       OK ] SharedPtrArr.ModifyElements (2 ms)
[ RUN      ] SharedPtrArr.ConstAccess
[       OK ] SharedPtrArr.ConstAccess (1 ms)
[ RUN      ] SharedPtrArr.CopyConstructor
[       OK ] SharedPtrArr.CopyConstructor (3 ms)
[ RUN      ] SharedPtrArr.CopyAssignment
[       OK ] SharedPtrArr.CopyAssignment (2 ms)
[ RUN      ] SharedPtrArr.CopyThenReset
[       OK ] SharedPtrArr.CopyThenReset (4 ms)
[ RUN      ] SharedPtrArr.MoveConstructor
[       OK ] SharedPtrArr.MoveConstructor (2 ms)
[ RUN      ] SharedPtrArr.MoveAssignment
[       OK ] SharedPtrArr.MoveAssignment (3 ms)
[ RUN      ] SharedPtrArr.UseCountMultiple
[       OK ] SharedPtrArr.UseCountMultiple (4 ms)
[ RUN      ] SharedPtrArr.Reset
[       OK ] SharedPtrArr.Reset (2 ms)
[ RUN      ] SharedPtrArr.ResetShared
[       OK ] SharedPtrArr.ResetShared (3 ms)
[ RUN      ] SharedPtrArr.DestructorCalledForEachElementWhenCountZero
[       OK ] SharedPtrArr.DestructorCalledForEachElementWhenCountZero (4 ms)
[----------] 13 tests from SharedPtrArr (64 ms total)

[----------] Global test environment tear-down
[==========] 13 tests from 1 test suite ran. (110 ms total)
[  PASSED  ] 13 tests.
==3039==
==3039== HEAP SUMMARY:
==3039==     in use at exit: 0 bytes in 0 blocks
==3039==   total heap usage: 323 allocs, 323 frees, 129,313 bytes allocated
==3039==
==3039== All heap blocks were freed -- no leaks are possible
==3039==
==3039== For lists of detected and suppressed errors, rerun with: -s
==3039== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```