#ifndef MOCHA_COMPARATOR_H
#define MOCHA_COMPARATOR_H
#include <string>
#include <to_string.hpp>
#include <functional>
#include <iostream>
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

// TODO: Add additional types to compare against.
namespace mocha {
  

template <typename T>
inline bool __equal(T a, T b) { return a == b; };

template <typename T, typename U>
inline bool __equal(T a, U b) {
  std::string a_t = type_name<decltype(a)>();
  std::string b_t = type_name<decltype(b)>();
  _mocha_util.debug(
    _mocha_util.generate_depth_string() +
    _mocha_util.color_yellow("[mocha::warn] - Using a default comparator for type [T = " + a_t + "] and [U = " + b_t + "] which will return false.")
  );
};

template<typename T>
inline bool __strict_equal(T a, T b) { return a == b; }

// Strict comparison of different types
// will default to false
template<typename T, typename U>
inline bool __strict_equal(T a, U b) {
  return false;
};

// Compare with int
template<>
inline bool __equal<>(int a, int64_t b) { return a == b; }
template<>
inline bool __equal<>(int a, bool b) { return a == int(b); }
template<>
inline bool __equal<>(int a, double b) { return a == int(std::round(b)); };
template<>
inline bool __equal<>(int a, float b) { return a == int(std::round(b)); };
template<>
inline bool __equal<>(int a, char b) { return a == int(std::round(b)); };
template<>
inline bool __equal<>(int a, std::string b) { return a == std::stoi(b); };

// Compare with int64_t
template<>
inline bool __equal<>(int64_t a, int b) { return a == b; }
template<>
inline bool __equal<>(int64_t a, bool b) { return a == int64_t(b); }
template<>
inline bool __equal<>(int64_t a, double b) { return a == int64_t(std::round(b)); };
template<>
inline bool __equal<>(int64_t a, float b) { return a == int64_t(std::round(b)); };
template<>
inline bool __equal<>(int64_t a, char b) { return a == int64_t(std::round(b)); };
template<>
inline bool __equal<>(int64_t a, std::string b) { return a == std::stoll(b); };

// Compare with doubles
// template<>
// inline bool __equal(double a, double b) { return a == b; }
template<>
inline bool __equal<>(double a, int b) { return std::round(a) == double(b); }
template<>
inline bool __equal<>(double a, int64_t b) { return std::round(a) == double(b); }
template<>
inline bool __equal<>(double a, bool b) { return std::round(a) == double(int(b)); }
template<>
inline bool __equal<>(double a, float b) { return a == double(b); };
template<>
inline bool __equal<>(double a, char b) { return std::round(a) == double(int(b)); };
template<>
inline bool __equal<>(double a, std::string b) { return a == std::stod(b); };

// Compare with floats
// template<>
// inline bool __equal(float a, float b) { return a == b; }
template<>
inline bool __equal<>(float a, int64_t b) { return std::round(a) == float(b); }
template<>
inline bool __equal<>(float a, int b) { return std::round(a) == float(b); }
template<>
inline bool __equal<>(float a, bool b) { return std::round(a) == float(int(b)); };
template<>
inline bool __equal<>(float a, double b) { return a == float(b); };
template<>
inline bool __equal<>(float a, char b) { return std::round(a) == float(int(b)); };
template<>
inline bool __equal<>(float a, std::string b) { return a == std::stof(b); };

// Compare with char
// template<>
// inline bool __equal(char a, char b) { return a == b; }
template<>
inline bool __equal<>(char a, int b) { return int(a - '0') == b; }
template<>
inline bool __equal<>(char a, int64_t b) { return int64_t(a - '0') == b; }
template<>
inline bool __equal<>(char a, bool b) { return int(a - '0') == int(b); }
template<>
inline bool __equal<>(char a, double b) { return int64_t(a - '0') == int64_t((std::round(b))); };
template<>
inline bool __equal<>(char a, float b) { return int64_t(a - '0') == int64_t((std::round(b))); };
template<>
inline bool __equal<>(char a, std::string b) { return std::string(1, a) == b; };

// Compare with string
// template<>
// inline bool __equal(std::string a, std::string b) { return a == b; }
template<>
inline bool __equal<>(std::string a, int b) { return a == utils::to_string(b); }
template<>
inline bool __equal<>(std::string a, int64_t b) { return a == utils::to_string(b); }
template<>
inline bool __equal<>(std::string a, bool b) { return a == utils::to_string(b); }
template<>
inline bool __equal<>(std::string a, double b) { return a == utils::to_string(b); };
template<>
inline bool __equal<>(std::string a, float b) { return a == utils::to_string(b); };
template<>
inline bool __equal<>(std::string a, char b) { return a == utils::to_string(b); };

// Compare with bools
// template<>
// inline bool __equal(bool a, bool b) { return a == b; }
template<>
inline bool __equal<>(bool a, int b) { return a == b; }
template<>
inline bool __equal<>(bool a, int64_t b) { return a == b; }
template<>
inline bool __equal<>(bool a, double b) { return a == int(std::round(b)); }
template<>
inline bool __equal<>(bool a, float b) { return a == int(std::round(b)); }
template<>
inline bool __equal<>(bool a, char b) { return a == int(std::round(b)); }
template<>
inline bool __equal<>(bool a, std::string b) { return utils::to_string(a) == b; }


template<typename t_type, typename u_type>
struct mocha_comparator {
  using T = typename std::conditional<std::is_fundamental<t_type>::value, t_type, t_type&>::type;
  using U = typename std::conditional<std::is_fundamental<u_type>::value, u_type, u_type&>::type;
  mocha_comparator() {
    equal = [&](T a, U b) -> bool { return __equal(a, b); };
    if (_mocha_util.is_same<T, U>()) {
      strict_equal = equal;
    } else  {
      strict_equal = [&] (T a, U b) -> bool { return __strict_equal(a, b); };
    }
  };

  mocha_comparator(std::function<bool(T, U)> comparator):
   equal(comparator),
   strict_equal(comparator) {};

  std::function<bool(T, U)> equal;
  std::function<bool(T, U)> strict_equal;
};

} // mocha


#endif