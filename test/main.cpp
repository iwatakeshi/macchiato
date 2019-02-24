#include <iostream>
#include <string>
#include "../mocha.hpp"
// Optionally use the namespace to do `describe` instead of `mocha::describe`, etc
using namespace mocha;

struct dummy_struct {
	dummy_struct() {};
	dummy_struct(int n): num(n) {};

	bool operator == (const dummy_struct& right) {
		return this->num == right.num;
	}
	private:
	int num = 0;
};

std::string to_string(dummy_struct const&) { return "dummy_struct"; }

int main() {
	describe("mocha", [&]() {
		describe("with whipcream", [&]() {
			it("should pass", [&]() {
				return expect(true).to->equal(true)->result();
			});

			it("should fail", [&]() {
				// Tell the compiler that we want this to be interpreted as a string
				// and not as a const char*
				return expect<std::string>("true").to->strict_equal(true)->result();
			});

			// An `it` call without a callback is considered "pending"
			// In other words, the test still needs to written/implemented.
			it("should pend");
			
			it("should magic", [&] () {
				return expect(dummy_struct()).to->never->equal(dummy_struct(10))->result();
			});

			it("should fly", [&] () {
				return expect(dummy_struct()).to->never->equal(100, 
				mocha_comparator<dummy_struct, int> ([&] (dummy_struct a, int b) -> bool {
					return false;
				}))->result();
			});

			it("should fly again", [&] () {
				return expect<dummy_struct>(dummy_struct()).to->never->equal<int>(100, 
				([&] (auto a, auto b) -> bool {
					return false;
				}))->result();
			});
		});
	});

	print_summary();

	return 0;
}