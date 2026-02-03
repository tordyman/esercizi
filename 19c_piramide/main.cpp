#include <iostream>
using namespace std;

class Piramide {
    friend ostream& operator<<(ostream& os, const Piramide& s);
    int dim;
    int *array;
    public:
    Piramide(int=1);
    Piramide(const Piramide&);
    Piramide& operator= (const Piramide&);
    Piramide& nuovovalore(int, int, int);
    int valore(int, int, int&)const;
    Piramide& specchia();
    ~Piramide(){delete[] array;}
};


Piramide::Piramide(int n) {
    dim=(n>0)?n:1;
    array = new int[dim*(dim+1)/2];
    for(int i=0;i<dim*(dim+1)/2;i++) {
        array[i] = 0;
    }
}

Piramide::Piramide(const Piramide & s) {
    dim=s.dim;
    array = new int[dim*(dim+1)/2];
    for(int i=0;i<dim*(dim+1)/2;i++) {
        array[i] = s.array[i];
    }
}

Piramide& Piramide::operator= (const Piramide & s) {
    if(this!=&s) {
        delete [] array;
        dim=s.dim;
        array = new int[dim*(dim+1)/2];
        for(int i=0;i<dim*(dim+1)/2;i++) {
            array[i] = s.array[i];
        }
    }
    return *this;
}

Piramide &Piramide::nuovovalore(int m, int n, int v) {

    if (m>=0 && m<dim) { //la riga m non esiste se la dim è più grande
        if (n>=0&& n<=m) { //nella riga m il massimo n sara m
            array[(m*(m+1)/2)+n]=v;
        }
    }
    return *this;
}

int Piramide::valore(int m, int n, int &v) const {//modifica direttamente la variabile nel main
    if (m>=0 && m<dim) {
        if (n>=0&& n<=m) {
            v=array[(m*(m+1)/2)+n];
            return 1;
        }
        return 0;
    }
}

Piramide &Piramide::specchia() {
    for (int i=0;i<dim;i++) {
        int m=i*(i+1)/2;
        for (int j=0;j<(i+1)/2;j++) {
            int x= array[m+j];
            array[m+j]=array[m+i-j];
            array[m +i-j]=x;
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const Piramide& s)
{
    int v;
    for (int i = 0; i < s.dim; i++) {
        for (int j = 0; j <= i; j++) {
            s.valore(i, j, v);
            os << v;
            if (j != i)
                os << '\t';
        }
        os << '\n';
    }
    return os;
}

int main() {
    cout << "=== TEST PIRAMIDE ===" << endl;

    // 1. Creazione di una piramide di altezza 4
    // La piramide avrà:
    // Riga 0: 1 elemento
    // Riga 1: 2 elementi
    // Riga 2: 3 elementi
    // Riga 3: 4 elementi
    Piramide p(4);

    // 2. Riempimento con valori
    // Riempiamo in modo che sia facile vedere se specchia funziona.
    // Esempio:
    // 1
    // 2 3
    // 4 5 6
    // 7 8 9 0
    int contatore = 1;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j <= i; j++) {
            // Uso % 10 per avere numeri a una cifra (0-9) per estetica
            p.nuovovalore(i, j, contatore % 10);
            contatore++;
        }
    }

    // 3. Stampa originale
    cout << "\nPiramide Originale:" << endl;
    cout << p << endl;

    // 4. Test Specchia
    // Ci aspettiamo che le righe si invertano:
    // "2 3" -> "3 2"
    // "4 5 6" -> "6 5 4"
    p.specchia();
    cout << "Piramide Specchiata:" << endl;
    cout << p << endl;

    // 5. Test Copia e Assegnamento (Gestione memoria)
    cout << "Test Copia (p2 copiata da p):" << endl;
    Piramide p2 = p; // Costruttore di copia

    // Modifico p2 per vedere se p1 rimane intatta
    p2.nuovovalore(0, 0, 9);

    cout << "P1 (Originale, cima invariata):" << endl;
    cout << p;
    cout << "P2 (Copia, cima modificata a 9):" << endl;
    cout << p2;

    return 0;
}