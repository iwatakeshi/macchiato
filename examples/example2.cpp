#include <iostream>
#include "mocha.hpp"
// Optionally use the namespace to do `describe` instead of `Macchiato::describe`, etc
using namespace mocha;

int main() {
	describe("Foo", [&]() {
		describe("with bar", [&]() {
			it("should baz", [&]() {
				return expect(true).to->equal(true)->result();
			});

			// This test will fail because it is false != true
			it("should qux", [&]() {
				return expect(false).to->equal(true)->result();
			});

			// An `it` call without a callback is considered "pending"
			// In other words, the test still needs to written/implemented.
			it("should norf");
		});
	});

	std::cout << mocha::output() << std::endl;

	return 0;
}