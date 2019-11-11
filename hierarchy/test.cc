#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "scatter.h"

template <typename T>
struct Holder {
  T value;
};

template <int I>
struct Int {
  int i = I;
};

TEST_CASE("Field test", "[field]") {
  GenScatterHierarchy<Holder, TypeList<Int<1>, Int<2>, Int<3>>> h;

  REQUIRE(Field<Int<1>>(h).value.i == 1);
  REQUIRE(Field<Int<2>>(h).value.i == 2);
  REQUIRE(Field<Int<3>>(h).value.i == 3);
}

TEST_CASE("FieldAt test", "[field_at]") {
  GenScatterHierarchy<Holder, TypeList<Int<1>, Int<2>, Int<3>, Int<1>>> h;

  REQUIRE(FieldAt<0>(h).value.i == 1);
  REQUIRE(FieldAt<1>(h).value.i == 2);
  REQUIRE(FieldAt<2>(h).value.i == 3);
  REQUIRE(FieldAt<3>(h).value.i == 1);

  FieldAt<3>(h).value.i = 4;
  REQUIRE(FieldAt<3>(h).value.i == 4);
  REQUIRE(FieldAt<0>(h).value.i == 1);
}
