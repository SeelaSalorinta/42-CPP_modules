#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form() : _name("DefaultF"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150)
{
	std::cout << "Form default constructor called" << std::endl;
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute) : _name(name),  _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	std::cout << "Form constructor with parameters called" << std::endl;
	checkGradeBounds(_gradeToSign);
	checkGradeBounds(_gradeToExecute);
}

Form::Form(const Form& other) : _name(other._name), _isSigned(other._isSigned), _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute)
{
	std::cout << "Form copy constructor called" << std::endl;
}

Form&	Form::operator=(const Form& other)
{
	std::cout << "Form copy assignment operator called" << std::endl;
	if (this != &other)
	{
		_isSigned = other._isSigned;
	}
	return *this;
}

Form::~Form()
{
	std::cout << "Form destructor called" << std::endl;
}

const char* Form::GradeTooHighException::what() const noexcept
{
	return "Form grade too high (min is 1).";
}

const char* Form::GradeTooLowException::what() const noexcept
{
	return "Form grade too low (max is 150) or signer too low.";
}

const char* Form::AlreadySignedException::what() const noexcept
{
	return "Form is already signed.";
}

void	Form::checkGradeBounds(int grade)
{
	if (grade < 1)
		throw Form::GradeTooHighException();
	if (grade > 150)
		throw Form::GradeTooLowException();
}

const std::string&	Form::getName() const
{
	return _name;
}

bool	Form::getIsSigned() const
{
	return _isSigned;
}

int	Form::getGradeToSign() const
{
	return _gradeToSign;
}

int	Form::getGradeToExecute() const
{
	return _gradeToExecute;
}

void	Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (_isSigned)
		throw Form::AlreadySignedException();
	if (bureaucrat.getGrade() > _gradeToSign)
		throw Form::GradeTooLowException();
	_isSigned = true;
}

std::ostream&	operator<<(std::ostream& out, const Form &form)
{
	out << form.getName() << ", form is signed: " << (form.getIsSigned() ? "yes" : "no") << ", grade required to sign is: " << form.getGradeToSign()
		<< ", grade required to execute is: " << form.getGradeToExecute();
	return out;
}