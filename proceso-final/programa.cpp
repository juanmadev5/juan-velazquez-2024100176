#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define CLIENTS_FILE "clients.txt"
#define TICKETS_FILE "tickets.txt"
#define LOCKED_USERS_FILE "locked-users.txt"
#define MAX_ATTEMPTS 3

struct User {
    int accountNumber;
    int pin;
    string name;
    double balance;
};

User currentUser;
int ticketNumber = 1;

bool isAccountLocked(int accountNumber);
void lockAccount(int accountNumber);
bool loadUserFromFile(int accountNumber, int pin);
bool login();
void showMenu();
void queryBalance();
void depositMoney();
void withdrawMoney();
void changePin();
void showTicket(string transactionType, double amount, double previousBalance);

int main() {
    int option;
    int menuOption;

    cout << "====================================\n";
    cout << "       BIENVENIDO AL CAJERO\n";
    cout << "====================================\n";

    do {
        cout << "\n========== MENU DE ACCESO ==========\n";
        cout << "1. Iniciar sesion\n";
        cout << "2. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> option;

        switch (option) {
            case 1:
                if (login()) {
                    cout << "\nBienvenido/a, " << currentUser.name << "!\n";

                    do {
                        showMenu();
                        cout << "Seleccione una opcion: ";
                        cin >> menuOption;

                        switch (menuOption) {
                            case 1:
                                queryBalance();
                                break;
                            case 2:
                                depositMoney();
                                break;
                            case 3:
                                withdrawMoney();
                                break;
                            case 4:
                                changePin();
                                break;
                            case 5:
                                cout << "\nCerrando sesion...\n";
                                break;
                            default:
                                cout << "\nOpcion invalida.\n";
                        }
                    } while (menuOption != 5);
                }
                break;

            case 2:
                cout << "\nGracias por utilizar nuestro cajero.\n";
                break;

            default:
                cout << "\nOpcion invalida.\n";
        }
    } while (option != 2);

    return 0;
}

