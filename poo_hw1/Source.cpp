#include <iostream>
using namespace std;

class Student{
	char name[50];
	char gender;
	int* grades;
	int noGrades;
	int code;
	char* address;
public:

	//default constructor
	Student(){ //1
		strcpy(this->name, "Alan Turing");
		gender = 'm';
		grades = NULL;
		noGrades = 0;
		code = 0;
		this->address = new char[strlen("Str Caderea Bastiliei Bucuresti") + 1];
		strcpy(this->address, "Str Caderea Bastiliei Bucuresti");
	}
	

	//constructor with arguments - at least 3 different versions  (different combination of needed arguments)
	//...
	Student(char* name, int code, char* address){ //2
		strcpy(this->name, name);
		gender = 'm';
		grades = NULL;
		noGrades = 0;
		this->code = code;
		this->address = new char[strlen(address) + 1];
		strcpy(this->address, address);
	}

	Student(char* name, char gender, int code, char* address){ //3
		strcpy(this->name, name);
		this->gender = gender;
		grades = NULL;
		noGrades = 0;
		this->code = code;
	    this->address = new char[strlen(address) + 1];
		strcpy(this->address, address);
	}

	Student(char* name, char gender, int code){ //4
		strcpy(this->name, name);
		this->gender = gender;
		grades = NULL;
		noGrades = 0;
		this->code = code;
		this->address = new char[strlen("Calea Grivitei Brasov") + 1];
		strcpy(this->address, "Calea Grivitei Brasov");
	}

	Student(char* name, char gender, char* address){ //5
		strcpy(this->name, name);
		this->gender = gender;
		grades = NULL;
		noGrades = 0;
		code = 0;
		this->address = new char[strlen(address) + 1];
		strcpy(this->address, address);
	}

	Student(char* name, int code){ //6
		strcpy(this->name, name);
		gender = 'm';
		grades = NULL;
		noGrades = 0;
		this->code = code;
		this->address = new char[strlen("Calea Victoriei Bucuresti") + 1];
		strcpy(this->address, "Calea Victoriei Bucuresti");
	}


	//destructor
	~Student(){
		//free HEAP memory
		delete[] this->grades;
		delete[] this->address;
	}


	//copy constructor
	Student(Student& s){
		strcpy(this->name, s.name);
		this->gender = s.gender;
		this->grades = new int[s.noGrades];
		for (int i = 0; i < s.noGrades; i++)
			this->grades[i] = s.grades[i];
		this->noGrades = s.noGrades;
		this->code = s.code;
		address = new char[strlen(s.address) + 1];
		strcpy(address, s.address);
	}


	void display(){
		//display student data
		cout << endl << "Student name: " << this->name;
		cout << endl << "Gender: " << this->gender;
		cout << endl << "Number of grades: " << this->noGrades;
		if (this->noGrades > 0){
			cout << endl << "Grades: ";
			for (int i = 0; i < this->noGrades; i++)
				cout << this->grades[i] << " ";
		}
		cout << endl << "Code: " << this->code;
		cout << endl << "Address: " << this->address;
		cout << endl;
	}


	//get for all attributes
	//...
	char* getName(){
		return this->name;
	}

	char getGender(){
		return this->gender;
	}

	void getGrades(){
		if (this->noGrades > 0){
			for (int i = 0; i < this->noGrades; i++)
				cout << this->grades[i] << " ";
		}
	}
	
	int getNoGrades(){
		return this->noGrades;
	}
	
	int getCode(){
		return this->code;
	}

	char* getAddress(){
		return this->address;
	}


	//to acces a single grade
	int get(int gradeIndex){
		//validate the index
		if (gradeIndex > 0 && gradeIndex <= this->noGrades)
			return grades[gradeIndex - 1];
	}


