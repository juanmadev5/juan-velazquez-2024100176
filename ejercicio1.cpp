#include<iostream>

using namespace std;

int main() {
	
	int day;
	
	cout << "Ingrese un dia de la semana (1-7) \n";
	cin >> day;
	
	switch(day) {
		case 1:
			cout << "Domingo";
			break;
		case 2:
			cout << "Lunes";
			break;
		case 3:
			cout << "Martes";
			break;
		case 4:
			cout << "Miercoles";
			break;
		case 5:
			cout << "Jueves";
			break;
		case 6:
			cout << "Viernes";
			break;
		case 7:
			cout << "Sabado";
			break;
		default:
			// si se ingresan numeros que no esten entre 1 y 7 caen aqui
			cout << "Opcion invalida\n";
			break;
	}
	
	return 0;
}
