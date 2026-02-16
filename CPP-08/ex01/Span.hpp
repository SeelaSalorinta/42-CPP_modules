#pragma once

#include <vector>

class Span
{
	private:
		unsigned int		_maximumSize;
		std::vector<int>	_numbers;

	public:
		Span() = delete;
		Span(unsigned int N);
		Span(const Span &other);
		Span& operator=(const Span &other);
		~Span();

		void addNumber(int number);
		long long longestSpan() const;
		long long shortestSpan() const;
		void addRange(std::vector<int>::iterator first, std::vector<int>::iterator last);
		void addRange(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last);
};
