#include "Contact.hpp"
#include "PhoneBook.hpp"

int	main(void)
{
	std::string	input;
	PhoneBook	my_book;

	std::cout << "================== PHONEBOOK MENU ==================" << std::endl;
	std::cout << "Type one of the following actions: " << std::endl;
	std::cout << "  - ADD     → Save a new contact" << std::endl;
	std::cout << "  - SEARCH  → Display a specific contact" << std::endl;
	std::cout << "  - EXIT    → Quit the program" << std::endl;
	std::cout << "====================================================" << std::endl;
	while (1)
	{
		std::cout << "\nYour choice of action: ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			break ;
		if (input == "ADD")
			my_book.addContact();
		else if (input == "SEARCH")
			my_book.searchContacts();
		else if (input == "EXIT")
			break ;
		else
			std::cout << "ERROR -----> Input did not match any of the allowed actions" << std::endl;
	}
	return (0);
}
