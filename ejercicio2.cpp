#include<iostream>

using namespace std;

float sum(float a, float b);
float res(float a, float b);
float mul(float a, float b);
float div(float a, float b);

int main() {
	
	int option;
	float a,b;
	
	cout << "-------Calculadora----------\n";
	cout << "Ingrese el primer numero\n";
	cin >> a;
	cout << "Ingrese el segundo numero\n";
	cin >> b;
	
	cout << "Ingrese una opcion\n";
	cout << "1 - Suma\n";
	cout << "2 - Resta\n";
	cout << "3 - Multiplicacion\n";
	cout << "4 - Division\n\n";
	cin >> option;
	
	switch(option) {
		case 1:
			cout << a << " mas " << b << " es " << sum(a,b);
			break;
		case 2:
			cout << a << " menos " << b << " es " << res(a,b);
			break;
		case 3:
			cout << a << " por " << b << " es " << mul(a,b);
			break;
		case 4:
			if(a == 0 || b == 0) {
				cout << "No puede dividir entre cero\n";
			} else {
				cout << "La division de " << a << " entre " << b << " es " << div(a,b);
			}
			break;
		default:
			cout << "Opcion invalida\n";
			return 1;
	}
	cout << "\n\nGracias por usar la calculadora.";
	return 0;
}

// implementamos las funciones prototipadas

float sum(float a, float b) {
	return a + b;
}


float res(float a, float b) {
	return a - b;
}

float mul(float a, float b) {
	return a * b;
}

// se asume que la division entre cero se verifica antes de invocar la funcion
float div(float a, float b) {
	return a / b;
}
