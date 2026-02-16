#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

/*int main() {
	// Test correct animals
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	
	i->makeSound(); // should output cat sound
	j->makeSound(); // should output dog sound
	meta->makeSound(); // should output animal sound
	
	// Test wrong animals
	const WrongAnimal* wrongMeta = new WrongAnimal();
	const WrongAnimal* wrongI = new WrongCat();
	
	std::cout << wrongI->getType() << " " << std::endl;
	wrongI->makeSound(); // should output WrongAnimal sound
	wrongMeta->makeSound(); // should output WrongAnimal sound
	
	// Clean up
	delete meta;
	delete j;
	delete i;
	delete wrongMeta;
	delete wrongI;
	
	// Additional tests
	std::cout << "\nAdditional tests:\n";
	Animal animal;
	Dog dog;
	Cat cat;
	
	animal.makeSound();
	dog.makeSound();
	cat.makeSound();
	
	Animal animalCopy(dog);
	std::cout << "animalCopy type: " << animalCopy.getType() << std::endl;
	animalCopy.makeSound();
	
	return 0;
}*/

#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

void print_header(const std::string& title) {
    std::cout << "\n\033[1;36m" << std::string(50, '=') << "\033[0m\n";
    std::cout << "\033[1;36m" << title << "\033[0m\n";
    std::cout << "\033[1;36m" << std::string(50, '=') << "\033[0m\n";
}

void print_subheader(const std::string& subtitle) {
    std::cout << "\n\033[1;33m" << subtitle << "\033[0m\n";
    std::cout << "\033[1;33m" << std::string(subtitle.length(), '-') << "\033[0m\n";
}

void test_basic_polymorphism() {
    print_header("TEST 1: BASIC POLYMORPHISM WITH VIRTUAL FUNCTIONS");
    
    print_subheader("Creating animals through base pointers");
    const Animal* generic = new Animal();
    const Animal* dog = new Dog();
    const Animal* cat = new Cat();
    
    print_subheader("Testing getType() method");
    std::cout << "Generic animal type: " << generic->getType() << std::endl;
    std::cout << "Dog type: " << dog->getType() << std::endl;
    std::cout << "Cat type: " << cat->getType() << std::endl;
    
    print_subheader("Testing makeSound() - POLYMORPHISM IN ACTION!");
    std::cout << "Generic animal sound: ";
    generic->makeSound();
    std::cout << "Dog sound: ";
    dog->makeSound();
    std::cout << "Cat sound: ";
    cat->makeSound();
    
    print_subheader("Cleaning up - VIRTUAL DESTRUCTORS WORKING");
    delete generic;
    delete dog;
    delete cat;
}

void test_wrong_polymorphism() {
    print_header("TEST 2: WHAT HAPPENS WITHOUT VIRTUAL FUNCTIONS");
    
    print_subheader("Creating WrongAnimals (no virtual makeSound)");
    const WrongAnimal* wrongGeneric = new WrongAnimal();
    const WrongAnimal* wrongCat = new WrongCat();
    
    print_subheader("Testing getType() method");
    std::cout << "WrongGeneric type: " << wrongGeneric->getType() << std::endl;
    std::cout << "WrongCat type: " << wrongCat->getType() << std::endl;
    
    print_subheader("Testing makeSound() - NO POLYMORPHISM!");
    std::cout << "Notice: Both will use WrongAnimal::makeSound() because\n";
    std::cout << "makeSound() is not virtual in WrongAnimal class!\n";
    std::cout << "WrongGeneric sound: ";
    wrongGeneric->makeSound();
    std::cout << "WrongCat sound: ";
    wrongCat->makeSound();
    
    print_subheader("Cleaning up");
    delete wrongGeneric;
    delete wrongCat;
}

void test_stack_objects() {
    print_header("TEST 3: STACK OBJECTS AND DIRECT CALLS");
    
    print_subheader("Creating objects on stack");
    Animal animal;
    Dog dog;
    Cat cat;
    
    print_subheader("Direct method calls (no polymorphism needed)");
    std::cout << "Animal type: " << animal.getType() << " - Sound: ";
    animal.makeSound();
    std::cout << "Dog type: " << dog.getType() << " - Sound: ";
    dog.makeSound();
    std::cout << "Cat type: " << cat.getType() << " - Sound: ";
    cat.makeSound();
}

void test_copy_constructor() {
    print_header("TEST 4: COPY CONSTRUCTORS AND OBJECT SLICING");
    
    print_subheader("Creating original objects");
    Dog originalDog;
    Cat originalCat;
    
    print_subheader("Using copy constructors");
    Dog copiedDog(originalDog);
    Cat copiedCat(originalCat);
    Animal animalFromDog(originalDog); // Object slicing!
    
    print_subheader("Testing copied objects");
    std::cout << "Copied dog type: " << copiedDog.getType() << " - Sound: ";
    copiedDog.makeSound();
    std::cout << "Copied cat type: " << copiedCat.getType() << " - Sound: ";
    copiedCat.makeSound();
    
    print_subheader("Demonstrating object slicing");
    std::cout << "Animal copied from dog type: " << animalFromDog.getType() << " - Sound: ";
    animalFromDog.makeSound();
    std::cout << "Note: animalFromDog is now just an Animal, not a Dog!\n";
}

void test_assignment_operator() {
    print_header("TEST 5: ASSIGNMENT OPERATORS");
    
    print_subheader("Creating animals");
    Animal animal1, animal2;
    Dog dog1, dog2;
    Cat cat1, cat2;
    
    print_subheader("Testing assignment between same types");
    animal2 = animal1;
    dog2 = dog1;
    cat2 = cat1;
    
    std::cout << "Assignment between same types completed successfully\n";
    
    print_subheader("Testing cross-type assignment (object slicing)");
    Animal animalFromDog;
    animalFromDog = dog1; // Only Animal part gets copied
    
    std::cout << "Animal assigned from dog type: " << animalFromDog.getType() << " - Sound: ";
    animalFromDog.makeSound();
    std::cout << "Note: Only the Animal part was copied (object slicing)\n";
}

void test_virtual_destructor_importance() {
    print_header("TEST 6: VIRTUAL DESTRUCTOR DEMONSTRATION");
    
    print_subheader("Creating animals with virtual destructors");
    Animal* animal = new Dog();
    std::cout << "Created Dog through Animal pointer\n";
    std::cout << "Deleting through Animal pointer (VIRTUAL DESTRUCTOR):\n";
    delete animal; // Should call both ~Dog() and ~Animal()
    
    print_subheader("Creating WrongAnimals without virtual destructors");
    WrongAnimal* wrongAnimal = new WrongCat();
    std::cout << "Created WrongCat through WrongAnimal pointer\n";
    std::cout << "Deleting through WrongAnimal pointer (NON-VIRTUAL DESTRUCTOR):\n";
    delete wrongAnimal; // Will only call ~WrongAnimal()
}

int main() {
    std::cout << "\033[1;35m" << "CPP04 - EX00: POLYMORPHISM DEMONSTRATION" << "\033[0m\n";
    std::cout << "\033[1;35m" << "==========================================" << "\033[0m\n";
    
    test_basic_polymorphism();
    test_wrong_polymorphism();
    test_stack_objects();
    test_copy_constructor();
    test_assignment_operator();
    test_polymorphic_array();
    test_virtual_destructor_importance();
    
    print_header("ALL TESTS COMPLETED!");

    return 0;
}