# Target approach requires CMake 3.9 or newer
cmake_minimum_required(VERSION 3.9)

project(MPIIO CXX)

find_package(MPI REQUIRED)

add_executable(mpiio-read mpiio-read.cc)
target_link_libraries(mpiio-read PRIVATE MPI::MPI_CXX)

add_executable(mpiio-write mpiio-write.cc)
target_link_libraries(mpiio-write PRIVATE MPI::MPI_CXX)

