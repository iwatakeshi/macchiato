#ifndef MOCHA_COMPARATOR_H
#define MOCHA_COMPARATOR_H
#include <string>
#include <to_string.hpp>
#include <functional>
#include <iostream>
#include <any>
#include <map>

namespace mocha {

template <typename t_type, typename u_type>
class mocha_comparator {
  // https://stackoverflow.com/a/28085851
  using T = typename std::conditional<std::is_fundamental<t_type>::value, t_type, t_type&>::type;
  using U = typename std::conditional<std::is_fundamental<u_type>::value, u_type, u_type&>::type;

public:
  mocha_comparator() {};
  
  mocha_comparator(std::function<bool(T, U)> comparator):
   equal(comparator),
   strict_equal(comparator) {};

  std::function<bool(T, U)> equal = [&] (T a, U b) -> bool { return equal_(a, b); };
  std::function<bool(T, U)> strict_equal = [&] (T a, U b) -> bool { return strict_equal(a, b); };

  template<class U>
  struct is_string
    : std::integral_constant<
        bool,
        std::is_same<char const *, typename std::decay<U>::type>::value ||
        std::is_same<char *, typename std::decay<U>::type>::value ||
        std::is_same<std::string, typename std::decay<U>::type>::value
  > {};

private:


  inline bool equal_(std::any a, std::any b) {
    std::cout << "equal() " << a.type().name() << " " << b.type().name() << std::endl;
    if (a.type() == b.type()) {
      
      // if (a.type().name() == )
    }
    return false;
  }

  inline bool strict_equal_(std::any a, std::any b) {
    std::cout << "strict_equal() " << a.type().name() << " " << b.type().name() << std::endl;
    std::cout << a.type().name() << " " << b.type().name() << std::endl;
    return true;
  }

  // template<typename V>
  // inline bool equal_(const char* a, int b) {
  //   return utils::to_string(a).compare(utils::to_string(b));
  // }

  // template <typename V, typename W>
  // inline bool equal_(V a, W b) { 
  //   std::cout << "HERE 2" << std::endl;
  //   return a == b; 
  // };

  // template<typename V>
  // inline bool equal_(V a, const char* b) {
  //   return utils::to_string(a).compare(utils::to_string(b));
  // }

  // template <typename V>
  // inline bool strict_equal_(V a, V b) {
  //   std::cout << "HERE 3" << std::endl;
  //   return a == b; 
  // };

  // template <typename V, typename W>
  // inline bool strict_equal_(V a, W b) {
  //   std::cout << "HERE 4" << std::endl;
  //   return a == b; 
  // };

  // Compare with int
  // inline bool strict_equal_(int a, int64_t b) { return false; }
  // inline bool strict_equal_(int a, bool b) { return false; }
  // inline bool strict_equal_(int a, const char* b) { return false; };
  // inline bool strict_equal_(int a, double b) { return false; };
  // inline bool strict_equal_(int a, float b) { return false; };
  // inline bool strict_equal_(int a, char b) { return false; };
  // inline bool strict_equal_(int a, std::string b) { return false; };

  // Compare with int64_t
  // inline bool strict_equal_(int64_t a, int b) { return false; }
  // inline bool strict_equal_(int64_t a, bool b) { return false; }
  // inline bool strict_equal_(int64_t a, const char* b) { return false; };
  // inline bool strict_equal_(int64_t a, double b) { return false; };
  // inline bool strict_equal_(int64_t a, float b) { return false; };
  // inline bool strict_equal_(int64_t a, char b) { return false; };
  // inline bool strict_equal_(int64_t a, std::string b) { return false; };

  // Compare with doubles
  // inline bool strict_equal_(double a, int b) { return false; }
  // inline bool strict_equal_(double a, int64_t b) { return false; }
  // inline bool strict_equal_(double a, bool b) { return false; }
  // inline bool strict_equal_(double a, const char* b) { return false; };
  // inline bool strict_equal_(double a, float b) { return false; };
  // inline bool strict_equal_(double a, char b) { return false; };
  // inline bool strict_equal_(double a, std::string b) { return false; };

  // Compare with floats
  // inline bool strict_equal_(float a, int b) { return false; }
  // inline bool strict_equal_(float a, int64_t b) { return false; }
  // inline bool strict_equal_(float a, bool b) { return false; }
  // inline bool strict_equal_(float a, const char* b) { return false; };
  // inline bool strict_equal_(float a, double b) { return false; };
  // inline bool strict_equal_(float a, char b) { return false; };
  // inline bool strict_equal_(float a, std::string b) { return false; };

  // Compare with char
  // inline bool strict_equal_(char a, int b) { return false; }
  // inline bool strict_equal_(char a, int64_t b) { return false; }
  // inline bool strict_equal_(char a, bool b) { return false; }
  // inline bool strict_equal_(char a, const char* b) { return false; };
  // inline bool strict_equal_(char a, double b) { return false; };
  // inline bool strict_equal_(char a, float b) { return false; };
  // inline bool strict_equal_(char a, std::string b) { return false; };

  // Compare with string
  // inline bool strict_equal_(std::string a, const char* b) { std::string s(b); return a == b; };
  // inline bool strict_equal_(std::string a, int b) { return false; }
  // inline bool strict_equal_(std::string a, int64_t b) { return false; }
  // inline bool strict_equal_(std::string a, bool b) { return false; }
  // inline bool strict_equal_(std::string a, double b) { return false; };
  // inline bool strict_equal_(std::string a, float b) { return false; };
  // inline bool strict_equal_(std::string a, char b) { return false; };

