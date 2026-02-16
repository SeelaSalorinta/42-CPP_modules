#include "Zombie.hpp"

void	randomChump(std::string name)
{
	Zombie	myrandomzombie(name); //on stack memory
	myrandomzombie.announce();
}

//myrandomzombie is destroyd as soon as this function ends,
// easy and diont have to remember to  delete