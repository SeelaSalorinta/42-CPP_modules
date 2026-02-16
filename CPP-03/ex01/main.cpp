#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	std::cout << "=== Creating ClapTrap and ScavTrap ===" << std::endl;
	ClapTrap alice("Alice");
	ScavTrap bob("Bob");

	std::cout << "\n--- Round 1: Alice attacks Bob ---" << std::endl;
	alice.attack("Bob");
	bob.takeDamage(0);  // ClapTrap's default attackDamage is 0

	std::cout << "\n--- Round 2: Bob attacks Alice ---" << std::endl;
	bob.attack("Alice");
	alice.takeDamage(20);  // ScavTrap's attackDamage is 20

	std::cout << "\n--- Round 3: Bob uses guardGate() ---" << std::endl;
	bob.guardGate();

	std::cout << "\n--- Round 4: Alice repairs herself ---" << std::endl;
	alice.beRepaired(5);

	std::cout << "\n--- Round 5: Bob repairs himself ---" << std::endl;
	bob.beRepaired(10);

	std::cout << "\n--- Round 6: Energy exhaustion test ---" << std::endl;
	for (int i = 0; i < 55; i++)
		bob.attack("Alice");  // Bob has 48 energy points, this will exhaust him

	std::cout << "\n--- Round 7: Attempting actions with no energy ---" << std::endl;
	bob.attack("Alice");
	bob.beRepaired(1);

	std::cout << "\n--- Round 8: Fatal damage to Alice ---" << std::endl;
	alice.takeDamage(100);
	alice.attack("Bob");      // Should fail (no HP)
	alice.beRepaired(10);     // Should fail (no HP)

	std::cout << "\n=== End of simulation ===" << std::endl;
	return 0;
}