#ifndef REPLACER_HPP
# define REPLACER_HPP

#include <string>
#include <fstream>
#include <iostream>

class Replacer
{
	private:
		std::string	_filename;
		std::string	_s1;
		std::string	_s2;
	
	public:
		Replacer(std::string filename, std::string s1, std::string s2);
		~Replacer();
		bool	replaceString();
};

#endif