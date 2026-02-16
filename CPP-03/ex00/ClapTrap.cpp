#include "ClapTrap.hpp"

ClapTrap::ClapTrap() : _name("DefaultClap"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
	std::cout << "ClapTrap constructor called for " << _name << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other) : _name(other._name), _hitPoints(other._hitPoints), _energyPoints(other._energyPoints), _attackDamage(other._attackDamage)
{
	std::cout << "ClapTrap copy constructor called" << std::endl;
}

ClapTrap&	ClapTrap::operator=(const ClapTrap& other)
{
	std::cout << "ClapTrap copy assignment operator called" << std::endl;
	if (this != &other)
	{
		_name = other._name;
		_hitPoints = other._hitPoints;
		_energyPoints = other._energyPoints;
		_attackDamage = other._attackDamage;
	}	
	return (*this);
}

ClapTrap::~ClapTrap()
{
	std::cout << "ClapTrap destructor called" << std::endl;
}

void	ClapTrap::attack(const std::string& target)
{
	if (_hitPoints <= 0)
		std::cout << COLOR_BLUE << "ClapTrap " << _name << " can't attack (no hit points left)!" << COLOR_RESET << std::endl;
	else if (_energyPoints <= 0)
		std::cout << COLOR_BLUE << "ClapTrap " << _name << " can't attack (no energy points left)!" << COLOR_RESET << std::endl;
	else
	{
		std::cout << COLOR_BLUE << "ClapTrap " << _name << " attacks " << target << " causing " << _attackDamage << " points of damage!" << COLOR_RESET << std::endl;
		_energyPoints--;
	}
}

void	ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints <= 0)
	{
		std::cout << COLOR_BLUE << "ClapTrap " << _name << " is already dead and can't take more damage." << COLOR_RESET << std::endl;
		return;
	}
	_hitPoints -= amount;
	if (_hitPoints < 0)
		_hitPoints = 0;
	std::cout << COLOR_BLUE << "ClapTrap " << _name << " takes " << amount << " points of damage. Remaining hitPoints: " << _hitPoints << COLOR_RESET << std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints <= 0)
		std::cout << COLOR_BLUE << "ClapTrap " <<_name << " can't repair, (no hit points left)!" << COLOR_RESET << std::endl;
	else if ( _energyPoints <= 0)
		std::cout << COLOR_BLUE << "ClapTrap " << _name << " can't repair, (no energy points left)!" << COLOR_RESET << std::endl;
	else
	{
		_hitPoints += amount;
		_energyPoints--;
		std::cout << COLOR_BLUE << "ClapTrap " << _name << " repairs itself for " << amount << " points. HitPoints: " << _hitPoints << ", energyPoints: " << _energyPoints << COLOR_RESET << std::endl;
	}
}