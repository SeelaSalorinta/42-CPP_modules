#include "FragTrap.hpp"
#include "ScavTrap.hpp" // Optional: to compare with other derived class
#include "ClapTrap.hpp" // For completeness

int main() {
	std::cout << "=== Creating ClapTrap, ScavTrap and FragTrap ===\n";
	ClapTrap    base("Clappy");
	ScavTrap    guard("Scavy");
	FragTrap    highFiveGuy("Fraggie");

	std::cout << "\n--- Testing unique ability: FragTrap highFivesGuys() ---\n";
	highFiveGuy.highFivesGuys();

	std::cout << "\n--- FragTrap attacks ClapTrap ---\n";
	highFiveGuy.attack("Clappy");         // Should cost 1 energy, do 30 dmg
	base.takeDamage(30);

	std::cout << "\n--- FragTrap repairs itself ---\n";
	highFiveGuy.beRepaired(25);           // Should cost 1 energy, heal 25 HP

	std::cout << "\n--- Exhaust FragTrap's energy ---\n";
	for (int i = 0; i < 100; ++i)
		highFiveGuy.attack("Scavy");     // Uses 100 energy

	std::cout << "\n--- Try to attack and repair with 0 energy ---\n";
	highFiveGuy.attack("Clappy");         // Should fail (0 energy)
	highFiveGuy.beRepaired(10);           // Should fail (0 energy)

	std::cout << "\n--- Take fatal damage ---\n";
	highFiveGuy.takeDamage(200);          // Should reduce HP to 0
	highFiveGuy.attack("Clappy");         // Should fail (0 HP)
	highFiveGuy.beRepaired(5);            // Should fail (0 HP)

	std::cout << "\n=== End of simulation ===\n";
	return 0;
}
