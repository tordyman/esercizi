#include <iostream>
using namespace std;

enum colore{ROSSO,GIALL0,VERDE};

class ListaColorata{
friend ostream& operator<<(ostream& os,const ListaColorata &);
     struct elem{
          int val;
          colore col;
          elem* next;
     };
     elem *testa;
     elem *coda;
     int num;
     void copia (const ListaColorata&);
     void elimina();
public:
     ListaColorata();
     ListaColorata(const ListaColorata&);
     ListaColorata& operator=(const ListaColorata&);
     int inserisci(colore,int);
     int estrai(colore,int&);
     int operator[](colore);
     int operator%(colore);
     int operator!() const;
     ~ListaColorata(){void elimina();}
};

void ListaColorata::copia(const ListaColorata& t1) {
     testa=NULL;
     coda=NULL;
     num= t1.num;
     if (t1.testa!=NULL) {
          testa=new elem; //crea un nuovo nodo
          testa->val = t1.testa->val;
          testa->col = t1.testa->col;
          coda=testa;

          elem *tmp=testa; //sto puntando alla cose di testa
          elem *aux = t1.testa->next;
          while (aux!=NULL) {
               tmp->next = new elem; //crea un nodo
               tmp = tmp->next; //sposto il puntatore
               tmp->val = aux->val; //copio val
               tmp->col = aux->col; //copio col
               coda=tmp;
               aux =aux->next;
          }
          tmp->next = NULL;
     }
}

void ListaColorata::elimina() {
     elem *tmp = testa;
     while (testa!=NULL) {
          testa=testa->next;
          delete tmp;
          tmp = testa;
     }
}

ListaColorata::ListaColorata(){
     testa=NULL;
     coda=NULL;
     num=0;
}

ListaColorata::ListaColorata(const ListaColorata &t1) {
     copia(t1);
}

ListaColorata &ListaColorata::operator=(const ListaColorata &t1) {
     if (this != &t1) {
          elimina();
          copia(t1);
     }
     return *this;
}

int ListaColorata::inserisci(colore c,int v) {
     elem* tmp = new elem;
     tmp->val=v;
     tmp->col=c;
     tmp->next=NULL;
     if (num==0)
          testa=coda=tmp;
     else {
          coda->next=tmp;
          coda=coda->next;
     }
     num++;
}

int ListaColorata::estrai(colore c,int& v) {
     if (testa==NULL)
          return 0;
     elem *tmp, *prec;
     tmp=testa;
     while (tmp->col!=c && tmp != NULL) {
     prec=tmp;
     tmp=tmp->next;
     }
     if (tmp == NULL)
          return 0;
     if (tmp == testa)
          testa=tmp->next;
     if (tmp == coda)
          coda=prec;
     else
          prec->next=tmp->next;
     v = tmp->val;
     delete tmp;
     num--;
     return 1;
}

int ListaColorata::operator[](colore c) const {
     elem *tmp=testa;
     int contval=0;
     while(tmp != NULL){
          if (tmp->col==c) {
               contval=contval+tmp->val;
          }
          tmp=tmp->next;
     }
     return contval;
}

int ListaColorata::operator%(colore c) {
     elem *tmp=testa;
     int contcol=0;
     while(tmp != NULL){
          if (tmp->col==c) {
               contcol++;
          }
          tmp=tmp->next;
     }
     return contcol;
}

int ListaColorata::operator!() const {
     return num;
}

ostream& operator<<(ostream& os,const ListaColorata& t1) {
     ListaColorata::elem *tmp;
     os<<'<';
     for (tmp = t1.testa; tmp != NULL; tmp = tmp->next) {

          if (tmp->col == ROSSO)
               os << 'R' <<',';
          else if (tmp->col == GIALL0)
               os << 'G'<<',';
          else if (tmp->val == VERDE)
               os << 'V'<<',';
     }
     os<<'>';
     return os;
}

int main(){}
