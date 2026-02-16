#ifndef INTERN_HPP
# define INTERN_HPP

#include <string>
#include <iostream>
#include <exception>

class AForm;

class Intern
{
	private:
		AForm*	createShrubbery(const std::string& target) const;
		AForm*	createRobotomy(const std::string& target) const;
		AForm*	createPresidential(const std::string& target) const;

	public:
		Intern();
		Intern(const Intern& other);
		Intern&	operator=(const Intern& other);
		~Intern();

		AForm*	makeForm(const std::string& formName, const std::string& target) const;

		class UnknownFormException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};
};

#endif