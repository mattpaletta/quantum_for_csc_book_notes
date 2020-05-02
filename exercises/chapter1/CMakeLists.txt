project(chapter1 LANGUAGES CXX)

add_library(chapter1 complex.hpp complex.cpp)

add_executable(test_chapter1 test_complex.cpp)
target_link_libraries(test_chapter1 chapter1 Catch2::Catch2)
