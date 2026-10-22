#include<iostream>
#include<string>

using namespace std;

struct Personaje {
	string nombre;
	int puntoFuerza;
};

int main() {
	Personaje p1 = {"personaje 1", 110};
	Personaje p2 = {"personaje 2", 1150};
	
	
	if(p1.puntoFuerza == p2.puntoFuerza) {
		cout << " ambos personajes tiene la misma fuerza: " << p1.nombre << " y " << p2.nombre << " " << p1.puntoFuerza << " puntos de fuerza";
		return 0;
	}
	if(p1.puntoFuerza > p2.puntoFuerza) {
		cout << p1.nombre << " es mas fuerte que " << p2.nombre << ". " << p1.puntoFuerza << " puntos de fuerza versus " << p2.puntoFuerza << " puntos de fuerza.";
	} else {
		cout << p2.nombre << " es mas fuerte que " << p1.nombre << ". " << p2.puntoFuerza << " puntos de fuerza versus " << p1.puntoFuerza << " puntos de fuerza.";
	}
}
