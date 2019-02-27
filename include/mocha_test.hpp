#ifndef MOCHA_TESTS_H
#define MOCHA_TESTS_H
#include <iostream>
#include <string>
#include <functional>
#include <map>
#include <vector>
#include "mocha_options.hpp"

void debug(std::string message) {
  std::cout << message << std::endl;
}

struct __mocha_test_state {
  int pass = 0;
  int fail = 0;
  int pend = 0;
};

__mocha_test_state _mocha_test_state;

struct __mocha_test_function {

  protected:
  virtual std::string depth_string() { return ""; };
  virtual std::string depth_string(int depth) const {
    std::string depth_string = "";
    for(auto i = 0; i < depth; i++) {
      depth_string += _mocha_options.indentation;
    }
    return depth_string;
  }
};

using mocha_test_function_t = std::function<void()>;

struct mocha_test_hook {
  protected:
  virtual void operator()(const mocha_test_function_t& hook) {
    // Find the hook's call stack associated with the current describe()
    auto current_call_stack = call_stack.find(depth_);
    // We found the stack
    if (current_call_stack != call_stack.end()) {
      auto stack = current_call_stack->second;
      // Add the hook to the local stack
      stack.push_back(hook);
      // Update the local stack
      call_stack[depth_] = stack;
    } else  {
      // Create the local stack
      std::vector stack = { hook };
      // Add the local stack
      call_stack = { { depth_, stack }};
    }
  };
  virtual void operator() (int depth) {
    auto current_call_stack = call_stack.find(depth);
    if (current_call_stack != call_stack.end()) {
      std::vector<mocha_test_function_t> stack = current_call_stack->second;
      auto hook = stack.back();
      hook();
      stack.pop_back();
      call_stack[depth] = stack;
    } else {
      debug("couldn't find it!");
    }
    depth_ = depth;
  }

  private:
  int depth_ = 0;
  std::map<int, std::vector<mocha_test_function_t>> call_stack;
  
};

struct mocha_before : mocha_test_hook {
  void operator()(mocha_test_function_t&& hook) {
    mocha_test_hook::operator()(hook);
  };
  
  private:
  friend struct mocha_describe;
  void operator() (int depth) {
    debug("before::operator(depth)");
    mocha_test_hook::operator()(depth);
  }
};

mocha_before before;

struct mocha_before_each : mocha_test_hook {
  void operator()(mocha_test_function_t&& hook) {
   mocha_test_hook::operator()(hook);
  };
  private:
  friend struct mocha_it;
  void operator() (int depth) {
    debug("before_each::operator(depth)");
    mocha_test_hook::operator()(depth);
  }
};

mocha_before_each before_each;

struct mocha_after : mocha_test_hook {
  void operator()(mocha_test_function_t&& hook) {
    mocha_test_hook::operator()(hook);
  };
  void operator() (int depth) {
    debug("after::operator(depth)");
    mocha_test_hook::operator()(depth);
  }
  private:
  friend struct mocha_describe;
};

mocha_after after;

struct mocha_after_each: mocha_test_hook {
  void operator()(mocha_test_function_t&& hook) {
    mocha_test_hook::operator()(hook);
  };
  private:
  friend struct mocha_it;
  void operator() (int depth) {
   debug("after_each::operator(depth)");
   mocha_test_hook::operator()(depth);
  }
};


mocha_after_each after_each;

struct mocha_describe : __mocha_test_function {
  mocha_describe(
    const mocha_before& before, 
    const mocha_after& after
  ): before_(before), after_(after) {};

  void only(mocha_test_function_t function) {
    only_ = true;
    before_(depth_);
    
    debug("describe::only(function)");

    function();
    
    after_(depth_);
    only_ = false;
  };

  void operator() (mocha_test_function_t function) {
    depth_ += 1;
    if (!only_) {
      before_(depth_ - 1);
      debug("describe::operator(function)");
      function();
      after_(depth_ - 1);
    }
    depth_ -= 1;
  };

  protected:
  int depth_ = 0;
  private:

  friend struct mocha_it;
  mocha_before before_;
  mocha_after after_;
  
  std::string depth_string() {
    return __mocha_test_function::depth_string(depth_);
  };

  bool only_ = false;
};

struct mocha_it : __mocha_test_function {
  mocha_it(
    const mocha_describe& describe,
    const mocha_before_each& before_each,
    const mocha_after_each& after_each
  ): describe_(describe), before_each_(before_each), after_each_(after_each) {};

  void only(mocha_test_function_t function) {
    only_ = true;
    debug("it::only(function)");
    function();
    only_ = false;
  };

  void operator()() {
    debug("it::operator()");
  }

  void operator() (mocha_test_function_t function) {
    if (!only_) {
      debug("it::operator(function)");
      function();
    }
  };

  protected:
  std::string depth_string() {
    return __mocha_test_function::depth_string(describe_.depth_ + 1);
  }
  private:
  mocha_describe describe_;
  mocha_before_each before_each_;
  mocha_after_each after_each_;
  bool only_ = false;
};

mocha_describe describe(before, after);
mocha_it it(describe, before_each, after_each);
#endif