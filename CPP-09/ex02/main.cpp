#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char** argv)
{
	if (argc == 1)
	{
		std::cout << "No arguments given.\n";
		return 1;
	}
	try {
		PmergeMe pm;
		pm.run(argc, argv);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << "\n";
		return 1;
	}
	return 0;
}
