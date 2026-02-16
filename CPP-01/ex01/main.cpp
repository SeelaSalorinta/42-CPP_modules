#include "Zombie.hpp"

int	main(void)
{
	int	amount = 8;
	int	amountTwo = 3;
	Zombie*	megs = zombieHorde(amount, "megans");
	Zombie*	kims = zombieHorde(amountTwo, "kims");

	if (!megs || !kims) //??
	{
		std::cerr << "Failed to create Zombie Horde" << std::endl;
		return (1);
	}
	for (int i = 0; i < amount; i++)
		megs[i].announce();
	for (int i = 0; i < amountTwo; i++)
		kims[i].announce();
	delete[] megs;
	delete[] kims;
	return (0);
}

//delete[] zombies;
//This tells C++ to: Call the destructor for each zombie and Free the whole block of memory