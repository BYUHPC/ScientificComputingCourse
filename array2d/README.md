This folder essentially has 1 classes of interest, [`array2d`](include/fsl/array2d.hh). This is a skeleton class that students are expected to implement. This serves as practice for C++ as well as learning how to map 2-dimensional arrays onto a 1-dimensional one, which we will need for our other exercises.

## Testing

This project is set up using [CMake](https://cmake.org/) and uses its CTest capabilities. The [Catch2](https://github.com/catchorg/Catch2) testing framework is set up to integrate with CTest.

A few tests for `array2d` have already been written in `tests/array2d.cc`. Students should expand these tests to cover more functionality.

Here is how to clone this project, build the tests, and run them:

```bash
git clone https://github.com/BYUHPC/ScientificComputingCourse.git SCC
mkdir SCC/array2d/build
cd SCC/array2d/build
cmake -DARRAY2D_BUILD_TESTING=ON ..
cmake --build .

# This is the command that runs the tests
cmake --build . --target test
```
This last command will fail because `array2d` is not fully implemented.

If you are running these commands on our clusters at BYU then you will need to run these commands before running any cmake commands:

```bash
module purge
module load cmake gcc
```

This is necesary because the versions of `cmake` and `gcc` our OS provides are too old to build this project. These commands load newer versions.
