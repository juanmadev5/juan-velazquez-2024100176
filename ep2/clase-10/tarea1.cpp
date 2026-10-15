#include<iostream>

using namespace std;

int main() {
	
	char c;
	
	while(true) {
		cout << "Ingrese una vocal minuscula para finalizar el programa\n";
		cin >> c;
		if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
			break;
		}
	}
}
