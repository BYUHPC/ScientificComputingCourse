#include "fsl/array2d.hh"
#include "catch/catch.hpp"

TEST_CASE("Empty arrays have certain properties", "[array2d]") {
  fsl::array2d<int> a{};
  REQUIRE(a.empty());
}

TEST_CASE("Non-empty arrays have certain properties", "[array2d]") {
  fsl::array2d<int> a{3, 4};
  REQUIRE(a.columns() == 4);
  REQUIRE(a.rows() == 3);
  REQUIRE(!a.empty());
}

// Add other TEST_CASEs to test operator[], copying the array, swap, etc.
