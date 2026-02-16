#pragma once

#include <vector>
#include <deque>
#include <string>
#include <cstddef>
#include <stdexcept>
#include <iostream>

class PmergeMe
{
	private:
		std::vector<unsigned int>	_ogVec;
		std::vector<unsigned int>	_vec;
		std::deque<unsigned int>	_deq;
		double		_timeUsVec;
		double		_timeUsDeq;

		static void	fordJohnsonSort(std::vector<unsigned int>& v);
		static void	fordJohnsonSort(std::deque<unsigned int>& d);
	
	public:
		PmergeMe() = default;
		PmergeMe(const PmergeMe& other) = delete;
		PmergeMe& operator=(const PmergeMe& other) = delete;
		~PmergeMe() = default;

		void	run(int argc, char** argv);
};

template <typename Container>
static void fillFromArgs(Container& out, int argc, char** argv)
{
	out.clear();
	for (int i = 1; i < argc; ++i)
	{
		std::string s(argv[i]);
		std::size_t pos = 0;
		int value;

		try {
			value = std::stoi(s, &pos);
		} catch (...) {
			throw std::runtime_error("Error");
		}

		if (pos != s.size() || value < 0)
			throw std::runtime_error("Error");

		out.push_back(static_cast<unsigned int>(value));
	}
}

template <typename Container>
void printContainer(const char* text, const Container& c)
{
	std::cout << text;
	for (typename Container::const_iterator it = c.begin(); it != c.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}
