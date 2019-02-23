#ifndef TYPE_UTILS_H
#define TYPE_UTILS_H
#include <string>
#include <to_string.hpp>

namespace mocha {
  namespace type_utils {
    // Compare with int
    bool strict_equal(int a, int b) { return a == b; }
    bool strict_equal(int a, int64_t b) { return false; }
    bool strict_equal(int a, bool b) { return false; }
    bool strict_equal(int a, const char* b) { return false; };
    bool strict_equal(int a, double b) { return false; };
    bool strict_equal(int a, float b) { return false; };
    bool strict_equal(int a, char b) { return false; };
    bool strict_equal(int a, std::string b) { return false; };

    // Compare with int64_t
    bool strict_equal(int64_t a, int b) { return false; }
    bool strict_equal(int64_t a, int64_t b) { return a == b; }
    bool strict_equal(int64_t a, bool b) { return false; }
    bool strict_equal(int64_t a, const char* b) { return false; };
    bool strict_equal(int64_t a, double b) { return false; };
    bool strict_equal(int64_t a, float b) { return false; };
    bool strict_equal(int64_t a, char b) { return false; };
    bool strict_equal(int64_t a, std::string b) { return false; };

    // Compare with doubles
    bool strict_equal(double a, double b) { return a == b; };
    bool strict_equal(double a, int b) { return false; }
    bool strict_equal(double a, int64_t b) { return false; }
    bool strict_equal(double a, bool b) { return false; }
    bool strict_equal(double a, const char* b) { return false; };
    bool strict_equal(double a, float b) { return false; };
    bool strict_equal(double a, char b) { return false; };
    bool strict_equal(double a, std::string b) { return false; };

    // Compare with floats
    bool strict_equal(float a, float b) { return a == b; };
    bool strict_equal(float a, int b) { return false; }
    bool strict_equal(float a, int64_t b) { return false; }
    bool strict_equal(float a, bool b) { return false; }
    bool strict_equal(float a, const char* b) { return false; };
    bool strict_equal(float a, double b) { return false; };
    bool strict_equal(float a, char b) { return false; };
    bool strict_equal(float a, std::string b) { return false; };

    // Compare with char
    bool strict_equal(char a, char b) { return a == b; };
    bool strict_equal(char a, int b) { return false; }
    bool strict_equal(char a, int64_t b) { return false; }
    bool strict_equal(char a, bool b) { return false; }
    bool strict_equal(char a, const char* b) { return false; };
    bool strict_equal(char a, double b) { return false; };
    bool strict_equal(char a, float b) { return false; };
    bool strict_equal(char a, std::string b) { return false; };

    bool strict_equal(std::string a, std::string b) { return a.compare(b) == 0; };
    bool strict_equal(std::string a, const char* b) { std::string s(b); return a == b; };
    bool strict_equal(std::string a, int b) { return false; }
    bool strict_equal(std::string a, int64_t b) { return false; }
    bool strict_equal(std::string a, bool b) { return false; }
    bool strict_equal(std::string a, double b) { return false; };
    bool strict_equal(std::string a, float b) { return false; };
    bool strict_equal(std::string a, char b) { return false; };

    // Compare with bools
    bool strict_equal(bool a, bool b) { return a == b; }		
    bool strict_equal(bool a, int b) { return false; }
    bool strict_equal(bool a, int64_t b) { return false; }
    bool strict_equal(bool a, const char* b) { return false; };
    bool strict_equal(bool a, double b) { return false; }
    bool strict_equal(bool a, float b) { return false; }
    bool strict_equal(bool a, char b) { return false; }
    bool strict_equal(bool a, std::string b) { return false; }

    // Compare with const char*
    bool strict_equal(const char* a, const char* b) { utils::to_string(a).compare(utils::to_string(b)) == 0; }
    bool strict_equal(const char* a, int b) { return false; }
    bool strict_equal(const char* a, int64_t b) { return false; };
    bool strict_equal(const char* a, bool b) { return false; };
    bool strict_equal(const char* a, double b) { return false; };
    bool strict_equal(const char* a, float b) { return false; };
    bool strict_equal(const char* a, char b) { return false; };
    bool strict_equal(const char* a, std::string b) { utils::to_string(a).compare(b) == 0; }

