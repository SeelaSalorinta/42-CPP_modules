#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact	_contacts[8];
		int		_contactAmount;
		void	makeTheSearch();
		void	displayAllContacts();

	public:
		PhoneBook();
		void	addContact();
		void	searchContacts();
};

#endif
