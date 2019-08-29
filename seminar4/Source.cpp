#include <iostream>
using namespace std;

class FidelityCard {
private:
	char name[50]; //username
	int* points;
	int noPayments;

public:
	FidelityCard() {
		strcpy(name, "John Doe");
		points = NULL;
		this->noPayments = 0;
	}
	FidelityCard(char* name) {
		strcpy(this->name, name);
		points = NULL;
		noPayments = 0;
	}
	~FidelityCard() {
		cout << endl << "Destructor called!";
		delete[] this->points;
	}

	//copy constructor
	FidelityCard(FidelityCard& existingCard) {
		strcpy(this->name, existingCard.name);
		this->noPayments = existingCard.noPayments;
		this->points = new int[existingCard.noPayments];
		for (int i = 0; i < this->noPayments; i++)
			points[i] = existingCard.points[i];
	}

	//accsor methods
	//for reading
	char * getName() {
		return this->name;
	}
	int getnoPayments() {
		return this->noPayments;
	}
	int getPoints(int i) {
		return this->points[i];
	}
	//for writing
	void setPoints(int* points, int n) {
		//DON'T
		//this->points = points;

		if (this->points != NULL)
			delete[] this->points;

		this->points = new int[n];

		for (int i = 0; i < n; i++) {
			this->points[i] = points[i];
		}
		this->noPayments = n;
	}

	void addPoints(int value) {
		int *temp = new int[this->noPayments + 1];
		for (int i = 0; i < noPayments; i++)
			temp[i] = points[i];
		temp[noPayments] = value;
		this->points = temp;
		this->noPayments += 1;
	}

};//class ends here

void printData(FidelityCard fc) {
	cout << endl << "Card owner: " << fc.getName();
	cout << endl << "Available points: ";
	int sum = 0;
	for (int i = 0; i < fc.getnoPayments(); i++) {
		sum += fc.getPoints(i);
	}
	cout << sum;
}

void something() {
	FidelityCard fc("Mike");
	int existingPoints[] = { 10, 67, 5 };
	fc.setPoints(existingPoints, 3);
}

void main() {

	something();

	FidelityCard card1;
	FidelityCard card2("Mike");
	cout << endl << "The owner is:" << card2.getName() << endl;
	printData(card2);

	int existingPoints[] = { 10, 67, 5 };
	card2.setPoints(existingPoints, 3);
	card2.addPoints(10);

	printData(card2);
}