	//set methods for all attributes  - must contain at least one validation
	//set for reading student data from console
	//set that will allow initialising the student grades array with an existing one
	//...
	void setName(char* newName){
		if (strlen(newName) <= 50)
			strcpy(this->name, newName);
		else
			cout << "Failed! The name is larger than 50 chars!";
	}

	void setGender(char newGender){
		if (newGender == 'm' || newGender == 'M' || newGender == 'f' || newGender == 'F')
			this->gender = newGender;
		else
			cout << endl << "Failed! We do not accept other genders than M or F!";
	}
	
	void setGrades(int* grades, int n){
		if (this->grades != NULL)
			delete[] this->grades;
		this->grades = new int[n];
		for (int i = 0; i < n; i++){
			this->grades[i] = grades[i];
		}
		this->noGrades = n;
	}
	
	void setCode(int newCode){
		if (newCode <= 9999)
			this->code = newCode;
		else
			cout << endl << "Failed! The code exceeds 4 digits!";
	}

	void setAddress(char* newAddress){
		if (newAddress != "Mars" && newAddress != "Moon" && newAddress != "Venus"){
			delete[] this->address;
			this->address = new char[strlen(newAddress) + 1];
			strcpy(this->address, newAddress);
		}
		else
			cout << endl << "Aliens are not allowed in terestrial education system!";
	}

	void setConsole(){
		cout << endl;

		cout << "Address: ";
		char newAddress[100];
		cin.getline(newAddress, 100);
		setAddress(newAddress);

		cout << "Name: ";
		gets(this->name);
		cout << "Gender: ";
		char newGender;
		cin >> newGender;
		while (newGender != 'm' && newGender != 'M' && newGender != 'f' && newGender != 'F'){
			cout << "Failed! We do not accept other genders than M or F!";
			cout << endl << "Gender: ";
			cin >> newGender;
		}
		this->gender = newGender;
		cout << "Number of grades: ";
		cin >> this->noGrades;
		if (this->noGrades > 0){
			this->grades = new int[this->noGrades];
			cout << "Grades: ";
			for (int i = 0; i < this->noGrades; i++)
				cin >> this->grades[i];
		}
		cout << "Code: ";
		int newCode;
		cin >> newCode;
		while (newCode > 9999){
			cout << "Failed! The code exceeds 4 digits! Please try again!";
			cout << endl << "Code: ";
			cin >> newCode;
		}
		this->code = newCode;		
	}

	void initializeGrades(Student& s){
		this->grades = new int[s.noGrades];
		for (int i = 0; i < s.noGrades; i++)
			this->grades[i] = s.grades[i];
		this->noGrades = s.noGrades;
	}


	//mandatory: generic methods for processing student data
	//compute grades average
	float average(){
		float avg = 0;
		for (int i = 0; i < this->noGrades; i++)
			avg += grades[i];
		avg = avg / this->noGrades;
		return avg;
	}


	//add a grade
	void takeExam(int grade){
		int *temp = new int[this->noGrades + 1];
		for (int i = 0; i < noGrades; i++)
			temp[i] = grades[i];
		temp[noGrades] = grade;
		this->grades = temp;
		this->noGrades += 1;
	}


	//check an address - checks if a student lives in a given city
	bool isFromCity(char* city){
		if (strlen(city) > strlen(this->address))
			return false;
		for (int i = 0; i <= strlen(this->address); i++){
			int j = 0;
				while (this->address[i] == city[j] && j < strlen(city)){
					j++;
					i++;
				}
				if (j == strlen(city))
					return true;
		}
		return false;
	}


	//at least 10 other generic data processing methods for a student - other than the set and get functions 
	bool isRepeater(){  //1
		if (average() < 5)
			return true;
		else
			return false;
	}

	void resetGrades(){  //2
		if (isRepeater()){
			delete[] this->grades;
			this->grades = NULL;
			this->noGrades = 0;
		}
	}

	bool scolarship(){  //3
		if (average() == 10)
			return true;
		else
			return false;
	}

