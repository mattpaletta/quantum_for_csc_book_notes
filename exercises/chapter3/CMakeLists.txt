project(chapter1 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter3 INTERFACE)
target_include_directories(chapter3 INTERFACE include)
target_link_libraries(chapter3 INTERFACE chapter2)

install(FILES ${_HDRS} DESTINATION include/chapter3)

add_executable(test_chapter3 test_chapter3.cpp)
target_link_libraries(test_chapter3 chapter3 Catch2::Catch2)
target_compile_options(test_chapter3 PRIVATE ${DEF_COMPILE_OPTIONS})

add_test(chapter3 test_chapter3)
