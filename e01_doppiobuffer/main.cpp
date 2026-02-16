
#include <iostream>
using namespace std;

class Doppiobuffer {

    class Buffercircolare {
        int prox_in, prox_out, num_elem, dim_buffer;
        int *buf;
    public:
        Buffercircolare(int=1);
        Buffercircolare(const Buffercircolare&);
        Buffercircolare& operator=(const Buffercircolare&);
        int inserisci(int);
        int estrai(int&);
        int pieno()const{return(num_elem == dim_buffer);}
        int vuoto()const{return(num_elem==0);}
        ~Buffercircolare() {delete[] buf;}
    };
    Buffercircolare v[2];
public:
    Doppiobuffer(int = 1);
    int inserisci(int,int);
    int estrai(int,int&);
    int sposta(int,int);
    int spostainverso(int,int);
    int operator%(int m);
    int operator!();

};

//-----------Buffercircolare--------------

Doppiobuffer::Buffercircolare::Buffercircolare(int cap) {

    prox_in = prox_out = num_elem = 0;
    dim_buffer=(cap>0)? cap:1;
    buf = new int[dim_buffer];
}

Doppiobuffer::Buffercircolare::Buffercircolare(const Buffercircolare &c) {
    prox_in=c.prox_in;
    prox_out=c.prox_out;
    num_elem=c.num_elem;
    dim_buffer=c.dim_buffer;
    buf = new int[dim_buffer];
    for (int i=0;i<dim_buffer;i++) {
        buf[i]=c.buf[i];
    }
}

Doppiobuffer::Buffercircolare& Doppiobuffer::Buffercircolare::operator=(const Buffercircolare &c) {
    if (this != &c) {
        prox_in=c.prox_in;
        prox_out=c.prox_out;
        num_elem=c.num_elem;
        if (dim_buffer != c.dim_buffer){
            delete[] buf;
            dim_buffer=c.dim_buffer;
            buf=new int[dim_buffer];
        }
        for (int i=0;i<dim_buffer;i++) {
            buf[i]=c.buf[i];
        }
    }
    return *this;
}

int Doppiobuffer::Buffercircolare::inserisci(int v) {

    if (num_elem<dim_buffer) {
        buf[prox_in]=v;
        prox_in++;
        if (prox_in==dim_buffer) {
            prox_in=0;
        }
        num_elem++;
        return 1;
    }
    return 0;
}

int Doppiobuffer::Buffercircolare::estrai(int &n) {
    if (num_elem>0) {
        n=buf[prox_out]; //questo passaggio ci mostra perchè abbiamo dovuto prendere n come riferimento
        prox_out++;
        if (prox_out==dim_buffer) {
            prox_out=0;
        }
        num_elem--;
        return 1;
    }
    return 0;
}


//-----------doppioBuffer----------------

Doppiobuffer::Doppiobuffer(int c) {
    c = (c < 1) ? 1 : c;
    if (c>1) { // viene messo per evitare un passaggio poichè il costruttore di default sa già cosa fare con c=1
        v[0] = Buffercircolare(c);
        v[1] = Buffercircolare(c);
    }
}

int Doppiobuffer::inserisci(int m,int val) {

    if (v[m].pieno())
        return 0;
    v[m].inserisci(val);
    return 1;
}

int Doppiobuffer::estrai(int m,int &val) {
    if (v[m].vuoto())
        return 0;
    return v[m].estrai(val);
}

int Doppiobuffer::sposta(int m, int n) {
    int val=0;
    for (int i=0;i<n;i++) {
        int ris1=v[m].estrai(val);
        if (ris1==0)
            return 0;
        int ris2=v[!m].inserisci(val);
        if (ris2==0)
            return 0;
    }
    return 1;
}

int Doppiobuffer::spostainverso(int m, int n) {
    int* tmp = new int[n];
    int val=0;
    for (int i=0;i<n;i++) {
        int ris1=v[m].estrai(val);
        tmp[i]=val;
    }
    delete[] tmp;
}

// programma incompleto

int main() {



}