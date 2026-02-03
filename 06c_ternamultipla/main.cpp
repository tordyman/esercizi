#include <iostream>
using namespace std;

class Terna {

friend ostream& operator<<(ostream&, const Terna&);
friend class TernaMultipla;
int val[3];

public:
    Terna(){
        val[0]=1;
        val[1]=1;
        val[2]=1;
    }
    Terna(const Terna& t);
    Terna& operator=(const Terna& t);
    Terna& modifica(unsigned int, int, int, int);
    int somma(unsigned int);

};

Terna::Terna(const Terna& t) {
    for (int i = 0; i < 3; i++) {
        val[i] = t.val[i];
    }
}

Terna& Terna::operator=(const Terna& t) {
    if (this != &t) {
        for (int i = 0; i < 3; i++) {
            val[i] = t.val[i];
        }
    }
    return *this;
}

Terna& Terna::modifica(unsigned int sel, int a, int b, int c) {
    if (sel & 1)  //Il simbolo & in questo contesto è l'operatore AND bit a bit
        val[0] = (a < 1) ? 1 : a; // fa il controllo per vedere che a non sia 0 o negativo
    if (sel & 2)
        val[1] = (b < 1) ? 1 : b;
    if (sel & 4)
        val[2] = (c < 1) ? 1 : c;
    return *this;
}

int Terna::somma(unsigned int sel) {
    int s = 0;
    if (sel & 1)  //Il simbolo & in questo contesto è l'operatore AND bit a bit
        s+=val[0];
    if (sel & 2)
        s+=val[1];
    if (sel & 4)
        s+=val[2];
    return s;
}

ostream& operator<<(ostream& os, const Terna& t)
{
    return (os << '<' << t.val[0] << ", " << t.val[1] << ", " << t.val[2] << '>');
}

class TernaMultipla {
    friend ostream& operator<<( ostream& , const TernaMultipla&);
    Terna *tt;
    int dim;
    public:
    TernaMultipla(int = 1);
    TernaMultipla(const TernaMultipla&);
    TernaMultipla& operator=(const TernaMultipla&);
    TernaMultipla& modifica(int, const Terna&);
    Terna terna(int) const;
    ~TernaMultipla(){delete[] tt;}
};

TernaMultipla::TernaMultipla(int n) {
    dim = (n > 1) ? n : 1;
    tt = new Terna[dim];
}

TernaMultipla::TernaMultipla(const TernaMultipla& s) {

    dim = s.dim;
    tt = new Terna[dim];
    for (int i = 0; i < dim; i++) {
        tt[i] = s.tt[i];
    }
}

TernaMultipla& TernaMultipla::operator=(const TernaMultipla& s) {
    if (this != &s) {
        delete[] tt;
        dim = s.dim;
        tt = new Terna[dim];
        for (int i = 0; i < dim; i++) {
            tt[i] = s.tt[i];
        }
    }
    return *this;
}

TernaMultipla& TernaMultipla::modifica(int n, const Terna &t) {
    n = (n > dim - 1) ? (dim - 1) : n;

    if (n >= 0) {
        tt[n] = t;
    } else {
        for (int i = 0; i < dim; i++)
            tt[i] = t;
    }

    return *this; // <--- ORA È FUORI: Viene eseguito in entrambi i casi!
}

Terna TernaMultipla::terna(int n) const {
    n = (n > dim - 1) ? (dim - 1) : n; //se un array ha dimensione dim, gli indici validi vanno da 0 a dim - 1
    if (n>=0) {
        return tt[n];
    }
    Terna t(tt[0]); //Invece di partire da zero (0, 0, 0), la inizializza copiando i valori della prima terna dell'array (tt[0]).
        for (int i = 1; i < dim; i++) {
            t.val[0] += tt[i].val[0];
            t.val[1] += tt[i].val[1];
            t.val[2] += tt[i].val[2];
        }

    return t;
}

ostream& operator<<(ostream& os, const TernaMultipla& s) {
    os << '[' << s.dim << ']';
    for (int i=0;i<s.dim;i++) {
        os << s.tt[i]; //questa riga chiama automaticamente l'operatore << della classe Terna
        if (i != s.dim - 1)
            os << ' '; //Stampa uno spazio separatore DOPO la terna, ma solo se NON siamo arrivati all'ultima
    }
    return os;
}

int main() {
    TernaMultipla tm(3); // Crea 3 terne
    Terna t_nuova;
    t_nuova.modifica(7, 10, 20, 30); // Crea una terna <10, 20, 30>

    tm.modifica(0, t_nuova); // Modifica la prima terna

    cout << "Stampa TernaMultipla:" << endl;
    cout << tm << endl;

    cout << "Somma totale (usando n=-1):" << endl;
    cout << tm.terna(-1) << endl;

    return 0;
}