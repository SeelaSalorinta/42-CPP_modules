#ifndef CONTACT_HPP
# define CONTACT_HPP

#include <iostream>
#include <iomanip>
#include <string>

class Contact
{
	private:
		std::string	_firstName;
		std::string	_lastName;
		std::string	_nickName;
		std::string	_phoneNumber;
		std::string	_darkestSecret;

	public:
		int	addInfo(const std::string& first, const std::string& last,
			const std::string& nick, const std::string& number,
			const std::string& secret);
		void	displayOneContact(int index);
		void	displaySearchFields(int index);
};

#endif
