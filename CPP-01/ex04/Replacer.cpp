#include "Replacer.hpp"

Replacer::Replacer(std::string filename, std::string s1, std::string s2) : _filename(filename), _s1(s1), _s2(s2) {}

Replacer::~Replacer() {}

bool	Replacer::replaceString()
{
	std::ifstream input(_filename);
	if (!input.is_open())
	{
		std::cerr << "Error: Could not open input file. Needs read permissions." << std::endl;
		return (false);
	}
	std::ofstream output(_filename + ".replace");
	if (!output.is_open())
	{
		std::cerr << "Error: Could not create output file." << std::endl;
		return (false);
	}
	std::string	line;
	while (std::getline(input, line)) //like getnextline
	{
		size_t	i = 0;
		while ((i = line.find(_s1, i)) != std::string::npos) //wile it finds s1 then replace, find return index where s1 starts
		{
			line = line.substr(0, i) + _s2 + line.substr(i + _s1.length());
			i += _s2.length();  // Move past the replaced part
		}
		output << line << "\n"; //add new line to outputfile
	}
	return (true);
}