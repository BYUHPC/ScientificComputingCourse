# The documentation changed quite a bit from 3.8 to 3.9
# If you have an older version may as well lower this number and try it
cmake_minimum_required(VERSION 3.9)

project(MPIIO CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(MPI REQUIRED)

add_executable(mpiio-read mpiio-read.cc)
add_executable(mpiio-write mpiio-write.cc)
set_target_properties(mpiio-read mpiio-write PROPERTIES
  COMPILE_FLAGS        "${MPI_CXX_COMPILE_FLAGS}"
  INCLUDE_DIRECTORIES  "${MPI_CXX_INCLUDE_PATH}"
  LINK_FLAGS           "${MPI_CXX_LINK_FLAGS}"
  LINK_LIBRARIES       "${MPI_CXX_LIBRARIES}"
)

