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
#include <cmath>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>
#include <to_string.hpp>
#include <type_traits>
#include "include/mocha_comparator.hpp"
#include "include/mocha_plugin.hpp"
#include "include/mocha_result.hpp"
#include "include/mocha_test_flags.hpp"
#include "include/mocha_settings.hpp"
#include "include/mocha_util.hpp"

namespace mocha {

	std::string summary() {
		return _mocha_util.summary();
	};

	void print_summary() {
		std::cout << summary() << std::endl;
	}

	void clear() {
		_mocha_util.clear();
	};

	template <typename T, typename U>
	using comparator_lambda = std::function<bool(T, U)>;

	// expect: BDD
	template <typename T>
	struct expect_t {

		expect_t(T actual) : actual(actual) { };
		
		/**
		 * Compares the actual and expected of the same type.
		 */
		expect_t* equal(T expected) {
			bool result = mocha_comparator<T, T>().equal(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
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
			bool result = mocha_comparator<T, U>().equal(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
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
		expect_t* equal(U expected, const mocha_comparator<T, U>& comparator) {
			bool result = comparator.equal(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
			);
			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* eql(U expected, const mocha_comparator<T, U>& comparator) {
			return this->equal(expected, comparator);
		};

		/**
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* equal(U expected, comparator_lambda<T, U> comparator) {
			bool result = comparator(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
			);
			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* eql(U expected, comparator_lambda<T, U> comparator) {
			return this->equal(expected, comparator);
		};

		/**
		 * Compares the actual and expected of the same type.
		 */
		expect_t* strict_equal(T expected) {
			bool result = mocha_comparator<T, T>().strict_equal(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to strictly " + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
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
			bool result = mocha_comparator<T, U>().strict_equal(this->actual, expected);
			// bool is_same_type = std::is_same<decltype(this->actual), decltype(expected)>::value;
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to strictly " + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
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
		expect_t* strict_equal(U expected, const mocha_comparator<T, U>& comparator) {
			bool result = comparator.strict_equal(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to strictly" + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
			);

			return this;
		};

		/**
		 * [alias]
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* seql(U expected, const mocha_comparator<T, U>& comparator) {
			return this->strict_equal(expected, comparator);
		};

		/**
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* strict_equal(U expected, comparator_lambda<T, U> comparator) {
			bool result = comparator(this->actual, expected);
			this->add_result_t(
				result,
				"Expected " + to_string(this->actual) + " to strictly" + (this->flags.negate ? "not " : "") + "equal " + to_string(expected)
			);

			return this;
		};		

		/**
		 * [alias]
		 * Compares the actual and expected of different types using a custom comparator function.
		 */
		template <typename U>
		expect_t* seql(U expected, comparator_lambda<T, U> comparator) {
			return this->strict_equal(expected, comparator);
		};

		expect_t* close_to(double expected) {
			return this->close_to(expected, 0.0001);
		};

		expect_t* close_to(double expected, double tolerance) {
			this->add_result_t(
				fabs(this->actual - expected) <= tolerance,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + (to_string(expected) + " within tolerance of " + to_string(tolerance))
			);

			return this;
		};

		expect_t* within(double lower, double upper) {
			this->add_result_t(
				this->actual > lower && this->actual < upper,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be above " + to_string(lower) + " and below " + to_string(upper)
			);

			return this;
		};


		expect_t* above(double expected) {
			this->add_result_t(
				this->actual > expected,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than " + to_string(expected)
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
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than or equal to " + to_string(expected)
			);

			return this;
		};
		expect_t* gte(double expected) {
			return this->least(expected);
		};

		expect_t* below(double expected) {
			this->add_result_t(
				this->actual < expected,
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be lesser than " + to_string(expected)
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
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be less than or equal to " + to_string(expected)
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
				"Expected " + to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "satisfy the given test"
			);
		};

		expect_t* satisfy(std::function<bool (T)> lambda_test, std::function<std::string (T, test_flags)> lambda_fail) {
			bool result = lambda_test(this->actual);
			std::string message = lambda_fail(this->actual, this->flags);

			return this->satisfy(result, message);
		};

		template <typename U>
		expect_t* satisfy(U expected, mocha_plugin<T, U> plugin) {
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
			struct is_string
				: std::integral_constant<
						bool,
						std::is_same<char const *, typename std::decay<U>::type>::value ||
						std::is_same<char *, typename std::decay<U>::type>::value ||
						std::is_same<std::string, typename std::decay<U>::type>::value
			> {};

			template<typename U>
			std::string to_string(U value) {
				return is_string<decltype(value)>::value ? "\"" + utils::to_string(value) + "\"" : utils::to_string(value);
			}
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

	void it(std::string description, std::function<result_t()> lambda_it) {

		result_t result = lambda_it();
		_mocha_util.log_result(result.did_pass ? _mocha_util.result_state::pass : _mocha_util.result_state::fail);

		std::string message = _mocha_util.generate_child_depth_string() + (result.did_pass ? _mocha_util.color_green("pass") :  _mocha_util.color_red("fail")) + ": " + description +
			(result.did_pass ? "" : "\n" + _mocha_util.generate_child_depth_string() + mocha_settings.indention + result.message) + "\n";

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
		std::cout << mocha::summary() << std::endl;

		return 0;
	}

#endif // defined(MOCHA_MAIN)
#endif