#include<iostream>
#include<cstdlib>

using namespace std;

float suma(float a, float b);
float resta(float a, float b);
float multiplicacion(float a, float b);
float division(float a, float b);

int main() {
	int option = 0;
	float num1 = 0;
	float num2 = 0;
	
	cout << "Ingrese la accion a efectuar: " << endl;
	cout << "1 - Sumar\n2 - Restar\n3 - Multiplicar\n4 - Division\n" << endl;
	
	cin >> option;
	
	if(option > 4 || option < 1) {
		cout << "Opcion invalida." << endl;
		return 0;
	}
	
	cout << "Ingrese el primer numero: ";
	cin >> num1;
	
	cout << "Ingrese el segundo numero: ";
	cin >> num2;
	
	switch(option) {
		case 1:
			cout << "La suma de " << num1 << " y " << num2 << " es " << suma(num1, num2) << endl;
			break;
		case 2:
			cout << "La resta de " << num1 << " y " << num2 << " es " << resta(num1, num2) << endl;
			break;
		case 3:
			cout << "La multiplicacion de " << num1 << " y " << num2 << " es " << multiplicacion(num1, num2) << endl;
			break;
		case 4:
			if(num2 == 0) {
				cout << "\nNo se puede dividir entre cero." << endl;
				return 0;
			}
			cout << "La division de " << num1 << " entre " << num2 << " es " << division(num1, num2) << endl;
			break;
		/*
			No necesitamos mostrar nada en caso de ingresar
			un valor invalido, la validacion ya se hace mas arriba.
		*/
		default: cout << "";
	}
	
	system("PAUSE");
	
	return EXIT_SUCCESS;
	
}

float suma(float a, float b) {
	return a + b;
}

float resta(float a, float b) {
	return a - b;
}

float multiplicacion(float a, float b) {
	return a * b;
}

float division(float a, float b) {
	return a / b;
}




