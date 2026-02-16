#include "Span.hpp"
#include <algorithm>
#include <stdexcept>

Span::Span(unsigned int N) : _maximumSize(N), _numbers() {}

Span::Span(const Span &other) 
: _maximumSize(other._maximumSize), _numbers(other._numbers) {}

Span& Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_maximumSize = other._maximumSize;
		_numbers = other._numbers;
	}
	return (*this);
}

Span::~Span() {}

void Span::addNumber(int number)
{
	if (_numbers.size() >= _maximumSize)
		throw std::runtime_error("Span is full: cannot addNumber()");
	
	_numbers.push_back(number);
}

long long Span::shortestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Cannot find shortest span: not enough numbers stored");

	std::vector<int> tmp(_numbers);
	std::sort(tmp.begin(), tmp.end());

	long long shortest = static_cast<long long>(tmp[1]) - static_cast<long long>(tmp[0]);

	for (size_t i = 1; i < tmp.size(); ++i)
	{
		long long diff = static_cast<long long>(tmp[i]) - static_cast<long long>(tmp[i - 1]);
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

long long Span::longestSpan() const
{
	if (_numbers.size() < 2)
		throw std::runtime_error("Cannot find longest span: not enough numbers stored");

	std::vector<int> tmp(_numbers);
	std::sort(tmp.begin(), tmp.end());

	return static_cast<long long>(tmp.back()) - static_cast<long long>(tmp.front());
}
void Span::addRange(std::vector<int>::iterator first, std::vector<int>::iterator last)
{
	if (last > first)
		throw std::runtime_error("Invalid iterator range (last before first)");
	std::size_t count = static_cast<std::size_t>(std::distance(first, last));
	
	if (count > (_maximumSize - _numbers.size()))
		throw std::runtime_error("Span is full: cannot add this range");
	
	_numbers.insert(_numbers.end(), first, last);
}

void Span::addRange(std::vector<int>::const_iterator first, std::vector<int>::const_iterator last)
{
	std::size_t count = static_cast<std::size_t>(std::distance(first, last));
	
	if (_numbers.size() + count > _maximumSize)
		throw std::runtime_error("Span is full: cannot add this range");
	
	_numbers.insert(_numbers.end(), first, last);
}