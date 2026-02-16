#include "Zombie.hpp"

Zombie*	zombieHorde(int amount, std::string name)
{
	if (amount <= 0)
		return (NULL);
	Zombie*	myHorde = new Zombie[amount];
	for (int i = 0; i < amount; i++)
		myHorde[i].setName(name);
	return (myHorde); //myHorde == &myHorde[0]
}