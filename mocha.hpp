// mocha
// v0.6.5
// https://github.com/MadLittleMods/mocha
//
// Mocha.js inspired testing for C++
//
// Requires C++11. Works on the following platforms:
//		- Most desktop environments
//		- Visual Studio
//		- Arduino
//
// This is a no dependency/full independent version of mocha
// We simply just concat the files together and remove the `#include *.h` to the h file dependencies

// -----------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------------

#include <to_string.hpp>

#if defined(ARDUINO)
#include "Arduino.h"
#endif



// By Luc Danton: http://chat.stackoverflow.com/transcript/message/21940188#21940188
// http://coliru.stacked-crooked.com/a/015660099e486a80
// Works as lambda<R, A, B, C> instead of std::function<R(A, B, C)>
//
// v0.2.0

#ifndef LAMBDA_SIGNATURE_H
#define LAMBDA_SIGNATURE_H

#include <utility>
#include <memory>

template<typename R, typename... Args>
struct holder_base {
	virtual ~holder_base() = default;

	virtual std::unique_ptr<holder_base> clone() const = 0;
	virtual R call(Args... args) = 0;
};

template<typename Functor, typename R, typename... Args>
struct holder: holder_base<R, Args...> {
	explicit holder(Functor functor): functor(std::move(functor)) {}

private:
	Functor functor;

public:
	R call(Args... args) override { return functor(std::forward<Args>(args)...); }
	std::unique_ptr<holder_base<R, Args...>> clone() const override
	{ return std::unique_ptr<holder> { new holder(*this) }; }
};

template<typename Functor, typename... Args>
struct holder<Functor, void, Args...>: holder_base<void, Args...> {
	explicit holder(Functor functor): functor(std::move(functor)) {}

private:
	Functor functor;

public:
	void call(Args... args) override { functor(std::forward<Args>(args)...); }
	std::unique_ptr<holder_base<void, Args...>> clone() const override
	{ return std::unique_ptr<holder> { new holder(*this) }; }
};

template<typename R, typename... Args>
struct lambda {
	template<typename Functor>
	lambda(Functor functor): functor(new holder<Functor, R, Args...>(std::move(functor))) {}

	lambda(lambda const& other): functor(other.functor->clone()) {}
	
	lambda& operator=(lambda const& other) { functor = other.functor->clone(); return *this; }

	lambda(lambda&& other) : functor { std::move(other.functor) }{}
	
	lambda& operator=(lambda&& other) {
		functor = std::move(other.functor);

		return *this;
	}
	//lambda(lambda&&) = default;
	//lambda& operator=(lambda&&) = default;

	R operator()(Args... args) { return functor->call(std::forward<Args>(args)...); }
private:
	std::unique_ptr<holder_base<R, Args...>> functor;
};


#endif



// pstring
// v0.3.1
//
// Requires C++11. Works on the following platforms:
//		- Most desktop environments
//		- Visual Studio
//		- Arduino


#ifndef PSTRING_H
#define PSTRING_H


#if defined(ARDUINO)
#include "Arduino.h"

struct pstring {
	String value;

	pstring() : pstring("") {};

	pstring(char const* val) : pstring(String(val)) {};

	pstring(String val): value(val) {};


	pstring(bool val) : value(val ? "true" : "false") {};

	pstring(int val): value(String(val)) {};
	
	pstring(unsigned int val): value(String(val)) {};

	pstring(double val):pstring(val, 4) {};

	pstring(double val, byte precision):value(pstring::float_to_string(val, precision)){};

	pstring operator + (char const* s) {
		return pstring(this->value + String(s));
	};
	
	pstring operator + (const pstring &s) {
		return pstring(this->value + s.value);
	};

	// For left hand side operator overloading
	friend pstring operator + (char const* s, const pstring &ps) {
		return pstring(String(s) + ps.value);
	};

	pstring& operator +=  (char const* s) {
		this->value = this->value + String(s);
		return *this;
	};
	
