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
				describe("comparison of type T and T", [&] {
					// it("should pass: 1 == 1", [&]() {
					// 	return expect(1).to->equal(1)->result();
					// });

					// it("should fail: 1 != 2", [&]() {
					// 	return expect(1).to->never->equal(2)->result();
					// });

					// it("should pass: 1.5 == 1.5", [&]() {
					// 	return expect(1.5).to->equal(1.5)->result();
					// });

					// it("should fail: 1.5 != 2.5", [&]() {
					// 	return expect(1.5).to->never->equal(2.5)->result();
					// });

					// it("should pass: true == true", [&]() {
					// 	return expect(true).to->equal(true)->result();
					// });

					// it("should fail: true != false", [&]() {
					// 	return expect(true).to->never->equal(false)->result();
					// });

					// it("should pass: 'a' == 'a'", [&]() {
					// 	return expect('a').to->equal('a')->result();
					// });

					// it("should fail: 'a' != 'b'", [&]() {
					// 	return expect('a').to->never->equal('b')->result();
					// });

					it("should pass: \"true\" == \"true\"", [&]() {
						return expect("true").to->equal("true")->result();
					});

					// it("should fail: \"true\" != \"false\"", [&]() {
					// 	return expect("true").to->never->equal("false")->result();
					// });

					// it("should pass: \"true\" (string) == \"true\" (string)", [&]() {
					// 	std::string a = "true";
					// 	std::string b = "true";
					// 	return expect(a).to->equal(b)->result();
					// });

					// it("should fail: \"true\" (string) != \"false\" (string)", [&]() {
					// 	std::string a = "true";
					// 	std::string b = "false";
					// 	return expect(a).to->never->equal(b)->result();
					// });
				}); // end - equal: comparison of type T and T

				describe("comparison of type T and U", [&] {
					
					// it("should pass: true == 1", [&] () {
					// 	return expect(true).to->equal(1)->result();
					// });

					// it("should pass: 1 == 1.0", [&]() {
					// 	return expect(1).to->equal(1.0)->result();
					// });

					// it("should pass: 1 == \"1\"", [&]() {
					// 	return expect(1).to->equal("1")->result();
					// });

					// it("should pass: 1 == \"1\" (string)", [&]() {
					// 	std::string b = "1";
					// 	return expect(1).to->equal(b)->result();
					// });

					// it("should pass: 1.7 == 2", [&]() {
					// 	return expect(1.7).to->equal(2)->result();
					// });

					// it("should pass: 1.7 == \"1.7\"", [&]() {
					// 	return expect(1.7).to->equal("1.7")->result();
					// });

					// it("should pass: 1.7 == \"1.7\" (string)", [&]() {
					// 	std::string b = "1.7";
					// 	return expect(1.7).to->equal(b)->result();
					// });

					// it("should pass: 1.7 != 'a'", [&]() {
					// 	return expect(1.7).to->never->equal('a')->result();
					// });

					// it("should pass: 'a' == \"a\" (string)", [&]() {
					// 	return expect('a').to->equal("a")->result();
					// });

					// it("should pass: \"true\" == \"true\"", [&]() {
					// 	return expect("true").to->equal("true")->result();
					// });

					// it("should pass: \"true\" != \"false\"", [&]() {
					// 	return expect("true").to->equal("false")->result();
					// });

					// it("should pass: \"true\" (string) == \"true\" (string)", [&]() {
					// 	std::string a = "true";
					// 	std::string b = "true";
					// 	return expect(a).to->equal(b)->result();
					// });

					// it("should pass: \"true\" (string) != \"false\" (string)", [&]() {
					// 	std::string a = "true";
					// 	std::string b = "false";
					// 	return expect(a).to->equal(b)->result();
					// });
				}); // end - equal comparison of type T and U
			});
		});
	});

	print_summary();

	return 0;
}