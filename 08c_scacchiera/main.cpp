#include <iostream>
using namespace std;

enum colore{BIANCO,NERO,ROSSO};
enum stato{LIBERA,OCCUPATA};

class Scacchiera{

    class casella {
        stato st;
        colore col;
    public:
    casella(){st=LIBERA;}
    };
    int dim;
    casella *cc;

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

Scacchiera& Scacchiera::operator*=(colore c){

}

Scacchiera& Scacchiera::operator-=(colore c){

}

Scacchiera& Scacchiera::operator/=(colore c){

}

int main() {

}