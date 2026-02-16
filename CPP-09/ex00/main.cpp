#include "BitcoinExchange.hpp"
#include <iostream>

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cout << "Error: could not open file." << std::endl;
		return 1;
	}
	if (argc != 2)
	{
		std::cout << "Usage : ./btc input.txt" << std::endl;
		return 1;
	}
	BitcoinExchange btc(argv[1]);

	try {
		btc.runBtc();
	}
	catch (std::exception &e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	return 0;
}