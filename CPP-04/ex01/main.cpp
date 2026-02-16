#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <cassert>


/*void printDivider(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n" << std::endl;
}

int main() {
    printDivider("1. Basic Creation and Deletion (Polymorphic)");


	Animal a_obj; // ✅ allowed in ex01
    a_obj.makeSound(); // generic animal sound
	
    Animal* a1 = new Dog();
    Animal* a2 = new Cat();

    delete a1;
    delete a2;

    printDivider("2. Array of Animals");

    const int N = 6;
    Animal* animals[N];

    for (int i = 0; i < N / 2; ++i)
        animals[i] = new Dog();
    for (int i = N / 2; i < N; ++i)
        animals[i] = new Cat();

    for (int i = 0; i < N; ++i)
        animals[i]->makeSound();

    for (int i = 0; i < N; ++i)
        delete animals[i];

    printDivider("3. Deep Copy Constructor");

    Dog dog1;
    dog1.makeSound();

    dog1.getBrain()->setIdea(0, "Chase the cat!");
    dog1.getBrain()->setIdea(1, "Eat dinner");

    Dog dog2 = dog1; // Copy constructor

    std::cout << "Dog2 idea[0]: " << dog2.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2 idea[1]: " << dog2.getBrain()->getIdea(1) << std::endl;

    // Change dog1 idea and check dog2 doesn't change
    dog1.getBrain()->setIdea(0, "Sleep all day");

    std::cout << "Dog1 idea[0] (changed): " << dog1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Dog2 idea[0] (should be unchanged): " << dog2.getBrain()->getIdea(0) << std::endl;

    printDivider("4. Assignment Operator Test");

    Cat cat1;
    cat1.getBrain()->setIdea(0, "Scratch sofa");
    cat1.getBrain()->setIdea(1, "Stare at nothing");

    Cat cat2;
    cat2 = cat1;

    std::cout << "Cat2 idea[0]: " << cat2.getBrain()->getIdea(0) << std::endl;
    std::cout << "Cat2 idea[1]: " << cat2.getBrain()->getIdea(1) << std::endl;

    cat1.getBrain()->setIdea(0, "Sleep on laptop");

    std::cout << "Cat1 idea[0] (changed): " << cat1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Cat2 idea[0] (should be unchanged): " << cat2.getBrain()->getIdea(0) << std::endl;

    return 0;
}*/

void print_header(const std::string& title) {
    std::cout << "\n\033[1;36m" << std::string(60, '=') << "\033[0m\n";
    std::cout << "\033[1;36m" << title << "\033[0m\n";
    std::cout << "\033[1;36m" << std::string(60, '=') << "\033[0m\n";
}

void test_basic_creation() {
    print_header("TEST 1: BASIC CREATION AND POLYMORPHIC DELETION");
    
    std::cout << "Creating Dog through Animal pointer...\n";
    Animal* dog = new Dog();
    std::cout << "Creating Cat through Animal pointer...\n";
    Animal* cat = new Cat();
    
    std::cout << "\nTesting sounds:\n";
    std::cout << "Dog: ";
    dog->makeSound();
    std::cout << "Cat: ";
    cat->makeSound();
    
    std::cout << "\nDeleting (should call proper destructors thanks to virtual)...\n";
    delete dog;
    delete cat;
}

void test_array_of_animals() {
    print_header("TEST 2: ARRAY OF ANIMALS WITH BRAINS");
    
    const int numAnimals = 4;
    Animal* animals[numAnimals];
    
    std::cout << "Creating array with 2 Dogs and 2 Cats...\n";
    for (int i = 0; i < numAnimals/2; ++i) {
        animals[i] = new Dog();
    }
    for (int i = numAnimals/2; i < numAnimals; ++i) {
        animals[i] = new Cat();
    }
    
    std::cout << "\nMaking sounds:\n";
    for (int i = 0; i < numAnimals; ++i) {
        std::cout << "Animal " << i << ": ";
        animals[i]->makeSound();
    }
    
    std::cout << "\nCleaning up array (testing virtual destructors)...\n";
    for (int i = 0; i < numAnimals; ++i) {
        delete animals[i];
    }
}

