/*#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <cassert>

void printDivider(const std::string& title) {
    std::cout << "\n=== " << title << " ===\n" << std::endl;
}

int main() {
    printDivider("1. Basic Creation and Deletion (Polymorphic)");

	AAnimal a_obj; // compiler  error in ex02
    a_obj.makeSound(); //wont work


    AAnimal* a1 = new Dog();
    AAnimal* a2 = new Cat();

    delete a1;
    delete a2;

    printDivider("2. Array of Animals");

    const int N = 6;
    AAnimal* animals[N];

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

#include "AAnimal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

void print_header(const std::string& title) {
    std::cout << "\n\033[1;36m" << std::string(50, '=') << "\033[0m\n";
    std::cout << "\033[1;36m" << title << "\033[0m\n";
    std::cout << "\033[1;36m" << std::string(50, '=') << "\033[0m\n";
}

void test_abstract_class_instantiation() {
    print_header("TEST: ABSTRACT CLASS INSTANTIATION (SHOULD FAIL)");
    
    // Uncommenting the next line should cause compilation error
    // AAnimal animal;  // ❌ Cannot instantiate abstract class
    
    std::cout << "This test confirms AAnimal cannot be instantiated directly ✓\n";
    std::cout << "(If this compiles, something is wrong with your abstract class)\n";
}

void test_polymorphism_with_abstract_base() {
    print_header("TEST: POLYMORPHISM WITH ABSTRACT BASE CLASS");
    
    std::cout << "Creating Dog and Cat through AAnimal pointers...\n";
    AAnimal* dog = new Dog();
    AAnimal* cat = new Cat();
    
    std::cout << "\nTesting polymorphic behavior:\n";
    std::cout << "Dog type: " << dog->getType() << " - Sound: ";
    dog->makeSound();
    
    std::cout << "Cat type: " << cat->getType() << " - Sound: ";
    cat->makeSound();
    
    std::cout << "\nTesting virtual destructors:\n";
    delete dog;
    delete cat;
}

void test_array_of_abstract_type() {
    print_header("TEST: ARRAY OF ABSTRACT TYPE POINTERS");
    
    const int numAnimals = 4;
    AAnimal* animals[numAnimals];
    
    std::cout << "Creating array of Dogs and Cats...\n";
    for (int i = 0; i < numAnimals/2; ++i) {
        animals[i] = new Dog();
    }
    for (int i = numAnimals/2; i < numAnimals; ++i) {
        animals[i] = new Cat();
    }
    
    std::cout << "\nProcessing array polymorphically:\n";
    for (int i = 0; i < numAnimals; ++i) {
        std::cout << "Animal " << i << " (" << animals[i]->getType() << "): ";
        animals[i]->makeSound();
    }
    
    std::cout << "\nCleaning up...\n";
    for (int i = 0; i < numAnimals; ++i) {
        delete animals[i];
    }
}

int main() {
    std::cout << "\033[1;35m" << "CPP04 - EX02: ABSTRACT CLASSES" << "\033[0m\n";
    std::cout << "\033[1;35m" << "===============================" << "\033[0m\n";
    
    // test_abstract_class_instantiation();  // Uncomment to verify compilation fails
    test_polymorphism_with_abstract_base();
    test_array_of_abstract_type();
    
    print_header("ALL TESTS COMPLETED!");
    
    return 0;
}