#include <iostream>
using namespace std;

class FidelityCard {
	const int id;
	char owner[50];
	int* points;
	int noPayments;
	static int noCards;
public:
	FidelityCard(char* name = "default") :id(FidelityCard::noCards) { //default name added by me
		FidelityCard::noCards += 1;
		strcpy(this->owner, name);
		points = NULL;
		noPayments = 0;
	}

	FidelityCard(FidelityCard& card) :id(++noCards) {
		strcpy(this->owner, card.owner);
		this->points = new int[card.noPayments];
		for (int i = 0; i < card.noPayments; i++)
			this->points[i] = card.points[i];
		this->noPayments = card.noPayments;
	}
	~FidelityCard() {
		delete[] this->points;
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

	char* getName() {
		return this->owner;
	}

	int& operator[](int index) {
		if (index >= 0 && index < this->noPayments)
			return this->points[index];
		else
			throw exception("The index is wrong");
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

	FidelityCard operator+=(int value) {

		int* newPoints = new int[this->noPayments + 1];
		for (int i = 0; i < this->noPayments; i++)
			newPoints[i] = this->points[i];
		newPoints[this->noPayments] = value;
		delete[] this->points;
		this->points = newPoints;
		this->noPayments += 1;

		return *this;
	}

	friend istream& operator>>(istream& input, FidelityCard& c);
	friend ostream& operator<<(ostream& out, FidelityCard& c);
};

int FidelityCard::noCards = 0;

int operator+=(int x, FidelityCard& c){
	x = c.getTotalPoints();
	return x;
}

istream& operator>>(istream& input, FidelityCard& c) {
	cout << endl << "Owner name: ";
	input >> c.owner;

	cout << "No of payments:";
	input >> c.noPayments;
	delete[] c.points;
	c.points = new int[c.noPayments];
	for (int i = 0; i < c.noPayments; i++) {
		cout << endl << "Points for the payment " << i + 1 << " :";
		input >> c.points[i];
	}

	return input;
}

ostream& operator<<(ostream& out, FidelityCard& c) {
	out << endl << "Card owner: " << c.owner;
	out << endl << "Points:";
	if (c.noPayments == 0)
		cout << "0";
	else
	{
		for (int i = 0; i < c.noPayments; i++)
			cout << " " << c.points[i];
	}
	return out;
}

class ClientsList {
private:
	int noClients;
	FidelityCard* cards;
	char storeName[50];

public:
	//default constructor
	ClientsList(char* storeName) {
		strcpy(this->storeName, storeName);
		this->cards = NULL;
		this->noClients = 0;
	}

	//TO DO copy constructor
	ClientsList(ClientsList& list){
		this->noClients = list.noClients;
		this->cards = new FidelityCard[list.getNoClients()];
		for (int i = 0; i < list.noClients; i++)
			this->cards[i] = list.cards[i];
		strcpy(this->storeName, list.storeName);
	}

	//TO DO destructor
	~ClientsList(){
		delete[] this->cards;
	}

	int getNoClients(){
		return this->noClients;
	}

	FidelityCard getCards(int value){
		return this->cards[value];
	}

	char* getStoreName(){
		return this->storeName;
	}

	//TO DO operator =
	void operator=(ClientsList& list){
		this->noClients = list.noClients;
		delete[] this->cards;
		this->cards = new FidelityCard[list.getNoClients()];
		for (int i = 0; i < list.noClients; i++)
			this->cards[i] = list.cards[i];
		strcpy(this->storeName, list.storeName);
	}


	//TO DO
	//required operators so main()  will run

	//operator +
	ClientsList operator+(FidelityCard& card){
		ClientsList result = *this;
		FidelityCard* newCards = new FidelityCard[result.noClients + 1];
		for (int i = 0; i < result.noClients; i++)
			newCards[i] = result.cards[i];

		newCards[result.noClients] = card;
		delete[] result.cards;
		result.cards = newCards;
		result.noClients += 1;
		return result;
	}

	ClientsList operator+(char* name){
		ClientsList result = *this;
		FidelityCard* newCards = new FidelityCard[result.noClients + 1];
		for (int i = 0; i < result.noClients; i++)
			newCards[i] = result.cards[i];

		FidelityCard newCard(name);
		newCards[result.noClients] = newCard;
		delete[] result.cards;
		result.cards = newCards;
		result.noClients += 1;
		return result;
	}

	//operator +=
	ClientsList operator+=(FidelityCard& card){
		FidelityCard* newCards = new FidelityCard[this->noClients + 1];
		for (int i = 0; i < this->noClients; i++)
			newCards[i] = this->cards[i];

		newCards[this->noClients] = card;
		delete[] this->cards;
		this->cards = newCards;
		this->noClients += 1;
		return *this;
	}

	//operator []
	FidelityCard& operator[](int index){
		if (index > 0 && index <= this->noClients)
			return this->cards[index - 1];
		else
			cout << endl << "A client with the index " << index << " does not exist!";
	}

	//operator int()
	explicit operator int(){
		return this->getTotalPoints();
	}

	int getTotalPoints(){
		int s = 0;
		for (int i = 0; i < this->noClients; i++)
			s += this->cards[i].getTotalPoints();
		return s;
	}

	//operator --
	ClientsList operator--(){
		if (this->noClients == 1){
			this->cards = NULL;
			this->noClients -= 1;
			return *this;
		}
		else if (this->noClients > 1){
			FidelityCard* newCards = new FidelityCard[this->noClients - 1];
			for (int i = 0; i < this->noClients - 1; i++)
				newCards[i] = this->cards[i];
			this->noClients -= 1;
			delete[] this->cards;
			this->cards = newCards;
			return *this;
		}
		else{
			cout << endl << "There are no clients!";
			return *this;
		}
	}

	//operator ()
	void operator()(int x, int y){ //I can't figure out how to return these two values with other method than using cout
		cout << this->cards[x];
		cout << this->cards[y];
		//return *this;
	}

	/*FidelityCard operator()(int x, int y){ 
		FidelityCard* newCards = new FidelityCard[2]; //this returns only the first card :(
		newCards[0] = this->cards[x];
		newCards[1] = this->cards[y];
		return *newCards;
	}*/

	//operators > & <
	bool operator>(ClientsList& x){
		if (this->noClients > x.noClients)
			return true;
		return false;
	}

	bool operator<(ClientsList& x){
		if (this->noClients < x.noClients)
			return true;
		return false;
	}

	friend istream& operator>>(istream& input, ClientsList& c);

};

//input output operators
istream& operator>>(istream& input, ClientsList& c){
	cout << endl << "Nr of clients: ";
	input >> c.noClients;
	cout << "Cards: ";
	//delete[] c.cards;
	//c.cards = new FidelityCard[c.noClients];
	for (int i = 0; i < c.noClients; i++)
		input >> c.cards[i];
	cout << "Store name: ";
	gets(c.storeName);
	//input >> c.storeName;
	return input;
}

ostream& operator<<(ostream& out, ClientsList& c){
	out << endl << "Nr of clients: " << c.getNoClients();
	out << endl << "Cards: ";
	for (int i = 0; i < c.getNoClients(); i++)
		out << c.getCards(i) << " ";
	out << endl << "Store name: " << c.getStoreName();
	return out;
}



void main() {
	//testing FidelityCard
	//FidelityCard card1;
	FidelityCard card1("John");
	card1 = card1 + 45;
	card1 = card1 + 12;
	card1 = card1 + 10;
	cout << card1;

	//copy constructor
	FidelityCard card2 = card1;
	card2 += 10;
	card2 += 5;
	cout << card2;

	FidelityCard card3("Alice");
	card3 += 45;
	card3 += 7;
	cout << card3;  //added by me

	//requirements for ClientsList

	ClientsList list1("OnlineShop");

	list1 += card1;
	list1 += card2;
	list1 = list1 + card3;

	cout << endl << "---------------------";
	cout << endl << "List data";

	cout << list1;
	
	cout << endl << "---------------------";
	cout << endl << "Client 1 data";

	cout << list1[5];
	
	list1 = list1 + "Mike";		//add a new card created for Mike

	cout << endl << "---------------------";
	cout << endl << "Lista data after adding Mike";

	cout << list1;
	
	int totalPoints = (int)list1;
	cout << endl << "---------------------";
	cout << endl << "Clients total points = " << totalPoints;

	
	ClientsList list2("PetShop");
	list2 += card1;

	cout << endl << "---------------------";
	cout << endl << "List data";

	cout << list2;
	
	if (list1 > list2)
		cout << endl << "************ Store one has more clients than store 2";
	else cout << endl << "************ Store one DOES NOT have more clients than store 2"; //added by me
	
	list2 = list1--;		//removes the last card in the list
	cout << endl << "---------------------";
	cout << endl << "Cards list 1";

	cout << list1;
	
	cout << endl << "---------------------";
	cout << endl << "Cards list 2";

	cout << list2;
	
	ClientsList list3("ITShop");

	list3 += card1;
	list3 += card2;
	list3 += card3;
	cout << endl << "-----------";
	cout << list3;

	cout << endl << "---------------------";
	cout << endl << "First 2 cards from list 3 are ";
	//cout << list3(0, 1); //commented by me
	list3(0, 1);  //added by me

	cout << endl << endl; //added by me
}