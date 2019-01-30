#include "fsl/array2d.hh"
#include "catch/catch.hpp"

TEST_CASE("Arrays have certain properties", "[array2d]") {
  fsl::array2d<int> a{3, 4};
  REQUIRE(a.rows() == 3);
  REQUIRE(a.columns() == 4);
}

TEST_CASE("operator[] is modifiable", "[array2d]") {
  fsl::array2d<int> a{2, 2};
  a[0][0] = 0;
  a[0][1] = 1;
  a[1][0] = 2;
  a[1][1] = 3;

  REQUIRE(a[0][0] == 0);
  REQUIRE(a[0][1] == 1);
  REQUIRE(a[1][0] == 2);
  REQUIRE(a[1][1] == 3);
}

TEST_CASE("operator() is congruent with operator[]", "[array2d]") {
  fsl::array2d<int> a{2, 2};
  a[0][0] = 0;
  a(0, 1) = 1;
  a[1][0] = 2;
  a(1, 1) = 3;

  REQUIRE(a(0, 0) == 0);
  REQUIRE(a[0][1] == 1);
  REQUIRE(a(1, 0) == 2);
  REQUIRE(a[1][1] == 3);
}

TEST_CASE("swap", "[array2d]") {
  fsl::array2d<int> a{2, 2};
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(1, 0) = 2;
  a(1, 1) = 3;

  fsl::array2d<int> b{2, 2};
  b(0, 0) = 4;
  b(0, 1) = 4;
  b(1, 0) = 4;
  b(1, 1) = 4;

  a.swap(b);

  REQUIRE(a(0, 0) == 4);
  REQUIRE(a(0, 1) == 4);
  REQUIRE(a(1, 0) == 4);
  REQUIRE(a(1, 1) == 4);

  REQUIRE(b(0, 0) == 0);
  REQUIRE(b(0, 1) == 1);
  REQUIRE(b(1, 0) == 2);
  REQUIRE(b(1, 1) == 3);
}

TEST_CASE("copy constructor", "[array2d]") {
  fsl::array2d<int> a{2, 2};
  a(0, 0) = 0;
  a(0, 1) = 1;
  a(1, 0) = 2;
  a(1, 1) = 3;

  fsl::array2d<int> b{a};
  // TODO: test that a(y, x) == b(y, x) for all valid xs and ys

  // TODO: test that modifying b(y, x) does not also change a(y, x)
}
