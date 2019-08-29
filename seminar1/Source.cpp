#include <iostream>
using namespace std;

void methodReadANumber(int *address);

void main() {
	int vb1 = 10;
	int vb2 = 20;
	int *pointer_1;
	void *pointer_2;
	char *pointer_3;

	pointer_1 = (int*)100; // STRONG TYPE RULE (acelasi tip de var)
	pointer_3 = (char*)200; //(_*)--> CAST

	pointer_1 += 1; // 100+4 biti de la INT
	pointer_3 += 1; // 200+1 bit de la CHAR

	pointer_1 = &vb1;
	*pointer_1 = 30;

	cout << "vb1 = " << vb1 << endl;
	cout << "Address of vb1 = " << pointer_1 << endl;

	methodReadANumber(&vb1);
	// OR methodReadANumber(pointer_1);
	cout << "vb1 = " << vb1 << endl;

}

void methodReadANumber(int *address) {
	//int vb1;
	cout << "Give us a number:";
	cin >> *address; //cin >> vb1;
					 //*address = vb1;
}