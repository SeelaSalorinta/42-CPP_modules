#include <iostream>
#include <string>
#include "whatever.hpp"

int main() {
	std::cout << "------ SUBJECT TESTS ------" << std::endl;

	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min(a, b) = " << ::min(a, b) << std::endl;
	std::cout << "max(a, b) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min(c, d) = " << ::min(c, d) << std::endl;
	std::cout << "max(c, d) = " << ::max(c, d) << std::endl;

	std::cout << "\n------ EXTRA TESTS ------" << std::endl;

	char x = 'a';
	char y = 'z';

	::swap(x, y);
	std::cout << "x = " << x << ", y = " << y << std::endl;
	std::cout << "min(x, y) = " << ::min(x, y) << std::endl;
	std::cout << "max(x, y) = " << ::max(x, y) << std::endl;

	double d1 = -1.00001;
	double d2 = -1.00002;

	::swap(d1, d2);
	std::cout << "d1 = " << d1 << ", d2 = " << d2 << std::endl;
	std::cout << "min(d1, d2) = " << ::min(d1, d2) << std::endl;
	std::cout << "max(d1, d2) = " << ::max(d1, d2) << std::endl;

	return 0;
}


