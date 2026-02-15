#include <iostream>
using namespace std;

class batteria{

    class pila {

        int cap;
        int inf;
        int sup;
        int cima;
        int* elem;

    public:
        int piena() const { return (cima == cap); }
        int vuota() const { return (cima == 0); }
        int compatibile(int) const;
        void limiti(int i, int s) { inf = i; sup = s; cima = 0; }
        int pop(int);
        int push(int);
        int top(int) const;
        pila(int = 1, int = 0, int = 1); //costruttore
        pila(const pila&); //costruttora di copia
        pila& operator=(const pila&); //operatore di assegnamento
        ~pila(){delete[] elem;}
    };

    int dim;
    pila* pp; //pp è il nostro vettore dinamico formato da pile

public:

    batteria(int = 1 ,int = 1 ,int = 2);
    batteria(const batteria&);
    batteria& operator=(const batteria&);
    batteria& limiti(int, int, int);
    batteria& push(int);
    int pop(int);
    int top(int) const;
    int pn(int) const;
    int vt(int) const;

    ~batteria(){delete[] pp;}
};
//--------------classe pila---------
batteria::pila::pila(int c, int i, int s) {
    cap = c;
    inf = i;
    sup = s;
    cima= 0; //perchè per adesso la pila è vuota
    elem = new int [cap];
}

batteria::pila::pila(const pila& p) {
    cap=p.cap;
    inf=p.inf;
    sup=p.sup;
    cima=p.cima;
    elem = new int[cap];
    for (int i = 0; i < cima; i++)
        elem[i] = p.elem[i];
}

batteria::pila& batteria::pila::operator=(const pila& p) {
    if (this != &p) {
        delete[] elem;
        cap=p.cap;
        inf=p.inf;
        sup=p.sup;
        cima=p.cima;
        elem = new int[cap];
        for (int i = 0; i < cima; i++)
            elem[i] = p.elem[i];
    }
    return* this;
}

int batteria::pila::compatibile(int v) const {
    return(v<=sup && v>=inf); //torna 1 se la condizione si avvera ovvero che v è compreso tra il lim sup e inf
}

int batteria::pila::pop(int v) {
    if (compatibile(v)&& !vuota())
        return elem[--cima];
    return -1;
}

int batteria::pila::push(int v) {
    if (compatibile(v) && !piena()) {
        //se il valore che vogliamo inserire è compatibile e la pila non è piena inserisce, incrementa la cima e ritorna 0 sennò -1
        elem[cima++]=v;
        return 0;
    }
    return -1;
}

int batteria::pila::top(int v) const {
    if ( compatibile(v) && !vuota() )
        return elem[cima - 1];
    return -1;
}

//--------------classe batteria----------


batteria::batteria(int n, int c, int m) {
    dim = (n > 0) ? n : 1;
    c = (c > 0) ? c : 1;
    m = (m > 2) ? m : 2;

    pp = new pila[dim];

    for (int i = 0; i < dim; i++)
        pp[i]=pila(c ,i*m,(i + 1) * m - 1);
}

batteria::batteria(const batteria& s) {
    dim=s.dim;
    for(int i=0;i<dim;i++) {
        pp[i] = s.pp[i];
    }
}

batteria& batteria::operator=(const batteria& s) {
    if (this != &s) {
        delete[]pp;
        dim=s.dim;
        pp=new pila[dim];
        for (int i=0;i<dim;i++)
            pp[i]=s.pp[i];
    }
    return *this;
}

batteria& batteria::limiti(int i, int inf, int sup) {
    if (i >= 0 && i < dim && inf >= 0 && sup > inf) {

        pp[i].limiti(inf,sup);
    }
    return *this;
}

batteria& batteria::push(int v) {
    if (v>0) {
        int i=0;
        while (i < dim && pp[i].push(v) == -1)
            i++;
    }
    return *this;
}

int batteria::pop(int v) {
    if (v>0) {
        int i = dim-1;
        while (i<0 && pp[i].pop(v)==-1) {
            i--;
        }
        return pp[i].pop(v);
    }
}

int batteria::top(int v) const{

        if (v>0) {
            int i = dim-1;
            while (i<0 && pp[i].top(v)==-1) {
                i--;
            }
            return pp[i].top(v);
        }
}

int batteria::pn(int v) const {

    for (int i=0;i<dim;i++) {

        if (pp[i].compatibile(v)&& !pp[i].piena()) {
            return 0;
        }
    }
    return 1;
}

int batteria::vt(int v) const {
    for (int i=0;i<dim;i++) {

        if (pp[i].compatibile(v)&& !pp[i].vuota()) {
            return 0;
        }
    }
    return 1;
}

int main(){

}
