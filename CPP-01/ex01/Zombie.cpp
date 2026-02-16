#include "Zombie.hpp"

Zombie::Zombie()
{
	std::cout << "Constructor is called" << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Destructor is called for " << _name << std::endl;
}

void	Zombie::announce() const
{
	std::cout << _name << ": is announced" << std::endl;
}

void	Zombie::setName(std::string name) //cant be const bc modifies member _name
{
	_name = name;
}