#include <iostream>
# include <stdlib.h>
using namespace std;
enum colore{BIANCO,NERO};
enum stato { LIBERA, OCCUPATA };



void errore(const char*s){ /*è come scrivere:
    char s1[ ] = "Pippo";
    char s2[ ] = { 'p','o','i','\0' };
    char* s3 = "ieri";
    char* s4 = "domani";
    è la stessa ideentica cosa.
    */
        cerr << "Percorso: " << s << '\n'; //uso cerr per scrivere sul canale degli errori
        exit(1);
}

class Percorso {

    class casella {

        colore col;
        stato st;
    public:
        casella(colore =BIANCO);
        void cambiaColore() { col = (col == BIANCO) ? NERO : BIANCO; }
        void occupa() { st = OCCUPATA; }
        void libera() { st = LIBERA; }
        int qualestato() const{return st;};
        int qualecolore() const{return col;};

    };
    int dim;
    casella *cc; //array dinamico di oggetti
    int avanza(int);

public:
    Percorso(int =10,colore=BIANCO);
    Percorso(const Percorso&);
    Percorso& operator=(const Percorso &);
    Percorso& immetti(colore);
    ~Percorso() { delete[] cc; }

};

Percorso::casella::casella(colore c) {
    col = c;       // Assegno il colore passato (che sarà BIANCO di default)
    st = LIBERA;   // Inizializzo anche lo stato (buona prassi)
}



Percorso::Percorso(int n,colore c) {
dim=n;
if (dim<1) {
    errore("Lunghezza errata");
}
    cc = new casella[dim];
    if (c == NERO)
        for (int i = 0; i < dim; i++)
            cc[i].cambiaColore();
}

Percorso::Percorso(const Percorso&p) {
    dim = p.dim;
    cc = new casella[dim];
    for (int i = 0; i < dim; i++)
        cc[i]=p.cc[i];
}

Percorso& Percorso::operator=(const Percorso &p) {
    if (this != &p) { //serve per controllare se l'oggetto è diverso dall'oggetto che si vuole effettivamente copiare guardandolo in memoria
        delete[] cc;
        dim=p.dim;
        cc=new casella[dim];
        for (int i=0;i<dim;i++) {
            cc[i]=p.cc[i];
        }
    }
    return *this;
}

Percorso &Percorso::immetti(colore c) {

    if ((cc[0].qualecolore()==c)&&(cc[0].qualestato()==LIBERA)) {
        int i=avanza(0);
        if (i<dim-1) //questa condizione serve perchè la pedina può finire il percorso
            cc[i].occupa();

    }
    return *this;
}

int Percorso::avanza(int i) {
    // Sposta la pedina dalla casella i-esima alla casella più avanzata
    // possibile

        int j;
        for (j = i + 1; j < dim && !cc[j].qualestato() &&
        cc[i].qualecolore() == cc[j].qualecolore(); j++);
        return j - 1;

}

int main() {
    
}