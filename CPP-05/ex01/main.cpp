#include "Bureaucrat.hpp"
#include "Form.hpp"

#define RESET "\033[0m"
#define BOLD  "\033[1m"
#define TITLE_COLOR "\033[33m"

static void title(const std::string& t)
{
	std::cout << "\n" << TITLE_COLOR << BOLD << "=== " << t << " ===" << RESET << "\n";
}

int main()
{
	title("Setup");
	Bureaucrat	b("Boss", 5);
	Form		travel("Travel Request", 10, 3);

	std::cout << b << std::endl;
	std::cout << travel << std::endl;

	title("Failing to sign (grade too low)");
	try {
		Bureaucrat intern("Intern", 11);
		std::cout << intern << std::endl;
		std::cout << travel << std::endl;
		intern.signForm(travel);
	} catch (std::exception& e) {
		std::cout << "Unexpected: " << e.what() << std::endl;
	}

	title("Successful sign (grade 8 <= 10) + try again");
	try {
		Bureaucrat senior("Senior", 8);
		std::cout << senior << std::endl;
		senior.signForm(travel);
		std::cout << travel << std::endl;

		std::cout << "Try to sign again" << std::endl;
		senior.signForm(travel);
		std::cout << travel << std::endl;
	} catch (std::exception& e) {
		std::cout << "Unexpected: " << e.what() << std::endl;
	}

	title("TEST: equal bureaucrat grade and form grade");
	try {
		Bureaucrat senior("Senior", 10);
		std::cout << senior << std::endl;
		senior.signForm(travel);
		std::cout << travel << std::endl;
	} catch (std::exception& e) {
		std::cout << "Unexpected: " << e.what() << std::endl;
	}

	title("Form constructor bounds: grade to sign < 1 (should throw)");
	try {
		Form badSign("BadSign", 0, 10);
		(void)badSign;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	title("Form constructor bounds: grade to execute > 150 (should throw)");
	try {
		Form badExec("BadExec", 10, 151);
		(void)badExec;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	return 0;
}

