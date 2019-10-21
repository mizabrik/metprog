#include <fstream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

template <typename... Types>
std::vector<std::tuple<Types...>> ReadCSV(std::istream &is);

template <typename... Types>
class ReadCSV_Reader {
  friend std::vector<std::tuple<Types...>> ReadCSV<Types...>(std::istream &);

  template <int N>
  using I2T = std::integral_constant<int, N>;

  using Start = I2T<0>;
  using End = I2T<sizeof...(Types) - 1>;

  void Read(std::tuple<Types...> &to, End pos) {
    ss_ >> std::get<pos.value>(to);

    ss_ >> std::ws;
    if (!ss_.eof()) {
      throw std::runtime_error("unexpected trailing characters");
    }
  }

  template <int N>
  void Read(std::tuple<Types...> &to, I2T<N> pos) {
    ss_ >> std::get<pos.value>(to);
    
    char comma;
    ss_ >> comma;
    if (!ss_ || comma != ',') {
      throw std::runtime_error("expected comma between fields");
    }

    Read(to, I2T<pos.value + 1>());
  }

  std::istringstream ss_;
};

template <typename... Types>
std::vector<std::tuple<Types...>> ReadCSV(std::istream &is) {
  static_assert(sizeof...(Types) > 0,
                "At least one type must be specified");

  std::vector<std::tuple<Types...>> result;

  ReadCSV_Reader<Types...> reader;

  for (std::string line; std::getline(is, line), is;) {
    result.emplace_back();
    reader.ss_.clear();
    reader.ss_.str(line);
    reader.Read(result.back(), typename ReadCSV_Reader<Types...>::Start());
  }

  return result;
}

template <typename... Types>
std::vector<std::tuple<Types...>> ReadCSV(std::string filename) {
  std::ifstream file(filename);
  return ReadCSV<Types...>(file);
}
