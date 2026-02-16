#include <iostream>
#include <string>
#include "Array.hpp"

int main() {
	std::cout << "--- Empty Array<int> ---" << std::endl;
	Array<int> empty;
	std::cout << "empty.size() = " << empty.size() << std::endl;
	try {
		std::cout << "empty[0] = " << empty[0] << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- Array<int> of size 5 ---" << std::endl;
	Array<int> a(5);
	for (unsigned int i = 0; i < a.size(); ++i)
		a[i] = (i + 1) * 10;

	for (unsigned int i = 0; i < a.size(); ++i)
		std::cout << "a[" << i << "] = " << a[i] << std::endl;

	std::cout << "\n--- Copy constructor ---" << std::endl;
	Array<int> b(a);
	for (unsigned int i = 0; i < b.size(); ++i)
		std::cout << "b[" << i << "] = " << b[i] << std::endl;

	b[0] = 999;
	std::cout << "After modifying b[0]:" << std::endl;
	std::cout << "a[0] = " << a[0] << std::endl;
	std::cout << "b[0] = " << b[0] << std::endl;

	std::cout << "\n--- Assignment operator ---" << std::endl;
	Array<int> c;
	c = a;
	for (unsigned int i = 0; i < c.size(); ++i)
		std::cout << "c[" << i << "] = " << c[i] << std::endl;

	c[1] = 4242;
	std::cout << "After modifying c[1]:" << std::endl;
	std::cout << "a[1] = " << a[1] << std::endl;
	std::cout << "c[1] = " << c[1] << std::endl;

	std::cout << "\n--- Array<std::string> ---" << std::endl;
	Array<std::string> s(3);
	s[0] = "Hello";
	s[1] = "Seela";
	s[2] = "Array";

	for (unsigned int i = 0; i < s.size(); ++i)
		std::cout << "s[" << i << "] = " << s[i] << std::endl;

	std::cout << "\n--- Out-of-bounds on strings ---" << std::endl;
	try {
		std::cout << s[10] << std::endl;
	} catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	std::cout << "\n--- Const access ---" << std::endl;
	const Array<int> ar(3);
	for (unsigned int i = 0; i < ar.size(); ++i)
		std::cout << ar[i] << std::endl;

	return 0;
}
