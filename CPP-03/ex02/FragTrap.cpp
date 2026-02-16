#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap()
{
	std::cout << "FragTrap default constructor called" << std::endl;
	_name = "DefaultFrag";
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	std::cout << "FragTrap constructor called for " << _name << std::endl;
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other)
{
	std::cout << "FragTrap copy constructor called for " << _name << std::endl;
}

FragTrap&	FragTrap::operator=(const FragTrap& other)
{
	std::cout << "FragTrap copy assignment operator called for " << _name << std::endl;
	ClapTrap::operator=(other);
	return (*this);
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor called" << std::endl;
}

void	FragTrap::attack(const std::string& target)
{
	if (_hitPoints <= 0)
	{
		std::cout << COLOR_GREEN << "FragTrap " << _name << " can't attack (no hit points left)!" << COLOR_RESET << std::endl;
		return ;
	}
	if (_energyPoints <= 0)
	{
		std::cout << COLOR_GREEN << "FragTrap " << _name << " can't attack (no energy points left)!" << COLOR_RESET << std::endl;
		return ;
	}
	_energyPoints--;
	std::cout << COLOR_GREEN << "FragTrap " << _name << " attacks " << target
			  << " with power, causing " << _attackDamage << " points of damage!" << COLOR_RESET << std::endl;
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << COLOR_GREEN << "FragTrap high fives guys" << COLOR_RESET << std::endl;
}