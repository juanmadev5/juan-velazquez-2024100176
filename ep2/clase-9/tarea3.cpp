#include<iostream>
#include<cstdlib>

using namespace std;

int main() {
	
	const int cen = -1;
	int suma = 0;
	float nota = 0, c = 0;
	
	cout << "Introduzca siguiente nota -1 centinela: ";
	cin >> nota;
	
	while(nota != cen) {
		
		c++;
		
		suma += nota;
		cout << "Introduzca la siguiente nota: -1 centinela: ";
		cin >> nota;
	}
	if(c > 0) {
		cout << "media = " << suma / c << endl;
	}
	else {
		cout << "no hay notas ";
	}
	
	
	system("PAUSE");
	return EXIT_SUCCESS;
}
