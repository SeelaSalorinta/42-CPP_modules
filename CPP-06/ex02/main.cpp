#include "Base.hpp"
#include <ctime>

int main()
{
	std::srand(std::time(NULL));

	std::cout << "=== GENERATE AND IDENTIFY 10 times ===\n" << std::endl;

	for (int i = 0; i < 10; i++)
	{
		Base* ptr = generate();
		std::cout << "Test " << i + 1 << ":\n";
		std::cout << "  identify(*ptr): ";
		identify(*ptr);           // reference version
		std::cout << "  identify(ptr):  ";
		identify(ptr);            // pointer version
		std::cout << std::endl;
		delete ptr;
	}

	return 0;
}