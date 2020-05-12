project(quantum_notes)
cmake_minimum_required(VERSION 3.8)

option(USE_WERROR "Compiles using WError" ON)

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

if (USE_WERROR)
	set(DEF_COMPILE_OPTIONS "-Werror" "-Wall" "-Wextra")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "DEBUG")
	set(DEF_COMPILE_OPTIONS "-Wall" "-Wextra")
endif()

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


find_package(Catch2 REQUIRED)
enable_testing()

add_subdirectory(chapter1)
add_subdirectory(chapter2)
add_subdirectory(chapter3)
add_subdirectory(chapter4)
add_subdirectory(chapter5)
