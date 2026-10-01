#include<iostream>

using namespace std;

int main() {
	string user = "";
	string password = "";
	int option = 0;
	int num1 = 0;
	int num2 = 0;
	
	cout << "Ingrese su usuario: ";
	cin >> user;
	
	cout << "Ingrese su contrasenha: ";
	cin >> password;
	
	if(user != "juan" || password != "1234") {
		cout << "Credenciales invalidas." << endl;
		return 0;
	}
	
	cout << "\nBienvenido al sistema " << user << "!\n" << endl;
	
	cout << "Ingrese la accion a efectuar: " << endl;
	cout << "1 - Sumar\n2 - Restar\n3 - Dividir\n4 - Multiplicar\n" << endl;
	
	cin >> option;
	
	if(option > 4 || option < 1) {
		cout << "Opcion invalida." << endl;
	}
	
	cout << "Ingrese el primer numero: ";
	cin >> num1;
	
	cout << "Ingrese el segundo numero: ";
	cin >> num2;
	
	switch(option) {
		case 1:
			cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
			break;
		case 2:
			cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
			break;
		case 3:
			if(num2 == 0) {
				cout << "\nNo puede dividir entre cero." << endl;
				break;
			}
			cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
			break;
		case 4:
			cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
			break;
		/*
			No necesitamos mostrar nada en caso de ingresar
			un valor invalido, la validacion ya se hace mas arriba.
		*/
		default: cout << "";
	}
	
	cout << "\nGracias por usar el sistema." << endl;
}






