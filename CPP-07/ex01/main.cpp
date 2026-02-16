#include "iter.hpp"
#include <iostream>

template <typename T>
void	print(const T &x)
{
	std::cout << x << " ";
}

void	increment(int &x)
{
	x += 1;
}

void	shout(std::string &s)
{
	s += "!";
}

void	toUpper(char &c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
}

int	main()
{
	std::cout << "--- INT ARRAY ---" << std::endl;
	int intArr[] = {1, 2, 3, 4, 5};

	std::cout << "Original: ";
	iter(intArr, 5, print<int>);
	std::cout << std::endl;

	iter(intArr, 5, increment);

	std::cout << "Incremented: ";
	iter(intArr, 5, print<int>);
	std::cout << std::endl;


	std::cout << "\n--- STRING ARRAY ---" << std::endl;
	std::string strArr[] = {"Hello", "Seela", "Cpp07"};

	std::cout << "Original: ";
	iter(strArr, 3, print<std::string>);
	std::cout << std::endl;

	iter(strArr, 3, shout);

	std::cout << "With exclamation: ";
	iter(strArr, 3, print<std::string>);
	std::cout << std::endl;

	std::cout << "\n--- CHAR ARRAY ---" << std::endl;
	char charArr[] = {'a', 'b', 'c', 'd'};

	std::cout << "Original: ";
	iter(charArr, 4, print<char>);
	std::cout << std::endl;

	iter(charArr, 4, toUpper);

	std::cout << "Uppercased: ";
	iter(charArr, 4, print<char>);
	std::cout << std::endl;

	return 0;
}
