#ifndef MOCHA_PLUGIN_H
#define MOCHA_PLUGIN_H
#include "mocha_test_flags.hpp"

namespace mocha {

template <typename T, typename U = T>
struct mocha_plugin {
  std::function<bool (T, U)> lambda_test;
  std::function<std::string (T, U, test_flags)> lambda_fail;

  mocha_plugin(
    std::function<bool (T, U)> lambda_test,
    std::function<std::string (T, U, test_flags)> lambda_fail
  ) : lambda_test(lambda_test), lambda_fail(lambda_fail) { };
};
  
} // mocha

#endif