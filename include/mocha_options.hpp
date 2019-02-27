#ifndef MOCHA_OPTIONS_H
#define MOCHA_OPTIONS_H
#include <string>

struct __mocha_options {
  bool debug = false;
  bool use_color = true;
  std::string indentation = "  ";
};

__mocha_options _mocha_options;

#endif