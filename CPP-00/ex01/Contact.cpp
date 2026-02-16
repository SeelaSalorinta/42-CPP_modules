#include "Contact.hpp"

int	Contact::addInfo(const std::string& first, const std::string& last,
					const std::string& nick, const std::string& number,
					const std::string& secret)
{
	_firstName = first;
	_lastName = last;
	_nickName = nick;
	_phoneNumber = number;
	_darkestSecret = secret;
	return (1);
}

static std::string	max10Chars(std::string field)
{
	int	length = field.length();

	if (length > 10)
		return (field.substr(0, 9) + ".");
	return (field);
}

void	Contact::displaySearchFields(int index)
{
	std::cout << "|" << std::setw(10) << index
		<< "|" << std::setw(10) << max10Chars(_firstName)
		<< "|" << std::setw(10) << max10Chars(_lastName)
		<< "|" << std::setw(10) << max10Chars(_nickName)
		<< "|" << std::endl;
}

void	Contact::displayOneContact(int index)
{
	std::cout << "\nDisplaying contact at index ---> " << index << std::endl;
	std::cout << "First name: " << _firstName << std::endl;
	std::cout << "Last name: " << _lastName << std::endl;
	std::cout << "Nickname: " << _nickName << std::endl;
	std::cout << "Phone number: " << _phoneNumber << std::endl;
	std::cout << "Darkest secret: " << _darkestSecret << std::endl;
}
