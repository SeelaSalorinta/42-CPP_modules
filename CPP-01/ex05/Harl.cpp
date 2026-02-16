#include "Harl.hpp"

Harl::Harl(){}

Harl::~Harl(){}

void	Harl::debug()
{
	std::cout << "I love having extra bacon for my ";
	std::cout << "7XL-double-cheese-triple-pickle-specialketchup burger. I really do!";
	std::cout << std::endl;
}

void	Harl::info()
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn't put enough bacon in my burger! ";
	std::cout << "If you did, I wouldn't be asking for more!";
	std::cout << std::endl;
}

void	Harl::warning()
{
	std::cout << "I think I deserve to have some extra bacon for free. ";
	std::cout << "I've been coming for years whereas you started working here since last month.";
	std::cout << std::endl;
}

void	Harl::error()
{
	std::cout << "This is unacceptable! I want to speak to the manager now.";
	std::cout << std::endl;
}

void	Harl::complain(std::string level)
{
	std::string levelNames[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	void (Harl::*functions[])() = {&Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	//needs to be Harl bc points to member functions
	//aka void Harl functionpointers
	for (int i = 0; i < 4; i++)
	{
		if (level == levelNames[i])
		{
			(this->*functions[i])(); //this->info(), the current object thats calling the functon akaa this
			return ; //whatever Harl instance is using the complain() method.
		} //that allows the compiler to correctly call this->debug(), this->info(), etc.
	}
	std::cout << "This input: " << level << " : did not match any of the levels" << std::endl;
	std::cout << "The levels are: DEBUG, INFO, WARNING and ERROR" << std::endl;
}
