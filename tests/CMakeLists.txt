# CMakeLists.txt for test
#########################

# Include directory containing source
include_directories (../include)

# Add compiler flags for OpenMP
find_package (OpenMP REQUIRED)
if    (OPENMP_FOUND )
  set (CMAKE_C_FLAGS           "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set (CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif (OPENMP_FOUND)

# Create main lib (as advised in Catch docs, to speed up compilation)
add_library (GridTestMain   test_main.cpp)

# Create test executables
add_executable        (test_1_basic_ops.exe   test_1_basic_ops.cpp)
target_link_libraries (test_1_basic_ops.exe   GridSIMD   GridTestMain)

add_executable        (test_2_OpenMP.exe      test_2_OpenMP.cpp)
target_link_libraries (test_2_OpenMP.exe      GridSIMD   GridTestMain)

add_executable        (test_3_consts.exe      test_3_consts.cpp)
target_link_libraries (test_3_consts.exe      GridSIMD   GridTestMain)

add_executable        (test_4_OpenMP.exe      test_4_OpenMP.cpp)
target_link_libraries (test_4_OpenMP.exe      GridSIMD)

add_executable        (test_5_OpenMP.exe      test_5_OpenMP.cpp)
target_link_libraries (test_5_OpenMP.exe      GridSIMD)

add_executable        (test_6_many_allocations.exe      test_6_many_allocations.cpp)
target_link_libraries (test_6_many_allocations.exe      GridSIMD)

add_executable        (test_7_allocations_in_constr.exe      test_7_allocations_in_constr.cpp)
target_link_libraries (test_7_allocations_in_constr.exe      GridSIMD)

add_executable        (test_8_allocations_in_constr.exe      test_8_allocations_in_constr.cpp)
target_link_libraries (test_8_allocations_in_constr.exe      GridSIMD)
