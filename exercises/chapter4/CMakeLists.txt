project(chapter4 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter4 INTERFACE)

target_include_directories(chapter4 INTERFACE include)
target_link_libraries(chapter4 INTERFACE chapter3)

install(FILES ${_HDRS} DESTINATION include/chapter4)

add_executable(test_chapter4 test_chapter4.cpp)
target_link_libraries(test_chapter4 chapter4 Catch2::Catch2)
target_compile_options(test_chapter4 INTERFACE ${DEF_COMPILE_OPTIONS})

add_test(chapter4 test_chapter4)