	int noFailedExams(){ //4
		int c = 0;
		for (int i = 0; i < this->noGrades; i++)
			if (this->grades[i] < 5)
				c++;
		return c;
	}

	bool integralist(){ //5
		if (noFailedExams())
			return false;
		else
			return true;
	}

	char* getFinancing(){ //6
		if (integralist())
			return "Budget";
		else
			return "Tax";
	}
	
	void removeExam(){ //7
		int *temp = new int[this->noGrades - 1];
		for (int i = 0; i < noGrades - 1; i++)
			temp[i] = grades[i];
		this->grades = temp;
		this->noGrades -= 1;
	}

	void removeAnExam(int gradeIndex){ //8
		int *temp = new int[this->noGrades - 1];
		int j = 0;
		for (int i = 0; i < this->noGrades; i++)
			if(j <= i){
				if (i == gradeIndex - 1)
					i++;
				temp[j] = grades[i];
				j++;
			}
		this->grades = temp;
		this->noGrades -= 1;
	}
	
	void retakeExam(int grade, int gradeIndex){ //9
		if (grade > 0 && grade <= 10 && gradeIndex > 0 && gradeIndex <= this->noGrades)
			this->grades[gradeIndex - 1] = grade;
	}

	void expel(){ //10
		strcpy(this->name, "Alan Turing");
		this->gender = 'm';
		delete[] this->grades;
		this->grades = NULL;
		this->noGrades = 0;
		this->code = 0;
		delete[] address;
		this->address = new char[strlen("Str Caderea Bastiliei Bucuresti") + 1];
		strcpy(this->address, "Str Caderea Bastiliei Bucuresti");
	}

};


