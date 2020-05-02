project(chapter1 LANGUAGES CXX)

add_library(chapter3 complex.hpp complex.cpp)
get_property(tensorflow_cc_INCLUDE_DIRS GLOBAL PROPERTY tensorflow_cc_INCLUDE_DIRS)
message("Tensorflow Headers: " ${tensorflow_cc_INCLUDE_DIRS})
target_include_directories(chapter3 PUBLIC ${tensorflow_cc_INCLUDE_DIRS})
target_link_libraries(chapter3 tensorflow_cc protobuf::libprotobuf absl::strings)
add_dependencies(chapter3 tensorflow_cc_target)

find_package(Protobuf REQUIRED)
add_executable(test_chapter3 test_complex.cpp)
target_link_libraries(test_chapter3 chapter3 Catch2::Catch2)
