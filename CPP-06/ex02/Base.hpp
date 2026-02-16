#pragma once

#include <cstdlib>
#include <iostream>
#include <exception>

class Base
{
	public:
		virtual ~Base();
};

Base *	generate(void);
void	identify(Base* p);
void	identify(Base& p);