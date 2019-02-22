// mocha
// v0.6.5
// https://github.com/MadLittleMods/mocha
//
// Mocha.js inspired testing for C++
//
// Requires C++11. Works on the following platforms:
//		- Most desktop environments
//		- Visual Studio
//
// This is a no dependency/full independent version of mocha
// We simply just concat the files together and remove the `#include *.h` to the h file dependencies

// -----------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------

#include <to_string.hpp>
#include <string>

// mocha
// v0.6.5
// https://github.com/MadLittleMods/mocha
//
// Mocha.js inspired testing for C++
//
// Requires C++11. Works on the following platforms:
//		- Most desktop environments
//		- Visual Studio


#ifndef MOCHA_H
#define MOCHA_H

// fabs
#include <cmath>

namespace mocha {

	namespace helpers {
		// Compare with int64_t
		bool strict_equal (int64_t a, int64_t b) { return a == b; }
		bool strict_equal(int64_t a, const char* b) { return false; };
		bool strict_equal(int64_t a, double b) { return false; };
		bool strict_equal(int64_t a, float b) { return false; };
		bool strict_equal(int64_t a, char b) { return false; };
		bool strict_equal(int64_t a, std::string b) { return false; };

	  // Compare with doubles
		bool strict_equal(double a, double b) { return a == b; };
		bool strict_equal(double a, const char* b) { return false; };
		bool strict_equal(double a, float b) { return false; };
		bool strict_equal(double a, char b) { return false; };
		bool strict_equal(double a, std::string b) { return false; };

		// Compare with floats
		bool strict_equal(float a, float b) { return a == b; };
		bool strict_equal(float a, const char* b) { return false; };
		bool strict_equal(float a, double b) { return false; };
		bool strict_equal(float a, char b) { return false; };
		bool strict_equal(float a, std::string b) { return false; };

		// Compare with char
		bool strict_equal(char a, char b) { return a == b; };
		bool strict_equal(char a, const char* b) { return false; };
		bool strict_equal(char a, double b) { return false; };
		bool strict_equal(char a, float b) { return false; };
		bool strict_equal(char a, std::string b) { return false; };

		bool strict_equal(std::string a, std::string b) { return a.compare(b) == 0; };
		bool strict_equal(std::string a, const char* b) { std::string s(b); return a == b; };
		bool strict_equal(std::string a, double b) { return false; };
		bool strict_equal(std::string a, float b) { return false; };
		bool strict_equal(std::string a, char b) { return false; };

		// Compare with bools
		bool strict_equal(bool a, bool b) { return a == b; }		
		bool strict_equal(bool a, const char* b) { return false; };
		bool strict_equal(bool a, double b) { return false; }
		bool strict_equal(bool a, float b) { return false; }
		bool strict_equal(bool a, char b) { return false; }
		bool strict_equal(bool a, std::string b) { return false; }

		// Compare with const char*
		bool strict_equal(const char* a, const char* b) {
			std::string c(a);
			std::string d(b);
			return c.compare(b) == 0;
		}
		bool strict_equal(const char* a, bool b) { return false; };
		bool strict_equal(const char* a, int64_t b) { return false; };
		bool strict_equal(const char* a, double b) { return false; };
		bool strict_equal(const char* a, float b) { return false; };
		bool strict_equal(const char* a, char b) { return false; };

	}

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


		std::string generate_current_depth_string() {
			std::string depth_string = "";
			for(unsigned int i = 0; i < depth_-1; i++) {
				depth_string += mocha_settings.indention;
			}

			return depth_string;
		};

		std::string generate_current_child_depth_string() {
			std::string child_depth_string = "";
			for(unsigned int i = 0; i < depth_; i++) {
				child_depth_string += mocha_settings.indention;
			}

			return child_depth_string;
		};

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
		enum result_type {
			pass, fail, pending
		};

