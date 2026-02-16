#ifndef AFORM_HPP
# define AFORM_HPP

#include <iostream>
#include <string>
#include <exception>

class Bureaucrat;

class AForm
{
	private:
		std::string const	_name;
		bool				_isSigned;
		int const			_gradeToSign;
		int const			_gradeToExecute;
		std::string const	_target;

		static void	checkGradeBounds(int grade);

	public:
		AForm() = delete;
		AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target);
		AForm(const AForm& other) = default;
		AForm&	operator=(const AForm& other) = delete;
		virtual ~AForm() = default;

		virtual void	executeAction() const = 0;

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
		class FormNotSignedException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};

		const std::string&	getName() const;
		bool				getIsSigned() const;
		int					getGradeToSign() const;
		int					getGradeToExecute() const;
		const std::string&	getTarget() const;

		void	beSigned(const Bureaucrat& bureaucrat);
		void	execute(Bureaucrat const& executor) const;
};

std::ostream&	operator<<(std::ostream& out, const AForm& form);

#endif