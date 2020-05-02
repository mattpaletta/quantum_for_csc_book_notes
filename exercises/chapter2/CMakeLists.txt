project(chapter2 LANGUAGES CXX)

add_library(chapter2 complex.hpp complex.cpp)

add_executable(test_chapter2 test_complex.cpp)
target_link_libraries(test_chapter2 chapter2 Catch2::Catch2)
