#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Personaje {
    string nombre;
    int vida;
    int ataque;
};

Personaje pedirDatos();
void registrarPersonaje();
void verPersonajes();
void mostrarMenu();

int main() {
    int opcion;

    do {
        mostrarMenu();
        cin >> opcion;

        // Si el usuario escribe algo que no es numero, limpiamos el buffer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            opcion = 0;
        }

        switch (opcion) {
            case 1:
                registrarPersonaje();
                break;
            case 2:
                verPersonajes();
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida, intente de nuevo." << endl;
        }
    } while (opcion != 3);

    return 0;
}

void mostrarMenu() {
    cout << endl;
    cout << "===== REGISTRO DE PERSONAJES =====" << endl;
    cout << "[1] Registrar nuevo personaje" << endl;
    cout << "[2] Ver todos los personajes guardados" << endl;
    cout << "[3] Salir" << endl;
    cout << "Elija una opcion: ";
}

Personaje pedirDatos() {
    Personaje p;

    cin.ignore(1000, '\n');  // limpiar el enter que quedo del menu
    cout << "Nombre: ";
    getline(cin, p.nombre);

    cout << "Vida: ";
    cin >> p.vida;
    while (cin.fail() || p.vida <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Valor invalido. Ingrese una vida mayor a 0: ";
        cin >> p.vida;
    }

    cout << "Ataque: ";
    cin >> p.ataque;
    while (cin.fail() || p.ataque <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Valor invalido. Ingrese un ataque mayor a 0: ";
        cin >> p.ataque;
    }

    return p;
}

void registrarPersonaje() {
    Personaje p = pedirDatos();

    ofstream archivo;
    archivo.open("personajes.txt", ios::app);  // ios::app agrega al final

    if (!archivo.is_open()) {
        cout << "Error: no se pudo abrir el archivo para escribir." << endl;
        return;
    }

    // Cada personaje va en una linea: nombre;vida;ataque
    archivo << p.nombre << ";" << p.vida << ";" << p.ataque << endl;

    archivo.close();
    cout << "Personaje guardado correctamente." << endl;
}

void verPersonajes() {
    ifstream archivo;
    archivo.open("personajes.txt");

    if (!archivo.is_open()) {
        cout << "No hay personajes guardados todavia (el archivo no existe)." << endl;
        return;
    }

    Personaje p;
    int contador = 0;

    cout << endl;
    cout << "----- LISTA DE PERSONAJES -----" << endl;

    while (getline(archivo, p.nombre, ';')) {
        archivo >> p.vida;
        archivo.ignore(); 
        archivo >> p.ataque;
        archivo.ignore(); 

        contador++;
        cout << contador << ". Nombre: " << p.nombre
             << " | Vida: " << p.vida
             << " | Ataque: " << p.ataque << endl;
    }

    if (contador == 0) {
        cout << "El archivo esta vacio." << endl;
    }

    archivo.close();
}