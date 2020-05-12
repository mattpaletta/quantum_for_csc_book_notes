project(chapter2 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")

add_library(chapter2 INTERFACE)
target_include_directories(chapter2 INTERFACE include)
target_link_libraries(chapter2 INTERFACE chapter1)

install(FILES ${_HDRS} DESTINATION include/chapter2)

add_executable(test_chapter2 test_chapter2.cpp)
target_link_libraries(test_chapter2 chapter2 Catch2::Catch2)
target_compile_options(test_chapter2 PRIVATE ${DEF_COMPILE_OPTIONS})

add_test(chapter2 test_chapter2)
