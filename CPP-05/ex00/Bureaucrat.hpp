#ifndef BUREAUCRAT_HPP
# define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat
{
	private:
		std::string const	_name;
		int					_grade;

	public:
		Bureaucrat();
		Bureaucrat(const std::string& name, int grade);
		Bureaucrat(const Bureaucrat& other);
		Bureaucrat&	operator=(const Bureaucrat& other);
		~Bureaucrat();

		class GradeTooLowException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};
		class GradeTooHighException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};

		const std::string&	getName() const;
		int					getGrade() const;

		void	incrementGrade();
		void	decrementGrade();
};

std::ostream&	operator<<(std::ostream& out, const Bureaucrat &bureaucrat);

#endif