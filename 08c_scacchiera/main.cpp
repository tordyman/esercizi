#include <iostream>
using namespace std;

enum colore{BIANCO,NERO,ROSSO};
enum stato{LIBERA,OCCUPATA};

class Scacchiera{

friend ostream& operator<<(ostream&, const Scacchiera&);

    class casella {
        stato st;
        colore col;
    public:
        casella(){st=LIBERA;}
        void occupa(){st=OCCUPATA;}
        void libera(){st=LIBERA;}
        int qualestato() const { return (st == LIBERA) ? 1 : 0; } // Ritorna 1 (true) se LIBERA, 0 (false) se OCCUPATA
        colore qualecolore() const { return col; }
    };
    int dim;
    casella *cc;
    int valida(int,colore); //funzione che servirà solo alle funzioni membro quindi la metto quì e non nel pubblic dove invece vanno funzioni utili nel main

public:
    Scacchiera(int= 1);
    Scacchiera(const Scacchiera&);
    Scacchiera& operator=(const Scacchiera&);
    Scacchiera& operator+=(colore);
    Scacchiera& operator*=(colore);
    Scacchiera& operator-=(colore);
    Scacchiera& operator/=(colore);
    ~Scacchiera(){delete[] cc;}
};


int Scacchiera::valida(int i,colore c) {

    int riga;
    int colonna;

    if (c==NERO){
        riga=i/dim; //questo calcolo ci darà il numero di righe
        colonna=i%dim; //questo invece il numero di colonne
        return((riga+colonna)%2);
    }
    if (c==BIANCO) {
        riga=i/dim; //questo calcolo ci darà il numero di righe
        colonna=i%dim; //questo invece il numero di colonne
        return!((riga+colonna)%2);
    }
    if (c==ROSSO) {
        return(1);
    }


}

Scacchiera::Scacchiera(int n) {
    dim = n > 0 ? n : 1;
    cc = new casella[dim * dim];
}

Scacchiera::Scacchiera(const Scacchiera& s) {
    dim = s.dim;
    int lun = dim * dim;
    cc = new casella[lun];
    for (int i = 0; i < lun; i++)
        cc[i] = s.cc[i];

    
}

Scacchiera& Scacchiera::operator=(const Scacchiera& s){
    if (this != &s) {
        delete[] cc;
        dim=s.dim;
        cc=new casella[dim*dim];
        for (int i = 0; i < (dim*dim); i++)
            cc[i] = s.cc[i];
    }

    return *this;
}

// += : Occupa la PRIMA casella libera del colore specificato
Scacchiera& Scacchiera::operator+=(colore c) {
    for (int i = 0; i < (dim * dim); i++) {
        if (valida(i, c) && cc[i].qualestato()) { // Se valida e libera
            cc[i].occupa();
            break; // Esco subito dopo averne occupata una!
        }
    }
    return *this;
}

Scacchiera& Scacchiera::operator*=(colore c){
    for (int i =0;i<(dim*dim);i++){
        if (valida( i, c) && (cc[i].qualestato()))
            cc[i].occupa();
    }
    return *this;
}

Scacchiera& Scacchiera::operator-=(colore c){
    for (int i=0;i<(dim*dim);i++){
        if (cc[i].qualecolore()==c && !cc[i].qualestato())
            cc[i].libera();
    }
    return *this;
}

Scacchiera& Scacchiera::operator/=(colore c){

    for (int i=0;i<(dim*dim);i++){
        if (cc[i].qualecolore()!=c && !cc[i].qualestato())
            cc[i].libera();
    }
    return *this;
}

ostream& operator<<(ostream& os, const Scacchiera& s) {
    {
        for (int i = 0; i < s.dim; i++) {
            for (int j = 0; j < s.dim; j++) {
                os << ((i + j) % 2 ? "n:" : "b:");
                if (s.cc[i * s.dim + j].qualestato()==OCCUPATA)
                    switch ( s.cc[i * s.dim + j].qualecolore() ) {
                    case BIANCO:
                            os << 'B';
                            break;
                    case NERO:
                            os << 'N';
                            break;
                    case ROSSO:
                            os << 'R';
                    }
                else
                    os << '-';
                if (j < s.dim - 1)
                    os << ' ';
            }
            if (i < s.dim - 1)
                os << '\n';
        }
        return os;
    }


}

int main() {

}