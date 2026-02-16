#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name)
{
	std::cout << "Constructor is called for " <<_name << std::endl;
}

Zombie::~Zombie()
{
	std::cout << "Destructor is called for " << _name << std::endl;
}

void	Zombie::announce() const
{
	std::cout << _name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
