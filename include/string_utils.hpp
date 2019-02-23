#ifndef STRING_UTILS_H
#define STRING_UTILS_H
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
namespace mocha{
  namespace string_utils {
    template <typename T>
    bool is_typeof_string(T value) {
      std::string s = utils::to_string(type_name<decltype(value)>());
      std::regex r("char \\[[0-9]+\\] const&");
      return s.find("char const*") != std::string::npos || std::regex_match(s, r) || s.find("basic_string")!= std::string::npos;
    }

    template <typename T>
		std::string quote_string(T value) {
			bool is_string = mocha::string_utils::is_typeof_string(value);
			std::string s = utils::to_string(value);
			return is_string ? "\"" + s + "\"" : s;
		}
  } // string_utils
  
} // mocha

#endif