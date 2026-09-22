# CMake generated Testfile for 
# Source directory: D:/dz_1
# Build directory: D:/dz_1/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[test_unique_ptr]=] "D:/dz_1/build/test_unique_ptr.exe")
set_tests_properties([=[test_unique_ptr]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/dz_1/CMakeLists.txt;43;add_test;D:/dz_1/CMakeLists.txt;0;")
add_test([=[test_unique_ptr_array]=] "D:/dz_1/build/test_unique_ptr_array.exe")
set_tests_properties([=[test_unique_ptr_array]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/dz_1/CMakeLists.txt;43;add_test;D:/dz_1/CMakeLists.txt;0;")
add_test([=[test_shared_ptr]=] "D:/dz_1/build/test_shared_ptr.exe")
set_tests_properties([=[test_shared_ptr]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/dz_1/CMakeLists.txt;43;add_test;D:/dz_1/CMakeLists.txt;0;")
add_test([=[test_shared_ptr_array]=] "D:/dz_1/build/test_shared_ptr_array.exe")
set_tests_properties([=[test_shared_ptr_array]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/dz_1/CMakeLists.txt;43;add_test;D:/dz_1/CMakeLists.txt;0;")
add_test([=[test_dynamic_array]=] "D:/dz_1/build/test_dynamic_array.exe")
set_tests_properties([=[test_dynamic_array]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/dz_1/CMakeLists.txt;43;add_test;D:/dz_1/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
