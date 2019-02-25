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
		describe("api", [&]() {
			
			describe("equal", [&] {
				it("should pass: true == true", [&]() {
					return expect(true).to->equal(true)->result();
				});

				it("should fail: true != false", [&]() {
					return expect(true).to->never->equal(false)->result();
				});

				it("should pass: \"true\" == \"true\"", [&]() {
					return expect("true").to->equal("true")->result();
				});

				it("should fail: \"true\" == \"false\"", [&]() {
					return expect("true").to->never->equal("false")->result();
				});

				it("should fail: true != false", [&]() {
					return expect<std::string>("true").to->equal(false)->result();
				});
			});
		});
	});

	print_summary();

	return 0;
}