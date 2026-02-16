#include <iostream>
#include <list>
#include <vector>
#include "MutantStack.hpp"

void	subjectsTestsList()
{
	std::cout << "----- SUBJECT TESTS WITH LIST -----" << std::endl;
	std::list<int> lst;

	lst.push_back(5);
	lst.push_back(17);

	std::cout << lst.back() << std::endl;

	lst.pop_back();

	std::cout << lst.size() << std::endl;

	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);

	std::list<int>::iterator it = lst.begin();
	std::list<int>::iterator ite = lst.end();

	++it;
	--it;

	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
}

void	subjectsTests()
{
	std::cout << "----- SUBJECT TESTS WITH MUTANTSTACK -----" << std::endl;

	MutantStack<int> mstack;
	mstack.push(5);
	mstack.push(17);

	std::cout << mstack.top() << std::endl;

	mstack.pop();
	
	std::cout << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	++it;
	--it;
	while (it != ite)
	{
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
}

void	differentIterators()
{
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(10);
	mstack.push(20);
	mstack.push(40);

	std::cout << "=== Forward iteration ===" << std::endl;
	for (MutantStack<int>::iterator it = mstack.begin(); it != mstack.end(); ++it)
		std::cout << *it << std::endl;

	std::cout << "\n=== Reverse iteration ===" << std::endl;
	for (MutantStack<int>::reverse_iterator rit = mstack.rbegin(); rit != mstack.rend(); ++rit)
		std::cout << *rit << std::endl;

	std::cout << "\n=== Const forward iteration ===" << std::endl;
	const MutantStack<int> cm = mstack;
	for (MutantStack<int>::const_iterator cit = cm.begin(); cit != cm.end(); ++cit)
		std::cout << *cit << std::endl;
}

static void vectorUnderlying()
{
	std::cout << "=== Vector as underlying container ===" << std::endl;
	MutantStack<int, std::vector<int>> ms;

	ms.push(1);
	ms.push(2);
	ms.push(3);

	for (MutantStack<int, std::vector<int>>::iterator it = ms.begin(); it != ms.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
}

int main()
{
	subjectsTests();
	subjectsTestsList();
	differentIterators();
	vectorUnderlying();
	return 0;
}