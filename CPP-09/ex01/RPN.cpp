#include "RPN.hpp"
#include <sstream>
#include <iostream>
#include <climits>
#include <cctype>
#include <stdexcept>

static bool isOperator(const std::string& tok)
{
	return tok.size() == 1 && (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/');
}

static bool isSingleDigit(const std::string& tok)
{
	return tok.size() == 1 && std::isdigit(static_cast<unsigned char>(tok[0]));
}

static int applyOp(char op, int a, int b)
{
	long long	result;

	switch (op)
	{
		case '+':
			result = static_cast<long long>(b) + a;
			break;
		case '-':
			result = static_cast<long long>(b) - a;
			break;
		case '*':
			result = static_cast<long long>(b) * a;
			break;
		case '/':
			if (a == 0)
				throw std::runtime_error("Error");
			result = static_cast<long long>(b) / a;
			break;	
		default:
			throw std::runtime_error("Error");
	}
	if (result > static_cast<long long>(INT_MAX) || result < static_cast<long long>(INT_MIN))
		throw std::runtime_error("Error");
	return static_cast<int>(result);
}

void	RPN::runRPN(std::string arg)
{
	std::stringstream ss(arg);
	std::string token;

	while (ss >> token)
	{
		if (isOperator(token))
		{
			if (_s.size() < 2)
				throw std::runtime_error("Error");
			int a = _s.top();
			_s.pop();
			int b = _s.top();
			_s.pop();
			int result = applyOp(token[0], a, b);
			_s.push(result);
		}
		else if (isSingleDigit(token))
		{
			int value = token[0] - '0';
			_s.push(value);
		}
		else
			throw std::runtime_error("Error");
	}
	if (_s.size() != 1)
		throw std::runtime_error("Error");
	std::cout << _s.top() << std::endl;
}