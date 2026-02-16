#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute, const std::string& target) : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute), _target(target)
{
	std::cout << "AForm constructor with parameters called" << std::endl;
	checkGradeBounds(_gradeToSign);
	checkGradeBounds(_gradeToExecute);
}

void	AForm::checkGradeBounds(int grade)
{
	if (grade < 1)
		throw AForm::GradeTooHighException();
	if (grade > 150)
		throw AForm::GradeTooLowException();
}

const char* AForm::GradeTooHighException::what() const noexcept
{
	return "Form grade too high (highest is 1).";
}

const char* AForm::GradeTooLowException::what() const noexcept
{
	return "Form grade too low (lowest is 150) or signer too low.";
}

const char* AForm::AlreadySignedException::what() const noexcept
{
	return "Form is already signed.";
}

const char* AForm::FormNotSignedException::what() const noexcept
{
	return "Form is not signed.";
}

const std::string&	AForm::getName() const
{
	return _name;
}

bool	AForm::getIsSigned() const
{
	return _isSigned;
}

int	AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int	AForm::getGradeToExecute() const
{
	return _gradeToExecute;
}

const std::string& AForm::getTarget() const
{
	return _target;
}

void	AForm::beSigned(const Bureaucrat& bureaucrat)
{
	if (_isSigned)
		throw AForm::AlreadySignedException();
	if (bureaucrat.getGrade() > _gradeToSign)
		throw AForm::GradeTooLowException();
	_isSigned = true;
}

void	AForm::execute(Bureaucrat const& executor) const
{
	if (_isSigned == false)
		throw AForm::FormNotSignedException();
	if (executor.getGrade() > _gradeToExecute)
		throw AForm::GradeTooLowException();
	executeAction();
}

std::ostream&	operator<<(std::ostream& out, const AForm &form)
{
	out << form.getName() << ", form is signed: " << (form.getIsSigned() ? "yes" : "no") << ", grade required to sign is: " << form.getGradeToSign()
		<< ", grade required to execute is: " << form.getGradeToExecute();
	return out;
}