  // Compare with bools
  // inline bool strict_equal_(bool a, int b) { return false; }
  // inline bool strict_equal_(bool a, int64_t b) { return false; }
  // inline bool strict_equal_(bool a, const char* b) { return false; };
  // inline bool strict_equal_(bool a, double b) { return false; }
  // inline bool strict_equal_(bool a, float b) { return false; }
  // inline bool strict_equal_(bool a, char b) { return false; }
  // inline bool strict_equal_(bool a, std::string b) { return false; }

  // Compare with const char*
  // inline bool strict_equal_(const char* a, const char* b) { return std::strcmp(a, b); }
  // inline bool strict_equal_(const char* a, int b) { return false; }
  // inline bool strict_equal_(const char* a, int64_t b) { return false; };
  // inline bool strict_equal_(const char* a, bool b) { return false; };
  // inline bool strict_equal_(const char* a, double b) { return false; };
  // inline bool strict_equal_(const char* a, float b) { return false; };
  // inline bool strict_equal_(const char* a, char b) { return false; };
  // inline bool strict_equal_(const char* a, std::string b) { return utils::to_string(a).compare(b) == 0; }

  // Compare with int
  // inline bool equal_(int a, int64_t b) { return a == b; }
  // inline bool equal_(int a, bool b) { return a == int(b); }
  // inline bool equal_(int a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(int a, double b) { return a == int(b); };
  // inline bool equal_(int a, float b) { return a == int(b); };
  // inline bool equal_(int a, char b) { return a == int(b); };
  // inline bool equal_(int a, std::string b) { return a == std::stoi(b); };
  
  // Compare with int64_t
  // inline bool equal_(int64_t a, bool b) { return a == int64_t(b); }
  // inline bool equal_(int64_t a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(int64_t a, double b) { return a == int64_t(b); };
  // inline bool equal_(int64_t a, float b) { return a == int64_t(b); };
  // inline bool equal_(int64_t a, char b) { return a == int64_t(b); };
  // inline bool equal_(int64_t a, std::string b) { return a == std::stoll(b); };

  // Compare with doubles
  // inline bool equal_(double a, int b) { return a == double(b); }
  // inline bool equal_(double a, int64_t b) { return a == double(b); }
  // inline bool equal_(double a, bool b) { return a == double(int(b)); }
  // inline bool equal_(double a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(double a, float b) { return a == double(b); };
  // inline bool equal_(double a, char b) { return a == double(int(b)); };
  // inline bool equal_(double a, std::string b) { return a == std::stod(b); };

  // Compare with floats
  // inline bool equal_(float a, int64_t b) { return a == float(b); }
  // inline bool equal_(float a, int b) { return a == float(b); }
  // inline bool equal_(float a, bool b) { return a == float(int(b)); };
  // inline bool equal_(float a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(float a, double b) { return a == float(b); };
  // inline bool equal_(float a, char b) { return a == float(int(b)); };
  // inline bool equal_(float a, std::string b) { return a == std::stof(b); };

  // Compare with char
  // inline bool equal_(const char* a, const char* b) { return std::strcmp(a, b); }
  // inline bool equal_(char a, int b) { return int(a - '0') == b; }
  // inline bool equal_(char a, int64_t b) { return int64_t(a - '0') == b; }
  // inline bool equal_(char a, bool b) { return int(a - '0') == int(b); }
  // inline bool equal_(char a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(char a, double b) { return int64_t(a - '0') == int64_t(b); };
  // inline bool equal_(char a, float b) { return int64_t(a - '0') == int64_t(b); };
  // inline bool equal_(char a, std::string b) { return utils::to_string(a).compare(b) == 0; };

  // Compare with string
  // inline bool equal_(std::string a, const char* b) { std::string s(b); return a == b; };
  // inline bool equal_(std::string a, int b) { return a.compare(utils::to_string(b)) == 0; }
  // inline bool equal_(std::string a, int64_t b) { return a.compare(utils::to_string(b)) == 0; }
  // inline bool equal_(std::string a, bool b) { return a.compare(utils::to_string(b)) == 0; }
  // inline bool equal_(std::string a, double b) { return a.compare(utils::to_string(b)) == 0; };
  // inline bool equal_(std::string a, float b) { return a.compare(utils::to_string(b)) == 0; };
  // inline bool equal_(std::string a, char b) { return a.compare(utils::to_string(b)) == 0; };

  // Compare with bools
  // inline bool equal_(bool a, int b) { return a == b; }
  // inline bool equal_(bool a, int64_t b) { return a == b; }
  // inline bool equal_(bool a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(bool a, double b) { return a == int(b); }
  // inline bool equal_(bool a, float b) { return a == int(b); }
  // inline bool equal_(bool a, char b) { return a == int(b); }
  // inline bool equal_(bool a, std::string b) { return utils::to_string(a).compare(b) == 0; }

  // Compare with const char*
  // inline bool equal_(const char* a, int b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(const char* a, int64_t b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(const char* a, bool b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(const char* a, double b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(const char* a, float b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(const char* a, char b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  // inline bool equal_(const char* a, std::string b) { return utils::to_string(a).compare(b) == 0; }

};

// mocha_comparator(const char*, std::any) -> mocha_comparator<std::string, std::string>;
// mocha_comparator(std::any, const char*) -> mocha_comparator<std::string, std::string>;

} // mocha


#endif