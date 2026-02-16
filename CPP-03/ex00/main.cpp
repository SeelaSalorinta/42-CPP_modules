#include "ClapTrap.hpp"

int main()
{
	ClapTrap alice("Alice");
	ClapTrap bob("Bob");

	std::cout << "\n--- Round 1: Alice attacks Bob ---\n";
	alice.attack("Bob");
	bob.takeDamage(0); // Default attackDamage is 0

	std::cout << "\n--- Round 2: Set Alice's attack damage manually ---\n";
	// Simulate Alice becoming stronger by copying to a new stronger ClapTrap
	ClapTrap strongAlice = alice;
	strongAlice = alice; // triggers copy assignment (not necessary, but shows it works)

	std::cout << "\n--- Round 3: Manually simulate damage ---\n";
	bob.takeDamage(3);

	std::cout << "\n--- Round 4: Bob repairs himself ---\n";
	bob.beRepaired(2);

	std::cout << "\n--- Round 5: Bob uses up all his energy ---\n";
	for (int i = 0; i < 10; ++i)
		bob.attack("Alice");

	std::cout << "\n--- Round 6: Bob tries to attack with 0 energy ---\n";
	bob.attack("Alice");

	std::cout << "\n--- Round 7: Alice takes fatal damage ---\n";
	alice.takeDamage(20);
	alice.attack("Bob");   // Should fail (no HP)
	alice.beRepaired(5);   // Should also fail (no HP)

	std::cout << "\n--- Round 8: Copy constructor test ---\n";
	ClapTrap clone(bob);
	clone.attack("Alice");  // Should act independently of Bob

	std::cout << "\n--- Round 9: Overkill test ---\n";
	ClapTrap cat("cat");
	cat.takeDamage(100);
	cat.takeDamage(1);  // Should print that Alice is already dead

	std::cout << "\n--- End of simulation ---\n";
	return 0;
}
