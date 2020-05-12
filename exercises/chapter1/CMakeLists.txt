project(chapter1 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter1 INTERFACE)
target_include_directories(chapter1 INTERFACE include)

install(TARGETS chapter1 DESTINATION lib)
install(FILES ${_HDRS} DESTINATION include/chapter1)

add_executable(test_chapter1 test_chapter1.cpp)
target_link_libraries(test_chapter1 chapter1 Catch2::Catch2)
target_compile_options(test_chapter1 PRIVATE ${DEF_COMPILE_OPTIONS})

add_test(chapter1 test_chapter1)
