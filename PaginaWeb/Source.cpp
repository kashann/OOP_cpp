#include <iostream>
#include <fstream>
using namespace std;

class PaginaWeb{
	char url[100];
	int rating;
	static int rating_max;
public: 
	PaginaWeb(char* link = "", int nota = 0){
		strcpy(this->url, link);
		if (nota <= 5 && nota >= 0){
			this->rating = nota;
		}
	}

	PaginaWeb(PaginaWeb& p){
		strcpy(this->url, p.url);
		this->rating = p.rating;
	}

	~PaginaWeb(){
		
	}

	void setAdresa(char* adresa){
		if (strlen(adresa) < 100){
			strcpy(this->url, adresa);
		}
	}

	char* getUrl(){
		return this->url;
	}

	int getRating(){
		return this->rating;
	}

	static int getRatingMaxim(){
		return PaginaWeb::rating_max;
	}

	PaginaWeb& operator=(PaginaWeb& p){
		setAdresa(p.url);
		this->rating = p.rating;
		return *this;
	}

	PaginaWeb& operator+=(int nr){
		if (this->rating + nr <= this->rating_max)
			this->rating += nr;
		return *this;
	}

	friend istream& operator>>(istream& in, PaginaWeb& p);
};
int PaginaWeb::rating_max = 5;
istream& operator>>(istream& in, PaginaWeb& p){
	cout << endl << "URL: ";
	in >> p.url;
	cout << "Rating: ";
	int x;
	in >> x;
	if (x <= PaginaWeb::rating_max && x >= 0){
		p.rating = x;
	}
	return in;
}
ostream& operator<<(ostream& out, PaginaWeb& p){
	out << endl << "The URL " << p.getUrl() << " is rated " << p.getRating();
	return out;
}
ofstream& operator<<(ofstream& fout, PaginaWeb& p){
	fout << endl << "The URL " << p.getUrl() << " is rated " << p.getRating();
	return fout;
}

class Bookmark{
	const int id;
	PaginaWeb pag;
	char* descriere;
public:
	Bookmark(int nr, PaginaWeb& p):id(nr){
		this->pag = p;
		this->descriere = NULL;
	}

	Bookmark(int nr, PaginaWeb& p, char* desc) :id(nr){
		this->pag = p;
		this->descriere = new char[strlen(desc) + 1];
		strcpy(this->descriere, desc);
	}

	Bookmark(Bookmark& b):id(b.id){
		this->pag = b.pag;
		if (b.descriere != NULL)
			strcpy(this->descriere, b.descriere);
		else this->descriere = NULL;
	}

	~Bookmark(){
		delete[] this->descriere;
	}

	Bookmark& operator=(Bookmark& b){
		this->pag = b.pag;
		if (b.descriere != NULL){
			delete[] this->descriere;
			this->descriere = new char[strlen(b.descriere) + 1];
			strcpy(this->descriere, b.descriere);
		}
		else this->descriere = NULL;
		return *this;
	}

	PaginaWeb getPag(){
		return this->pag;
	}

	int getId(){
		return this->id;
	}

	void setDescriere(char* desc){
		delete[] this->descriere;
		this->descriere = new char[strlen(desc) + 1];
		strcpy(this->descriere, desc);
	}

	bool operator>(Bookmark& b){
		if (this->pag.getRating() > b.pag.getRating())
			return true;
		return false;
	}

	char* getUrl(){
		return this->pag.getUrl();
	}

	int getRating(){
		return this->pag.getRating();
	}

	static void printLista(Bookmark* b, int nrb, char* filename, int r){
		ofstream save;
		save.open(filename, ios::out);
		if (save.is_open()){
			for (int i = 0; i < nrb; i++){
				if (b[i].getRating() >= r)
					save << &b[i];
			}
			save.close();
		}
	}

	explicit operator int(){
		int x;
		x = strlen(this->getUrl());
		return x;
	}

	friend istream& operator>>(istream& in, Bookmark& p);
};
istream& operator>>(istream& in, Bookmark& p){
	in >> p.pag;
	cout << "Descriere: ";
	delete[] p.descriere;
	char buff[100];
	//cin.ignore();
	//gets(buff);
	cin >> buff;
	p.descriere = new char[strlen(buff) + 1];
	strcpy(p.descriere, buff);
	return in;
}
ostream& operator<<(ostream& out, Bookmark& p){
	out << endl << "ID: " << p.getId() << " -> " << p.getPag();
	return out;
}
ofstream& operator<<(ofstream& fout, Bookmark& p){
	fout << endl << "ID: " << p.getId() << " -> " << p.getPag();
	return fout;
}

void main(){
	PaginaWeb p1;
	PaginaWeb p2("www.ase.ro", 5);
	PaginaWeb p3 = p2;
	cin >> p1;
	p2.setAdresa("www.csie.ase.ro");
	p1 += 1; //incrementare rating
	cout << p1 << p2 << p3;
	cout << endl;

	Bookmark b1(1, p2);
	Bookmark b2(2, p3, "Pagina ASE");
	b1.setDescriere("Pagina Web ASE");
	if (b2 > b1)
		cout << endl << b2.getUrl() << " are rating mai mare";
	else cout << endl << b1.getUrl() << " are rating mai mare";
	cout << b1;
	cin >> b1;
	cout << "Lungime URL: " << (int)b1;
	cout << endl << b1.getUrl() << " are ratingul " << b1.getRating() << " din maxim " << PaginaWeb::getRatingMaxim();
	cout << endl;

	Bookmark ** bookmarks = new Bookmark *[100];
	int nrBookmarks = 0;
	cout << "No bookmarks:";
	cin >> nrBookmarks;
	for (int i = 0; i < nrBookmarks; i++){
		PaginaWeb p;
		Bookmark b(1, p);
		//cin >> b;
		//*bookmarks[i] = b;
		cin >> *bookmarks[i];
	}
	for (int i = 0; i < nrBookmarks; i++){
		cout << bookmarks[i] << endl;
	}
	
	Bookmark::printLista(*bookmarks, nrBookmarks, "Favorite.txt", 3);
	
	cout << endl;
}