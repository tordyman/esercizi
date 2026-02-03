#include <iostream>
using namespace std;

class Rotore {

    friend ostream& operator<<(ostream&, const Rotore&);
    int * settore;
    int dim;
    int selettore;

public:
    Rotore(int = 1);
    Rotore(const Rotore&);
    Rotore& operator=(const Rotore&);
    Rotore& inserisci(int); //restituisce l'oggetto
    int estrai(); //restituisce un valore
    int operator%(int) const; //il const l'abbiamo messo poichè la funzione è di sola lettura; non modificherà nessuna variabile interna all'oggetto".
    int operator!() const;
    ~Rotore() { delete[] settore; }
};

Rotore::Rotore(int n){
    dim=(n>0)?n:1;
    selettore=0;
    settore = new int[dim];
    settore[0]=1;
    for (int i = 1; i < dim; i++)
        settore[i] = 0;
}

Rotore::Rotore(const Rotore & r) {
    dim=r.dim;
    selettore=r.selettore;
    settore = new int[dim];
    for (int i=0;i<dim;i++)
        settore[i]=r.settore[i];

}

Rotore& Rotore::operator=(const Rotore& r) {
    if (this != &r){
        if (dim != r.dim) {
            delete[] settore;
            settore = new int[dim];
        }
        selettore=r.selettore;
        for (int i=0;i<dim;i++)
            settore[i]=r.settore[i];
    }
    return *this;
}

Rotore& Rotore::inserisci(int t) {
    if (t >= 0 && t < dim)
        settore[t]++;
    return *this;
}

int Rotore::estrai() {
    //controlliamo le richieste nel settore nella posizione selettore
    //se trova richieste -> richieste -1 & ritorna numero settore
    //senno ruota (++ --) finchè non trova richieste
    //richiesta trovata sposta selettore
    if (settore[selettore]!=0) {
        settore[selettore]--;
        return selettore;
    }
    else {
        for (int i=selettore+1;i<dim;i++) {
            if (settore[i]>0) {
                settore[i]--;
                selettore=i;
                return i;

            }

            for (int j=selettore-1;j>=0;j--) {
                if (settore[j]>0) {
                    settore[j]--;
                    selettore=j;
                    return j;

                }
            }
        }

    }
}

int Rotore::operator%(int t) const {
    if (t >= 0 && t < dim)
        return settore[t];
    return -1;
}

int Rotore::operator!() const {
    int conta=0;
    for(int i=0;i<dim;i++)
        conta+= settore[i];
    return conta;
}

ostream& operator<<(ostream& os, const Rotore& r) {

    for (int i = 0; i < r.dim; i++) {
        if (i == r.selettore)
            os << '[' << r.settore[i] << ']';
        else
            os << r.settore[i];
        if (i != r.dim - 1)
            os << ", ";
    }
    return os;
}


int main() {
cout << "=== TEST CLASSE ROTORE ===" << endl;

    // 1. Test Costruttore
    cout << "\n--- 1. Creazione 04c_Rotore (dimensione 5) ---" << endl;
    Rotore r1(5);
    cout << "Stato iniziale: " << r1 << endl;
    // Atteso: {[1], 0, 0, 0, 0} (il selettore è su 0)

    // 2. Test Inserimento (Concatenato)
    cout << "\n--- 2. Inserimento richieste ---" << endl;
    cout << "Inserisco richiesta in pos 2, 2 (di nuovo) e 4." << endl;
    r1.inserisci(2).inserisci(2).inserisci(4);
    cout << "Stato attuale: " << r1 << endl;
    // Atteso: {[1], 0, 2, 0, 1}

    // 3. Test Operatore ! (Conteggio totale)
    cout << "\n--- 3. Test conteggio totale (!r1) ---" << endl;
    cout << "Totale richieste pendenti: " << !r1 << endl;
    // Atteso: 1 + 2 + 1 = 4

    // 4. Test Operatore % (Lettura valore)
    cout << "\n--- 4. Test ispezione (% 2) ---" << endl;
    cout << "Richieste nella casella 2: " << (r1 % 2) << endl;
    // Atteso: 2

    // 5. Test Estrazione (Logica movimento)
    cout << "\n--- 5. Test Estrazione (estrai) ---" << endl;

    // Estrazione 1: dovrebbe prendere quella in posizione 0 (selettore attuale)
    int pos = r1.estrai();
    cout << "Estratto da pos: " << pos << " -> 04c_Rotore: " << r1 << endl;

    // Estrazione 2: Pos 0 è vuota. Cerca avanti. Dovrebbe trovare pos 2.
    pos = r1.estrai();
    cout << "Estratto da pos: " << pos << " -> 04c_Rotore: " << r1 << endl;
    // Il selettore ora dovrebbe essersi spostato su [2]

    // Estrazione 3: Pos 2 ha ancora 1 richiesta. Dovrebbe restare lì.
    pos = r1.estrai();
    cout << "Estratto da pos: " << pos << " -> 04c_Rotore: " << r1 << endl;

    // 6. Test Costruttore di Copia
    cout << "\n--- 6. Test Copia Profonda ---" << endl;
    Rotore r2 = r1; // Creo r2 uguale a r1
    cout << "r2 (copia): " << r2 << endl;

    r2.inserisci(0); // Modifico r2
    cout << "Ho aggiunto richiesta a r2 in pos 0." << endl;
    cout << "r1 (originale): " << r1 << endl; // Non deve essere cambiato
    cout << "r2 (modificato): " << r2 << endl; // Deve essere cambiato

    // 7. Test Assegnamento
    cout << "\n--- 7. Test Assegnamento (=) ---" << endl;
    Rotore r3(2);
    r3 = r1; // Assegno r1 a r3 (che aveva dimensione diversa)
    cout << "r3 (dopo assegnamento da r1): " << r3 << endl;

    cout << "\n=== FINE TEST ===" << endl;
    return 0;
}
