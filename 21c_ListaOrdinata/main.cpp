#include <iostream>
using namespace std;

class ListaOrdinata {
    class lista {
    struct elem {
        int val;
        elem* next;
    };
        elem* testa;
        //elem* coda; //in un lista ordinata non ti serve perchè l'inserimento non è sempre in fondo
        int num;
        void copia(const lista&);
        void elimina();
    public:
        lista();
        lista(const lista&);
        lista& operator=(const lista&);
        void inserisci(int);
        int estrai(int);
        ~lista();
    };
    lista pari, dispari; //creo due liste
public:
    void inserisci(int);
    int estrai(int);
    int estraipari();
    int estaridispari();
    int operator[](int);
    int operator!();
};

void ListaOrdinata::lista::copia(const lista& s) {
    num=s.num;
    testa=NULL;
    if (s.testa!=NULL) {
        testa=new elem; //creamo un nuovo elem in testa
        testa->val=s.testa->val;
        elem* tmp=testa;
        elem* aux=s.testa->next;
        while (aux!=NULL) {

        }
    }
}

void ListaOrdinata::lista::elimina() {

}


int main() {

}