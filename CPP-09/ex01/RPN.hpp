#pragma once

#include <stack>
#include <string>

class RPN
{
	private:
		std::stack<int> _s;

	public:
		RPN() = default;
		RPN(const RPN& other) = default;
		RPN&	operator=(const RPN& other) = default;
		~RPN() = default;

		void	runRPN(std::string arg);
};