	pstring& operator +=  (const pstring &s) {
		this->value = this->value + s.value;
		return *this;
	};

	operator String() { return this->value; }

	private:
		static String float_to_string(float val, byte precision) {
			// returns val with number of decimal places determine by precision
			// precision is a number from 0 to 6 indicating the desired decimial places
			// example: floatToString(3.1415, 2); // returns 3.14 (two decimal places)

			String output_ = "";

			if(val < 0.0){
				output_ += "-";
				val = -val;
			}

			output_ += int(val);  //prints the int part
			if(precision > 0)
			{
				output_ += "."; // print the decimal point

				unsigned long frac;
				unsigned long mult = 1;
				byte padding = precision -1;
				while(precision--)
					mult *=10;

				if(val >= 0)
					frac = (val - int(val)) * mult;
				else
					frac = (int(val)- val ) * mult;
				unsigned long frac1 = frac;

				while( frac1 /= 10 )
					padding--;
				while(  padding--)
					output_ += "0";

				output_ += frac;
			}

			return output_;
		};
};


#else
#include <string>
#include <iostream>
// std::min, std::max
#include <algorithm>

struct pstring {
	std::string value;

	pstring() : pstring("") {};

	pstring(char const* val) : pstring(std::string(val)) {};

	pstring(std::string val) : value(val) {};

	pstring(bool val) : value(val ? "true" : "false") {};

	pstring(int val) : value(std::to_string(val)) {};

	pstring(unsigned int val) : value(std::to_string(val)) {};

	pstring(double val)
		: value(remove_trailing_zero(std::to_string(val))) {};

	pstring operator + (char const* s) {
		return pstring(this->value + std::string(s));
	};

	pstring operator + (const pstring &s) {
		return pstring(this->value + s.value);
	};

	// For left hand side operator overloading
	friend pstring operator + (char const* s, const pstring &ps) {
		return pstring(std::string(s) + ps.value);
	};

	pstring& operator += (char const* s) {
		this->value = this->value + std::string(s);
		return *this;
	};
	pstring& operator += (const pstring &s) {
		this->value = this->value + s.value;
		return *this;
	};

	friend std::ostream& operator << (std::ostream& stream, const pstring &s) {
		return stream << s.value;
	};

	operator std::string() { return this->value; }

	private:
		static std::string remove_trailing_zero(std::string str) {
			return str.erase((std::min)((int)str.find_last_not_of('0') + 2, (int)str.length()), std::string::npos);
		};
};

#endif


#endif




// mocha
// v0.6.5
// https://github.com/MadLittleMods/mocha
//
// Mocha.js inspired testing for C++
//
// Requires C++11. Works on the following platforms:
//		- Most desktop environments
//		- Visual Studio
//		- Arduino


#ifndef MOCHA_H
#define MOCHA_H

#if defined(ARDUINO)
#include "Arduino.h"
#endif

// fabs
#include <cmath>

//#include "lambdaSig.h"
//#include "pstring.h"

namespace mocha {

	struct test_result {
		pstring message;
		bool did_pass = true;
	};

	struct test_flags {
		bool negate = false;
	};


	template <typename T, typename U = T>
	struct mocha_plugin {
		lambda<bool, T, U> lambda_test;
		lambda<pstring, T, U, test_flags> lambda_fail;

		mocha_plugin(
			lambda<bool, T, U> lambda_test,
			lambda<pstring, T, U, test_flags> lambda_fail
		) : lambda_test(lambda_test), lambda_fail(lambda_fail) { };
	};


	struct _mocha_settings {
		bool use_color = true;
		pstring indention = "\t";
	};

	_mocha_settings mocha_settings;

	struct __mocha_util_class {

		void increment_depth() {
			this->depth_ += 1;
		};

		void decrement_depth() {
			this->depth_ -= 1;
		};


