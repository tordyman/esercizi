#include <iostream>
#include <string>

class Smartphone {
public:
    std::string modello;
    int batteria;

    // Costruttore normale
    Smartphone(std::string m, int b) : modello(m), batteria(b) {}

    // Costruttore di copia: viene chiamato quando passiamo l'oggetto "per valore"
    Smartphone(const Smartphone &altro) {
        modello = altro.modello;
        batteria = altro.batteria;
        std::clog << "[LOG] Chiamato costruttore di copia per: " << modello << std::endl;
    }
};

// FUNZIONE CHE RICEVE PER VALORE
// Qui viene creata una copia locale dell'oggetto 's'
void usaTelefono(Smartphone s) {
    s.batteria = 0; // Scarichiamo la batteria della COPIA
    std::cout << "Dentro la funzione: " << s.modello << " ha batteria al " << s.batteria << "%" << std::endl;
}

int main() {
    Smartphone mioTelefono("iPhone", 100);

    std::cout << "Prima della funzione: " << mioTelefono.batteria << "%" << std::endl;

    // Chiamata alla funzione: qui avviene la "chiamata implicita" al costruttore di copia
    usaTelefono(mioTelefono);

    // L'originale non è cambiato!
    std::cout << "Dopo la funzione: " << mioTelefono.batteria << "%" << std::endl;

    return 0;
}