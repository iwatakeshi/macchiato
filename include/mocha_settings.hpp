#ifndef MOCHA_SETTINGS_H
#define MOCHA_SETTINGS_H
namespace mocha {
struct __mocha_settings {
  bool use_color = true;
  std::string indention = "  ";
};

__mocha_settings mocha_settings;

} // mocha

#endif