void test_deep_copy_constructor() {
    print_header("TEST 3: DEEP COPY CONSTRUCTOR");
    
    std::cout << "Creating original Dog...\n";
    Dog original;
    original.getBrain()->setIdea(0, "Chase the cat!");
    original.getBrain()->setIdea(1, "Eat dinner");
    
    std::cout << "Creating copy using copy constructor...\n";
    Dog copy = original;  // Copy constructor
    
    std::cout << "\nOriginal ideas: " << original.getBrain()->getIdea(0) 
              << ", " << original.getBrain()->getIdea(1) << std::endl;
    std::cout << "Copy ideas: " << copy.getBrain()->getIdea(0) 
              << ", " << copy.getBrain()->getIdea(1) << std::endl;
    
    // Test that they're different objects
    std::cout << "\nModifying original...\n";
    original.getBrain()->setIdea(0, "Sleep all day");
    
    std::cout << "Original idea[0]: " << original.getBrain()->getIdea(0) << std::endl;
    std::cout << "Copy idea[0] (should be unchanged): " << copy.getBrain()->getIdea(0) << std::endl;
    
    // Test memory addresses are different (proves deep copy)
    std::cout << "\nMemory addresses:\n";
    std::cout << "Original brain: " << original.getBrain() << std::endl;
    std::cout << "Copy brain: " << copy.getBrain() << std::endl;
    std::cout << "Are they different? " << (original.getBrain() != copy.getBrain() ? "YES ✓" : "NO ✗") << std::endl;
}

void test_deep_assignment_operator() {
    print_header("TEST 4: DEEP ASSIGNMENT OPERATOR");
    
    std::cout << "Creating two Cats...\n";
    Cat cat1;
    Cat cat2;
    
    cat1.getBrain()->setIdea(0, "Scratch the sofa");
    cat1.getBrain()->setIdea(1, "Stare at nothing");
    
    std::cout << "Before assignment:\n";
    std::cout << "Cat1 ideas: " << cat1.getBrain()->getIdea(0) << ", " << cat1.getBrain()->getIdea(1) << std::endl;
    std::cout << "Cat2 ideas: " << cat2.getBrain()->getIdea(0) << ", " << cat2.getBrain()->getIdea(1) << std::endl;
    
    std::cout << "\nPerforming assignment (cat2 = cat1)...\n";
    cat2 = cat1;
    
    std::cout << "After assignment:\n";
    std::cout << "Cat1 ideas: " << cat1.getBrain()->getIdea(0) << ", " << cat1.getBrain()->getIdea(1) << std::endl;
    std::cout << "Cat2 ideas: " << cat2.getBrain()->getIdea(0) << ", " << cat2.getBrain()->getIdea(1) << std::endl;
    
    // Test deep copy
    std::cout << "\nModifying cat1...\n";
    cat1.getBrain()->setIdea(0, "Sleep on laptop");
    
    std::cout << "Cat1 idea[0]: " << cat1.getBrain()->getIdea(0) << std::endl;
    std::cout << "Cat2 idea[0] (should be unchanged): " << cat2.getBrain()->getIdea(0) << std::endl;
    
    std::cout << "Memory addresses different? " << (cat1.getBrain() != cat2.getBrain() ? "YES ✓" : "NO ✗") << std::endl;
}

void test_brain_functionality() {
    print_header("TEST 5: BRAIN FUNCTIONALITY");
    
    std::cout << "Creating Brain...\n";
    Brain brain;
    
    std::cout << "Setting ideas...\n";
    for (int i = 0; i < 5; ++i) {
        brain.setIdea(i, "Idea number " + std::to_string(i));
    }
    
    std::cout << "Retrieving ideas:\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "Idea " << i << ": " << brain.getIdea(i) << std::endl;
    }
    
    // Test bounds checking
    std::cout << "\nTesting bounds checking:\n";
    std::cout << "Idea at index -1: '" << brain.getIdea(-1) << "' (should be empty)\n";
    std::cout << "Idea at index 100: '" << brain.getIdea(100) << "' (should be empty)\n";
}

int main() {
    std::cout << "\033[1;35m" << "CPP04 - EX01: DEEP COPY AND COMPOSITION" << "\033[0m\n";
    std::cout << "\033[1;35m" << "========================================" << "\033[0m\n";
    
    test_basic_creation();
    test_array_of_animals();
    test_deep_copy_constructor();
    test_deep_assignment_operator();
    test_brain_functionality();
    
    print_header("ALL TESTS COMPLETED!");
    return 0;
}