void main(){
	//creates default student
	Student student1;
	//test each existing argument based constructor
	//Student student2(....)
	Student student2("Alan", 2, "Bvd Dacia Bucuresti");
	Student student3("Turing", 'm', 3, "Bvd Dorobanti Constanta");
	Student student4("Joan", 'f', 4);
	Student student5("Clarke", 'f', "Str Mihai Eminescu Ploiesti");
	Student student6("Enigma", 6);


	//test copy constructor
	//Student student5 = student4 where student4 already exists
	Student student7 = student6;
	

	//display all previous created students
	student1.display();
	student2.display();
	student3.display();
	student4.display();
	student5.display();
	student6.display();
	student7.display();


	//all implemented methods are tested
	//getters
	cout << endl << "The name of student1 is: " << student1.getName();
	cout << endl << "The gender of student2 is: " << student2.getGender();
	cout << endl << "The grades of student3 are: ";
	student3.getGrades();
	cout << endl << "The nr. of grades of student3 is: " << student3.getNoGrades();
	cout << endl << "The code of student4 is: " << student4.getCode();
	cout << endl << "The address of student5 is: " << student5.getAddress();
	cout << endl;


	//setters
	student7.setName("John");
	cout << endl << "Post setName student7: " << student7.getName();

	student6.setGender('n');
	student6.setGender('f');
	cout << endl << "Post setGender student6: " << student6.getGender();

	int newGrades[] = { 10, 8, 6 };
	student7.setGrades(newGrades, 3);
	cout << endl << "Post setGrades student7: ";
	student7.getGrades();
	cout << endl << "The new nr. of grades of student7 is: " << student7.getNoGrades();

	student4.setAddress("Mars");
	student4.setAddress("Bvd Ion Mihalache Bucuresti");
	cout << endl << "Post setAddress student4: " << student4.getAddress();

	student5.setCode(5);
	cout << endl << "Post setCode student5: " << student5.getCode();

	cout << endl << endl << "Set student10 from console!";
	Student student10;
	student10.setConsole();
	cout << endl << "The new student10: ";
	student10.display();
	
	cout << endl << "Student5's no grades: " << student5.getNoGrades();
	student5.initializeGrades(student7);
	cout << endl << "Student5's grades initialized with student7's grades: ";
	student5.getGrades();


	//mandatory
	cout << endl << "The avg grade of student7 is: " << student7.average();

	student1.takeExam(7);
	cout << endl << "Student1 has taken an exam.";
	cout << endl << "The grades of student1 are: ";
	student1.getGrades();
	cout << endl << "The nr. of grades of student1 is: " << student1.getNoGrades();
	cout << endl << "The first grade of student1 is: " << student1.get(1);
	cout << endl;

	cout << endl << "The address of student2: " << student2.getAddress();
	cout << endl << "Is student2 from the city Bucuresti? ";
	if (student2.isFromCity("Bucuresti"))
		cout << "Yes";
	else
		cout << "No";
	cout << endl << "Is student2 from the city Ploiesti? ";
	if (student2.isFromCity("Ploiesti"))
		cout << "Yes";
	else
		cout << "No";
	cout << endl << "Is student2 from the city Parangaricutirimicuaro? ";
	if (student2.isFromCity("Parangaricutirimicuaro"))
		cout << "Yes";
	else
		cout << "No";
	cout << endl << "(actual city from Mexico - exceeds no chars from orginial address)";
	cout << endl;


	//other methods
	//1
	cout << endl << "Is student7 a repeater? ";
	if (student7.isRepeater())
		cout << "Yes";
	else cout << "No";
	cout << endl;

	//2
	Student student8 = student1;
	int newGrades2[] = { 2, 4, 6 };
	student8.setGrades(newGrades2, 3);
	cout << endl << "The grades of student8: ";
	student8.getGrades();
	cout << endl << "Is student8 a repeater? ";
	if (student8.isRepeater()){
		cout << "Yes";
		student8.resetGrades();
		cout << endl << "The grades have been reseted. ";
		student8.getGrades();
	}
	else cout << "No";
	cout << endl;

	//3
	Student student9;
	int newGrades3[] = { 10, 10, 10, 10, 10 };
	student9.setGrades(newGrades3, 5);
	cout << endl << "Student9 grades: ";
	student9.getGrades();
	cout << endl << "Is "<< student9.getName() << " recieving a scolarship? ";
	if (student9.scolarship())
		cout << "Yes";
	else cout << "No";

	//4
	student7.takeExam(3);
	student7.takeExam(5);
	cout << endl << "The grades of student7: ";
	student7.getGrades();
	cout << endl << "The nr of failed exams of student7 is: " << student7.noFailedExams();

	//5
	cout << endl << "Is student9 an integralist? ";
	if (student9.integralist())
		cout << "Yes";
	else
		cout << "No";
	cout << endl;

	//6
	cout << endl << "What is student9's financing form? " << student9.getFinancing();
	cout << endl << "What about student7? " << student7.getFinancing();
	cout << endl;

	//7
	cout << endl << "Student9 grades: ";
	student9.getGrades();
	student9.removeExam();
	cout << endl << "The last grade has been removed.";
	cout << endl << "Student9 grades: ";
	student9.getGrades();
	cout << endl;

	//8
	student4.takeExam(1);
	student4.takeExam(2);
	student4.takeExam(3);
	cout << endl << "Student4 grades: ";
	student4.getGrades();
	student4.removeAnExam(2);
	cout << endl << "The 2nd grade has been removed.";
	cout << endl << "Student4 grades: ";
	student4.getGrades();
	cout << endl;

	//9
	cout << endl << "Student4 has retaken her first exam and she took 6.";
	student4.retakeExam(6, 1);
	cout << endl << "Student4 grades: ";
	student4.getGrades();
	cout << endl;

	//10
	cout << endl << "Student4:";
	student4.setName("Ms. Very Dumb");
	student4.display();
	student4.expel();
	cout << endl << "Student4 has been expelled! All data is now reseted to default.";
	student4.display();


	cout << endl << endl;
}