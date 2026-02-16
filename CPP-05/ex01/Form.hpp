#ifndef FORM_HPP
# define FORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class Form
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_gradeToSign;
		int const			_gradeToExecute;

		static void	checkGradeBounds(int grade);

	public:
		Form();
		Form(const std::string& name, int gradeToSign, int gradeToExecute);
		Form(const Form& other);
		Form&	operator=(const Form& other);
		~Form();

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
		class AlreadySignedException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};

		const std::string&	getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;

		void	beSigned(const Bureaucrat& bureaucrat);
};

std::ostream&	operator<<(std::ostream& out, const Form& form);

#endif