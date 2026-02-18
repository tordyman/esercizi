#include <iostream>
using namespace std;
enum metallo{RAME,ARGENTO,ORO};
class catena {

    friend ostream& operator<<(ostream& os,const catena&);

    struct elem {
        metallo val; // il dato
        elem *next; //puntatore a prossimo elemento È un puntatore. Non contiene il prossimo anello, ma l'indirizzo di memoria dove si trova il prossimo anello.
    }; //Importante: L'ultimo anello della catena avrà next = NULL che concluderà il percorso
    elem *testa; //È il puntatore al primo anello. se testa è a NULL la catena è vuota
    elem *coda;  //è il puntatore all'ultimo elemento
    int num; //è un contatore, tiene traccia di quanti anelli ci sono
public:

    catena();
    catena (const catena& );
    catena& operator=(const catena&);
    void inserisci(metallo);
    int estrai();
    int estrai(metallo);
    int operator%(int);
    int operator!();
    ~catena();
};

catena::catena() {
    testa=NULL;
    coda=NULL;
    num=0; //la catena è vuota
    }

catena::catena(const catena& s) {
    testa=NULL;
    coda=NULL;
    num = 0;
    if (s.testa!=NULL) {
        //se esistono valori da copiare
        testa = new elem;         // 1. Creo il primo anello nuovo
        testa->val = s.testa->val;// 2. Copio il valore (es. ORO) dalla testa
        num++;                    // 3. Conto il primo anello
        elem *tmp = testa;        //tmp è un puntatore elem che punta a testa e lo useremo per modificare le cose
        elem *aux = s.testa->next; //secondo anello
        while (aux != NULL) {
            tmp->next = new elem; //Il Costruttore (tmp) guarda avanti (next) e crea un nuovo anello vuoto (new elem).
            tmp = tmp->next; //Il Costruttore salta sul nuovo anello appena creato.
            tmp->val = aux->val; //tmp copia il val di aux
            tmp->val = aux->val; //aux va all'anello dopo della sua lista
            num++; //il numero di elementi si incrementa
        }
        coda = tmp; //la coda è l'ultimo elemento di tmp
        tmp->next = NULL; //l'ultimo anello è collegato a null tramite next
    }
}

catena &catena::operator=(const catena &s) {

    if (this != &s) {
        //cancella
        elem *tmp = testa;
        while (testa != NULL) {
            testa = testa->next;
            delete tmp;
            tmp = testa;
        }
        //poi copia
        num = 0;
        testa = coda = NULL;
        if (s.testa != NULL) {
            testa = new elem;
            testa->val = s.testa->val;
            num++;
            elem *tmp = testa, *aux = s.testa->next;
            while (aux != NULL) {
                tmp->next = new elem;
                tmp = tmp->next;
                tmp->val = aux->val;
                aux = aux->next;
                num++;
            }
            coda = tmp;
            tmp->next = NULL;
        }
    }
    return *this;
}


void catena::inserisci(metallo v) { //crei un nuovo anello di quel tipo di metallo

    elem *tmp = new elem; //Chiede al computer lo spazio per UN SOLO anello(struct elem) in memoria dinamica , è diverso da se ci mettessi le parentesi []
    /*
    elem *p1 = new elem;     // OK: Oggetto singolo
    delete p1;               // OK: Cancello oggetto singolo

    elem *p2 = new elem[1];  // OK: Array di 1 elemento
    delete[] p2;             // OK: Cancello l'array
    */
    //VA USATO -> PERCHE' NON ABBIAMO LA STRUCT ELEM MA SOLO UN PUNTATORE AD ESSO

    tmp->val = v; //vai su tmp entra in val e scrivi v(es:ORO)
    tmp->next = NULL; //null è il segnale di stop che ci sta a dire che dopo non c'è niente nella lista
    if (num == 0) //se la catena è vuota
        testa = coda = tmp; //il primo elemento sarà uguale sia in testa che in coda, perchè è una lista a un solo elemento
    else {
        coda->next = tmp; //coda punta all'anello A, dentro A abbiamo next che punta a NULL perchè è l'ultimo, cambi next all'anello B
        coda = coda->next; //ora facciamo ripuntare la coda all ultimo (anello B)
    }
    num++; //la catena si incrementa di un elemento
}

int catena::estrai() {
    if (num == 0) //se la lista è vuota non estrae niente
        return 0;
    elem *tmp = testa; //il nostro tmp sarà in l'elemento in testa
    testa = testa->next; //spostastiamo il puntatore testa a quello prima dell elemento in testa
    delete tmp; //cancelliamo tmp
    num--; //leviamo un elemento dalla lista
    return 1;
}

int catena::estrai(metallo v) {
    if (testa == NULL)
        return 0;
    elem *tmp, *prec;
    for (tmp = testa; tmp != NULL && tmp->val != v; tmp = tmp->next)
        //prendo l'anello in testa; e continuo il ciclo finchè la condizione non viene rispettata(anello diverso da NULL e diverso da valore diverso da v);tmp= prossimo tmp
        prec = tmp;
    if (tmp == NULL)
        return 0;
    if (tmp == testa) //se il primo anello da togliere è la testa
        testa = tmp->next; // cambio posizione della testa
    else
        prec->next = tmp->next; //prendiamo l'anello precedente il suo next diventa e lo poniamo uguale al next di tmp (così da collegare i bracci)
    num--;
    return 1;
}

int catena::operator%(int v) {
    elem *tmp;
    int cont;
    for (tmp=testa;tmp!=NULL;tmp=tmp->next) {
        if (tmp->val==v)
        cont++;
    }
    return cont;
}

int catena::operator!() {
return num;
}

int main() {
    cout<<"ciao"<<endl;
}

catena::~catena() {
    elem *tmp = testa; //crea un elemento in testa
    while (testa != NULL) { //finche testa non è NULL
        testa = testa->next; //sposti la testa sul prossimo anello
        //Se cancellassi subito l'anello corrente, perderesti l'informazione su dove si trova il prossimo (perché l'indirizzo next è scritto dentro l'anello che stai per distruggere).
        delete tmp; //Cancella dalla memoria l'anello puntato da tmp
        tmp = testa; //Sposti il puntatore "demolitore" (tmp) sulla nuova posizione di testa
    }
}


ostream &operator<<(ostream &os, const catena& s)
{
    catena::elem *tmp;
    for (tmp = s.testa; tmp != NULL; tmp = tmp->next) {
        if (tmp->val == RAME)
            os << 'R';
        else if (tmp->val == ARGENTO)
            os << 'A';
        else
            os << 'O';
    }
    return os;
}