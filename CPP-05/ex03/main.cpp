#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

#include <iostream>
#include <string>

#define RESET "\033[0m"
#define BOLD  "\033[1m"
#define TITLE_COLOR "\033[31m"

static void title(const std::string& t)
{
	std::cout << "\n" << TITLE_COLOR << BOLD << "=== " << t << " ===" << RESET << "\n";
}

int main()
{
	title("Setup: Intern + a couple of bureaucrats");
	Intern		intern;
	Bureaucrat	boss("Boss", 5);
	Bureaucrat	mid("Mid", 50);
	std::cout << boss << "\n" << mid << "\n";

	title("Intern creates known forms");
	AForm*	shrub = 0;
	AForm*	robo = 0;
	AForm*	pardon = 0;

	try { shrub = intern.makeForm("shrubbery creation", "home");}
	catch (std::exception& e) { std::cout << "Create shrub failed: " << e.what() << "\n"; }
	try { robo = intern.makeForm("robotomy request", "Bender");}
	catch (std::exception& e) { std::cout << "Create robo failed: " << e.what() << "\n"; }
	try { pardon = intern.makeForm("presidential pardon", "FormX");}
	catch (std::exception& e) { std::cout << "Create pardon failed: " << e.what() << "\n"; }

	title("Intern rejects unknown form name");
	try {
		AForm* nope = intern.makeForm("form 28C", "Nobody");
		delete nope;
	} catch (std::exception& e) {
		std::cout << "Intern couldn't create: " << e.what() << "\n";
	}

	title("Sign & execute the forms created by the intern");
	if (shrub)
	{
		mid.signForm(*shrub);
		mid.executeForm(*shrub);
	}
	if (robo)
	{
		mid.signForm(*robo);
		boss.executeForm(*robo);
	}
	if (pardon)
	{
		boss.signForm(*pardon);
		boss.executeForm(*pardon);
	}

	title("Cleanup");
	delete shrub;
	delete robo;
	delete pardon;

	return 0;
}