#include <iostream>
using namespace std;

class Piramide {
    int dim;
    int *array;
    public:
    Piramide(int=1);
    Piramide(const Piramide&);
    Piramide& operator= (const Piramide&);
    Piramide& nuovovalore(int, int, int);
    int valore(int, int, int&)const;
    Piramide& specchia();
    ~Piramide();
};


Piramide::Piramide(int n) {
    dim=(n>0)?n:1;
    array = new int[dim*(dim+1)/2];
    for(int i=0;i<dim*(dim+1)/2;i++) {
        array[i] = 0;
    }
}

Piramide::Piramide(const Piramide & s) {
    dim=s.dim;
    array = new int[dim*(dim+1)/2];
    for(int i=0;i<dim*(dim+1)/2;i++) {
        array[i] = s.array[i];
    }
}

Piramide& Piramide::operator= (const Piramide & s) {
    if(this!=&s) {
        delete [] array;
        dim=s.dim;
        array = new int[dim*(dim+1)/2];
        for(int i=0;i<dim*(dim+1)/2;i++) {
            array[i] = s.array[i];
        }
    }
    return *this;
}

Piramide &Piramide::nuovovalore(int m, int n, int v) {

    if (m>=0 && m<dim) { //la riga m non esiste se la dim è più grande
        if (n>=0&& n<=m) { //nella riga m il massimo n sara m
            array[(m*(m+1)/2)+n]=v;
        }
    }
    return *this;
}

int Piramide::valore(int m, int n, int &v) const {//modifica direttamente la variabile nel main
    if (m>=0 && m<dim) {
        if (n>=0&& n<=m) {
            v=array[(m*(m+1)/2)+n];
            return 1;
        }
        return 0;
    }
}

Piramide &Piramide::specchia() {
    for (int i;i<dim;i++) {
        int m=i*(i+1)/2;
        for (int j;j<(i+1)/2;j++) {
            int x= array[m+j];
            array[m+j]=array[m+i-j];
            array[x +i-j]=x;
        }
    }
}

int main() {

}