#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

#include <iostream>
#include <string>

#define RESET "\033[0m"
#define BOLD  "\033[1m"
#define TITLE_COLOR "\033[35m"

static void title(const std::string& t)
{
	std::cout << "\n" << TITLE_COLOR << BOLD << "=== " << t << " ===" << RESET << "\n";
}

int main()
{
	title("Setup: bureaucrats & forms");
	Bureaucrat boss("Boss", 5);
	Bureaucrat senior("Senior", 72);
	Bureaucrat intern("Intern", 150);

	ShrubberyCreationForm shrub("home");
	RobotomyRequestForm   robo("myrobo");
	PresidentialPardonForm pardon("mypardon");

	std::cout << boss << "\n" << senior << "\n" << intern << "\n";
	std::cout << shrub << "\n" << robo << "\n" << pardon << "\n";

	title("Execute before signing (should fail: not signed)");
	boss.executeForm(shrub);
	boss.executeForm(robo);
	boss.executeForm(pardon);

	title("Signing attempts (some fail, some succeed)");
	intern.signForm(shrub);
	senior.signForm(shrub);
	senior.signForm(robo);
	senior.signForm(pardon);
	boss.signForm(pardon);

	title("Check that files have been actually signed");
	std::cout << shrub << "\n" << robo << "\n" << pardon << "\n";

	title("Execute with various grades");
	senior.executeForm(shrub);
	senior.executeForm(robo);
	boss.executeForm(robo);
	intern.executeForm(pardon);
	boss.executeForm(pardon);

	title("Robotomy randomness demo (run multiple times)");
	for (int i = 0; i < 10; ++i) {
		boss.executeForm(robo);
	}

	title("the destructors are called");

	return 0;
}
