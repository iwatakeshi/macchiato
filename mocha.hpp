// mocha
// https://github.com/iwatakeshi/mocha
//
// Mocha.js inspired testing for C++
//
// Requires C++11. Works on the following platforms:
//		- Most desktop environments
//		- Visual Studio
#ifndef MOCHA_H
#define MOCHA_H

#include <to_string.hpp>
#include <string>
#include <functional>
#include <iostream>
#include "include/type_utils.hpp"
#include <cmath>
// Extend the namespace utils (to_string.hpp)
namespace utils {
  std::string to_string(std::string s) {
    return "\"" + s + "\"";
  }

  std::string to_string(const char* c_str) {
    std::string s(c_str);
    return "\"" + s + "\"";
  }
}

namespace mocha {
	struct _mocha_settings {
		bool use_color = true;
		std::string indention = "\t";
	};

	_mocha_settings mocha_settings;

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

		std::string output() {
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

	std::string output() {
		return _mocha_util.output();
	};

	void clear() {
		_mocha_util.clear();
	};

struct result_t {
		std::string message;
		bool did_pass = true;
	
		inline result_t operator + (const result_t& right) {
			auto result = result_t();

			result.did_pass = this->did_pass && right.did_pass;
			result.message = this->message + (
				right.message.compare(_mocha_util.generate_depth_string()) == 0 ? 
				"" : "\n" + _mocha_util.generate_depth_string() + right.message
			);
			return result;
		}

		inline const result_t& operator = (const result_t& right) {
			this->message = right.message;
			this->did_pass = right.did_pass;
			return *this;
		}

		inline result_t& operator += (const result_t& right) {
			this->did_pass = this->did_pass && right.did_pass;
			this->message += ("\n" + _mocha_util.generate_depth_string() + right.message);
			return *this;
		}

		inline result_t operator && (const result_t& right) {
			auto result = result_t();
			result.did_pass = this->did_pass && right.did_pass;
			result.message = this->message + (
				right.message.empty() ? "" : 
				"\n" + 
				_mocha_util.generate_parent_depth_string() + 
				_mocha_util.generate_child_depth_string()
			) + right.message;
			return result;
		}

		inline result_t operator || (const result_t& right) {
			auto result = result_t();
			result.did_pass = this->did_pass || right.did_pass;
			result.message = this->message + "\n" +
			_mocha_util.generate_parent_depth_string() + 
			_mocha_util.generate_child_depth_string() + right.message;
			return result;
		}
	};

	struct test_flags {
		bool negate = false;
	};


	template <typename T, typename U = T>
	struct mocha_plugin {
		std::function<bool (T, U)> lambda_test;
		std::function<std::string (T, U, test_flags)> lambda_fail;

		mocha_plugin(
			std::function<bool (T, U)> lambda_test,
			std::function<std::string (T, U, test_flags)> lambda_fail
		) : lambda_test(lambda_test), lambda_fail(lambda_fail) { };
	};

	// expect: BDD
	template <typename T>
	struct expect_t {

		expect_t(T actual) : actual(actual) { };

		template <typename t_type, typename u_type>
		struct comparator {
			// https://stackoverflow.com/a/28085851
			using A = typename std::conditional<std::is_fundamental<t_type>::value, t_type, t_type&>::type;
			using B = typename std::conditional<std::is_fundamental<u_type>::value, u_type, u_type&>::type;
			
			bool compare(A actual, B expected) {
				return actual == expected;
			}

			bool compare(A actual, B expected, std::function<bool(A a, B b)> lambda) {
				return lambda(actual, expected);
			}
		};
		
		/**
		 * Compares the actual and expected of the same type.
		 */
		expect_t* equal(T expected) {
			bool result = comparator<T, T>().compare(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);
			return this;
		};
	
		/**
		 * [alias]
		 * Compares the actual and expected of the same type.
		 */
		expect_t* eql(T expected) {
			return this->equal(expected);
		};

		/**
		 * Compares the actual and expected of different types.
		 */
		template<typename U>
		expect_t* equal(U expected) {
			bool result = type_utils::equal(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);
			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of different types.
		 */
		template <typename U>		
		expect_t* eql(U expected) {
			return this->equal(expected);
		};

		/**
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* equal(U expected, std::function<bool(T a, U b)> lambda) {
			bool result = comparator<T, U>().compare(this->actual, expected, lambda);
			this->add_result_t(
				result,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);
			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* eql(U expected, std::function<bool(T a, U b)> lambda) {
			return this->equal(expected, lambda);
		};

		/**
		 * Compares the actual and expected of the same type.
		 */
		expect_t* strict_equal(T expected) {
			bool result = comparator<T, T>().compare(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + utils::to_string(this->actual) + " to strictly " + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);
			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of the same type.
		 */
		expect_t* seql(T expected) {
			return this->equal(expected);
		};

		/**
		 * Compares the actual and expected of different types.
		 */
		template <typename U>
		expect_t* strict_equal(U expected) {
			bool result = type_utils::strict_equal(this->actual, expected);
			// bool is_same_type = std::is_same<decltype(this->actual), decltype(expected)>::value;
			this->add_result_t(
				result,
				"Expected " + utils::to_string(this->actual) + " to strictly " + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);
			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of different types.
		 */
		template <typename U>
		expect_t* seql(U expected) {
			return this->strict_equal(expected);
		};

		/**
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* strict_equal(U expected, std::function<bool(T a, U b)> lambda) {
			bool result = comparator<T, U>().compare(this->actual, expected, lambda);
			this->add_result_t(
				result,
				"Expected " + utils::to_string(this->actual) + " to strictly" + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);

			return this;
		};
		
		/**
		 * [alias]
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* seql(U expected, std::function<bool(T a, U b)> lambda) {
			return this->strict_equal(expected, lambda);
		};

		expect_t* close_to(double expected) {
			return this->close_to(expected, 0.0001);
		};

		expect_t* close_to(double expected, double tolerance) {
			this->add_result_t(
				fabs(this->actual - expected) <= tolerance,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + (utils::to_string(expected) + " within tolerance of " + utils::to_string(tolerance))
			);

			return this;
		};

		expect_t* within(double lower, double upper) {
			this->add_result_t(
				this->actual > lower && this->actual < upper,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be above " + utils::to_string(lower) + " and below " + utils::to_string(upper)
			);

			return this;
		};


		expect_t* above(double expected) {
			this->add_result_t(
				this->actual > expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than " + utils::to_string(expected)
			);

			return this;
		};
		expect_t* gt(double expected) {
			return this->above(expected);
		};
		expect_t* greater_than(double expected) {
			return this->above(expected);
		};

		expect_t* least(double expected) {
			this->add_result_t(
				this->actual >= expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than or equal to " + utils::to_string(expected)
			);

			return this;
		};
		expect_t* gte(double expected) {
			return this->least(expected);
		};

		expect_t* below(double expected) {
			this->add_result_t(
				this->actual < expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be lesser than " + utils::to_string(expected)
			);

			return this;
		};

		expect_t* lt(double expected) {
			return this->below(expected);
		};

		expect_t* less_than(double expected) {
			return this->below(expected);
		};

		expect_t* most(double expected) {
			this->add_result_t(
				this->actual <= expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be less than or equal to " + utils::to_string(expected)
			);

			return this;
		};

		expect_t* lte(double expected) {
			return this->most(expected);
		};

		expect_t* satisfy(std::function<bool (T)> lambda_test) {
			bool result = lambda_test(this->actual);

			return this->satisfy(
				result,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "satisfy the given test"
			);
		};

		expect_t* satisfy(std::function<bool (T)> lambda_test, std::function<std::string (T, test_flags)> lambda_fail) {
			bool result = lambda_test(this->actual);
			std::string message = lambda_fail(this->actual, this->flags);

			return this->satisfy(result, message);
		};

		template <typename U>
		expect_t* satisfy(mocha_plugin<T, U> plugin, U expected) {
			bool result = plugin.lambda_test(this->actual, expected);
			std::string message = plugin.lambda_fail(this->actual, expected, this->flags);

			return this->satisfy(result, message);
		};

		expect_t* satisfy(bool result, std::string message) {
			this->add_result_t(
				result,
				message
			);

			return this;
		};

		class member_logic {
			expect_t* expect_pointer;
			std::function<void (expect_t*)> getter_lambda;
			public:
				member_logic(expect_t *i, std::function<void (expect_t*)> getter_lambda) : expect_pointer(i), getter_lambda(getter_lambda) {};

				// Setter
				expect_t* operator = (const expect_t i) {
					return this->expect_pointer = (expect_t*)&i;

				};
				
				// Setter
				expect_t* operator = (const expect_t *i) {
					return this->expect_pointer = (expect_t*)i;
				};
				
				// Getter
				expect_t* operator -> () {
					this->getter_lambda(this->expect_pointer);
					return this->expect_pointer;
				};

				// Getter
				operator expect_t* () const {
					this->getter_lambda(this->expect_pointer);
					return this->expect_pointer;
				};
		};


		// Sets the negate flag when used
		// expect<int>(3).to->never->equal->(5);
		member_logic never{this, [&](expect_t* expect_pointer) {
			expect_pointer->flags.negate = !expect_pointer->flags.negate;
		}};



		// Provided as chainable getters to improve the readability of your assertions.
		// They do not provide testing capabilities.
		expect_t* to = this;
		expect_t* be = this;
		expect_t* been = this;
		expect_t* is = this;
		expect_t* that = this;
		expect_t* which = this;
		// `and` is a reserved keyword
		expect_t* then = this;//expect_t* and = this;
		expect_t* has = this;
		expect_t* have = this;
		expect_t* with = this;
		expect_t* at = this;
		expect_t* of = this;
		expect_t* same = this;

		result_t result() {
			return result_;
		};

		operator bool() {
			return result_.did_pass;
		};

		protected:
			T actual;
			test_flags flags;
			result_t result_;

			void add_result_t(bool result, std::string message) {
				bool did_pass = (this->flags.negate ? !result : result);
				result_.did_pass = result_.did_pass && did_pass;
				result_.message = did_pass ? _mocha_util.color_green(message) : _mocha_util.color_red(message);
				// Reset the flag
				this->flags.negate = false;
			};

			template<class U>
			struct is_c_str
				: std::integral_constant<
						bool,
						std::is_same<char const *, typename std::decay<U>::type>::value ||
						std::is_same<char *, typename std::decay<U>::type>::value
			> {};

		//private:
	};

	template <typename T>
	expect_t<T> expect(T&& x) {
		return { std::forward<T>(x) };
	};

void describe(std::string description, std::function<void()> lambda_describe) {
		// We just got to this depth_
		_mocha_util.increment_depth();

		// Log the current subject
		_mocha_util.log(_mocha_util.generate_parent_depth_string() + description + "\n");

		// Run the describe and get the results
		// They should of put some `it` calls inside the callback
		lambda_describe();

		// Now that we are done, reduce the depth_
		_mocha_util.decrement_depth();
	};

	void it(std::string description) {
		_mocha_util.log_result(_mocha_util.result_state::pending);

		std::string message = _mocha_util.generate_child_depth_string() +
			_mocha_util.color_cyan("----: " + description) +
			"\n";

		_mocha_util.log(message);
	};

	void it(std::string description, std::function<mocha::result_t()> lambda_it) {

		mocha::result_t result = lambda_it();
		_mocha_util.log_result(result.did_pass ? _mocha_util.result_state::pass : _mocha_util.result_state::fail);

		std::string message = _mocha_util.generate_child_depth_string() +
			(result.did_pass ? _mocha_util.color_green("pass") : 
			_mocha_util.color_red("fail")) + ": " + description +
			(result.did_pass ? "" : "\n" + _mocha_util.generate_child_depth_string() + mocha_settings.indention + result.message) +
			"\n";

		_mocha_util.log(message);
	};

	void parse_cli_args(int argc, char * const argv[]) {
		// Some CLI options/flags
		for(int i = 0; i < argc; i++) {
			if(std::strcmp(argv[i], "--no-color") == 0) {
				mocha::mocha_settings.use_color = false;
			}
		}
	};
}

#include <vector>

// MOCHA_RUN_TESTS
// --------------------------------------------
// --------------------------------------------

// Just a simple way to get a unique name after passing in a name.
// Concats that name with the line number
//
// via: https://github.com/philsquared/Catch/blob/35f4266d0022ed039923fbbba2c4495435ad1465/single_include/catch.hpp#L58
#define MOCHA_INTERNAL_UNIQUE_NAME_LINE2( name, line ) name ## line
#define MOCHA_INTERNAL_UNIQUE_NAME_LINE( name, line ) MOCHA_INTERNAL_UNIQUE_NAME_LINE2( name, line )
#define MOCHA_INTERNAL_UNIQUE_NAME( name ) MOCHA_INTERNAL_UNIQUE_NAME_LINE( name, __LINE__ )

namespace mocha {
	std::vector<std::function<void()>> run_registry;

	void _run_all_registered_tests_from_macro() {
		// Run all of the calls made in `MOCHA_RUN_TESTS([] { /* ... */ });
		for(std::function<void()> i : mocha::run_registry) {
			i();
		}
	};

	struct runtests_macro_registrar_type {
		template <typename Func>
		runtests_macro_registrar_type(Func&& registrant) {
			// If they want our main, we need to save up the calls and call them in our main
			// below any settings that may have been set
			#if defined(MOCHA_MAIN)
				run_registry.emplace_back(registrant);
			// Otherwise just call it now because that is what they expect (synchronous)
			#else
				registrant();
			#endif
		}
	};
}

// Defines and Constructs an object of `mocha::runtests_macro_registrar_type` type. This means the constructor is exectuted with __VA_ARGS__ passed in.
// `INTERNAL_UNIQUE_NAME(run_registrar)` could be any name but this allows for easy uniqueness with it still being somewhat named
// The double colon tells the compiler to look in the global scope for that type. This is just in case someone defines something of the same name where this is called
//
// via: https://github.com/rmartinho/nonius/blob/01115c1d4062de88ffca798545ac7c70b4ad4623/include/nonius/benchmark.h%2B%2B#L96
#define MOCHA_RUN_TESTS( ... ) \
	namespace { static ::mocha::runtests_macro_registrar_type MOCHA_INTERNAL_UNIQUE_NAME(runtests_macro_registrar)(__VA_ARGS__); }

// end MOCHA_RUN_TESTS
// --------------------------------------------
// --------------------------------------------



// Define some runners if they want to go barebones
#if defined(MOCHA_MAIN)

	#include <iostream>
	#include <string>

	// Standard C/C++ main entry point
	int main (int argc, char * const argv[]) {
		mocha::parse_cli_args(argc, argv);

		// The reset is only necessary if we were reptively runnin then outputting
		//mocha::clear();
		mocha::_run_all_registered_tests_from_macro();
		std::cout << mocha::output() << std::endl;

		return 0;
	}

#endif // defined(MOCHA_MAIN)

#endif // MOCHA_H
