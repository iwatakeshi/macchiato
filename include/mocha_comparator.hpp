#ifndef MOCHA_COMPARATOR_H
#define MOCHA_COMPARATOR_H
#include <string>
#include <to_string.hpp>
#include <functional>
#include <iostream>
#include <any>
#include <map>
#include <cmath>
#include "mocha_util.hpp"

// https://stackoverflow.com/a/53865723/1251031
#ifndef _MSC_VER
#   include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>
#include <to_string.hpp>
#include <regex>
#include <type_traits>
template <class T>
std::string
type_name() {
	typedef typename std::remove_reference<T>::type TR;
  std::unique_ptr<char, void(*)(void*)> own
           (
#ifndef _MSC_VER
  abi::__cxa_demangle(typeid(TR).name(), nullptr, nullptr, nullptr),
#else
  	nullptr,
#endif
	std::free
);
	std::string r = own != nullptr ? own.get() : typeid(TR).name();
	if (std::is_const<TR>::value)
		r += " const";
	if (std::is_volatile<TR>::value)
		r += " volatile";
	if (std::is_lvalue_reference<T>::value)
		r += "&";
	else if (std::is_rvalue_reference<T>::value)
		r += "&&";
	return r;
}

namespace mocha {

void debug (std::string message = "") {
	std::cout << message << std::endl; 
}

template <typename t_type, typename u_type>
struct mocha_comparator {
  // https://stackoverflow.com/a/28085851
  using T = typename std::conditional<std::is_fundamental<t_type>::value, t_type, t_type&>::type;
  using U = typename std::conditional<std::is_fundamental<u_type>::value, u_type, u_type&>::type;

public:
  mocha_comparator() {
    if (_mocha_util.is_same<T, U>()) {
      equal = [&] (T a, U b) -> bool { return compare(a, b); };
      strict_equal = equal;
    } else  {
      equal = [&] (T a, U b) -> bool { return equal_(a, b); };
      strict_equal = [&] (T a, U b) -> bool { return strict_equal_(a, b); };
    }
  };


  
  mocha_comparator(std::function<bool(T, U)> comparator):
   equal(comparator),
   strict_equal(comparator) {};

  std::function<bool(T, U)> equal;
  std::function<bool(T, U)> strict_equal;

private:

  /**
   * Dummy Functions
   * ======================
   * When the types are different, fool the compiler
   * to make it think we will use this function
   * when the types are the same for compare()
   * and visa-versa for equal() and strict_equal()
   */
  
  template<typename V, typename W>
  inline bool compare(V a, W b) { return true; }
  template<typename V>
  inline bool equal_(V a, V b) { return true; }
  template<typename V>
  inline bool strict_equal_(V a, V b) { return true; }
  /* ====================================================== */

  // Compare two objects of the same types
  template<typename V>
  inline bool compare(V a, V b) { return a == b; }

  // Compare with int
  inline bool equal_(int a, int64_t b) { return a == b; }
  inline bool equal_(int a, bool b) { return a == int(b); }
  inline bool equal_(int a, double b) { return a == int(std::round(b)); };
  inline bool equal_(int a, float b) { return a == int(std::round(b)); };
  inline bool equal_(int a, char b) { return a == int(std::round(b)); };
  inline bool equal_(int a, std::string const& b) { return a == std::stoi(b); };
  
  // Compare with int64_t
  inline bool equal_(int64_t a, int64_t b) { return a == b; }
  inline bool equal_(int64_t a, bool b) { return a == int64_t(b); }
  inline bool equal_(int64_t a, double b) { return a == int64_t(std::round(b)); };
  inline bool equal_(int64_t a, float b) { return a == int64_t(std::round(b)); };
  inline bool equal_(int64_t a, char b) { return a == int64_t(std::round(b)); };
  inline bool equal_(int64_t a, std::string const& b) { return a == std::stoll(b); };

  // Compare with doubles
  inline bool equal_(double a, int b) { return std::round(a) == double(b); }
  inline bool equal_(double a, int64_t b) { return std::round(a) == double(b); }
  inline bool equal_(double a, bool b) { return std::round(a) == double(int(b)); }
  inline bool equal_(double a, float b) { return a == double(b); };
  inline bool equal_(double a, char b) { return std::round(a) == double(int(b)); };
  inline bool equal_(double a, std::string const& b) { return a == std::stod(b); };

  // Compare with floats
  inline bool equal_(float a, int64_t b) { return std::round(a) == float(b); }
  inline bool equal_(float a, int b) { return std::round(a) == float(b); }
  inline bool equal_(float a, bool b) { return std::round(a) == float(int(b)); };
  inline bool equal_(float a, double b) { return a == float(b); };
  inline bool equal_(float a, char b) { return std::round(a) == float(int(b)); };
  inline bool equal_(float a, std::string const& b) { return a == std::stof(b); };

