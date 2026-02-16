#include <iostream>
#include <string>

int	main(void)
{
	std::string		brain = "HI THIS IS BRAIN";
	std::string*	brainPtr = &brain; //&brain: gives the memory address of the actual brain string
	std::string&	brainRef = brain;

	std::cout << "Memory address of brain : " << &brain << std::endl;
	std::cout << "Memory address of brainPtr : " << brainPtr << std::endl;
	std::cout << "Memory address of brainRef : " << &brainRef << std::endl;

	std::cout << "Value of brain: " << brain << std::endl;
	std::cout << "Value of brainPtr : " << *brainPtr << std::endl; //💬 Pointer gives you the address, *pointer gives you the value.
	std::cout << "Value of brainRef : " << brainRef << std::endl;
}
//  A reference is like a nickname — it refers to an existing variable.
//ref is just another name for brain.
// Anything you do to ref, you're actually doing to brain.
// so basically ref works just like normal strng in the printing bc bascally they are the same thing