		void log_result(result_type type) {
			if(type == result_type::pass) {
				this->num_passed_++;
			}
			else if(type == result_type::fail) {
				this->num_failed_++;
			}
			else if(type == result_type::pending) {
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

struct test_result {
		std::string message;
		bool did_pass = true;
	
		inline test_result operator+(const test_result& right) {
			auto result = test_result();
			result.did_pass = this->did_pass && right.did_pass;
			result.message = this->message + "\n" +
			_mocha_util.generate_current_depth_string() + 
			_mocha_util.generate_current_child_depth_string() + right.message;
			return result;
		}

		inline test_result operator &&(const test_result& right) {
			auto result = test_result();
			result.did_pass = this->did_pass && right.did_pass;
			result.message = this->message + "\n" +
			_mocha_util.generate_current_depth_string() + 
			_mocha_util.generate_current_child_depth_string() + right.message;
			return result;
		}

		inline test_result operator ||(const test_result& right) {
			auto result = test_result();
			result.did_pass = this->did_pass || right.did_pass;
			result.message = this->message + "\n" +
			_mocha_util.generate_current_depth_string() + 
			_mocha_util.generate_current_child_depth_string() + right.message;
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
	struct expect_type {

		expect_type(T actual) : actual(actual) { };

		template <typename U>
		expect_type* equal(U expected) {
			bool result = helpers::strict_equal(this->actual, expected);

			// std::cout << utils::to_string(is_c_str<decltype(this->actual)>::value) << ", "
			// 		<< utils::to_string(is_c_str<decltype(expected)>::value) << std::endl;
			
			// bool is_actual_c_str = is_c_str<decltype(this->actual)>::value;
			// bool is_expected_c_str = is_c_str<decltype(this->actual)>::value;

			// if (is_actual_c_str && is_expected_c_str) {
			// 	result = strict_equal(this->actual, expected);			
			// } else if (!is_actual_c_str && !is_expected_c_str) {
			// 	result == this->actual == expected;
			// }

			this->add_test_result(
				result,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + utils::to_string(expected)
			);

			return this;
		};
		template <typename U>
		expect_type* eql(U expected) {
			return this->equal(expected);
		};

		expect_type* close_to(double expected) {
			return this->close_to(expected, 0.0001);
		};
		expect_type* close_to(double expected, double tolerance) {
			this->add_test_result(
				fabs(this->actual - expected) <= tolerance,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + (utils::to_string(expected) + " within tolerance of " + utils::to_string(tolerance))
			);

			return this;
		};

		expect_type* within(double lower, double upper) {
			this->add_test_result(
				this->actual > lower && this->actual < upper,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be above " + utils::to_string(lower) + " and below " + utils::to_string(upper)
			);

			return this;
		};


		expect_type* above(double expected) {
			this->add_test_result(
				this->actual > expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than " + utils::to_string(expected)
			);

			return this;
		};
		expect_type* gt(double expected) {
			return this->above(expected);
		};
		expect_type* greater_than(double expected) {
			return this->above(expected);
		};

		expect_type* least(double expected) {
			this->add_test_result(
				this->actual >= expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than or equal to " + utils::to_string(expected)
			);

			return this;
		};
		expect_type* gte(double expected) {
			return this->least(expected);
		};

		expect_type* below(double expected) {
			this->add_test_result(
				this->actual < expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be lesser than " + utils::to_string(expected)
			);

			return this;
		};
		expect_type* lt(double expected) {
			return this->below(expected);
		};
		expect_type* less_than(double expected) {
			return this->below(expected);
		};

		expect_type* most(double expected) {
			this->add_test_result(
				this->actual <= expected,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be less than or equal to " + utils::to_string(expected)
			);

			return this;
		};
		expect_type* lte(double expected) {
			return this->most(expected);
		};

		expect_type* satisfy(std::function<bool (T)> lambda_test) {
			bool result = lambda_test(this->actual);

			return this->satisfy(
				result,
				"Expected " + utils::to_string(this->actual) + " to " + (this->flags.negate ? "not " : "") + "satisfy the given test"
			);
		};
		expect_type* satisfy(std::function<bool (T)> lambda_test, std::function<std::string (T, test_flags)> lambda_fail) {
			bool result = lambda_test(this->actual);
			std::string message = lambda_fail(this->actual, this->flags);

			return this->satisfy(result, message);
		};
		template <typename U>
		expect_type* satisfy(mocha_plugin<T, U> plugin, U expected) {
			bool result = plugin.lambda_test(this->actual, expected);
			std::string message = plugin.lambda_fail(this->actual, expected, this->flags);

			return this->satisfy(result, message);
		};

		expect_type* satisfy(bool result, std::string message) {
			this->add_test_result(
				result,
				message
			);

			return this;
		};

		class member_logic {
			expect_type* expect_pointer;
			std::function<void (expect_type*)> getter_lambda;
			public:
				member_logic(expect_type *i, std::function<void (expect_type*)> getter_lambda) : expect_pointer(i), getter_lambda(getter_lambda) {};

				// Setter
				expect_type* operator = (const expect_type i) {
					return this->expect_pointer = (expect_type*)&i;

				};
				// Setter
				expect_type* operator = (const expect_type *i) {
					return this->expect_pointer = (expect_type*)i;
				};
				// Getter
				expect_type* operator -> () {
					this->getter_lambda(this->expect_pointer);
					return this->expect_pointer;
				};
				// Getter
				operator expect_type* () const {
					this->getter_lambda(this->expect_pointer);
					return this->expect_pointer;
				};
		};


		// Sets the negate flag when used
		// expect<int>(3).to->never->equal->(5);
		member_logic never{this, [&](expect_type* expect_pointer) {
			expect_pointer->flags.negate = !expect_pointer->flags.negate;
		}};



		// Provided as chainable getters to improve the readability of your assertions.
		// They do not provide testing capabilities.
		expect_type* to = this;
		expect_type* be = this;
		expect_type* been = this;
		expect_type* is = this;
		expect_type* that = this;
		expect_type* which = this;
		// `and` is a reserved keyword
		expect_type* then = this;//expect_type* and = this;
		expect_type* has = this;
		expect_type* have = this;
		expect_type* with = this;
		expect_type* at = this;
		expect_type* of = this;
		expect_type* same = this;



		test_result result() {
			return this->test_result;
		};

		operator bool() {
			return this->test_result.did_pass;
		};


		protected:
			T actual;
			test_flags flags;

			test_result test_result;

			void add_test_result(bool result, std::string message) {
				bool did_pass = (this->flags.negate ? !result : result);

				this->test_result.did_pass = this->test_result.did_pass && did_pass;

				if(!did_pass) {
					// Concat a newline if this is a consecutive test
					if(this->test_result.message.length() > 0) {
						this->test_result.message += "\n";
					}
					this->test_result.message += message;
				}



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
	expect_type<T> expect(T&& x) {
		return { std::forward<T>(x) };
	};

void describe(std::string description, std::function<void()> lambda_describe) {
		// We just got to this depth_
		_mocha_util.increment_depth();

		// Log the current subject
		_mocha_util.log(_mocha_util.generate_current_depth_string() + description + "\n");

		// Run the describe and get the results
		// They should of put some `it` calls inside the callback
		lambda_describe();

		// Now that we are done, reduce the depth_
		_mocha_util.decrement_depth();
	};

	void it(std::string description) {
		_mocha_util.log_result(_mocha_util.result_type::pending);

		std::string message = _mocha_util.generate_current_child_depth_string() +
			_mocha_util.color_cyan("----: " + description) +
			"\n";

		_mocha_util.log(message);
	};

	void it(std::string description, std::function<mocha::test_result()> lambda_it) {
		mocha::test_result test_result = lambda_it();

		_mocha_util.log_result(test_result.did_pass ? _mocha_util.result_type::pass : _mocha_util.result_type::fail);

		std::string message = _mocha_util.generate_current_child_depth_string() +
			(test_result.did_pass ? _mocha_util.color_green("pass") : _mocha_util.color_red("fail")) + ": " +
			description +
			(test_result.did_pass ? "" : "\n" + _mocha_util.generate_current_child_depth_string() + mocha_settings.indention + test_result.message) +
			"\n";

		_mocha_util.log(message);
	};


	using expect_type_lambda = mocha::expect_type<bool>*;
	void it(std::string description, std::function<expect_type_lambda()> lambda_it) {
		mocha::test_result test_result = lambda_it()->result();
		it(description, [&] { return test_result; });
	}

	void parse_cli_args(int argc, char * const argv[]) {
		// Some CLI options/flags
		for(int i = 0; i < argc; i++) {
			//std::cout << argv[i] << std::endl;
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
