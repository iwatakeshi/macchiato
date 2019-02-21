prebuilt_cxx_library(
  name = 'mocha',
  header_only = True,
  header_namespace = '',
  exported_headers = [
    'mocha.hpp',
  ],
  licenses = [
    'LICENSE',
  ], 
  visibility = [
    'PUBLIC',
  ],
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