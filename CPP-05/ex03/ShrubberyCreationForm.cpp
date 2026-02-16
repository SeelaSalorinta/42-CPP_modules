#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) 
: AForm("ShrubberyCreationForm", 145, 137, target)
{
	std::cout << "Shrubbery constructor called" << std::endl;
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
: AForm(other)
{
	std::cout << "Shrubbery copy constructor called" << std::endl;
}
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& other)
{
	std::cout << "Shrubbery copy assigment operator called" << std::endl;
	(void)other;
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
	std::cout << "Shrubbery destructor called" << std::endl;
}

const char*	ShrubberyCreationForm::FileErrorException::what() const noexcept
{
	return "File could not be created or opened";
}

void ShrubberyCreationForm::executeAction() const
{
	std::ofstream ofs((getTarget() + "_shrubbery").c_str());
	if (!ofs)
		throw ShrubberyCreationForm::FileErrorException();
	ofs << "          _________\n"
		"       __/         \\__\n"
		"     _/   o   o      \\_\n"
		"    /   o     o   o    \\\n"
		"   /  o   o   o     o    \\\n"
		"   \\    o   o   o   o   /\n"
		"    \\__     o     ____/ \n"
		"       \\___     ___/    \n"
		"           \\___/        \n"
		"            |||         \n"
		"            |||         \n"
		"            |||         \n"
		"           _|||_        \n";
	ofs.close();
}
