#include <vector>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "index.h"

typedef TypeList<
  char, TypeList<
    int, TypeList<
      double *, TypeList<
        int, EmptyList
      >
    >
  >
> TL;

TEST_CASE("GetIndexOf test", "[get_index_of]") {
  REQUIRE((GetIndexOf<char, TL>()) == 0);
  REQUIRE((GetIndexOf<int, TL>()) == 1);
  REQUIRE((GetIndexOf<double *, TL>()) == 2);
  REQUIRE((GetIndexOf<unsigned, TL>()) == -1);
  REQUIRE((GetIndexOf<signed char, TL>()) == -1 );
  REQUIRE((GetIndexOf<const double *, TL>()) == -1);
}

void AppendIntList(EmptyList list, std::vector<int> &to) {}

template <typename List>
void AppendIntList(List list, std::vector<int> &to) {
  to.push_back(List::Head);
  AppendIntList(typename List::Tail(), to);
}

template <typename List>
std::vector<int> IntListToVector() {
  std::vector<int> res;
  AppendIntList(List(), res);
  return res;
}

TEST_CASE("IndicesOf test", "[indices_of]") {
  std::vector<int> res;

  res = IntListToVector<IndicesOf<char, TL>::indices>();
  REQUIRE(res.size() == 1);
  REQUIRE(res[0] == 0);

  res = IntListToVector<IndicesOf<int, TL>::indices>();
  REQUIRE(res.size() == 2);
  REQUIRE(res[0] == 1);
  REQUIRE(res[1] == 3);

  res = IntListToVector<IndicesOf<double *, TL>::indices>();
  REQUIRE(res.size() == 1);
  REQUIRE(res[0] == 2);

  res = IntListToVector<IndicesOf<unsigned, TL>::indices>();
  REQUIRE(res.size() == 0);
  res = IntListToVector<IndicesOf<signed char, TL>::indices>();
  REQUIRE(res.size() == 0);
  res = IntListToVector<IndicesOf<const double *, TL>::indices>();
  REQUIRE(res.size() == 0);
}
