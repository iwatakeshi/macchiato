#ifndef MOCHA_TESTS_H
#define MOCHA_TESTS_H
#include <string>
#include "mocha_options.hpp"

struct __mocha_test_state {
  int pass = 0;
  int fail = 0;
  int pend = 0;
};

__mocha_test_state _mocha_test_state;

struct __mocha_test {
  protected:
  virtual std::string depth_string() { return ""; };
};


struct __mocha_describe : __mocha_test {

  void only() {
    only_ = true;
    // run test
    only_ = false;
  };

  void operator() () {
    depth_ += 1;
    if (!only_) {
       // run test here
    }
    depth_ -= 1;
  };

  protected:
  int depth_ = 0;
  private:
  friend struct __mocha_it;
  std::string depth_string() {
  std::string depth_string = "";
    for(auto i = 0; i < depth_; i++) {
      depth_string += _mocha_options.indentation;
    }
    return depth_string;
  };

  bool only_ = false;
};

struct __mocha_it : __mocha_test {

  __mocha_it() {};
  __mocha_it(const __mocha_describe& describe) {
    describe_ = describe;
  }
  void only() {
    only_ = true;
    // run test
    only_ = false;
  };

  void operator() () {
    if (!only_) {
       // run test here
    }
  };

  protected:
  std::string depth_string() {
    return describe_.depth_string() += _mocha_options.indentation;
    // return "";
  }
  private:
  __mocha_describe describe_;
  bool only_ = false;
};

__mocha_describe describe;
__mocha_it it(describe);
#endif