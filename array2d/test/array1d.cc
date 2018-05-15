#include "catch/catch.hpp"
#include <numeric>

#include "fsl/array1d.hh"

TEST_CASE("Empty arrays have certain properties", "[array1d]") {
  fsl::array1d<int> a{};
  REQUIRE(a.empty());
  REQUIRE(a.size() == 0);

  REQUIRE(std::accumulate(a.begin(), a.end(), 17) == 17);
}

TEST_CASE("Non-empty arrays have certain properties", "[array1d]") {
  fsl::array1d<int> a{6};
  REQUIRE(!a.empty());
  REQUIRE(a.size() == 6);

  a[0] = 1;
  a[1] = 1;
  a[2] = 2;
  a[4] = 5;
  a[5] = 8;

  REQUIRE(std::accumulate(a.begin(), a.end(), 0) == 17);
}

TEST_CASE("Example of failing test", "[array1d]") {
  REQUIRE(false);
}

