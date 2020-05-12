project(chapter5 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter5 INTERFACE)

target_include_directories(chapter5 INTERFACE include)
target_link_libraries(chapter5 INTERFACE chapter4)

install(FILES ${_HDRS} DESTINATION include/chapter5)

add_executable(test_chapter5 test_chapter5.cpp)
target_link_libraries(test_chapter5 chapter5 Catch2::Catch2)
target_compile_options(test_chapter5 INTERFACE ${DEF_COMPILE_OPTIONS})

add_test(chapter5 test_chapter5)
