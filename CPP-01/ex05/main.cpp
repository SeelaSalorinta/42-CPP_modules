#include "Harl.hpp"

int	main(int argc, char **argv)
{
	Harl	harl = Harl();
	if (argc == 1)
	{
		harl.complain("");
		harl.complain("DEBUG");
		harl.complain("INFO");
		harl.complain("WARNING");
		harl.complain("ERROR");
	}
	else
	{
		for (int i = 1; i < argc; i++)
			harl.complain(argv[i]);
	}
	return (0);
}