load('//:buckaroo_macros.bzl', 'buckaroo_deps')

prebuilt_cxx_library(
  name = 'mocha',
  header_only = True,
  header_namespace = '',
  exported_headers = [
    'mocha.hpp',
    'include/mocha_comparator.hpp',
    'include/mocha_plugin.hpp',
    'include/mocha_result.hpp',
    'include/mocha_settings.hpp',
    'include/mocha_util.hpp',
    'include/mocha_test_flags.hpp',
  ],
  licenses = [
    'LICENSE',
  ], 
  visibility = [
    'PUBLIC',
  ],
  deps = buckaroo_deps()
)

cxx_binary(
  name = 'main',
  srcs = [
    'main.cpp',
  ],
  deps = [
    ':mocha',
  ],
)