project(chapter4 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter4 ${_HDRS} chapter4.cpp)

target_include_directories(chapter4 PUBLIC include)
target_link_libraries(chapter4 chapter3)

install(TARGETS chapter4 DESTINATION lib)
install(FILES ${_HDRS} DESTINATION include/chapter4)

add_executable(test_chapter4 test_chapter4.cpp)
target_link_libraries(test_chapter4 chapter4 Catch2::Catch2)
