cmake_minimum_required(VERSION 3.10)
project(array2d LANGUAGES CXX)

include(GNUInstallDirs)

# Creates a library with no sources
add_library(array2d INTERFACE)

# Indicates that the lib needs C++14
target_compile_features(array2d INTERFACE cxx_std_14)

# This sets up the include directory for the lib
target_include_directories(array2d INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
)

# This creates an export; this is useful for other CMake projects
install(TARGETS array2d EXPORT array2d)

# This actually writes out the export when `install` is ran
install(EXPORT array2d DESTINATION "${CMAKE_INSTALL_DATAROOTDIR}/cmake")

# This copies the include files when `install` is ran
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# users of the library do not need to build tests by default; they are likely
# only interested in installing headers and cmake files
option(ARRAY2D_BUILD_TESTING "enable testing for array2d" OFF)

if(ARRAY2D_BUILD_TESTING)
	# this must be called before adding subdirectories that have tests
	enable_testing()

	add_subdirectory(test)
endif()
