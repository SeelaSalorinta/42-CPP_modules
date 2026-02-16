#include "Zombie.hpp"

Zombie*	newZombie(std::string name)
{
	return (new Zombie(name));  // Allocated on the heap
}

//use heap if you need to return the object from the function
