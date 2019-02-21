// This tells mocha to provide a main function. Only do this in one source/cpp file
#define MOCHA_MAIN
#include "mocha.hpp"
using namespace mocha;

MOCHA_RUN_TESTS([] {
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
});