    // Compare with int
    bool equal(int a, int b) { return a == b; }
    bool equal(int a, int64_t b) { return a == b; }
    bool equal(int a, bool b) { return a == int(b); }
    bool equal(int a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(int a, double b) { return a == int(b); };
    bool equal(int a, float b) { return a == int(b); };
    bool equal(int a, char b) { return a == int(b); };
    bool equal(int a, std::string b) { return a == std::stoi(b); };
    
    // Compare with int64_t
    bool equal(int64_t a, int b) { return a == b; }
    bool equal(int64_t a, int64_t b) { return a == b; }
    bool equal(int64_t a, bool b) { return a == int64_t(b); }
    bool equal(int64_t a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(int64_t a, double b) { return a == int64_t(b); };
    bool equal(int64_t a, float b) { return a == int64_t(b); };
    bool equal(int64_t a, char b) { return a == int64_t(b); };
    bool equal(int64_t a, std::string b) { return a == std::stoll(b); };

    // Compare with doubles
    bool equal(double a, double b) { return a == b; };
    bool equal(double a, int b) { return a == double(b); }
    bool equal(double a, int64_t b) { return a == double(b); }
    bool equal(double a, bool b) { return a == double(int(b)); }
    bool equal(double a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(double a, float b) { return a == double(b); };
    bool equal(double a, char b) { return a == double(int(b)); };
    bool equal(double a, std::string b) { return a == std::stod(b); };

    // Compare with floats
    bool equal(float a, float b) { return a == b; };
    bool equal(float a, int64_t b) { return a == float(b); }
    bool equal(float a, int b) { return a == float(b); }
    bool equal(float a, bool b) { return a == float(int(b)); };
    bool equal(float a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(float a, double b) { return a == float(b); };
    bool equal(float a, char b) { return a == float(int(b)); };
    bool equal(float a, std::string b) { return a == std::stof(b); };

    // Compare with char
    bool equal(char a, char b) { return a == b; };
    bool equal(char a, int b) { return int(a - '0') == b; }
    bool equal(char a, int64_t b) { return int64_t(a - '0') == b; }
    bool equal(char a, bool b) { return int(a - '0') == int(b); }
    bool equal(char a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(char a, double b) { return int64_t(a - '0') == int64_t(b); };
    bool equal(char a, float b) { return int64_t(a - '0') == int64_t(b); };
    bool equal(char a, std::string b) { return utils::to_string(a).compare(b) == 0; };

    bool equal(std::string a, std::string b) { return a.compare(b) == 0; };
    bool equal(std::string a, const char* b) { std::string s(b); return a == b; };
    bool equal(std::string a, int b) { return a.compare(utils::to_string(b)) == 0; }
    bool equal(std::string a, int64_t b) { return a.compare(utils::to_string(b)) == 0; }
    bool equal(std::string a, bool b) { return a.compare(utils::to_string(b)) == 0; }
    bool equal(std::string a, double b) { return a.compare(utils::to_string(b)) == 0; };
    bool equal(std::string a, float b) { return a.compare(utils::to_string(b)) == 0; };
    bool equal(std::string a, char b) { return a.compare(utils::to_string(b)) == 0; };

    // Compare with bools
    bool equal(bool a, bool b) { return a == b; }		
    bool equal(bool a, int b) { return a == b; }
    bool equal(bool a, int64_t b) { return a == b; }
    bool equal(bool a, const char* b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(bool a, double b) { return a == int(b); }
    bool equal(bool a, float b) { return a == int(b); }
    bool equal(bool a, char b) { return a == int(b); }
    bool equal(bool a, std::string b) { return utils::to_string(a).compare(b) == 0; }

    // Compare with const char*
    bool equal(const char* a, const char* b) { utils::to_string(a).compare(utils::to_string(b)) == 0; }
    bool equal(const char* a, int b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(const char* a, int64_t b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(const char* a, bool b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(const char* a, double b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(const char* a, float b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(const char* a, char b) { return utils::to_string(a).compare(utils::to_string(b)) == 0; };
    bool equal(const char* a, std::string b) { return utils::to_string(a).compare(b) == 0; }
  }
} // mocha 

#endif