#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const char* ARCHIVO_MOVIMIENTOS = "movimientos.txt";
const char* ARCHIVO_SALDO = "saldo.txt";

struct Usuario {
    int cuenta;
    int pin;
    string nombre;
    double saldo;
};

Usuario usuarioActual;
int numeroTicket = 1;

// Usuario precargado (su saldo se lee y se guarda en saldo.txt)
Usuario clienteCarlos = {1002, 4321, "Carlos", 500000.0};

// Prototipos de funciones
void cargarSaldo();
void guardarSaldo();
bool iniciarSesion();
void menuPrincipal();
void consultarSaldo();
void depositar();
void retirar();
void verMovimientos();
void registrarMovimiento(string operacion, double monto, double saldoAnterior);
void mostrarTicket(string operacion, double monto, double saldoAnterior);
void escribirTicket(ostream& salida, string operacion, double monto, double saldoAnterior);

int main() {
    int opcion;

    cout << fixed;          // muestra los montos sin notacion cientifica
    cout.precision(0);      // sin decimales (guaranies)

    cargarSaldo();          // recupera el ultimo saldo guardado

    cout << "====================================\n";
    cout << "       BIENVENIDO AL CAJERO\n";
    cout << "====================================\n";

    do {
        cout << "\n========== MENU DE ACCESO ==========\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            if (iniciarSesion()) {
                cout << "\nBienvenido/a, " << usuarioActual.nombre << "!\n";
                menuPrincipal();
            }
        } else if (opcion == 2) {
            cout << "\nGracias por utilizar nuestro cajero.\n";
        } else {
            cout << "\nOpcion invalida.\n";
        }
    } while (opcion != 2);

    return 0;
}

// Lee el saldo guardado; si el archivo no existe, queda el saldo inicial
void cargarSaldo() {
    ifstream archivo(ARCHIVO_SALDO);
    double saldoGuardado;

    if (archivo >> saldoGuardado) {
        clienteCarlos.saldo = saldoGuardado;
    }
}

// Sobrescribe saldo.txt con el saldo actual
void guardarSaldo() {
    ofstream archivo(ARCHIVO_SALDO);
    archivo << fixed;
    archivo.precision(0);
    archivo << clienteCarlos.saldo;
}

bool iniciarSesion() {
    int cuenta, pin;

    cout << "\n========== INICIAR SESION ==========\n";
    cout << "Numero de cuenta: ";
    cin >> cuenta;
    cout << "PIN: ";
    cin >> pin;

    if (cuenta == clienteCarlos.cuenta && pin == clienteCarlos.pin) {
        usuarioActual = clienteCarlos;
        cout << "\nInicio de sesion exitoso.\n";
        return true;
    }

    cout << "\nCuenta o PIN incorrectos.\n";
    return false;
}

void registrarMovimiento(string operacion, double monto, double saldoAnterior) {
    ofstream archivo(ARCHIVO_MOVIMIENTOS, ios::app);
    if (archivo.is_open()) {
        archivo << fixed;
        archivo.precision(0);
        archivo << "Ticket #" << numeroTicket
                << " | Cuenta: " << usuarioActual.cuenta
                << " | Titular: " << usuarioActual.nombre
                << " | Operacion: " << operacion
                << " | Monto: Gs. " << monto
                << " | Saldo anterior: Gs. " << saldoAnterior
                << " | Saldo actual: Gs. " << usuarioActual.saldo << "\n";
        archivo.close();
    }
}

void verMovimientos() {
    ifstream archivo(ARCHIVO_MOVIMIENTOS);
    string linea;

    cout << "\n========== HISTORIAL DE MOVIMIENTOS ==========\n";

    if (!archivo.is_open()) {
        cout << "No hay movimientos registrados todavia.\n";
        return;
    }

    bool hayLineas = false;
    while (getline(archivo, linea)) {
        cout << linea << "\n";
        hayLineas = true;
    }

    if (!hayLineas) {
        cout << "El archivo de movimientos esta vacio.\n";
    }

    archivo.close();
}

void escribirTicket(ostream& salida, string operacion, double monto, double saldoAnterior) {
    salida << "\n====================================\n";
    salida << "           COMPROBANTE\n";
    salida << "====================================\n";
    salida << "Numero de ticket: " << numeroTicket << "\n";
    salida << "Cuenta: " << usuarioActual.cuenta << "\n";
    salida << "Titular: " << usuarioActual.nombre << "\n";
    salida << "Operacion: " << operacion << "\n";
    salida << "Monto: Gs. " << monto << "\n";
    salida << "Saldo anterior: Gs. " << saldoAnterior << "\n";
    salida << "Saldo actual: Gs. " << usuarioActual.saldo << "\n";
    salida << "====================================\n";
}

void mostrarTicket(string operacion, double monto, double saldoAnterior) {
    escribirTicket(cout, operacion, monto, saldoAnterior);
    cout << "\nComprobante emitido en pantalla.\n";
    numeroTicket++;
}

void consultarSaldo() {
    cout << "\n========== CONSULTA DE SALDO ==========\n";
    cout << "Titular: " << usuarioActual.nombre << "\n";
    cout << "Numero de cuenta: " << usuarioActual.cuenta << "\n";
    cout << "Saldo disponible: Gs. " << usuarioActual.saldo << "\n";
}

void depositar() {
    double monto;

    cout << "\n========== DEPOSITO ==========\n";
    cout << "Ingrese el monto a depositar: Gs. ";
    cin >> monto;

    if (monto <= 0) {
        cout << "\nEl monto debe ser mayor a cero.\n";
        return;
    }

    double saldoAnterior = usuarioActual.saldo;
    usuarioActual.saldo += monto;
    clienteCarlos.saldo = usuarioActual.saldo;
    guardarSaldo();

    registrarMovimiento("DEPOSITO", monto, saldoAnterior);
    cout << "\nDeposito realizado correctamente.\n";
    mostrarTicket("DEPOSITO", monto, saldoAnterior);
}

void retirar() {
    double monto;

    cout << "\n========== RETIRO ==========\n";
    cout << "Ingrese el monto a retirar: Gs. ";
    cin >> monto;

    if (monto <= 0) {
        cout << "\nEl monto debe ser mayor a cero.\n";
        return;
    }
    if (monto > usuarioActual.saldo) {
        cout << "\nSaldo insuficiente.\n";
        return;
    }

    double saldoAnterior = usuarioActual.saldo;
    usuarioActual.saldo -= monto;
    clienteCarlos.saldo = usuarioActual.saldo;
    guardarSaldo();

    registrarMovimiento("RETIRO", monto, saldoAnterior);
    cout << "\nRetiro realizado correctamente.\n";
    mostrarTicket("RETIRO", monto, saldoAnterior);
}

void menuPrincipal() {
    int opcion;

    do {
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Depositar dinero\n";
        cout << "3. Retirar dinero\n";
        cout << "4. Ver movimientos\n";
        cout << "5. Cerrar sesion\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: consultarSaldo(); break;
            case 2: depositar();      break;
            case 3: retirar();        break;
            case 4: verMovimientos(); break;
            case 5: cout << "\nCerrando sesion...\n"; break;
            default: cout << "\nOpcion invalida.\n";
        }
    } while (opcion != 5);
}
