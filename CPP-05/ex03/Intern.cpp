#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

Intern::Intern()
{
	std::cout << "Intern constructor called" << std::endl;
}

Intern::Intern(const Intern&)
{
	std::cout << "Intern copy constructor called" << std::endl;
}
Intern& Intern::operator=(const Intern&)
{
	std::cout << "Intern copy assigment operator called" << std::endl;
	return *this;
}

Intern::~Intern()
{
	std::cout << "Intern destructor called" << std::endl;
}

const char*	Intern::UnknownFormException::what() const noexcept
{
	return "Unknown form name! Use either shrubbery creation, robotomy request or presidential pardon";
}

AForm*	Intern::createShrubbery(const std::string& target) const
{
	return (new ShrubberyCreationForm(target));
}

AForm*	Intern::createRobotomy(const std::string& target) const
{
	return (new RobotomyRequestForm(target));
}

AForm*	Intern::createPresidential(const std::string& target) const
{
	return (new PresidentialPardonForm(target));
}

AForm*	Intern::makeForm(const std::string& formName, const std::string& target) const
{
	typedef AForm* (Intern::*Creator)(const std::string&) const;
	static const std::string formNames[] = {"shrubbery creation", "robotomy request", "presidential pardon"};
	static const Creator creators[] = {&Intern::createShrubbery, &Intern::createRobotomy, &Intern::createPresidential};
	for (int i = 0; i < 3; i++)
	{
		if (formName == formNames[i])
		{
			AForm *newForm =(this->*creators[i])(target);
			std::cout << "Intern creates " << newForm->getName() << " targeting " << target << std::endl;
			return newForm; 
		}
	}
	throw UnknownFormException();
}