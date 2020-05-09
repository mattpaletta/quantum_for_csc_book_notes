project(chapter1 LANGUAGES CXX)

file(GLOB_RECURSE _HDRS "include/*.hpp")
add_library(chapter3 ${_HDRS} chapter3.cpp)

target_include_directories(chapter3 PUBLIC include)
target_link_libraries(chapter3 chapter2)

install(TARGETS chapter3 DESTINATION lib)
install(FILES ${_HDRS} DESTINATION include/chapter3)

add_library(tf_example tf_demo.cpp)
get_property(tensorflow_cc_INCLUDE_DIRS GLOBAL PROPERTY tensorflow_cc_INCLUDE_DIRS)

# message("Tensorflow Headers: " ${tensorflow_cc_INCLUDE_DIRS})

target_include_directories(tf_example PUBLIC ${tensorflow_cc_INCLUDE_DIRS})
target_link_libraries(tf_example tensorflow_cc protobuf::libprotobuf absl::strings)
add_dependencies(tf_example tensorflow_cc_target)

add_executable(test_chapter3 test_complex.cpp)
target_link_libraries(test_chapter3 chapter3 Catch2::Catch2)
