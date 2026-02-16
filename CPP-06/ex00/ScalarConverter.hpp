#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <cerrno>
#include <cmath>
#include <limits>
#include <climits>
#include <cctype>

class ScalarConverter
{
	public:
		ScalarConverter() = delete;
		ScalarConverter(const ScalarConverter& other) = delete;
		ScalarConverter&	operator=(const ScalarConverter& other) = delete;
		~ScalarConverter() = delete;

		static void	convert(std::string const& input);
};
