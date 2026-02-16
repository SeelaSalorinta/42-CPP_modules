#include "Bureaucrat.hpp"
#include <iostream>
#include <string>

#define RESET "\033[0m"
#define BOLD  "\033[1m"
#define TITLE_COLOR "\033[36m"

static void title(const std::string& t) {
	std::cout << "\n" << TITLE_COLOR << BOLD << "=== " << t << " ===" << RESET << "\n";
}

int main() {
	title("Basic increment/decrement");
	try {
		Bureaucrat basic("Basic", 3);
		std::cout << "basic: " << basic << std::endl;
		basic.incrementGrade();
		std::cout << "after increment: " << basic << std::endl;
		basic.decrementGrade();
		std::cout << "after decrement: " << basic << std::endl;
	} catch (std::exception& e) {
		std::cout << "Unexpected error: " << e.what() << std::endl;
	}

	title("Construct with too high grade (0) — should throw");
	try {
		Bureaucrat badHigh("badHigh", 0);
		std::cout << "badHigh: " << badHigh << std::endl;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	title("Construct with too low grade (151) — should throw");
	try {
		Bureaucrat badLow("badLow", 151);
		std::cout << "badlow: " << badLow << std::endl;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	title("Increment at top grade (1) — should throw");
	try {
		Bureaucrat top("CannotIncrement", 1);
		std::cout << "Top: " << top << std::endl;
		top.incrementGrade();
		std::cout << "after increment: " << top << std::endl;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	title("Decrement at lowest grade (150) — should throw");
	try {
		Bureaucrat low("CannotDecrement", 150);
		std::cout << "low: " << low << std::endl;
		low.decrementGrade();
		std::cout << "after decrement: " << low << std::endl;
	} catch (std::exception& e) {
		std::cout << "Caught: " << e.what() << std::endl;
	}

	title("Copy constructor & assignment");
	try {
		Bureaucrat seela("Seela", 10);
		std::cout << seela << std::endl;

		Bureaucrat copy(seela);
		std::cout << "Copy: " << copy << std::endl;

		Bureaucrat scorpio("Scorpio", 50);
		std::cout << "scorpio: " << scorpio << std::endl;
		scorpio = seela;
		std::cout << "Name should not change: " << scorpio << std::endl;
	} catch (std::exception& e) {
		std::cout << "Unexpected error: " << e.what() << std::endl;
	}
	return 0;
}
