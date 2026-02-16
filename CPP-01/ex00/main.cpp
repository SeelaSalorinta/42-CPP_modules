#include "Zombie.hpp"

int	main(void)
{
	Zombie*	myzombie = newZombie("Claire"); //HEAP
	randomChump("Jamie"); //stack inside function
	myzombie->announce();
	delete myzombie;
	return (0);
}