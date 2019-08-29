#include <iostream>
using namespace std;

class Person {
	char* name;
	int age;
public:
	Person(char* Name, int Age) {
		this->age = Age;
		name = new char[strlen(Name) + 1];
		strcpy(name, Name);
	}

	~Person() { //destructor
		delete[] name;
	}

	Person(Person& p) { //copy constructor
		this->age = p.age;
		name = new char[strlen(p.name) + 1];
		strcpy(name, p.name);
	}

	int getAge() {
		return this->age;
	}
	char* getName() {
		return this->name;
	}
	void setName(char* newName) { //rename
		delete[] name;
		name = new char[strlen(newName) + 1];
		strcpy(name, newName);
	}
};

void main() {
	//Person p;
	Person p1("John", 21);
	p1.setName("Mike");

	Person *p2; // ONLY A POINTER
	p2 = &p1;
	p2 = new Person("Alice", 21); // de abia aici the person has been created

								  // define an array of Persons
	int values[100];
	int* values2 = new int[100];

	//Person persons[100];  //it wont work because we dont have the default constructor
	//Person *persons = new Person[100]; // it doesnt work with static arrays (adding persons when we dont have all their values
	int n = 10;
#define N 100;

	//int test[n];
	int *test2 = new int[n];


	Person**persons = new Person*[100];

	persons[0] = new Person("First person", 20);
	persons[1] = new Person("Second person", 20);

	delete[] persons[0];
	delete[] persons[1];
	delete[] persons;
	persons = new Person*[200];
}