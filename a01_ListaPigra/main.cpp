/*Una lista pigra � una lista di elementi interi che ritarda l'effettiva cancellazione dei propri elementi
fintanto che questi sono meno di M, costante definita a priori (es. M=3). Al raggiungimento di questa
soglia, la lista viene automaticamente compattata, ovvero vengono effettivamente rimossi dalla lista gli
elementi cancellati. Le operazioni che possono essere effettuate su una lista pigra sono le seguenti:

� ListaPigra l;
Costruttore di default, che inizializza una lista pigra l vuota.

� ListaPigra l(l1);
Costruttore di copia, che inizializza la lista pigra l coi valori della lista pigra l1.

� l = l1
Operatore di assegnamento, che sostituisce i valori della lista pigra risultato l con quelli della lista pigra
l1.

� l.inserisci(v)
Inserisce in fondo alla lista pigra l il valore v.

� l.cancella(v)
Cancella tutti gli elementi della lista pigra l che hanno valore v. Restituisce il numero di occorrenze di
v cancellate. Nel caso di raggiungimento della soglia M, la lista viene automaticamente compattata.

� !l
Operatore di negazione logica, che restituisce il numero di elementi (non cancellati) nella lista.

� cout << l
Operatore di uscita per il tipo ListaPigra. L�uscita ha la forma seguente:
7, [3], 5, 2, 2
Dove ci sono quattro elementi non cancellati di valore 7, 5, 2, 2, e un elemento cancellato (ma non
ancora rimosso) di valore 3. Gli elementi sono visualizzati nell�ordine di inserimento, con all�inizio quello
inserito per primo.

� v
Distruttore.

Mediante il linguaggio C++, realizzare il tipo di dati astratti definito dalle precedenti specifiche.
Individuare le eventuali situazioni di errore, e metterne in opera un corretto trattamento*/
*/

#include <iostream>
using namespace std;

class ListaPigra{

    friend ostream& operator<<(ostream& os,const ListaPigra&);
    int const M=3;
    int cont;

    struct elem {
        int val;
        elem* next;
    };
    int num;
    elem* testa;
    elem* coda;

    void copia(const ListaPigra&);
    void elimina();

public:

    ListaPigra();
    ListaPigra(const ListaPigra&);
    ListaPigra& operator=(const ListaPigra&);
    void inserisci(int);
    int cancella(int);
    int operator!()const;
    ~ListaPigra();
};

void ListaPigra::copia(const ListaPigra& l) {
    num=l.num;
    testa=NULL;
    coda=NULL;
    if (l.testa!=NULL) {
        testa = new elem;
        testa->val=l.testa->val;
        elem* TMP= testa;
        elem* AUX= l.testa->next;
        while (AUX!=NULL) {

            TMP=new elem;
            TMP=TMP->next;
            TMP->val=AUX->val;
            AUX=AUX->next;
        }
        coda=TMP;
        TMP->next=NULL;
    }
}

void ListaPigra::elimina() {
    elem* TMP =testa;
    while (testa!=NULL) {
        testa=TMP->next;
        delete TMP;
        TMP=testa;
    }
    coda=NULL;
    num=0;
}

ListaPigra::ListaPigra() {
    num=0;
    testa=NULL;
    coda=NULL;
}

ListaPigra::ListaPigra(const ListaPigra& l) {
    copia(l);
}

ListaPigra& ListaPigra::operator=(const ListaPigra& l) {
    if (this != &l) {
        copia(l);
        elimina();
    }
    return *this;
}

void ListaPigra::inserisci(int v) {

    elem* TMP=new elem;
    TMP->val=v;
    TMP->next=NULL;
    if (num==0) {
        testa=coda=TMP;
    }
    else {
        coda->next=TMP;
        coda=TMP;
    }
    num++;
}

int ListaPigra::cancella(int v) {
    if (num==0)
        return 0;
    int trovati=0;
    elem* prec=NULL;
    elem* TMP=testa;

    while(TMP!=NULL) {
        if (TMP->val==v) {

            if (TMP==testa) {
                testa=TMP->next;
            }
            else{
                prec->next = TMP->next;
            }

            if (TMP==coda) {
                coda=prec;
            }

            //cancello
            elem* da_eliminare = TMP;
            TMP = TMP->next;
            delete da_eliminare;
            num--;
            cont++;
            trovati++;
        }
        else{
            prec=TMP;
            TMP=TMP->next;
        }
    }
    if (cont>=M) {
        elimina();
    }
    return trovati;
}

int ListaPigra::operator!() const {
    return num;
}

ostream& operator<<(ostream& os,const ListaPigra& l) {

    ListaPigra::elem* TMP=l.testa;

    while (TMP != NULL) {

        if (l.testa == NULL) {

            return os;
        }

        // Stampiamo il valore dell'elemento
        os << TMP->val;

        // Se non siamo all'ultimo elemento, stampiamo una virgola e uno spazio
        if (TMP->next != NULL) {
            os << ", ";
        }

        // Avanziamo al nodo successivo
        TMP = TMP->next;
    }

    return os;
}


ListaPigra::~ListaPigra() {
  elimina();
}

int main(){
}
