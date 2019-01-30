This folder essentially has 1 class of interest, [`array2d`](include/fsl/array2d.hh). This is a skeleton class that students are expected to implement. This serves as practice for C++ as well as learning how to map 2-dimensional arrays onto a 1-dimensional one, which we will need for our other exercises.

## Building and Testing

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
This build commands will fail until `array2d` is fully implemented.

If you are running these commands on our clusters at BYU then you will need to run these commands before running any cmake commands:

```bash
module purge
module load cmake gcc
```

This is necessary because the versions of `cmake` and `gcc` our OS provides are too old to build this project. These commands load newer versions.

### Configuring for CLion
[CLion](https://www.jetbrains.com/clion/) is a somewhat popular IDE for C++ created by JetBrains that runs on Linux, Mac, and Windows. They currently offer many of their [products for free to students](https://www.jetbrains.com/student/), including CLion. This gives code completion, build workflows, visual debugging, git integration, etc in  one product so I recommend it to students who want an integrated experience.

As this project is simple there is little to do to get CLion working. Visit the instructions [configuring CMake in CLion](https://www.jetbrains.com/help/clion/configuring-cmake.html) to learn how to add `-DARRAY2D_BUILD_TESTING=ON` for this project so it is aware of test cases.
