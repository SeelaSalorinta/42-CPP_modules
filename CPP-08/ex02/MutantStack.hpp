#pragma once

#include <stack>
#include <deque>

template <typename T, class Container = std::deque<T>>
class MutantStack : public std::stack<T, Container>
{
public:
	using iterator = typename Container::iterator;
	using const_iterator = typename Container::const_iterator;
	using reverse_iterator = typename Container::reverse_iterator;
	using const_reverse_iterator = typename Container::const_reverse_iterator;

	MutantStack() = default;
	MutantStack(const MutantStack&) = default;
	MutantStack& operator=(const MutantStack&) = default;
	~MutantStack() = default;

	iterator begin()
	{
		return this->c.begin();
	}
	iterator end()
	{
		return this->c.end();
	}
	const_iterator begin() const
	{
		return this->c.begin();
	}
	const_iterator end() const
	{
		return this->c.end();
	}
	reverse_iterator rbegin()
	{
		return this->c.rbegin();
	}
	reverse_iterator rend()
	{
		return this->c.rend();
	}
	const_reverse_iterator rbegin() const
	{
		return this->c.rbegin();
	}
	const_reverse_iterator rend() const
	{
		return this->c.rend();
	}
};