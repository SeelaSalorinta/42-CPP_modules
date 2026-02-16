#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

void testVector()
{
	std::cout << "\n=== Testing std::vector ===\n";

	std::vector<int> vec = {10, 20, 30, 40, 50};

	try {
		auto it = easyfind(vec, 30);
		std::cout << "Found: " << *it << "\n";
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	try {
		auto it = easyfind(vec, 99);
		std::cout << "Found: " << *it << "\n";
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
}

void testList()
{
	std::cout << "\n=== Testing std::list ===\n";

	std::list<int> lst = {1, 2, 3, 4, 5};

	try {
		auto it = easyfind(lst, 4);
		std::cout << "Found: " << *it << "\n";
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
	try {
		auto it = easyfind(lst, 42);
		std::cout << "Found: " << *it << "\n";
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << "\n";
	}
}

void testConst()
{
	std::cout << "\n=== Testing const ===\n";

	const std::vector<int> vec = {1, 2, 3, 2, 5};

 try
	{
		auto it = easyfind(vec, 2);
		std::cout << "Found value: " << *it << std::endl;
		std::cout << "Index of found value: "
				  << std::distance(vec.begin(), it) << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

int	main()
{
	testVector();
	testList();
	testConst();
	return 0;
}


