#include<iostream>
#include<fstream>
using namespace std;

class InterfataCalendar{
public:
	virtual bool inTimpulSerii() = 0;
};

class WrongHourException :public exception{
public:
	WrongHourException(char* msg) :exception(msg){

	}
};

class IntrareCalendar{
	char dataCalendar[20];
	int ora;
	int minute;
	int secunde;
public:
	IntrareCalendar(){
		strcpy(this->dataCalendar, "01/01/2017");
		this->ora = 12;
		this->minute = 0;
		this->secunde = 0;
	}

	IntrareCalendar(char* data, int h, int m){
		if (strlen(data) <= 20)
			strcpy(this->dataCalendar, data);
		this->ora = h;
		this->minute = m;
		this->secunde = 0;
	}

	IntrareCalendar(IntrareCalendar& ic){
		strcpy(this->dataCalendar, ic.dataCalendar);
		this->ora = ic.ora;
		this->minute = ic.minute;
		this->secunde = ic.secunde;
	}

	IntrareCalendar& operator=(IntrareCalendar& ic){
		strcpy(this->dataCalendar, ic.dataCalendar);
		this->ora = ic.ora;
		this->minute = ic.minute;
		this->secunde = ic.secunde;
		return *this;
	}

	~IntrareCalendar(){

	}

	char* getData(){
		return this->dataCalendar;
	}

	int getOra(){
		return this->ora;
	}

	int getMin(){
		return this->minute;
	}

	int getSec(){
		return this->secunde;
	}

	void setData(char* data){
		if (strlen(data) <= 20){
			strcpy(this->dataCalendar, data);
		}
	}

	void addOra(int nr){
		if (nr <= 24 - this->ora)
			this->ora += nr;
	}

	IntrareCalendar operator++(){
		IntrareCalendar copie = *this;
		this->minute++;
		if (this->minute >= 60){
			this->ora++;
			this->minute -= 60;
		}
		return copie;
	}

	friend istream& operator>>(istream& in, IntrareCalendar& ic);
};
istream& operator>>(istream& in, IntrareCalendar& ic){
	cout << endl << "Data: ";
	in >> ic.dataCalendar;
	cout << "H: ";
	in >> ic.ora;
	cout << "M: ";
	in >> ic.minute;
	cout << "S: ";
	in >> ic.secunde;
	return in;
}
ostream& operator<<(ostream& out, IntrareCalendar& ic){
	out << endl << ic.getData() << "  " << ic.getOra() << ":" << ic.getMin() << ":" << ic.getSec();
	return out;
}
ofstream& operator<<(ofstream& fout, IntrareCalendar& ic){
	fout << endl << ic.getData() << "  " << ic.getOra() << ":" << ic.getMin() << ":" << ic.getSec();
	return fout;
}

class Eveniment:public InterfataCalendar{
	const int id_intrare;
	IntrareCalendar data;
	char* detalii;
	static int nrIntrari;
public:
	Eveniment(int id, IntrareCalendar& ic):id_intrare(id){
		Eveniment::nrIntrari++;
		this->data = ic;
		this->detalii = new char[1];
		strcpy(this->detalii, "");
	}

	Eveniment(int id, IntrareCalendar& ic, char* info) :id_intrare(id){
		Eveniment::nrIntrari++;
		this->data = ic;
		this->detalii = new char[strlen(info) + 1];
		strcpy(this->detalii, info);
	}

	Eveniment(Eveniment& e):id_intrare(e.id_intrare){
		this->data = e.data;
		this->detalii = new char[strlen(e.detalii) + 1];
		strcpy(this->detalii, e.detalii);
	}

	Eveniment& operator=(Eveniment& e){
		this->data = e.data;
		delete[] this->detalii;
		this->detalii = new char[strlen(e.detalii) + 1];
		strcpy(this->detalii, e.detalii);
	}

	~Eveniment(){
		delete[] this->detalii;
	}

	void setDetalii(char* info){
		delete[] this->detalii;
		this->detalii = new char[strlen(info) + 1];
		strcpy(this->detalii, info);
	}

	Eveniment& operator+=(int ore){
		this->data.addOra(ore);
		return *this;
	}

	int getId(){
		return this->id_intrare;
	}

	IntrareCalendar& getData(){
		return this->data;
	}

	char* getDetalii(){
		return this->detalii;
	}

	explicit operator int(){
		int h = this->data.getOra() * 60;
		int m = this->data.getMin();
		return h + m;
	}

	static int total(){
		return Eveniment::nrIntrari;
	}

	static void salvareFisier(Eveniment** e, int nre, char* filename, char* zi){
		ofstream save;
		save.open(filename, ios::out);
		if (save.is_open()){
			for (int i = 0; i < nre; i++){
				if (strcmp(e[i]->data.getData(), zi) == 0)
					save << endl << *e[i];
			}
			save.close();
		}
	}

	bool inTimpulSerii(){
		if (this->data.getOra() >= 18 && this->data.getOra() <= 24)
			return true;
		else
			throw new WrongHourException("Wrong hour!");
	}

	friend istream& operator>>(istream& in, Eveniment& e);
};
int Eveniment::nrIntrari = 0;
istream& operator>>(istream& in, Eveniment& e){
	in >> e.data;
	cout << "Detalii: ";
	cin.ignore();
	char buffer[200];
	cin >> buffer;
	//gets(buffer);
	strcpy(e.detalii, buffer);
	return in;
}
ostream& operator<<(ostream& out, Eveniment& e){
	out << endl << "ID: " << e.getId() << e.getData() << " // " << e.getDetalii();
	return out;
}
ofstream& operator<<(ofstream& fout, Eveniment& e){
	fout << endl << "ID: " << e.getId() << e.getData() << " // " << e.getDetalii();
	return fout;
}


void main(){
	IntrareCalendar m1; //12h 1.1.2017
	IntrareCalendar m2("23/01/2017", 9, 30); //no secs
	IntrareCalendar m3 = m2;
	//cin >> m1;
	cout << m1 << m2 << m3;
	m2.setData("23.01.2017");
	m3 = m1;
	IntrareCalendar m4 = m2++; //minute incrementate (atentie ora)
	cout << endl << m2 << m3 << m4 << endl;
	
	Eveniment e1(1, m2); //no details
	Eveniment e2(2, m4, "Examen POO");
	e1.setDetalii("Pregatire examen");
	e1 += 2; //+2 ore
	//cout << e1;

	//cin >> e1;
	cout << endl << e1 << endl << e2;
	int totalMinute = (int)e1; //generare total minute
	cout << endl << "Total evenimente: " << Eveniment::total() << endl; //nr tottal evenimente
	
	int nrEvenimente;
	nrEvenimente = 3;
	Eveniment** agenda = new Eveniment*[nrEvenimente];
	agenda[0] = new Eveniment(3, m2, "Examen POO");
	agenda[1] = new Eveniment(4, m4, "Pregatire examen");
	agenda[2] = new Eveniment(5, m2, "Rezultate POO");
	for (int i = 0; i < nrEvenimente; i++){
		cout << endl << *agenda[i];
	}

	Eveniment::salvareFisier(agenda, nrEvenimente, "Agenda.txt", "23.01.2017");

	/*try{
		if (e2.inTimpulSerii())
			cout << endl << "Evenimentul se petrece in timpul serii";
	}
	catch(WrongHourException* e){
		cout << endl << "Wrong hour!";
	}


	*/

	cout << endl;
}