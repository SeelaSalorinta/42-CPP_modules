#include "ScalarConverter.hpp"

static bool isChar = false;
static bool isInt = false;
static bool isFloat = false;
static bool isDouble = false;
static double value = 0.0;

static char		convertToChar() { return static_cast<char>(value); }
static int		convertToInt() { return static_cast<int>(value); }
static float	convertToFloat() { return static_cast<float>(value); }

static void	printPseudoLiterals(double v)
{
	if (std::isnan(v)) {
		std::cout << "nan";
		return;
	}
	if (v == INFINITY) {
		std::cout << "+inf";
		return;
	}
	if (v == -INFINITY) {
		std::cout << "-inf";
		return;
	}
}

static void	printInfo()
{
	std::cout << "char: ";
	if (!isChar)
		std::cout << "impossible" << std::endl;
	else if (!std::isprint(static_cast<int>(value)))
		std::cout << "Non displayable" << std::endl;
	else {
		std::cout << "'" << convertToChar() << "'" << std::endl;
	}

	std::cout << "int: ";
	if (!isInt
		|| value < static_cast<double>(INT_MIN)
		|| value > static_cast<double>(INT_MAX)) {
		std::cout << "impossible" << std::endl;
	}
	else {
		std::cout << convertToInt() << std::endl;
	}

	std::cout << "float: ";
	if (!isFloat)
		std::cout << "impossible" << std::endl;
	else if (std::isnan(value) || std::isinf(value)) {
		printPseudoLiterals(value);
		std::cout << "f" << std::endl;
	}
	else {
		float f = convertToFloat();
		if (std::isinf(f)) {
			std::cout << "impossible" << std::endl;
		} else {
			std::cout.setf(std::ios::fixed);
			std::cout.precision(1);
			std::cout << f << "f" << std::endl;
			std::cout.unsetf(std::ios::fixed);
		}
	}

	std::cout << "double: ";
	if (!isDouble)
		std::cout << "impossible" << std::endl;
	else if (std::isnan(value) || std::isinf(value)) {
		printPseudoLiterals(value);
		std::cout << std::endl;
	}
	else {
		std::cout.setf(std::ios::fixed);
		std::cout.precision(1);
		std::cout << value << std::endl;
		std::cout.unsetf(std::ios::fixed);
	}
}

static void	reset()
{
	isChar = isInt = isFloat = isDouble = false;
	value = 0.0;
}

static bool	handlePseudoLiteral(std::string const& input)
{
	if (input == "nan" || input == "nanf") {
		reset();
		value = std::numeric_limits<double>::quiet_NaN();
		isFloat = isDouble = true;
		return true;
	}
	if (input == "inf" || input == "+inf" 
		|| input == "inff" || input == "+inff") {
		reset();
		value = INFINITY;
		isFloat = isDouble = true;
		return true;
	}
	if (input == "-inf" || input == "-inff") {
		reset();
		value = -INFINITY;
		isFloat = isDouble = true;
		return true;
	}
	return false;
}

static bool	handleCharLiteral(std::string const& input)
{
	if (input.size() == 1 && !std::isdigit(static_cast<unsigned char>(input[0]))) {
		reset();
		value = static_cast<unsigned char>(input[0]);
		isChar = isInt = isFloat = isDouble = true;
		return true;
	}
	return false;
}

static bool	handleIntLiteral(std::string const& input)
{
	errno = 0;
	char *endp = 0;
	long li = std::strtol(input.c_str(), &endp, 10);
	if (errno == ERANGE || !endp || *endp != '\0')
		return false;
	if (li < static_cast<long>(INT_MIN) || li > static_cast<long>(INT_MAX))
		return false;
	reset();
	value = static_cast<double>(li);
	isInt = isFloat = isDouble = true;
	isChar = (value >= -128.0 && value <= 127.0);
	return true;
}

static bool	handleFloatLiteral(std::string const& input)
{
	if (input.size() <= 1 || input[input.size() - 1] != 'f')
		return false;
	std::string core = input.substr(0, input.size() - 1);
	errno = 0;
	char *end = 0;
	double v = std::strtod(core.c_str(), &end);
	if (!end || *end != '\0')
		return false;
	if (errno == ERANGE) {
		reset();
		return true;
	}
	reset();
	value = v;
	isFloat = isDouble = true;
	isInt = (value >= static_cast<double>(INT_MIN)
		&& value <= static_cast<double>(INT_MAX));
	isChar = (value >= -128.0 && value <= 127.0);
	return true;
}

static bool	handleDoubleLiteral(std::string const& input)
{
	errno = 0;
	char *end = 0;
	double v = std::strtod(input.c_str(), &end);
	if (!end || *end != '\0')
		return false;
	if (errno == ERANGE) {
		reset();
		return true;
	}
	reset();
	value = v;
	isDouble = isFloat  = true;
	isInt = (value >= static_cast<double>(INT_MIN)
		&& value <= static_cast<double>(INT_MAX));
	isChar = (value >= -128.0 && value <= 127.0);
	return true;
}

void ScalarConverter::convert(std::string const& input)
{
	reset();

	if (input.empty()) {
		printInfo();
		return;
	}
	if (handlePseudoLiteral(input)) {
		printInfo();
		return;
	}
	if (handleCharLiteral(input)) {
		printInfo();
		return;
	}
	if (handleIntLiteral(input)) {
		printInfo();
		return;
	}
	if (handleFloatLiteral(input)) {
		printInfo();
		return;
	}
	if (handleDoubleLiteral(input)) {
		printInfo();
		return;
	}
	printInfo();
}