  // Compare with char
  inline bool equal_(char a, int b) { return int(a - '0') == b; }
  inline bool equal_(char a, int64_t b) { return int64_t(a - '0') == b; }
  inline bool equal_(char a, bool b) { return int(a - '0') == int(b); }
  inline bool equal_(char a, double b) { return int64_t(a - '0') == int64_t((std::round(b))); };
  inline bool equal_(char a, float b) { return int64_t(a - '0') == int64_t((std::round(b))); };
  inline bool equal_(char a, std::string const& b) { return std::string(1, a) == b; };

  // Compare with string
  inline bool equal_(std::string const& a, int b) { return a == utils::to_string(b); }
  inline bool equal_(std::string const& a, int64_t b) { return a == utils::to_string(b); }
  inline bool equal_(std::string const& a, bool b) { return a == utils::to_string(b); }
  inline bool equal_(std::string const& a, double b) { return a == utils::to_string(b); };
  inline bool equal_(std::string const& a, float b) { return a == utils::to_string(b); };
  inline bool equal_(std::string const& a, char b) { return a == utils::to_string(b); };

  // Compare with bools
  inline bool equal_(bool a, int b) { return a == b; }
  inline bool equal_(bool a, int64_t b) { return a == b; }
  inline bool equal_(bool a, double b) { return a == int(std::round(b)); }
  inline bool equal_(bool a, float b) { return a == int(std::round(b)); }
  inline bool equal_(bool a, char b) { return a == int(std::round(b)); }
  inline bool equal_(bool a, std::string const& b) { return utils::to_string(a) == b; }

  // Compare with int
  inline bool strict_equal_(int a, int64_t b) { return false; }
  inline bool strict_equal_(int a, bool b) { return false; }
  inline bool strict_equal_(int a, double b) { return false; };
  inline bool strict_equal_(int a, float b) { return false; };
  inline bool strict_equal_(int a, char b) { return false; };
  inline bool strict_equal_(int a, std::string const& b) { return false; };

  // Compare with int64_t
  inline bool strict_equal_(int64_t a, int b) { return false; }
  inline bool strict_equal_(int64_t a, bool b) { return false; }
  inline bool strict_equal_(int64_t a, double b) { return false; };
  inline bool strict_equal_(int64_t a, float b) { return false; };
  inline bool strict_equal_(int64_t a, char b) { return false; };
  inline bool strict_equal_(int64_t a, std::string const& b) { return false; };

  // Compare with doubles
  inline bool strict_equal_(double a, int b) { return false; }
  inline bool strict_equal_(double a, int64_t b) { return false; }
  inline bool strict_equal_(double a, bool b) { return false; }
  inline bool strict_equal_(double a, float b) { return false; };
  inline bool strict_equal_(double a, char b) { return false; };
  inline bool strict_equal_(double a, std::string const& b) { return false; };

  // Compare with floats
  inline bool strict_equal_(float a, int b) { return false; }
  inline bool strict_equal_(float a, int64_t b) { return false; }
  inline bool strict_equal_(float a, bool b) { return false; }
  inline bool strict_equal_(float a, double b) { return false; };
  inline bool strict_equal_(float a, char b) { return false; };
  inline bool strict_equal_(float a, std::string const& b) { return false; };

  // Compare with char
  inline bool strict_equal_(char a, int b) { return false; }
  inline bool strict_equal_(char a, int64_t b) { return false; }
  inline bool strict_equal_(char a, bool b) { return false; }
  inline bool strict_equal_(char a, double b) { return false; };
  inline bool strict_equal_(char a, float b) { return false; };
  inline bool strict_equal_(char a, std::string const& b) { return false; };

  // Compare with string
  inline bool strict_equal_(std::string const& a, int b) { return false; }
  inline bool strict_equal_(std::string const& a, int64_t b) { return false; }
  inline bool strict_equal_(std::string const& a, bool b) { return false; }
  inline bool strict_equal_(std::string const& a, double b) { return false; };
  inline bool strict_equal_(std::string const& a, float b) { return false; };
  inline bool strict_equal_(std::string const& a, char b) { return false; };

  // Compare with bools
  inline bool strict_equal_(bool a, int b) { return false; }
  inline bool strict_equal_(bool a, int64_t b) { return false; }
  inline bool strict_equal_(bool a, double b) { return false; }
  inline bool strict_equal_(bool a, float b) { return false; }
  inline bool strict_equal_(bool a, char b) { return false; }
  inline bool strict_equal_(bool a, std::string const& b) { return false; }
};

} // mocha


#endif