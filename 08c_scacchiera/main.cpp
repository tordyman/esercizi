#include <iostream>
using namespace std;

enum colore{BIANCO,NERO,ROSSO};

class Scacchiera{

    class casella {
    public:

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

int main() {

}