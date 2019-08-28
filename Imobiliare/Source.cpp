#include <iostream>
using namespace std;

class Locuinta {
protected:
	char* numeClient;
	int suprafataUtila;
	float discount;
public:
	Locuinta(char* nume, int mp, float disc) {
		this->numeClient = new char(strlen(nume) + 1);
		strcpy(this->numeClient, nume);
		this->suprafataUtila = mp;
		this->discount = disc;
	}

	Locuinta() {
		this->numeClient = NULL;
		this->suprafataUtila = 0;
		this->discount = 0;
	}

	Locuinta(Locuinta& l) {
		this->suprafataUtila = l.suprafataUtila;
		this->discount = l.discount;
		if (l.numeClient == NULL)
			this->numeClient = NULL;
		else {
			this->numeClient = new char[strlen(l.numeClient) + 1];
			strcpy(this->numeClient, l.numeClient);
		}
	}

	~Locuinta() {
		delete[] this->numeClient;
	}

	explicit operator int() {
		return this->suprafataUtila;
	}

	void operator++() {
		if (this->discount >= 0 && this->discount < 10)
			this->discount++;
	}

	void operator--() {
		if (this->discount > 0)
			this->discount--;
	}

	void getNume() {
		cout << this->numeClient;
	}

	Locuinta& operator=(const Locuinta& l) {
		this->suprafataUtila = l.suprafataUtila;
		this->discount = l.discount;
		if (l.numeClient == NULL)
			this->numeClient = NULL;
		else {
			delete[] this->numeClient;
			this->numeClient = new char[strlen(l.numeClient) + 1];
			strcpy(this->numeClient, l.numeClient);
		}
		return *this;
	}

	virtual float CalculChirie(int x, int y) = 0;
};

class Apartament :public Locuinta {
	int etaj;
public:
	Apartament() :Locuinta() {
		this->etaj = 0;
	}

	Apartament(char* nume, int mp, float disc, int et) :Locuinta(nume, mp, disc) {
		this->etaj = et;
	}

	Apartament(Apartament& a) :Locuinta(a) {
		this->etaj = a.etaj;
	}

	Apartament& operator=(const Apartament& a) {
		Locuinta::operator=(a);
		this->etaj = a.etaj;
		return *this;
	}

	float CalculChirie(int x, int y) {
		float r;
		r = x * suprafataUtila * (1 - y * discount / 100.0);
		return r;
	}
};

class Casa :public Locuinta {
	int suprafataCurte;
	int nrEtaje;
	float* suprafataEtaje;
public:
	Casa() :Locuinta() {
		this->suprafataCurte = 0;
		this->nrEtaje = 0;
		this->suprafataEtaje = NULL;
	}

	Casa(char* nume, int mp, float disc, int curte, int etaje, float* suprafete) :Locuinta(nume, mp, disc) {
		this->suprafataCurte = curte;
		this->nrEtaje = etaje;
		if (this->nrEtaje) {
			this->suprafataEtaje = new float[etaje]();
			for (int i = 0; i < etaje; i++) {
				this->suprafataEtaje[i] = suprafete[i];
			}
		}
		else
			this->suprafataEtaje = NULL;
	}

	Casa(Casa& c) :Locuinta(c) {
		this->suprafataCurte = c.suprafataCurte;
		this->nrEtaje = c.nrEtaje;
		if (c.suprafataEtaje == NULL)
			this->suprafataEtaje = NULL;
		else {
			this->suprafataEtaje = new float[this->nrEtaje];
			for (int i = 0; i < this->nrEtaje; i++) {
				this->suprafataEtaje[i] = c.suprafataEtaje[i];
			}
		}
	}

	~Casa() {
		delete[] this->suprafataEtaje;
	}

	Casa& operator=(Casa& c) {
		Locuinta::operator=(c);
		this->suprafataCurte = c.suprafataCurte;
		this->nrEtaje = c.nrEtaje;
		if (c.suprafataEtaje == NULL)
			this->suprafataEtaje = NULL;
		else {
			delete[] this->suprafataEtaje;
			this->suprafataEtaje = new float[this->nrEtaje];
			for (int i = 0; i < this->nrEtaje; i++) {
				this->suprafataEtaje[i] = c.suprafataEtaje[i];
			}
		}
		return *this;
	}

	float CalculChirie(int x, int y) {
		float r;
		r = x * (suprafataUtila + 0.2 * suprafataCurte) * (1 - y * discount / 100.0);
		return r;
	}
};

class AgentieImobiliara {
	Locuinta* *locuinte;
	int noLocuinte;
public:
	AgentieImobiliara() {
		this->noLocuinte = 0;
		this->locuinte = NULL;
	}

	AgentieImobiliara(int nr, Locuinta** l) {
		this->noLocuinte = nr;
		if (nr) {
			this->locuinte = new Locuinta*[nr];
			for (int i = 0; i < nr; i++) {
				//this->locuinte[i] = &l[i];
				this->locuinte[i] = l[i];
			}
		}
	}

	int getNoLocuinte() {
		return this->noLocuinte;
	}

	Locuinta* getLocuinta(int index) {
		if (index < noLocuinte && index >= 0)
			return locuinte[index];
	}

	AgentieImobiliara& operator+=(Locuinta& l) {
		Locuinta* *noi = new Locuinta*[this->noLocuinte + 1];
		for (int i = 0; i < this->noLocuinte; i++) {
			noi[i] = locuinte[i];
			noi[this->noLocuinte] = &l;
			delete[] this->locuinte;
			this->locuinte = noi;
			this->noLocuinte++;
			return *this;
		}
	}
};
ostream& operator<<(ostream& out, AgentieImobiliara& a) {
	for (int i = 0; i < a.getNoLocuinte(); i++) {
		out << endl;
		a.getLocuinta(i)->getNume();
	}
	return out;
}

void main() {
	float* etaje1 = new float[1];
	etaje1[0] = 90.0;
	
	Locuinta* *cartier = new Locuinta*[5];
	cartier[0] = new Apartament("Kashan Nadeem", 67, 6, 1);
	cartier[1] = new Apartament("Vlad Caragea", 75, 8, 2);
	cartier[2] = new Casa("Andrei Prepelita", 90, 3, 40, 1, etaje1);

	for (int i = 0; i < 3; i++) {
		cout << i + 1 << ": ";
		cout << cartier[i]->CalculChirie(5, 1) << endl;
	}
	
	float* etaje2 = new float[3];
	etaje2[0] = 200;
	etaje2[1] = 150;
	etaje2[2] = 100;
	Casa cus("Alex Cus", 500, 10, 200, 3, etaje2);
	
	AgentieImobiliara domenii;
	domenii += cus;
	cout << endl << domenii;

	AgentieImobiliara grivita(3, cartier);
	cout << endl << grivita << endl;
}