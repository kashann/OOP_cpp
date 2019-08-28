#include <iostream>
using namespace std;

class Revizie {
	int km;
	int an;
	int valoare;
public:
	Revizie() {
		this->km = 0;
		this->an = 2017;
		this->valoare = 0;
	}

	Revizie(int kilom, int year, int val) {
		this->km = kilom;
		this->an = year;
		this->valoare = val;
	}

	Revizie(Revizie& r) {
		this->km = r.km;
		this->an = r.an;
		this->valoare = r.valoare;
	}

	void display() {
		cout << endl << "Kilometrii: " << this->km;
		cout << endl << "An: " << this->an;
		cout << endl << "Valoare: " << this->valoare;
	}

	int getVal() {
		return this->valoare;
	}

	int getKm() {
		return this->km;
	}

	int getAn() {
		return this->an;
	}

	void operator=(Revizie& r) {
		this->km = r.km;
		this->an = r.an;
		this->valoare = r.valoare;
	}

	friend istream& operator >> (istream& in, Revizie& r);
};
istream& operator >> (istream& in, Revizie& r) {
	cout << endl << "Kilometrii: ";
	in >> r.km;
	cout << "An: ";
	in >> r.an;
	cout << "Valoare: ";
	in >> r.valoare;
	return in;
}
ostream& operator<<(ostream& out, Revizie& r) {
	out << endl << "Kilometrii: " << r.getKm();
	out << endl << "An: " << r.getAn();
	out << endl << "Valoare: " << r.getVal();
	return out;
}

class Autovehicul {
	char nr_inmatriculare[10];
	char proprietar[30];
	Revizie* revizii;
	int noRevizii;
public:
	Autovehicul() {
		strcpy(this->nr_inmatriculare, '\0');
		strcpy(this->proprietar, '\0');
		this->revizii = NULL;
		this->noRevizii = 0;
	}

	Autovehicul(char* nr, char* nume, int rev, Revizie** r) {
		strcpy(this->nr_inmatriculare, nr);
		strcpy(this->proprietar, nume);
		this->noRevizii = rev;
		if (rev) {
			this->revizii = new Revizie[rev];
			for (int i = 0; i < rev; i++) {
				this->revizii[i] = *r[i];
			}
		}
	}

	~Autovehicul() {
		delete[] revizii;
	}

	Autovehicul(Autovehicul& a) {
		strcpy(this->nr_inmatriculare, a.nr_inmatriculare);
		strcpy(this->proprietar, a.proprietar);
		this->revizii = new Revizie[a.noRevizii];
		for (int i = 0; i < a.noRevizii; i++) {
			this->revizii[i] = a.revizii[i];
		}
		this->noRevizii = a.noRevizii;
	}

	char* getNrInm() {
		return this->nr_inmatriculare;
	}

	char* getProprietar() {
		return this->proprietar;
	}

	int getNoRevizii() {
		return this->noRevizii;
	}

	Revizie getRevizie(int nr) {
		if (nr >= 0 && nr <= this->noRevizii)
			return this->revizii[nr];
	}

	void setProprietar(char* name) {
		if (strlen(name) <= 30)
			strcpy(this->proprietar, name);
	}

	void addRevizie(Revizie& r) {
		this->revizii[this->noRevizii] = r;
		this->noRevizii += 1;
	}

	float obtineValoareRevizii() {
		float s = 0;
		for (int i = 0; i < this->noRevizii; i++) {
			s += this->revizii[i].getVal();
		}
		return s;
	}

	void operator=(Autovehicul& a) {
		strcpy(this->nr_inmatriculare, a.nr_inmatriculare);
		strcpy(this->proprietar, a.proprietar);
		delete[] this->revizii;
		this->revizii = new Revizie[a.noRevizii];
		for (int i = 0; i < a.noRevizii; i++) {
			this->revizii[i] = a.revizii[i];
		}
		this->noRevizii = a.noRevizii;
	}

	void operator+=(Revizie& r) {
		addRevizie(r);
	}

	friend istream& operator >> (istream& in, Autovehicul& a);
};
istream& operator >> (istream& in, Autovehicul& a) {
	cout << endl << "Numar inmatriculare: ";
	in >> a.nr_inmatriculare;
	cout << "Proprietar: ";
	in >> a.proprietar;
	cout << "Nr revizii: ";
	in >> a.noRevizii;
	if (a.noRevizii) {
		delete[] a.revizii;
		a.revizii = new Revizie[a.noRevizii];
		for (int i = 0; i < a.noRevizii; i++) {
			cout << "Revizia " << i + 1 << ": ";
			in >> a.revizii[i];
		}
	}
	return in;
}
ostream& operator<<(ostream& out, Autovehicul& a) {
	out << endl << "Numar inmatriculare: " << a.getNrInm();
	out << endl << "Proprietar: " << a.getProprietar();
	out << endl << "Nr revizii: " << a.getNoRevizii();
	if (a.getNoRevizii()) {
		for (int i = 0; i < a.getNoRevizii(); i++) {
			out << endl << endl << "Revizia " << i + 1 << ": " << a.getRevizie(i);
		}
	}
	return out;
}

void main() {
	Revizie* *carte = new Revizie*[5];
	carte[0] = new Revizie(14780, 2008, 800);
	carte[1] = new Revizie(30289, 2010, 1200);
	carte[2] = new Revizie(44730, 2012, 1000);
	carte[3] = new Revizie(52560, 2017, 1350);

	Autovehicul Skoda("B 06 KAS", "Kashan Nadeem", sizeof(carte), carte);
	cout << Skoda << endl;

	cout << "\nValoare totala revizii: " << Skoda.obtineValoareRevizii();

	cout << endl;
}