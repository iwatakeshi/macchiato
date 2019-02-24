#ifndef MOCHA_RESULT_H
#define MOCHA_RESULT_H
#include <string>
#include "mocha_util.hpp"

namespace mocha {
  struct result_t {
		std::string message;
		bool did_pass = true;
	
		inline result_t operator + (const result_t& right) {
			auto result = result_t();
			result.did_pass = this->did_pass && right.did_pass;
			result.message = this->message + "\n" + _mocha_util.generate_depth_string() + right.message;
			return result;
		}

		inline result_t operator - (const result_t& right) {
			auto result = result_t();
			result.did_pass = this->did_pass || right.did_pass;
			result.message = this->message + "\n" + _mocha_util.generate_depth_string() + right.message;
			return result;
		}

		inline const result_t& operator = (const result_t& right) {
			this->message = right.message;
			this->did_pass = right.did_pass;
			return *this;
		}

		inline result_t& operator += (const result_t& right) {
			auto result = this->operator+(right);
			this->did_pass = result.did_pass;
			this->message = result.message;
			return *this;
		}

		inline result_t& operator -= (const result_t& right) {
			auto result = this->operator+(right);
			this->did_pass = result.did_pass;
			this->message = result.message;
			return *this;
		}

		inline result_t operator && (const result_t& right) {
			return this->operator+(right);
		}

		inline result_t operator || (const result_t& right) {
			return this->operator-(right);
		}

		inline result_t operator &= (const result_t& right) {
			return this->operator+=(right);
		}

		inline result_t operator |= (const result_t& right) {
			return this->operator-=(right);
		}
	};
} // mocha

#endif