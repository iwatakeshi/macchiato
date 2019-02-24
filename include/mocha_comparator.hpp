#ifndef MOCHA_COMPARATOR_H
#define MOCHA_COMPARATOR_H
#include <to_string.hpp>
#include <functional>

namespace mocha {

template <typename t_type, typename u_type>
class mocha_comparator {
  // https://stackoverflow.com/a/28085851
  using T = typename std::conditional<std::is_fundamental<t_type>::value, t_type, t_type&>::type;
  using U = typename std::conditional<std::is_fundamental<u_type>::value, u_type, u_type&>::type;

public:
  mocha_comparator() {
      
      strict_equal = std::bind(strict_equal_);
    }
  
  mocha_comparator(std::function<bool(T, U)> comparator): 
    equal(comparator), 
    strict_equal(comparator);

  template<typename V, typename W>
  std::function<bool(V, W)> equal;

  template<typename V, typename W>
  std::function<bool(V, W)> strict_equal;

private:
// Compare with int
  bool strict_equal_(int a, int b) { return a == b; }
  bool strict_equal_(int a, int64_t b) { return false; }
  bool strict_equal_(int a, bool b) { return false; }
  bool strict_equal_(int a, const char* b) { return false; };
  bool strict_equal_(int a, double b) { return false; };
  bool strict_equal_(int a, float b) { return false; };
  bool strict_equal_(int a, char b) { return false; };
  bool strict_equal_(int a, std::string b) { return false; };

  // Compare with int64_t
  bool strict_equal_(int64_t a, int b) { return false; }
  bool strict_equal_(int64_t a, int64_t b) { return a == b; }
  bool strict_equal_(int64_t a, bool b) { return false; }
  bool strict_equal_(int64_t a, const char* b) { return false; };
  bool strict_equal_(int64_t a, double b) { return false; };
  bool strict_equal_(int64_t a, float b) { return false; };
  bool strict_equal_(int64_t a, char b) { return false; };
  bool strict_equal_(int64_t a, std::string b) { return false; };

  // Compare with doubles
  bool strict_equal_(double a, double b) { return a == b; };
  bool strict_equal_(double a, int b) { return false; }
  bool strict_equal_(double a, int64_t b) { return false; }
  bool strict_equal_(double a, bool b) { return false; }
  bool strict_equal_(double a, const char* b) { return false; };
  bool strict_equal_(double a, float b) { return false; };
  bool strict_equal_(double a, char b) { return false; };
  bool strict_equal_(double a, std::string b) { return false; };

  // Compare with floats
  bool strict_equal_(float a, float b) { return a == b; };
  bool strict_equal_(float a, int b) { return false; }
  bool strict_equal_(float a, int64_t b) { return false; }
  bool strict_equal_(float a, bool b) { return false; }
  bool strict_equal_(float a, const char* b) { return false; };
  bool strict_equal_(float a, double b) { return false; };
  bool strict_equal_(float a, char b) { return false; };
  bool strict_equal_(float a, std::string b) { return false; };

  // Compare with char
  bool strict_equal_(char a, char b) { return a == b; };
  bool strict_equal_(char a, int b) { return false; }
  bool strict_equal_(char a, int64_t b) { return false; }
  bool strict_equal_(char a, bool b) { return false; }
  bool strict_equal_(char a, const char* b) { return false; };
  bool strict_equal_(char a, double b) { return false; };
  bool strict_equal_(char a, float b) { return false; };
  bool strict_equal_(char a, std::string b) { return false; };

  bool strict_equal_(std::string a, std::string b) { return a.compare(b) == 0; };
  bool strict_equal_(std::string a, const char* b) { std::string s(b); return a == b; };
  bool strict_equal_(std::string a, int b) { return false; }
  bool strict_equal_(std::string a, int64_t b) { return false; }
  bool strict_equal_(std::string a, bool b) { return false; }
  bool strict_equal_(std::string a, double b) { return false; };
  bool strict_equal_(std::string a, float b) { return false; };
  bool strict_equal_(std::string a, char b) { return false; };

  // Compare with bools
  bool strict_equal_(bool a, bool b) { return a == b; }		
  bool strict_equal_(bool a, int b) { return false; }
  bool strict_equal_(bool a, int64_t b) { return false; }
  bool strict_equal_(bool a, const char* b) { return false; };
  bool strict_equal_(bool a, double b) { return false; }
  bool strict_equal_(bool a, float b) { return false; }
  bool strict_equal_(bool a, char b) { return false; }
  bool strict_equal_(bool a, std::string b) { return false; }

