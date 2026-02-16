#include "Span.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <climits>

static void printHeader(const std::string& title)
{
	std::cout << "\n==============================\n";
	std::cout << title << "\n";
	std::cout << "==============================\n";
}

static void testSubject()
{
	printHeader("SUBJECT TESTS");

	try {
		Span sp(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);

		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest:  " << sp.longestSpan()  << std::endl,

		std::cout << "Trying to add one more number (should throw)...\n";
		sp.addNumber(11);
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testNoNumbers()
{
	printHeader("Test: No numbers (should throw)");

	try {
		Span sp(5);
		std::cout << sp.shortestSpan() << std::endl; // should throw
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testOneNumber()
{
	printHeader("Test: One number (should throw)");

	try {
		Span sp(5);
		sp.addNumber(10);
		std::cout << sp.longestSpan() << std::endl; // should throw
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testNegativeNumbers()
{
	printHeader("Test: Negative numbers");

	try {
		std::vector<int> vec;
		vec.push_back(5);
		vec.push_back(-3);
		vec.push_back(-10);
		vec.push_back(20);

		Span sp(static_cast<unsigned int>(vec.size()));
		sp.addRange(vec.begin(), vec.end());

		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest:  " << sp.longestSpan()  << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testAddRangeOverflow()
{
	printHeader("Test: addRange exceeding capacity (should throw)");

	try {
		std::vector<int> vec(5, 42);
		Span sp(3);
		sp.addRange(vec.begin(), vec.end()); 
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testBigRandom()
{
	printHeader("Big test: 10,000 random numbers");

	const unsigned int N = 10000;
	Span sp(N);

	std::vector<int> nums;
	nums.reserve(N);

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	for (unsigned int i = 0; i < N; ++i)
		nums.push_back(std::rand());

	try {
		sp.addRange(nums.begin(), nums.end());
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan()  << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testConstAddRange()
{
	printHeader("Test: const addRange");

	const std::vector<int> v = {2, 3, 10, 20, 30};
	Span sp(5);

	try {
		sp.addRange(v.begin(), v.end());
		std::cout << "Added const range successfully.\n";
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest:  " << sp.longestSpan()  << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

static void testMax()
{
	printHeader("Test: INT_MAX and INT_MIN");

	try {
		Span sp(2);
		sp.addNumber(INT_MAX);
		sp.addNumber(INT_MIN);
		std::cout << "Shortest: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest:  " << sp.longestSpan()  << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}
}

int main()
{
	testSubject();
	testNoNumbers();
	testOneNumber();
	testNegativeNumbers();
	testAddRangeOverflow();
	testBigRandom();
	testConstAddRange();
	testMax();
	return 0;
}
