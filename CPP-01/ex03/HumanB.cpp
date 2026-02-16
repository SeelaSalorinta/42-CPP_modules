#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(nullptr) {}

HumanB::~HumanB() {}

void	HumanB::setWeapon(Weapon& weapon)
{
	this->_weapon = &weapon;
}

void	HumanB::attack()
{
	if (!_weapon)
	{
		std::cerr << _name << " can't attack, no weapon set" << std::endl; //cerr or cout???
		return ;
	}
	std::cout << _name << " attacks with their " << _weapon->getType() << std::endl;
}