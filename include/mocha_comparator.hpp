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

template <typename T, typename U>
using comparator_lambda = std::function<bool(T, U)>;

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

/**
 * ========================
 *          bool
 * ========================
 */
template<>
inline bool __equal<>(bool a, unsigned short int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, short int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned long long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, long long int b) { return (b == 0 || b == 1) && a == (bool)(b); };
template<>
inline bool __equal<>(bool a, unsigned char b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, char b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, wchar_t b) { return false; };
template<>
inline bool __equal<>(bool a, float b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, double b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, long double b) { return ((int)(b) == 0 || (int)(b) == 1) && a == (int)(b); };
template<>
inline bool __equal<>(bool a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(bool a, nullptr_t b) { return false; };

/**
 * ========================
 *    unsigned short int
 * ========================
 */
template<>
inline bool __equal<>(unsigned short int a, bool b) { return __equal(b, a); };
template<>
inline bool __equal<>(unsigned short int a, unsigned int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, short int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, unsigned long int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, long int b) { return (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, unsigned long long int b) { return (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, long long int b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, unsigned char b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, char b) { return a == (unsigned short int)(b); };
template<>
inline bool __equal<>(unsigned short int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(unsigned short int a, float b) { return (unsigned short int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned short int a, double b) { return a == (unsigned short int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned short int a, long double b) { return a == (unsigned short int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned short int a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(unsigned short int a, nullptr_t b) { return false; };

/**
 * ========================
 *        short int
 * ========================
 */
template<>
inline bool __equal<>(short int a, bool b) { return __equal(b, a); };
template<>
inline bool __equal<>(short int a, unsigned short int b) { return __equal(b, a); };
template<>
inline bool __equal<>(short int a, unsigned int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, unsigned long int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, long int b) { return (short int)(b); }
template<>
inline bool __equal<>(short int a, unsigned long long int b) { return (short int)(b); };
template<>
inline bool __equal<>(short int a, long long int b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, unsigned char b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, char b) { return a == (short int)(b); };
template<>
inline bool __equal<>(short int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(short int a, float b) { return (short int)(std::round(b)); };
template<>
inline bool __equal<>(short int a, double b) { return a == (short int)(std::round(b)); };
template<>
inline bool __equal<>(short int a, long double b) { return a == (short int)(std::round(b)); };
template<>
inline bool __equal<>(short int a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(short int a, nullptr_t b) { return false; };

/**
 * ========================
 *       unsigned int
 * ========================
 */
template<>
inline bool __equal<>(unsigned int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned int a, unsigned short int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, short int b) { return a == (int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned long int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, long int b) { return (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned long long int b) { return (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, long long int b) { return a == (unsigned int)(b); }
template<>
inline bool __equal<>(unsigned int a, unsigned char b) { return a == (unsigned int)(b); };
template<>
inline bool __equal<>(unsigned int a, char b) { return a == (unsigned int)(b); };
template<>
inline bool __equal<>(unsigned int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(unsigned int a, float b) { return (unsigned int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned int a, double b) { return a == (unsigned int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned int a, long double b) { return a == (unsigned int)(std::round(b)); }
template<>
inline bool __equal<>(unsigned int a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(unsigned int a, nullptr_t b) { return false; }

/**
 * ========================
 *          int
 * ========================
 */
template<>
inline bool __equal<>(int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(int a, unsigned short int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, short int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, unsigned int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, unsigned long int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, long int b) { return (int)(b); }
template<>
inline bool __equal<>(int a, unsigned long long int b) { return (int)(b); }
template<>
inline bool __equal<>(int a, long long int b) { return a == (int)(b); }
template<>
inline bool __equal<>(int a, unsigned char b) { return a == (int)(b); };
template<>
inline bool __equal<>(int a, char b) { return a == (int)(b); };
template<>
inline bool __equal<>(int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(int a, float b) { return (int)(std::round(b)); };
template<>
inline bool __equal<>(int a, double b) { return a == (int)(std::round(b)); };
template<>
inline bool __equal<>(int a, long double b) { return a == (int)(std::round(b)); }
template<>
inline bool __equal<>(int a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(int a, nullptr_t b) { return false; }

/**
 * ========================
 *    unsigned long int
 * ========================
 */
template<>
inline bool __equal<>(unsigned long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned long int a, nullptr_t b) { return false; }
template<>
inline bool __equal<>(unsigned long int a, unsigned short int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, short int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned long int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, long int b) { return (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned long long int b) { return (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, long long int b) { return a == (unsigned long int)(b); }
template<>
inline bool __equal<>(unsigned long int a, unsigned char b) { return a == (unsigned long int)(b); };
template<>
inline bool __equal<>(unsigned long int a, char b) { return a == (unsigned long int)(b); };
template<>
inline bool __equal<>(unsigned long int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(unsigned long int a, float b) { return (unsigned long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long int a, double b) { return a == (unsigned long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long int a, long double b) { return a == (unsigned long int)(std::round(b)); }
template<>
inline bool __equal<>(unsigned long int a, std::string b) { return utils::to_string(a) == b; };

/**
 * ========================
 *        long int
 * ========================
 */
template<>
inline bool __equal<>(long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(long int a, nullptr_t b) { return false; }
template<>
inline bool __equal<>(long int a, unsigned short int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, short int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned long int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned long long int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, long long int b) { return a == (long int)(b); }
template<>
inline bool __equal<>(long int a, unsigned char b) { return a == (long int)(b); };
template<>
inline bool __equal<>(long int a, char b) { return a == (long int)(b); };
template<>
inline bool __equal<>(long int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(long int a, float b) { return (long int)(std::round(b)); };
template<>
inline bool __equal<>(long int a, double b) { return a == (long int)(std::round(b)); };
template<>
inline bool __equal<>(long int a, long double b) { return a == (long int)(std::round(b)); }
template<>
inline bool __equal<>(long int a, std::string b) { return utils::to_string(a) == b; };


/**
 * ========================
 *        unsigned long long int
 * ========================
 */
template<>
inline bool __equal<>(unsigned long long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned long long int a, nullptr_t b) { return false; }
template<>
inline bool __equal<>(unsigned long long int a, unsigned short int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, short int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, unsigned int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, unsigned long int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, long int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, long long int b) { return a == (unsigned long long int)(b); }
template<>
inline bool __equal<>(unsigned long long int a, unsigned char b) { return a == (unsigned long long int)(b); };
template<>
inline bool __equal<>(unsigned long long int a, char b) { return a == (unsigned long long int)(b); };
template<>
inline bool __equal<>(unsigned long long int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(unsigned long long int a, float b) { return (unsigned long long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long long int a, double b) { return a == (unsigned long long int)(std::round(b)); };
template<>
inline bool __equal<>(unsigned long long int a, long double b) { return a == (unsigned long long int)(std::round(b)); }
template<>
inline bool __equal<>(unsigned long long int a, std::string b) { return utils::to_string(a) == b; };

/**
 * ========================
 *      long long int
 * ========================
 */
template<>
inline bool __equal<>(long long int a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(long long int a, nullptr_t b) { return false; }
template<>
inline bool __equal<>(long long int a, unsigned short int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, short int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned long int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, long int b) { return a == (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned long long int b) { return (long long int)(b); }
template<>
inline bool __equal<>(long long int a, unsigned char b) { return a == (long long int)(b); };
template<>
inline bool __equal<>(long long int a, char b) { return a == (long long int)(b); };
template<>
inline bool __equal<>(long long int a, wchar_t b) { return false; };
template<>
inline bool __equal<>(long long int a, float b) { return (long long int)(std::round(b)); };
template<>
inline bool __equal<>(long long int a, double b) { return a == (long long int)(std::round(b)); };
template<>
inline bool __equal<>(long long int a, long double b) { return a == (long long int)(std::round(b)); }
template<>
inline bool __equal<>(long long int a, std::string b) { return utils::to_string(a) == b; };

/**
 * ========================
 *        unsigned char
 * ========================
 */
template<>
inline bool __equal<>(unsigned char a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(unsigned char a, char b) { return a == (unsigned char)(b); };
template<>
inline bool __equal<>(unsigned char a, wchar_t b) { return false; };
template<>
inline bool __equal<>(unsigned char a, float b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(unsigned char a, double b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(unsigned char a, long double b) { return __equal(int(std::round(b)), a); }
template<>
inline bool __equal<>(unsigned char a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(unsigned char a, nullptr_t b) { return false; }

/**
 * ========================
 *        char
 * ========================
 */
template<>
inline bool __equal<>(char a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(char a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(char a, wchar_t b) { return false; };
template<>
inline bool __equal<>(char a, float b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(char a, double b) { return __equal(int(std::round(b)), a); };
template<>
inline bool __equal<>(char a, long double b) { return __equal(int(std::round(b)), a); }
template<>
inline bool __equal<>(char a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(char a, nullptr_t b) { return false; }

/**
 * ========================
 *        wchar_t
 * ========================
 */
template<>
inline bool __equal<>(wchar_t a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(wchar_t a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(wchar_t a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(wchar_t a, float b) { return false; };
template<>
inline bool __equal<>(wchar_t a, double b) { return false; };
template<>
inline bool __equal<>(wchar_t a, long double b) { return false; }
template<>
inline bool __equal<>(wchar_t a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(wchar_t a, nullptr_t b) { return false; }

/**
 * ========================
 *        float
 * ========================
 */
template<>
inline bool __equal<>(float a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(float a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(float a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(float a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(float a, double b) { return a == (float)(b); };
template<>
inline bool __equal<>(float a, long double b) { return a == (float)(b); }
template<>
inline bool __equal<>(float a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(float a, nullptr_t b) { return false; }

/**
 * ========================
 *        double
 * ========================
 */
template<>
inline bool __equal<>(double a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(double a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, float b) { return __equal(b, a); };
template<>
inline bool __equal<>(double a, long double b) { return a == (double)(b); }
template<>
inline bool __equal<>(double a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(double a, nullptr_t b) { return false; }

/**
 * ========================
 *        long double
 * ========================
 */
template<>
inline bool __equal<>(long double a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(long double a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, float b) { return __equal(b, a); };
template<>
inline bool __equal<>(long double a, std::string b) { return utils::to_string(a) == b; };
template<>
inline bool __equal<>(long double a, nullptr_t b) { return false; };

/**
 * ========================
 *        string
 * ========================
 */
template<>
inline bool __equal<>(std::string a, bool b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, short int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, long long int b) { return __equal(b, a); }
template<>
inline bool __equal<>(std::string a, unsigned char b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, char b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, wchar_t b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, float b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, double b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, long double b) { return __equal(b, a); };
template<>
inline bool __equal<>(std::string a, nullptr_t b) { return __equal(b, a); };



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