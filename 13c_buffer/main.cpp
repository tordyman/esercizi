#include <iostream>
using namespace std;

enum prio { ALTA=1, BASSA=0 };

class Buffer {

    struct priorità{
    int nelem;
    int pros_in;
    int pros_out;
    int* v;
    };

    int dim;
    priorità pp[2];

public:
    Buffer(int=1);
    Buffer(const Buffer& );
    Buffer& operator=(const Buffer&);
    int inserisci(int,prio);
    int estrai(int,prio);
    int inserisci(int);
    int estrai(int);
    int operator!() const {
    return pp[1].nelem + pp[0].nelem;
    }
    int operator%(prio p) const {
        return pp[p].nelem;
    }

    ~Buffer() {
        delete[] pp[1].v;
        delete[] pp[0].v;
    }
};

Buffer::Buffer(int n) {
    dim=n;
    for (int i=0;i<2;i++) {
        pp[i].nelem=0;
        pp[i].pros_in=0;
        pp[i].pros_out=0;
        pp[i].v=new int[dim];
    }

}

Buffer::Buffer(const Buffer& b) {

    dim=b.dim;

    for (int i=0;i<2;i++) {
        pp[i].pros_in = b.pp[i].pros_in;
        pp[i].pros_out = b.pp[i].pros_out;
        pp[i].nelem = b.pp[i].nelem;

        pp[i].v= new int[dim];
        for ( int i=0; i<dim; i++)
            pp[i].v[i]=b.pp[i].v[i];

    }
}

Buffer& Buffer::operator=( const Buffer& b){
    if (this != &b) {
        for (int i=0;i<2;i++) {
            pp[i].pros_in=b.pp[i].pros_in;
            pp[i].pros_out=b.pp[i].pros_out;
            pp[i].nelem=b.pp[i].nelem;
            if (dim!=b.dim) {
                delete[]pp[i].v;
                dim=b.dim;
                pp[i].v=new int[dim];
            }
            for (int i=0;i<dim;i++) {
                pp[i].v[i] = b.pp[i].v[i];
            }
        }
    }
    return *this;
    }

int Buffer::inserisci(int val, prio p) {

    if (pp[p].nelem<dim) {

        pp[p].v[pp[p].pros_in++]=val;
        pp[p].pros_in++;
        if (pp[p].pros_in == dim)
            pp[p].pros_in = 0;
        pp[p].nelem++;
        return 1;
    }
    return 0;
    }

int Buffer::estrai(int val, prio p) {

    if (pp[p].nelem>0) {

        val=pp[p].v[pp[p].pros_out++];
        pp[p].pros_out++;
        if (pp[p].pros_out == dim)
            pp[p].pros_out = 0;
        pp[p].nelem--;
        return 1;
    }
    return 0;
}

int Buffer::inserisci(int val) {
    if (inserisci(val, ALTA)==1)
        return 1;

        return inserisci(val, BASSA);
    }

int Buffer::estrai(int val) {
    if (estrai(val, ALTA)==1)
        return 1;

    return estrai(val, BASSA);
}

int main() {

}