# Set minimal required CMake version
cmake_minimum_required (VERSION 2.8.12)

# Set project name
project (Grid-SIMD)

#set (CMAKE_BUILD_TYPE  Debug)
set (CMAKE_BUILD_TYPE  Release)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -mavx -mf16c")

# Write all binary files to the bin directory
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_SOURCE_DIR}/bin)

# Add lib directory
add_subdirectory (src)

# Add tests directory
add_subdirectory (tests)
