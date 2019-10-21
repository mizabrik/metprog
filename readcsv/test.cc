#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "readcsv.h"

TEST_CASE("ReadCSV test", "[read_csv]") {
  std::stringstream ss;
  ss << "12, 42.2, foo" << std::endl
     << "0, -1, bar" << std::endl;

  REQUIRE(ReadCSV<int, double, std::string>(ss) == std::vector<std::tuple<int, double, std::string>>{
    {12, 42.2, "foo"},
    {0, -1, "bar"}
  });
}