  // Compare with const char*
  bool strict_equal_(const char* a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; }
  bool strict_equal_(const char* a, int b) { return false; }
  bool strict_equal_(const char* a, int64_t b) { return false; };
  bool strict_equal_(const char* a, bool b) { return false; };
  bool strict_equal_(const char* a, double b) { return false; };
  bool strict_equal_(const char* a, float b) { return false; };
  bool strict_equal_(const char* a, char b) { return false; };
  bool strict_equal_(const char* a, std::string b) { return utils::to_string(a).compare(b) == 0; }

  // Compare with int
  bool equal_(int a, int b) { return a == b; }
  bool equal_(int a, int64_t b) { return a == b; }
  bool equal_(int a, bool b) { return a == int(b); }
  bool equal_(int a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(int a, double b) { return a == int(b); };
  bool equal_(int a, float b) { return a == int(b); };
  bool equal_(int a, char b) { return a == int(b); };
  bool equal_(int a, std::string b) { return a == std::stoi(b); };
  
  // Compare with int64_t
  bool equal_(int64_t a, int b) { return a == b; }
  bool equal_(int64_t a, int64_t b) { return a == b; }
  bool equal_(int64_t a, bool b) { return a == int64_t(b); }
  bool equal_(int64_t a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(int64_t a, double b) { return a == int64_t(b); };
  bool equal_(int64_t a, float b) { return a == int64_t(b); };
  bool equal_(int64_t a, char b) { return a == int64_t(b); };
  bool equal_(int64_t a, std::string b) { return a == std::stoll(b); };

  // Compare with doubles
  bool equal_(double a, double b) { return a == b; };
  bool equal_(double a, int b) { return a == double(b); }
  bool equal_(double a, int64_t b) { return a == double(b); }
  bool equal_(double a, bool b) { return a == double(int(b)); }
  bool equal_(double a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(double a, float b) { return a == double(b); };
  bool equal_(double a, char b) { return a == double(int(b)); };
  bool equal_(double a, std::string b) { return a == std::stod(b); };

  // Compare with floats
  bool equal_(float a, float b) { return a == b; };
  bool equal_(float a, int64_t b) { return a == float(b); }
  bool equal_(float a, int b) { return a == float(b); }
  bool equal_(float a, bool b) { return a == float(int(b)); };
  bool equal_(float a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(float a, double b) { return a == float(b); };
  bool equal_(float a, char b) { return a == float(int(b)); };
  bool equal_(float a, std::string b) { return a == std::stof(b); };

  // Compare with char
  bool equal_(char a, char b) { return a == b; };
  bool equal_(char a, int b) { return int(a - '0') == b; }
  bool equal_(char a, int64_t b) { return int64_t(a - '0') == b; }
  bool equal_(char a, bool b) { return int(a - '0') == int(b); }
  bool equal_(char a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(char a, double b) { return int64_t(a - '0') == int64_t(b); };
  bool equal_(char a, float b) { return int64_t(a - '0') == int64_t(b); };
  bool equal_(char a, std::string b) { return utils::to_string(a).compare(b) == 0; };

  bool equal_(std::string a, std::string b) { return a.compare(b) == 0; };
  bool equal_(std::string a, const char* b) { std::string s(b); return a == b; };
  bool equal_(std::string a, int b) { return a.compare(utils::to_string(b)) == 0; }
  bool equal_(std::string a, int64_t b) { return a.compare(utils::to_string(b)) == 0; }
  bool equal_(std::string a, bool b) { return a.compare(utils::to_string(b)) == 0; }
  bool equal_(std::string a, double b) { return a.compare(utils::to_string(b)) == 0; };
  bool equal_(std::string a, float b) { return a.compare(utils::to_string(b)) == 0; };
  bool equal_(std::string a, char b) { return a.compare(utils::to_string(b)) == 0; };

  // Compare with bools
  bool equal_(bool a, bool b) { return a == b; }		
  bool equal_(bool a, int b) { return a == b; }
  bool equal_(bool a, int64_t b) { return a == b; }
  bool equal_(bool a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(bool a, double b) { return a == int(b); }
  bool equal_(bool a, float b) { return a == int(b); }
  bool equal_(bool a, char b) { return a == int(b); }
  bool equal_(bool a, std::string b) { return utils::to_string(a).compare(b) == 0; }

  // Compare with const char*
  bool equal_(const char* a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; }
  bool equal_(const char* a, int b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(const char* a, int64_t b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(const char* a, bool b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(const char* a, double b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(const char* a, float b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(const char* a, char b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
  bool equal_(const char* a, std::string b) { return utils::to_string(a).compare(b) == 0; }

};

} // mocha


#endif