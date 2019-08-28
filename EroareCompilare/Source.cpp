#include <iostream>
#include <fstream>
using namespace std;

class EroareCompilare {
	char text[100];
	const int id_eroare;
	int tip_eroare;
	static int TIPURI_ERORI;
public:
	EroareCompilare() :id_eroare(0) {
		strcpy(this->text, "");
		this->tip_eroare = 0;
	}

	EroareCompilare(int id, char* txt, int err) :id_eroare(id) {
		if (err <= EroareCompilare::TIPURI_ERORI)
			this->tip_eroare = err;
		if (strlen(txt) < 100)
			strcpy(this->text, txt);
	}

	EroareCompilare(EroareCompilare& e) :id_eroare(e.id_eroare) {
		this->tip_eroare = e.tip_eroare;
		strcpy(this->text, e.text);
	}

	~EroareCompilare() {

	}

	EroareCompilare operator=(EroareCompilare& e) {
		this->tip_eroare = e.tip_eroare;
		strcpy(this->text, e.text);
		return *this;
	}

	void setMesaj(char* txt) {
		if (strlen(txt) < 100)
			strcpy(this->text, txt);
	}

	char* getText() {
		return this->text;
	}

	int getId() {
		return this->id_eroare;
	}

	int getTip() {
		return this->tip_eroare;
	}

	static int getTipMaxim() {
		return EroareCompilare::TIPURI_ERORI;
	}

	EroareCompilare operator++() {
		if (this->tip_eroare < EroareCompilare::TIPURI_ERORI)
			this->tip_eroare++;
		return *this;
	}

	friend istream& operator >> (istream& in, EroareCompilare& e);
};
int EroareCompilare::TIPURI_ERORI = 15;
istream& operator >> (istream& in, EroareCompilare& e) {
	cout << endl << "Text: ";
	cin >> e.text;
	//gets(e.text);
	cout << "Tip: ";
	in >> e.tip_eroare;
	return in;
}
ostream& operator<<(ostream& out, EroareCompilare& e) {
	out << endl << "Id:" << e.getId() << "  Tip:" << e.getTip();
	out << endl << e.getText();
	return out;
}

class RezultateCompilare {
	EroareCompilare eroare_compilare;
	int* liniiSursa;
	int numar_aparitii;
public:
	RezultateCompilare(EroareCompilare& e) {
		this->eroare_compilare = e;
		this->liniiSursa = NULL;
		this->numar_aparitii = 0;
	}

	RezultateCompilare(EroareCompilare& e, char* txt, int* lines) {
		this->eroare_compilare = e;
		this->eroare_compilare.setMesaj(txt);
		this->numar_aparitii = sizeof(lines) / sizeof(int);
		this->liniiSursa = new int[this->numar_aparitii];
		for (int i = 0; i < this->numar_aparitii; i++) {
			this->liniiSursa[i] = lines[i];
		}
	}

	RezultateCompilare(RezultateCompilare& r) {
		this->eroare_compilare = r.eroare_compilare;
		this->numar_aparitii = r.numar_aparitii;
		this->liniiSursa = new int[this->numar_aparitii];
		for (int i = 0; i < this->numar_aparitii; i++) {
			this->liniiSursa[i] = r.liniiSursa[i];
		}
	}

	RezultateCompilare operator=(RezultateCompilare& r) {
		this->eroare_compilare = r.eroare_compilare;
		this->numar_aparitii = r.numar_aparitii;
		delete[] this->liniiSursa;
		this->liniiSursa = new int[this->numar_aparitii];
		for (int i = 0; i < this->numar_aparitii; i++) {
			this->liniiSursa[i] = r.liniiSursa[i];
		}
		return *this;
	}

	void setDescriere(char* txt) {
		this->eroare_compilare.setMesaj(txt);
	}

	bool operator>(RezultateCompilare& r) {
		if (this->numar_aparitii > r.numar_aparitii)
			return true;
		else return false;
	}

	operator int() {
		if (this->numar_aparitii >= 1) {
			int x = this->liniiSursa[this->numar_aparitii - 1];
			return x;
		}
	}

	EroareCompilare getErr() {
		return this->eroare_compilare;
	}

	int getNrA() {
		return this->numar_aparitii;
	}

	int getLine(int index) {
		return this->liniiSursa[index];
	}

	int getTip() {
		return this->eroare_compilare.getTip();
	}

	char* getText() {
		return this->eroare_compilare.getText();
	}

	static int getTipMaxim() {
		return EroareCompilare::getTipMaxim();
	}

	friend istream& operator >> (istream& in, RezultateCompilare& r);
};
istream& operator >> (istream& in, RezultateCompilare& r) {
	/*cout << endl << "Text: ";
	gets(e.text);
	cout << "Tip: ";
	in >> e.tip_eroare;*/
	return in;
}
ostream& operator<<(ostream& out, RezultateCompilare& r) {
	out << r.getErr();
	out << endl << "Lines: ";
	for (int i = 0; i < r.getNrA(); i++) {
		out << r.getLine(i) << " ";
	}
	return out;
}

void main() {
	EroareCompilare e1;
	EroareCompilare e2(1, "Lipsa ;", 5);
	EroareCompilare e3 = e2;
	//cin >> e2;
	cout << e2 << e3;
	e2.setMesaj("Variabila neinitializata");
	e2++; //tip eroare ++ < tipuri erori max
	cout << e2 << e3;

	RezultateCompilare r1(e2);
	int linii[] = { 10, 45, 67 };
	RezultateCompilare r2(e3, "Identificator lipsa", linii);
	r1.setDescriere("Variabila necunoscuta");
	if (r2 > r1)
		cout << endl << r2.getText() << " apare de mai multe ori";
	else
		cout << endl << r1.getText() << " apare de mai multe ori";
	cout << r1;

	//cin >> r1;
	cout << "Ultima linie cu eroare: " << (int)r1;
	cout << r1.getText() << " are tipul " << r1.getTip() << " din maxim " << RezultateCompilare::getTipMaxim();

	cout << endl;
}