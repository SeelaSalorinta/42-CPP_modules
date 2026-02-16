#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string& target) 
: AForm("RobotomyRequestForm", 72, 45, target)
{
	std::cout << "Robotomy constructor called" << std::endl;
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
: AForm(other)
{
	std::cout << "Robotomy copy constructor called" << std::endl;
}
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& other)
{
	std::cout << "Robotomy copy assigment operator called" << std::endl;
	(void)other;
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
	std::cout << "Robotomy destructor called" << std::endl;
}

void	RobotomyRequestForm::executeAction() const
{
	std::cout << "DRILLING NOISES DRRRR" << std::endl;
	if (std::rand() % 2)
		std::cout << getTarget() << " has been robotomized successfully!\n";
	else
		std::cout << "Robotomy failed on " << getTarget() << ".\n";
}