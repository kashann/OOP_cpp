#include <iostream>
using namespace std;

class FidelityCard {
	char owner[50];
	int* points;
	int noPayments;

public:
	FidelityCard(char* name) {
		strcpy(this->owner, name);
		points = NULL;
		noPayments = 0;
	}

	FidelityCard(FidelityCard& card) {
		strcpy(this->owner, card.owner);
		this->points = new int[card.noPayments];
		for (int i = 0; i < card.noPayments; i++)
			this->points[i] = card.points[i];
		this->noPayments = card.noPayments;
	}

	~FidelityCard() {
		delete[] this->points;
	}

	void displayData() {
		cout << endl << "Card owner: " << this->owner;
		cout << endl << "Points: ";
		if (this->noPayments == 0)
			cout << "0";
		else
		{
			for (int i = 0; i < this->noPayments; i++)
				cout << " " << this->points[i];
		}
	}
	FidelityCard operator+(int value) {

		FidelityCard result = *this;

		int* newPoints = new int[this->noPayments + 1];
		for (int i = 0; i < this->noPayments; i++)
			newPoints[i] = this->points[i];
		newPoints[this->noPayments] = value;
		delete[] result.points;
		result.points = newPoints;
		result.noPayments += 1;
		return result;
	}

	void operator=(FidelityCard c) {
		strcpy(this->owner, c.owner);
		this->noPayments = c.noPayments;

		delete[] this->points;

		this->points = new int[c.noPayments];
		for (int i = 0; i < c.noPayments; i++)
			this->points[i] = c.points[i];
	}

	int getTotalPoints() {
		int s = 0;
		for (int i = 0; i < this->noPayments; i++)
			s += points[i];
		return s;
	}
	friend FidelityCard operator+(int value, FidelityCard c);
};

FidelityCard operator+(int value, FidelityCard c) {
	FidelityCard result = c;

	int* newPoints = new int[c.noPayments + 1];
	for (int i = 0; i < c.noPayments; i++)
		newPoints[i] = c.points[i];
	newPoints[c.noPayments] = value;
	delete[] result.points;
	result.points = newPoints;
	result.noPayments += 1;
	return result;
}

bool operator>(FidelityCard c1, FidelityCard c2) {
	if (c1.getTotalPoints() > c2.getTotalPoints())
		return true;
	else
		return false;
}


void main() {
	//	FidelityCard card1;  no default constructor because you have at least 1 other constructor
	FidelityCard card1("John");
	card1.displayData();

	//copy constructor
	FidelityCard card2 = card1;
	card2.displayData();

	FidelityCard card3("Alice");
	card3 = card1;


	//card2 + 10; // card2.operator+(10);
	card2 = card2 + 10;
	card2.displayData();

	card1 = card2 + 10;
	card1 = card1 + 20;
	card1 = 30 + card1;
	card1.displayData();

	if (card1 > card2)
		cout << endl << "Card1 has more points" << endl;
}