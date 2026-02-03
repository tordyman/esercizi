#include <iostream>
using namespace std;

class Righello {
    friend ostream& operator<<(ostream&, const Righello&);
    struct casella {
        int valore; //val casella
        int pedina; //val pedina (se 0  pedina non presente)
    };
    casella* rig;
    int dim;

    public:
    Righello(int = 1);
    Righello(const Righello&);
    Righello& operator = (const Righello&);
    Righello& operator +=(int);
    Righello& operator -=(int);
    Righello& valore(int, int);
    Righello& operator *=(int);
    Righello& operator /=(int);

    ~Righello() { delete[] rig; }
};

Righello::Righello(int n) {
    dim=(n>0)?n:1;
    rig = new casella[dim];

    for(int i=0; i<dim; i++) {
        rig[i].valore=1;
        rig[i].pedina=0;
    }
}

Righello::Righello(const Righello& s)
{
    dim=s.dim;
    rig = new casella[dim];
    for (int i=0; i<dim; i++) {
        rig[i]=s.rig[i];
    }

}

Righello& Righello::operator=(const Righello& s) {
    if (this != &s) {//se i due indirizzi di memoria non coincidono
        if (dim != s.dim) { //se la dimensione non coincide
            delete[] rig; //dealloca il vettore dimamico
            dim=s.dim;
            rig = new casella[dim]; //creiamo un nuovo vettore dimanico con la specifica dimensione
        }
        for (int i = 0; i < dim; i++)
            rig[i] = s.rig[i];
    }
    return *this;
}

Righello& Righello::operator+=(int n) {
    if (n>0) {

        for (int i = dim - 1; i >= 0; i--)
            if (!rig[i].pedina && rig[i].valore >= n) { // se la pedina è vuota e il valore della casella corrisponde a n
                rig[i].pedina = n; //allora prenderà il valore
                break;
            }
    }
return *this;
}

Righello& Righello::operator-=(int n) {

    if (n>0) {
        for (int i = dim - 1; i >= 0; i--) {
            if (rig[i].pedina = n) {
                rig[i].pedina=0;
                break;
            }
        }
    }
    return *this;
}

Righello &Righello::valore(int i, int n) {

    if (n>0 && i>=0 && i<dim && !rig[i].pedina) {
        rig[i].valore = n;
        return *this;
    }

}

Righello& Righello::operator*=(int n) {
    if (n>0) {
        for (int i = 0; i < dim; i++){
            if (!rig[i].pedina && rig[i].valore >= n) {// se la pedina è vuota e il valore della casella corrisponde a n
                rig[i].pedina = n; //allora prenderà il valore
            }
        }
    }
    return *this;
}

Righello& Righello::operator/=(int n) {
    if (n>0) {
        for (int i = 0; i < dim; i++){
            if (!rig[i].pedina && rig[i].valore >= n) {
                rig[i].pedina = 0;
            }
        }
    }
    return *this;
}

ostream& operator<<(ostream& os, const Righello& s) {
    for (int i=0;i<s.dim;i++) {
        os<<'('<<s.rig[i].valore<<')';
        if (s.rig[i].pedina != 0)
            os << s.rig[i].pedina;
        if (i < s.dim - 1)
            os << ", ";
    }
    return os;
}

int main() {

}