#include "ScalarConverter.hpp"

#define RESET "\033[0m"
#define TITLE_COLOR "\033[36m"

static void title(const std::string& t) {
	std::cout << "\n" << TITLE_COLOR << "=== " << t << " ===" << RESET << "\n";
}

static void test(const std::string& input)
{
	std::cout << "==============================\n";
	std::cout << "   Input: \"" << input << "\"\n";
	std::cout << "------------------------------\n";
	ScalarConverter::convert(input);
	std::cout << "==============================\n\n";
}

int main(int argc, char **argv)
{
	if (argc == 2)
	{
		test(argv[1]);
		return 0;
	}
	std::cout << "Running internal test cases...\n\n";

	title("Chars");
	test("a");
	test("z");
	test("!");

	title("Ints");
	test("42");
	test("-42");
	test("2147483647");   // INT_MAX
	test("2147483648");   // overflow
	test("-2147483648");  // INT_MIN
	test("-2147483649");  // underflow

	title("Floats");
	test("0.0f");
	test("4.2f");
	test("-4.2f");
	test("1.5f");
	test("3.4028235e+38f");    // FLT_MAX
	test("3.4028236e+38f");    // overflow
	test("-3.4028235e+38f");   // -FLT_MAX
	test("-3.4028236e+38f");    // underflow

	title("Doubles");
	test("0.0");
	test("4.2");
	test("-4.2");
	test(".5");
	test("5.");
	test("1.7976931348623157e+308");   // DBL_MAX
	test("1.8e+308");                  // overflow
	test("-1.7976931348623157e+308");  // -DBL_MAX
	test("-1.8e+308");                 // underflow

	title("Pseudo");
	test("nan");
	test("nanf");
	test("+inf");
	test("-inf");
	test("+inff");
	test("-inff");

	title("Invalid");
	test("");
	test("abc");
	test("12a");
	test("++1");
	test("4.2ff");

	return 0;
}
