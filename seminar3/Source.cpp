#include <iostream>
using namespace std;

class Student {
private:
	int code;
	char name[50];
	int* grades;
	int noGrades;
	char* faculty;

public:

	//default constructor
	Student() {
		code = 0;
		this->grades = NULL;
		this->noGrades = 0;
		//this->name = "John Doe";
		strcpy(this->name, "John Doe");
		this->faculty = new char[strlen(faculty) + 1];
		strcpy(this->faculty, faculty);
		// SOOOO WRONG , DONT USE = FOR STRINGS
		//this->faculty = "CSIE";
	}

	Student(int code, char* name, char* faculty) {
		this->noGrades = 0;
		this->grades = NULL;
		strcpy(this->name, name);
		//shadowing		code = code;
		this->code = code;
		this->faculty = new char[strlen(faculty) + 1];
		strcpy(this->faculty, faculty);

	}

	int getCode() {
		return this->code;
	}

	char* getName() {
		return this->name;
	}

	void setFaculty(char* newFaculty) {
		delete[] this->faculty;
		this->faculty = new char[strlen(newFaculty) + 1];
		strcpy(this->faculty, newFaculty);
	}

};

void main() {
	Student s1;
	Student s2(1, "Lilly", "COM");

	cout << "The code is " << s1.getCode() << endl;
	cout << "The code is " << s2.getCode() << endl;

	cout << s1.getName() << endl;
	cout << s2.getName() << endl;

	s2.setFaculty("MAN");
}