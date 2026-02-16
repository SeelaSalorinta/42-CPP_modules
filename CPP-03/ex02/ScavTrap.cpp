#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap()
{
	std::cout << "ScavTrap default constructor called" << std::endl;
	_name = "DefaultScav";
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	std::cout << "ScavTrap constructor called for " << _name << std::endl;
	_hitPoints = 100;
	_energyPoints = 50;
	_attackDamage = 20;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other)
{
	std::cout << "ScavTrap copy constructor called for " << _name << std::endl;
}

ScavTrap&	ScavTrap::operator=(const ScavTrap& other)
{
	std::cout << "ScavTrap copy assignment operator called for " << _name << std::endl;
	ClapTrap::operator=(other);
	return (*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor called" << std::endl;
}

void	ScavTrap::attack(const std::string& target)
{
	if (_hitPoints <= 0)
	{
		std::cout << COLOR_PURPLE << "ScavTrap " << _name << " can't attack (no hit points left)!" << COLOR_RESET << std::endl;
		return ;
	}
	if (_energyPoints <= 0)
	{
		std::cout << COLOR_PURPLE << "ScavTrap " << _name << " can't attack (no energy points left)!" << COLOR_RESET << std::endl;
		return ;
	}
	_energyPoints--;
	std::cout << COLOR_PURPLE << "ScavTrap " << _name << " fiercely attacks " << target
			  << ", causing " << _attackDamage << " points of damage!" << COLOR_RESET << std::endl;
}

void	ScavTrap::guardGate()
{
	std::cout << COLOR_PURPLE << "ScavTrap " << _name << " is now in Gate keeper mode." << COLOR_RESET << std::endl;
}