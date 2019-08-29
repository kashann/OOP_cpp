#include <iostream>

using namespace std;

void main() {
	//static arrays (always in stack)
	int values1[100];
	int values3[10];

	//dynamic (always in heap)
	int* values2;
	values2 = new int[50]; //malloc /-delete //new /-free

	//printing
	values1[0] = 99;
	values1[1] = 98;
	cout << endl << "First 5 values from values1: ";
	for (int i = 0; i < 5; i++)
		cout << " " << values1[i];
	cout << endl << "First 5 values from values2: ";
	for (int i = 0; i < 5; i++)
		cout << " " << values2[i];
	//we have to initialize the array or we will get maximum numbers

	//change the size
	//int values1[101] // errror, its a mistake
	/*values3[10] = 99;
	values3[11] = 99;
	values3[12] = 100;
	values3[13] = 101;

	cout << endl << "First 5 values from values 1: ";
	for (int i = 0; i < 5; i++)
	cout << " " << values1[i];
	cout << endl;*/

	// change the size
	/*for (;;) {
	values2 = new int[51]; //ramul o ia razna si se umple (2gb)
	}*/
	//1 clean-up
	/*for (;;){
	delete [] values2;
	values2 = new int[51]; //memorie stabila in task manager
	}*/
	int *temp = new int[51]; //resizeing a new array
	for (int i = 0; i < 50; i++)
		temp[i] = values2[i];
	delete[] values2;
	values2 = temp;

	//values1 = new int[200]; //nu se poate modifica static array sau sterge
	//delete [] values1;


	//strings
	//static string
	char name[50];
	char name2[] = "Popescu";
	//name2 = "Ionut"; //you cannot do this

	//messing up with the ending \0
	//name2[3] = 0; // '\0'
	//name2[7] = 'i';
	cout << endl << "Person name: " << name2;

	//dynamic string
	char* studentName;
	//studentName = "Ionut"; //NEVER put "=" between 2 strings

	//how to dynamically allocate a string
	studentName = new char[strlen("Ionut") + 1]; //strlen doesnt count the \0
	strcpy(studentName, "Ionut"); //correct way


	cout << endl << "The student name is " << studentName << endl;

	//delete[] studentName;
	//studentName = "Popescu";
	//cout << endl << "The student name is " << studentName;
}