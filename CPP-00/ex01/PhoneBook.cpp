#include "PhoneBook.hpp"

PhoneBook::PhoneBook()
{
	_contactAmount = 0;
}

std::string	promptField(const std::string& prompt)
{
	std::string	input;

	while (1)
	{
		std::cout << prompt;
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (!input.empty() && input.find_first_not_of(" \t") != std::string::npos)
			return (input);
		std::cout << "ERROR ----> Field cannot be empty or have only spaces." << std::endl;
	}
}

void	PhoneBook::displayAllContacts()
{
	for (int i = 0; i < _contactAmount && i < 8; i++)
		_contacts[i].displaySearchFields(i);
}

void	PhoneBook::addContact()
{
	std::string	first = promptField( "Type contact's first name: ");
	std::string	last = promptField( "Type contact's last name: ");
	std::string	nick = promptField( "Type contact's nickname: ");
	std::string	phone = promptField( "Type contact's phone number: ");
	std::string	secret = promptField( "Type contact's darkest secret: ");
	
	int	index = _contactAmount % 8;
	if (_contacts[index].addInfo(first, last, nick, phone, secret))
		_contactAmount++;
}

void	PhoneBook::makeTheSearch()
{
	std::string	input;

	while (1)
	{
		std::cout << "Write the index number of the contact you want to display: ";
		std::getline(std::cin, input);
		if (std::cin.eof())
			exit(0);
		if (input.empty())
		{
			std::cout << "ERROR ----> Field cannot be empty." << std::endl;
			continue ;
		}
		bool valid = input.find_first_not_of("0123456789") == std::string::npos;
		if (!valid)
			std::cout << "ERROR ----> Invalid index: not a number" << std::endl;
		else
		{
			int index = std::atoi(input.c_str());
			if (index >= 0 && index <= 7 && index < _contactAmount)
			{
				_contacts[index].displayOneContact(index);
				break ;
			}
			else
				std::cout << "ERROR ----> Invalid index: out of range" << std::endl;
		}
	}
}

void	PhoneBook::searchContacts()
{
	if (_contactAmount == 0)
	{
		std::cout << "ERROR ----> Phonebook has no contacts!" << std::endl;
		std::cout << "Please add a contact to be able to search." << std::endl;
		return ;
	}
	std::cout << "|" << std::setw(10) << "Index"
		<< "|" << std::setw(10) << "First Name"
		<< "|" << std::setw(10) << "Last Name"
		<< "|" << std::setw(10) << "Nickname"
		<< "|\n";
	displayAllContacts();
	std::cout << std::endl;
	makeTheSearch();
}