// Verifica si la cuenta ya está registrada en el archivo de bloqueados
bool isAccountLocked(int accountNumber) {
    ifstream file(LOCKED_USERS_FILE);

    if (!file.is_open()) {
        return false; // Si el archivo no existe, no hay cuentas bloqueadas aún
    }

    int lockedAcc;
    while (file >> lockedAcc) {
        if (lockedAcc == accountNumber) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Guarda la cuenta en el archivo de bloqueados
void lockAccount(int accountNumber) {
    ofstream file(LOCKED_USERS_FILE, ios::app);
    if (file.is_open()) {
        file << accountNumber << "\n";
        file.close();
    }
}

// Carga el usuario leyendo del archivo txt
bool loadUserFromFile(int accountNumber, int pin) {
    ifstream file(CLIENTS_FILE);

    if (!file.is_open()) {
        return false;
    }

    int acc, p; // cuenta y pin
    string n; // nombre
    double bal; // saldo

    while (file >> acc >> p >> n >> bal) {
        if (acc == accountNumber && p == pin) {
            currentUser.accountNumber = acc;
            currentUser.pin = p;
            currentUser.name = n;
            currentUser.balance = bal;
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool login() {
    int account;
    int pin;
    int attempts = 0;

    cout << "\n========== INICIAR SESION ==========\n";
    cout << "Numero de cuenta: ";
    cin >> account;

    // Verificamos antes de pedir el PIN si la cuenta ya está bloqueada permanentemente
    if (isAccountLocked(account)) {
        cout << "\nEsta cuenta se encuentra bloqueada por seguridad.\n";
        return false;
    }

    while (attempts < MAX_ATTEMPTS) {
        cout << "PIN: ";
        cin >> pin;

        if (loadUserFromFile(account, pin)) {
            cout << "\nInicio de sesion exitoso.\n";
            return true;
        }

        attempts++;
        cout << "\nCuenta o PIN incorrectos.\n";

        if (attempts < MAX_ATTEMPTS) {
            cout << "Intentos restantes: " << (MAX_ATTEMPTS - attempts) << "\n";
        }
    }

    // Si se agotan los intentos, guardamos la cuenta en el archivo de bloqueados
    lockAccount(account);
    cout << "\nAcceso bloqueado por demasiados intentos. Cuenta registrada en bloqueados.\n";
    return false;
}

void showMenu() {
    cout << "\n========== MENU PRINCIPAL ==========\n";
    cout << "1. Consultar saldo\n";
    cout << "2. Depositar dinero\n";
    cout << "3. Retirar dinero\n";
    cout << "4. Cambiar PIN\n";
    cout << "5. Cerrar sesion\n";
    cout << "====================================\n";
}

void queryBalance() {
    cout << "\n========== CONSULTA DE SALDO ==========\n";
    cout << "Titular: " << currentUser.name << "\n";
    cout << "Numero de cuenta: " << currentUser.accountNumber << "\n";
    cout << "Saldo disponible: Gs. " << currentUser.balance << "\n";
}

void depositMoney() {
    double amount;
    double previousBalance;

    cout << "\n========== DEPOSITO ==========\n";
    cout << "Ingrese el monto a depositar: Gs. ";
    cin >> amount;

    if (amount <= 0) {
        cout << "\nEl monto debe ser mayor a cero.\n";
        return;
    }

    previousBalance = currentUser.balance;
    currentUser.balance += amount;

    cout << "\nDeposito realizado correctamente.\n";
    showTicket("DEPOSITO", amount, previousBalance);
}

void withdrawMoney() {
    double amount;
    double previousBalance;

    cout << "\n========== RETIRO ==========\n";
    cout << "Ingrese el monto a retirar: Gs. ";
    cin >> amount;

    if (amount <= 0) {
        cout << "\nEl monto debe ser mayor a cero.\n";
        return;
    }

    if (amount > currentUser.balance) {
        cout << "\nSaldo insuficiente.\n";
        return;
    }

    previousBalance = currentUser.balance;
    currentUser.balance -= amount;

    cout << "\nRetiro realizado correctamente.\n";
    showTicket("RETIRO", amount, previousBalance);
}

void changePin() {
    int currentPin;
    int newPin;

    cout << "\n========== CAMBIO DE PIN ==========\n";
    cout << "Ingrese su PIN actual: ";
    cin >> currentPin;

    if (currentPin != currentUser.pin) {
        cout << "\nPIN incorrecto.\n";
        return;
    }

    cout << "Ingrese su nuevo PIN: ";
    cin >> newPin;

    if (newPin < 1000 || newPin > 9999) {
        cout << "\nEl PIN debe tener 4 digitos.\n";
        return;
    }

    currentUser.pin = newPin;
    cout << "\nPIN actualizado correctamente.\n";
}

void showTicket(string transactionType, double amount, double previousBalance) {
    char answer;

    cout << "\n====================================\n";
    cout << "           COMPROBANTE\n";
    cout << "====================================\n";
    cout << "Numero de ticket: " << ticketNumber << "\n";
    cout << "Cuenta: " << currentUser.accountNumber << "\n";
    cout << "Titular: " << currentUser.name << "\n";
    cout << "Operacion: " << transactionType << "\n";
    cout << "Monto: Gs. " << amount << "\n";
    cout << "Saldo anterior: Gs. " << previousBalance << "\n";
    cout << "Saldo actual: Gs. " << currentUser.balance << "\n";
    cout << "====================================\n";

    cout << "\nDesea guardar el ticket? (S/N): ";
    cin >> answer;

    if (answer == 'S' || answer == 's') {
        ofstream file(TICKETS_FILE, ios::app);

        if (file.is_open()) {
            file << "\n====================================\n";
            file << "           COMPROBANTE\n";
            file << "====================================\n";
            file << "Numero de ticket: " << ticketNumber << "\n";
            file << "Cuenta: " << currentUser.accountNumber << "\n";
            file << "Titular: " << currentUser.name << "\n";
            file << "Operacion: " << transactionType << "\n";
            file << "Monto: Gs. " << amount << "\n";
            file << "Saldo anterior: Gs. " << previousBalance << "\n";
            file << "Saldo actual: Gs. " << currentUser.balance << "\n";
            file << "====================================\n";
            file.close();

            cout << "\nTicket guardado correctamente.\n";
        } else {
            cout << "\nError al crear el archivo.\n";
        }
    } else {
        cout << "\nTicket no guardado.\n";
    }

    ticketNumber++;
}