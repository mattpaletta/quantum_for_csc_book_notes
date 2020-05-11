project(quantum_notes)
cmake_minimum_required(VERSION 3.8)

option(JS_ONLY "Compiles to native JS (No WASM)" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build, options are: Debug Release." FORCE)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
	message("Memory and refcounting: ENABLED")
	option(ENABLE_REF_DEBUG "enable memory and refcounting debugging" ON)
else()
	message("Memory and refcounting: DISABLED")
	option(ENABLE_REF_DEBUG "enable memory and refcounting debugging" OFF)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    add_compile_options("-g")
endif()

SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

function(add_external_library)
    set(options)
    set(oneValueArgs TARGET WORKING_DIRECTORY OUTPUT COMMENT)
    set(multiValueArgs COMMAND INCLUDE_DIRS)
    cmake_parse_arguments(ARGS "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    # Specify how to build the result of the library
    add_custom_command(OUTPUT "${ARGS_OUTPUT}"
        COMMAND ${ARGS_COMMAND}
        WORKING_DIRECTORY "${ARGS_WORKING_DIRECTORY}"
        COMMENT "${ARGS_COMMENT}")

    # Create a target out of the library compilation result
    add_custom_target(${ARGS_TARGET}_target DEPENDS ${ARGS_OUTPUT})

    # Create an library target out of the library compilation result
    add_library(${ARGS_TARGET} STATIC IMPORTED GLOBAL)
    add_dependencies(${ARGS_TARGET} ${ARGS_TARGET}_target)

	file(MAKE_DIRECTORY ${ARGS_INCLUDE_DIRS})

    # Specify where the library is and where to find the headers
    set_target_properties(${ARGS_TARGET}
        PROPERTIES
        IMPORTED_LOCATION "${ARGS_OUTPUT}"
        INTERFACE_INCLUDE_DIRECTORIES "${ARGS_INCLUDE_DIRS}")
	set_property(GLOBAL PROPERTY ${ARGS_TARGET}_INCLUDE_DIRS ${ARGS_INCLUDE_DIRS})
endfunction()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/public")
#add_executable(a ${SOURCES})

#if(JS_ONLY)
#	message(STATUS "Setting compilation target to native JavaScript")
#	set(CMAKE_EXECUTABLE_SUFFIX ".js")
#	set_target_properties(a PROPERTIES LINK_FLAGS "-s WASM=0 -s EXPORTED_FUNCTIONS='[_main]'")
#else(JS_ONLY)
#	message(STATUS "Setting compilation target to WASM")
#	set(CMAKE_EXECUTABLE_SUFFIX ".wasm.js")
#	set_target_properties(a PROPERTIES LINK_FLAGS "-s WASM=1 -s EXPORTED_FUNCTIONS='[_main]'")
#endif(JS_ONLY)

if (ENABLE_REF_DEBUG)
	add_definitions(-DPy_REF_DEBUG)
	add_definitions(-DPYMALLOC_DEBUG)
	add_definitions(-DPy_TRACE_REFS)
endif()


find_program(Bazelisk bazelisk REQUIRED)
find_program(Bazel bazel REQUIRED)

set(TENSORFLOW_DIR ${CMAKE_SOURCE_DIR}/tensorflow)
message("Tensoflow: " ${TENSORFLOW_DIR})

add_custom_target(configure_bazel
	COMMAND ${Bazelisk}
	USES_TERMINAL
	WORKING_DIRECTORY ${TENSORFLOW_DIR})

set(TF_SIMD_FLAGS " --copt=-mfpmath=both --copt=-mavx --copt=-mavx2 --copt=-mfma --copt=-msse4.1 --copt=-msse4.2")
set(CUSTOM_TF_CONFIG "--config=monolithic --config=v2 --config=noaws --config=nogcp --config=nohdfs --config=nonccl")
set(TF_NEED_CUDA 0)
set(TF_CUDA_CLANG 0) # Use nvcc for cuda
set(TF_DOWNLOAD_CLANG 0)
set(TF_TENSORRT_VERSION 0)
set(TF_NEED_ROCM 0)
set(TF_CONFIGURE_IOS 0)
set(TF_ENABLE_XLA 0)
set(TF_NEED_OPENCL_SYCL 0)
set(TF_SET_ANDROID_WORKSPACE 0)
set(CC_OPT_FLAGS "-march=native -Wno-sign-compare ${CUSTOM_TF_CONFIG} ${TF_SIMD_FLAGS}")

find_program(Python python3 REQUIRED)
message("Found Python3: " ${Python})

execute_process(COMMAND ${Python} -c "import sys; print(sys.executable, )"
	OUTPUT_VARIABLE PYTHON_BIN_PATH
	WORKING_DIRECTORY /
	OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND ${Python} -c "from distutils.sysconfig import get_python_lib; print(get_python_lib(), )"
	WORKING_DIRECTORY /
	OUTPUT_VARIABLE PYTHON_LIB_PATH
	OUTPUT_STRIP_TRAILING_WHITESPACE)

message("Python Bin Path: " ${PYTHON_BIN_PATH})
message("Python Lib Path: " ${PYTHON_LIB_PATH})
set(TF_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/tensorflow)

add_custom_target(list_tf_targets
	USES_TERMINAL
	DEPENDS configure_bazel
	WORKING_DIRECTORY ${TENSORFLOW_DIR}
	COMMAND bazel query "attr(visibility, \"//visibility:public\", //tensorflow:*)")

add_custom_target(configure_tf
	USES_TERMINAL
	DEPENDS configure_bazel
	WORKING_DIRECTORY ${TENSORFLOW_DIR}
	COMMAND export PYTHONPATH="${Python}"
			PYTHON_BIN_PATH="${PYTHON_BIN_PATH}"
			PYTHON_LIB_PATH="${PYTHON_LIB_PATH}"
			TF_NEED_CUDA="${TF_NEED_CUDA}"
			TF_CUDA_CLANG="${TF_CUDA_CLANG}"
			TF_DOWNLOAD_CLANG="${TF_DOWNLOAD_CLANG}"
			TF_TENSORRT_VERSION="${TF_TENSORRT_VERSION}"
			TF_NEED_ROCM="${TF_NEED_ROCM}"
			TF_CONFIGURE_IOS="${TF_CONFIGURE_IOS}"
			TF_ENABLE_XLA="${TF_ENABLE_XLA}"
			TF_NEED_OPENCL_SYCL="${TF_NEED_OPENCL_SYCL}"
			TF_SET_ANDROID_WORKSPACE="${TF_SET_ANDROID_WORKSPACE}"
			CC_OPT_FLAGS="${CC_OPT_FLAGS}"
			TEST_TMPDIR="${TF_BIN_DIR}" # Specify bazel output location
			&& ./configure)

add_external_library(TARGET tensorflow_cc
	# Build tensorflow into the CMAKE Binary_DIR

	#                                                               build with 'opt' flags
	COMMAND export TEST_TMPDIR="${TF_BIN_DIR}" && ${Bazelisk} build -c opt //tensorflow:tensorflow_cc
	WORKING_DIRECTORY "${TENSORFLOW_DIR}"
	INCLUDE_DIRS
		"${TF_BIN_DIR}/bazel-tensorflow;" # Standard Headers
		"${TENSORFLOW_DIR}/;" # Standard Headers
		"${TF_BIN_DIR}/bazel-bin/;" # Generated Protobuf
		"${TF_BIN_DIR}/bazel-tensorflow/external/eigen_archive/;" # Patch for Eigen
		"${TENSORFLOW_DIR}/../abseil-cpp" # Missing absl library
	OUTPUT
		"${TENSORFLOW_DIR}/bazel-bin/tensorflow/libtensorflow_cc.2.1.0.dylib"
		"${TENSORFLOW_DIR}/bazel-bin/" # Generated Protobuf
	DEPENDS configure_tf)
add_dependencies(tensorflow_cc_target configure_tf)
add_subdirectory(abseil-cpp)

find_package(Catch2 REQUIRED)
find_package(Protobuf REQUIRED) # Required for tensorflow

add_subdirectory(chapter1)
add_subdirectory(chapter2)
add_subdirectory(chapter3)
add_subdirectory(chapter4)
