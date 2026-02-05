#include <iostream>
#include <string>

class Documento {
public:
    std::string titolo;

    Documento(std::string t) : titolo(t) {}

    // Costruttore di copia
    Documento(const Documento &altro) {
        titolo = altro.titolo;
        std::cout << "[LOG] Costruttore di copia: sto trasportando il documento '" << titolo << "' fuori dalla funzione." << std::endl;
    }
};

// FUNZIONE CHE RESTITUISCE UN OGGETTO PER VALORE
Documento creaDocumentoStandard() {
    Documento temp("Contratto_Standard"); // Oggetto locale
    return temp; // Qui viene chiamato il costruttore di copia per restituire il valore
}

int main() {
    std::cout << "Chiamata a creaDocumentoStandard()..." << std::endl;

    // L'oggetto restituito dalla funzione viene "copiato" dentro 'mioDoc'
    Documento mioDoc = creaDocumentoStandard();

    std::cout << "Documento ricevuto nel main: " << mioDoc.titolo << std::endl;

    return 0;
}