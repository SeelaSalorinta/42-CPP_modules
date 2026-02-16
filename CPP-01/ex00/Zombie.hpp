#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
	private:
		std::string	_name; //prvate attribute
	
	public:
		Zombie(std::string name); //constructor
		~Zombie(); //destructor
		void	announce() const;
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif