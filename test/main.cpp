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

  int get_num() const {
    return num;
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
          it("should: 1 == 1", [&]() {
            return expect(1).to->equal(1)->result();
          });

          it("should: 1 != 2", [&]() {
            return expect(1).to->never->equal(2)->result();
          });

          it("should: 1.5 == 1.5", [&]() {
            return expect(1.5).to->equal(1.5)->result();
          });

          it("should: 1.5 != 2.5", [&]() {
            return expect(1.5).to->never->equal(2.5)->result();
          });

          it("should: true == true", [&]() {
            return expect(true).to->equal(true)->result();
          });

          it("should: true != false", [&]() {
            return expect(true).to->never->equal(false)->result();
          });

          it("should: 'a' == 'a'", [&]() {
            return expect('a').to->equal('a')->result();
          });

          it("should: 'a' != 'b'", [&]() {
            return expect('a').to->never->equal('b')->result();
          });

          it("should: \"true\" == \"true\"", [&]() {
            return expect("true").to->eql("true")->result();
          });

          it("should: \"true\" != \"false\"", [&]() {
            return expect("true").to->never->equal("false")->result();
          });

          it("should: \"true\" == \"true\"", [&]() {
            std::string a = "true";
            std::string b = "true";
            return expect(a).to->equal(b)->result();
          });

          it("should: \"true\" != \"false\"", [&]() {
            std::string a = "true";
            std::string b = "false";
            return expect(a).to->never->equal(b)->result();
          });

          it("should: dummy_struct() == dummy_struct()", [&]() {
            return expect(dummy_struct()).to->equal(dummy_struct())->result();
          });
        }); // end - equal: comparison of type T and T

        describe("comparison of type T and U", [&] {
          
          it("should: true != 1", [&] () {
            return expect(true).to->never->strict_equal(1)->result();
          });

          it("should: 1 != 1.0", [&]() {
            return expect(1).to->never->strict_equal(1.0)->result();
          });

          it("should: 1 != \"1\"", [&]() {
            std::string b = "1";
            return expect(1).to->never->strict_equal(b)->result();
          });

          it("should: 1.7 != 2", [&]() {
            return expect(1.7).to->never->strict_equal(2)->result();
          });

          it("should: 1.7 != \"1.7\"", [&]() {
            return expect(1.7).to->never->strict_equal("1.7")->result();
          });

          it("should: 1.7 != 'a'", [&]() {
            return expect(1.7).to->never->strict_equal('a')->result();
          });

          it("should: 'a' != \"a\"", [&]() {
            return expect('a').to->never->strict_equal("a")->result();
          });
        }); // end - equal comparison of type T and U
      });

      describe("equal (using mocha_comparator)", [&] () {
          it("should: dummy_struct(1).get_num() == 1", [&]() {
            return expect(dummy_struct(1)).to->equal(1, 
            mocha_comparator<dummy_struct, int>(
              [&] (dummy_struct a, auto b) -> bool {
              return a.get_num() == b;
            }))->result();
          });
        });

        describe("equal (using comparator)", [&] () {
          it("should: dummy_struct(1).get_num() == 1", [&]() {
            return expect(dummy_struct(1)).to->equal(
              1, 
              [&] (dummy_struct a, auto b) -> bool {
                return a.get_num() == b;
              })->result();
          });
        });

      describe("strict_equal", [&] {
        describe("comparison of type T and T", [&] {
          it("should: 1 == 1", [&]() {
            return expect(1).to->strict_equal(1)->result();
          });

          it("should: 1 != 2", [&]() {
            return expect(1).to->never->strict_equal(2)->result();
          });

          it("should: 1.5 == 1.5", [&]() {
            return expect(1.5).to->strict_equal(1.5)->result();
          });

          it("should: 1.5 != 2.5", [&]() {
            return expect(1.5).to->never->strict_equal(2.5)->result();
          });

          it("should: true == true", [&]() {
            return expect(true).to->strict_equal(true)->result();
          });

          it("should: true != false", [&]() {
            return expect(true).to->never->strict_equal(false)->result();
          });

          it("should: 'a' == 'a'", [&]() {
            return expect('a').to->strict_equal('a')->result();
          });

          it("should: 'a' != 'b'", [&]() {
            return expect('a').to->never->strict_equal('b')->result();
          });

          it("should: \"true\" == \"true\"", [&]() {
            return expect("true").to->strict_equal("true")->result();
          });

          it("should: \"true\" != \"false\"", [&]() {
            return expect("true").to->never->strict_equal("false")->result();
          });

          it("should: \"true\" == \"true\"", [&]() {
            std::string a = "true";
            std::string b = "true";
            return expect(a).to->strict_equal(b)->result();
          });

          it("should: \"true\" != \"false\"", [&]() {
            std::string a = "true";
            std::string b = "false";
            return expect(a).to->never->strict_equal(b)->result();
          });

          it("should: dummy_struct() == dummy_struct()", [&]() {
            return expect(dummy_struct()).to->strict_equal(dummy_struct())->result();
          });
        }); // end - equal: comparison of type T and T

        describe("comparison of type T and U", [&] {
          
          // it("should: true == 1", [&] () {
          // 	return expect(true).to->never->strict_equal(1)->result();
          // });

          // it("should: 1 == 1.0", [&]() {
          // 	return expect(1).to->never->strict_equal(1.0)->result();
          // });

          // it("should: 1 == \"1\"", [&]() {
          // 	std::string b = "1";
          // 	return expect(1).to->never->strict_equal(b)->result();
          // });

          // it("should: 1.7 == 2", [&]() {
          // 	return expect(1.7).to->strict_equal(2)->result();
          // });

          // it("should: 1.7 == \"1.7\"", [&]() {
          // 	return expect(1.7).to->never->strict_equal("1.7")->result();
          // });

          // it("should: 1.7 != 'a'", [&]() {
          // 	return expect(1.7).to->never->strict_equal('a')->result();
          // });

          // it("should: 'a' == \"a\"", [&]() {
          // 	return expect('a').to->never->strict_equal("a")->result();
          // });
        }); // end - equal comparison of type T and U
      });

      describe("strict_equal (using mocha_comparator)", [&] () {
          it("should: dummy_struct(1).get_num() == 1", [&]() {
            return expect(dummy_struct(1)).to->equal(1, 
            mocha_comparator<dummy_struct, int>(
              [&] (dummy_struct a, auto b) -> bool {
              return a.get_num() == b;
            }))->result();
          });
        });
    
      describe("strict_equal (using comparator)", [&] () {
        it("should: dummy_struct(1).get_num() == 1", [&]() {
          return expect(dummy_struct(1)).to->equal(
            1, 
            [&] (dummy_struct a, auto b) -> bool {
              return a.get_num() == b;
            })->result();
        });
      });
    });
  });

  print_summary();

  return 0;
}