#ifndef MOCHA_UTIL_H
#define MOCHA_UTIL_H
#include <string>
#include "mocha_settings.hpp"
#include <to_string.hpp>
namespace mocha {

  struct __mocha_util_class {

    void increment_depth() {
      this->depth_ += 1;
    };

    void decrement_depth() {
      this->depth_ -= 1;
    };

    std::string generate_parent_depth_string() {
      std::string depth_string = "";
      for(unsigned int i = 0; i < depth_-1; i++) {
        depth_string += mocha_settings.indention;
      }

      return depth_string;
    };

    std::string generate_child_depth_string() {
      std::string child_depth_string = "";
      for(unsigned int i = 0; i < depth_; i++) {
        child_depth_string += mocha_settings.indention;
      }

      return child_depth_string;
    };

    std::string generate_depth_string() {
      return generate_parent_depth_string() + 
             generate_child_depth_string();
    }

    std::string color_cyan(std::string input) {
      return mocha_settings.use_color ? std::string("\033[36;1m" + input + "\033[0m") : input;
    };

    std::string color_green(std::string input) {
      return mocha_settings.use_color ? std::string("\033[32;1m" + input + "\033[0m") : input;
    };
    std::string color_red(std::string input) {
      return mocha_settings.use_color ? std::string("\033[31;1m" + input + "\033[0m") : input;
    };


    // Just a helper to add to the resultant output_
    void log(std::string message) {
      output_ += message;
    };


    // Helper to increment the summary of tests
    enum result_state {
      pass, fail, pending
    };

    void log_result(result_state type) {
      if(type == result_state::pass) {
        this->num_passed_++;
      }
      else if(type == result_state::fail) {
        this->num_failed_++;
      }
      else if(type == result_state::pending) {
        this->num_pending_++;
      }
    };

    std::string summary() {
      std::string result = this->output_;
      // Add a small summary at the end
      result += std::string("\n\n") +
        this->color_green(utils::to_string(this->num_passed_) + " passing") + "\n" +
        this->color_red(utils::to_string(this->num_failed_) + " failing") + "\n" +
        this->color_cyan(utils::to_string(this->num_pending_) + " pending");


      result += "\n";

      return result;
    };

    void clear() {
      this->output_ = "";
      this->num_passed_ = 0;
      this->num_failed_ = 0;
      this->num_pending_ = 0;

    };

    private:
      std::string output_ = "";
      unsigned int depth_ = 0;
      unsigned int num_passed_ = 0;
      unsigned int num_failed_ = 0;
      unsigned int num_pending_ = 0;


  };

  __mocha_util_class _mocha_util;
  
} // mocha

#endif