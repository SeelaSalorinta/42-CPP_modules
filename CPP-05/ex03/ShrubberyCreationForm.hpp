#ifndef SHRUBBERYCREATIONFORM_HPP
# define SHRUBBERYCREATIONFORM_HPP

#include "AForm.hpp"
#include <string>
#include <fstream>
#include <exception>

class ShrubberyCreationForm : public AForm
{
	protected:
		void	executeAction() const;

	public:
		explicit ShrubberyCreationForm(const std::string& target);
		ShrubberyCreationForm(const ShrubberyCreationForm& other);
		ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
		~ShrubberyCreationForm();

		class FileErrorException : public std::exception
		{
			public:
				const char* what() const noexcept override;
		};
};

#endif
