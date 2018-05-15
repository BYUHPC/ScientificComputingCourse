This folder essentially has 2 classes of interest:

  - [`array1d`](include/fsl/array1d.hh)
  - [`array2d`](include/fsl/array2d.hh)

The first is a (hopefully) working implementation of an array whose size is known only at runtime and cannot be changed after construction. It provides value semantics, which roughly means it is copyable and the copies are distinct from the original (changes made to the copy do not affect the original). C++ does not provide such a class; `vector` and `valarray` are as close as it gets.

The second file contains `array2d` and is one students should implement as an excercise. It depends on `array1d`. This serves as practice for C++ as well as learning how to map 2-dimensional arrays onto a 1-dimensional one, which we will need for our other exercises.

# Testing

This project is set up using [CMake](https://cmake.org/) and uses its CTest capabilities. The [Catch2](https://github.com/catchorg/Catch2) testing framework is set up to integrate with CTest.

Tests for `array1d` have already been written. Students need to create a new file in `tests/` for testing `array2d` and edit `tests/CMakeLists.txt` to add include it in CMake.

Here is how to clone this project and build the tests (which will fail because I explicitly fail one of the tests so you can get familiar with the output; you can remove this test):

```bash
git clone https://github.com/BYUHPC/ScientificComputingCourse.git SCC
mkdir SCC/array2d/build
cd SCC/array2d/build
cmake -DARRAY2D_BUILD_TESTING=ON ..
cmake --build .

# This is the command that runs the tests
cmake --build . --target test
```

If you are running these commands on our clusters at BYU then you will need to run these commands before running any cmake commands:

```bash
module purge
module load cmake gcc
```

This is necesary because the versions of `cmake` and `gcc` our OS provides are too old to build this project. These commands load newer versions.
