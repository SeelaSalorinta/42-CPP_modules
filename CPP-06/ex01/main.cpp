#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

int main()
{
	Data	original;
	original.index = 42;
	original.name = "Seela";

	std::cout << "Original pointer: " << &original << std::endl;

	uintptr_t serialized = Serializer::serialize(&original);
	std::cout << "Serialized (uintptr_t): " << serialized << std::endl;

	Data* desirializedData = Serializer::deserialize(serialized);
	std::cout << "Deserialized pointer: " << desirializedData << std::endl;

	if (desirializedData == &original)
		std::cout << GREEN << "Pointers match" << RESET << std::endl;
	else
		std::cout << RED << "Pointers DO NOT match" << RESET << std::endl;

	std::cout << "Original data: index=" << original.index
			<< ", name=" << original.name
			<< std::endl;
	std::cout << "Restored data: index=" << desirializedData->index
			<< ", name=" << desirializedData->name
			<< std::endl;

	return 0;
}

