#include<iostream>
#include<string>
using namespace std;


class Person {
public:
	Person(string n, int a) { sName = n; iAge = a; };
	string sName;
	int iAge;
	void print() { cout << sName << " " << iAge << endl; };

	void MakePerson() {
		unique_ptr<Person> personOne(new Person("Charlie", 19));
		unique_ptr<Person> personTwo(new Person("Tom", 21));
		personOne->print();
		personTwo->print();
	}


};


int main()
{
	Person pone("a", 2);
	pone.MakePerson();
	system("pause");
	return 0;
}

