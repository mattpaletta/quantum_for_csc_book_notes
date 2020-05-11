project(chapter1 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter3 ${_HDRS} chapter3.cpp)

target_include_directories(chapter3 PUBLIC include)
target_link_libraries(chapter3 chapter2)

install(TARGETS chapter3 DESTINATION lib)
install(FILES ${_HDRS} DESTINATION include/chapter3)

add_executable(test_chapter3 test_complex.cpp)
target_link_libraries(test_chapter3 chapter3 Catch2::Catch2)
