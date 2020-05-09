project(chapter2 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")

add_library(chapter2 ${_HDRS} chapter2.cpp)
target_include_directories(chapter2 PUBLIC include)

install(TARGETS chapter2 DESTINATION lib)
install(FILES ${_HDRS} DESTINATION include/chapter2)

add_executable(test_chapter2 test_chapter2.cpp)
target_link_libraries(test_chapter2 chapter2 Catch2::Catch2)
