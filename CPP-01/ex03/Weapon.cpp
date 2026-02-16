#include "Weapon.hpp"

Weapon::Weapon(std::string type) : _type(type) {}

Weapon::~Weapon() {}

void	Weapon::setType(std::string newtype)
{
	_type = newtype;
}

const std::string&	Weapon::getType() const
{
	return (_type);
}