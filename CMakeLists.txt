cmake_minimum_required(VERSION 3.21)
project(classes)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)

add_library(rational rationals/Rational.cpp rationals/Rational.hpp)
target_include_directories(rational PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(rational_test rationals/tests/rational_test.cpp)
target_link_libraries(rational_test rational GTest::gtest GTest::gtest_main)




add_library(matrices matrices/matrix.cpp matrices/matrix.hpp)
target_include_directories(matrices PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(matrix_test matrices/tests/matrix_test.cpp)
target_link_libraries(matrix_test matrices GTest::gtest GTest::gtest_main)




add_library(bitmaps
        bitmaps/bitmap.cpp bitmaps/bitmap.hpp
        bitmaps/bitmapz.hpp bitmaps/bitmapz.cpp
        bitmaps/linearization.cpp bitmaps/linearization.hpp
        bitmaps/shape.cpp bitmaps/shape.hpp
        bitmaps/color.cpp bitmaps/color.hpp)
target_include_directories(bitmaps PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(bitmaps matrices)

add_executable(bitmap_test bitmaps/tests/bitmap_test.cpp)
target_link_libraries(bitmap_test bitmaps GTest::gtest GTest::gtest_main)







