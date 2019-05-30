#include <iostream>
#include <string>
#include <memory>

void makePersonSP(); // Function prototype.
void makePersonUP(); // Function prototype.

class Person // Person class.
{
	public:
		Person(std::string name, int age) { sName = name; iAge = age;} // Constructor of the class.
		std::string sName; // Name to use.
		int iAge; // Age to use.
		void print() { std::cout << sName << " " << iAge << std::endl; } // Print out the name and age of the person.
};

int main()
{
	makePersonSP(); // Run the function.
	makePersonUP(); // Run the function.
	system("pause");
	return 0;
}

void makePersonSP()
{
	/// Using smart pointers.
	std::shared_ptr<Person> sp_personOne(new Person("Charlie", 19)); // Create a new person in a shared pointer. Shared pointers can be owned by multiple pointers.
	std::shared_ptr<Person> sp_personTwo; // Create another shared pointer.
	std::weak_ptr<Person> wp_person;
	wp_person = sp_personOne;
	sp_personOne->print(); // Print name and age.
	sp_personTwo = sp_personOne; // Person Two now owns person one data as well person one. This is allowed because of shared pointer.
	sp_personOne = nullptr; // Set the person one to null.
	sp_personTwo->print(); // Print out the name and age again with person two.
	sp_personTwo = nullptr; // Set the person two to null.
}

void makePersonUP()
{
	std::unique_ptr<Person> up_personOne(new Person("Tom", 21)); // Unique pointer - only can be owned by one of these. They cannot be shared like shared pointers.
	up_personOne->print(); // Print the name and age.
	up_personOne = nullptr; // Set the pointer to null.
}

