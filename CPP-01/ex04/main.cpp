#include "Replacer.hpp"

int	main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cout << "Usage: ./Sed_is_for_losers <filename> <string1> <string2>" << std::endl;
		return (1);
	}
	Replacer myReplacer(argv[1], argv[2], argv[3]);
	if (!myReplacer.replaceString())
		return (1);
	return (0);
}