		pstring generate_current_depth_string() {
			pstring depth_string = "";
			for(unsigned int i = 0; i < depth_-1; i++) {
				depth_string += mocha_settings.indention;
			}

			return depth_string;
		};

		pstring generate_current_child_depth_string() {
			pstring child_depth_string = "";
			for(unsigned int i = 0; i < depth_; i++) {
				child_depth_string += mocha_settings.indention;
			}

			return child_depth_string;
		};

		pstring color_cyan(pstring input) {
			return mocha_settings.use_color ? pstring("\033[36;1m" + input.value + "\033[0m") : input;
		};

		pstring color_green(pstring input) {
			return mocha_settings.use_color ? pstring("\033[32;1m" + input.value + "\033[0m") : input;
		};
		pstring color_red(pstring input) {
			return mocha_settings.use_color ? pstring("\033[31;1m" + input.value + "\033[0m") : input;
		};


		// Just a helper to add to the resultant output_
		void log(pstring message) {
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

		pstring output() {
			pstring result = pstring(this->output_);
			// Add a small summary at the end
			result += pstring("\n\n") +
				this->color_green(pstring(this->num_passed_) + " passing") + "\n" +
				this->color_red(pstring(this->num_failed_) + " failing") + "\n" +
				this->color_cyan(pstring(this->num_pending_) + " pending");


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
			pstring output_ = "";

			unsigned int depth_ = 0;

			unsigned int num_passed_ = 0;
			unsigned int num_failed_ = 0;
			unsigned int num_pending_ = 0;


	};

	__mocha_util_class _mocha_util;

	pstring output() {
		return _mocha_util.output();
	};

	void clear() {
		_mocha_util.clear();
	};



	void describe(
		pstring description,
		lambda<void> lambda_describe
	) {
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

	void it(pstring description) {
		_mocha_util.log_result(_mocha_util.result_type::pending);

		pstring message = _mocha_util.generate_current_child_depth_string() +
			_mocha_util.color_cyan(pstring("----: ") + description) +
			"\n";

		_mocha_util.log(message);
	};

	void it(pstring description, lambda<mocha::test_result> lambda_it) {
		mocha::test_result test_result = lambda_it();

		_mocha_util.log_result(test_result.did_pass ? _mocha_util.result_type::pass : _mocha_util.result_type::fail);

		pstring message = _mocha_util.generate_current_child_depth_string() +
			(test_result.did_pass ? _mocha_util.color_green("Pass") : _mocha_util.color_red("Fail")) + ": " +
			description +
			(test_result.did_pass ? "" : "\n" + _mocha_util.generate_current_child_depth_string() + mocha_settings.indention + test_result.message) +
			"\n";

		_mocha_util.log(message);
	};


	// expect: BDD
	template <typename T>
	struct expect_type {

		expect_type(T actual) : actual(actual) { };



		template <typename U>
		expect_type* equal(U expected) {
			this->add_test_result(
				this->actual == expected,
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "equal " + pstring(expected)
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
				pstring("Expected ") + pstring(utils::to_string(this->actual)) + " to " + (this->flags.negate ? "not " : "") + "equal " + pstring(expected) + " within tolerance of " + pstring(tolerance)
			);

			return this;
		};

		expect_type* within(double lower, double upper) {
			this->add_test_result(
				this->actual > lower && this->actual < upper,
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be above " + pstring(lower) + " and below " + pstring(upper)
			);

			return this;
		};


		expect_type* above(double expected) {
			this->add_test_result(
				this->actual > expected,
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than " + pstring(expected)
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
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be greater than or equal to " + pstring(expected)
			);

			return this;
		};
		expect_type* gte(double expected) {
			return this->least(expected);
		};

		expect_type* below(double expected) {
			this->add_test_result(
				this->actual < expected,
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be lesser than " + pstring(expected)
			);

			return this;
		};
		expect_type* lt(double expected) {
			return this->below(expected);
		};
		expect_type* lessThan(double expected) {
			return this->below(expected);
		};

		expect_type* most(double expected) {
			this->add_test_result(
				this->actual <= expected,
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "be less than or equal to " + pstring(expected)
			);

			return this;
		};
		expect_type* lte(double expected) {
			return this->most(expected);
		};

		expect_type* satisfy(lambda<bool, T> lambda_test) {
			bool result = lambda_test(this->actual);

			return this->satisfy(
				result,
				pstring("Expected ") + pstring(this->actual) + " to " + (this->flags.negate ? "not " : "") + "satisfy the given test"
			);
		};
		expect_type* satisfy(lambda<bool, T> lambda_test, lambda<pstring, T, test_flags> lambda_fail) {
			bool result = lambda_test(this->actual);
			pstring message = lambda_fail(this->actual, this->flags);

			return this->satisfy(result, message);
		};
		template <typename U>
		expect_type* satisfy(mocha_plugin<T, U> plugin, U expected) {
			bool result = plugin.lambda_test(this->actual, expected);
			pstring message = plugin.lambda_fail(this->actual, expected, this->flags);

			return this->satisfy(result, message);
		};

		expect_type* satisfy(bool result, pstring message) {
			this->add_test_result(
				result,
				message
			);

			return this;
		};




		class member_logic {
			expect_type* expect_pointer;
			lambda<void, expect_type*> getter_lambda;
			public:
				member_logic(expect_type *i, lambda<void, expect_type*> getter_lambda) : expect_pointer(i), getter_lambda(getter_lambda) {};

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

			void add_test_result(bool result, pstring message) {
				bool did_pass = (this->flags.negate ? !result : result);

				this->test_result.did_pass = this->test_result.did_pass && did_pass;

				if(!did_pass) {
					// Concat a newline if this is a consecutive test
					if(this->test_result.message.value.length() > 0) {
						this->test_result.message += "\n";
					}
					this->test_result.message += message;
				}



				// Reset the flag
				this->flags.negate = false;
			};


		//private:
	};

	template <typename T>
	expect_type<T> expect(T&& x) {
		return { std::forward<T>(x) };
	};



	void parse_cli_args(int argc, char * const argv[]) {
		// Some CLI options/flags
		for(int i = 0; i < argc; i++) {
			//std::cout << argv[i] << std::endl;
			if(strcmp(argv[i], "--no-color") == 0) {
				mocha::mocha_settings.use_color = false;
			}
		}
	};



}



#include <vector>
#if defined(ARDUINO)
	// We just add a define in case anyone wants to detect it later to avoid multiple declaration errors
	#ifndef std_vector_arduino_throw_polyfill
	#define std_vector_arduino_throw_polyfill
		// via https://forum.pjrc.com/threads/23467-Using-std-vector?p=69787&viewfull=1#post69787
		namespace std {
			inline void __throw_bad_alloc() {
				Serial.println("Unable to allocate memory");
			}

			inline void __throw_length_error( char const*e ) {
				Serial.print("Length Error :");
				Serial.println(e);
			}
		}
	#endif
#endif


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
	std::vector<lambda<void>> run_registry;

	void _run_all_registered_tests_from_macro() {
		// Run all of the calls made in `MOCHA_RUN_TESTS([] { /* ... */ });
		for(lambda<void> i : mocha::run_registry) {
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

	#if defined(ARDUINO)

		// Keeps track since we last sent a serial in our debug serial
		elapsedMicros sinceSerial;

		void setup() {
			Serial.begin(9600);
		}

		void loop() {
			// Print it out every 1 second
			if (sinceSerial >= 1 * 1000000) {
				mocha::clear();
				mocha::_run_all_registered_tests_from_macro();
				Serial.print(mocha::output().value);

				sinceSerial = 0;
			}
		}
	#else // defined(ARDUINO)
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
	#endif // defined(ARDUINO)

#endif // defined(MOCHA_MAIN)



#endif // MOCHA_H
