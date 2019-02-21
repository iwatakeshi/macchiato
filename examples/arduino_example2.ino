#include "mocha.hpp"
using namespace mocha;


// Keeps track since we last sent a serial in our debug serial
elapsedMicros sinceSerial;


void setup() {
	Serial.begin(9600);

}

void loop() {
	

	if (sinceSerial >= 1 * 1000000) {

		// Necessary because we run multiple times over and over
		// We don't want to see the sum of all, just the results of this run, so we need to reset
		mocha::clear();

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

		Serial.print(mocha::output().value);

		sinceSerial = 0;
	}
}