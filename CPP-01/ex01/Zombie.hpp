#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

#include <iostream>
#include <string>

class Zombie
{
	private:
		std::string	_name;

	public:
		Zombie(); //constructor
		~Zombie(); //destructor
		void	announce() const;
		void	setName(std::string name);
};

Zombie*	zombieHorde(int amount, std::string name);

#endif
