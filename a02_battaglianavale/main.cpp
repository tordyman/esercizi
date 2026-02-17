/* Una BattagliaNavale rappresenta una tabella del celebre gioco battaglia navale. La tabella � un quadrato
di NxN caselle, ognuna delle quali pu� essere occupata da una (sezione di) nave o da acqua. Ciascuna
casella � identificata da una coppia di coordinate x e y, ognuna delle quali varia da 0 a N-1. La casella
di coordinate 0,0 � quella in alto a sinistra. Le operazioni che possono essere effettuate su una
BattagliaNavale sono le seguenti:

� BattagliaNavale b;
Costruttore di default, che inizializza una BattagliaNavale b di dimensioni 10x10. All�inizio, le caselle
sono tutte acqua.

� BattagliaNavale b(N);
Costruttore che inizializza una BattagliaNavale b di dimensioni NxN. All�inizio, le caselle sono tutte acqua.

� BattagliaNavale b1(b);
Costruttore di copia, che inizializza la BattagliaNavale b1 col valore di b.

� b1 = b
Operatore di assegnamento, che sostituisce il valore della BattagliaNavale risultato b1 con quello di b.

� b.naveOriz(x, y, dim)
Operazione che posiziona una nave nella BattagliaNavale b. La nave � disposta orizzontalmente, ha
l�estremit� sinistra che occupa la casella x,y, ed � lunga dim caselle. La funzione fallisce se le caselle
che la nave andrebbe ad occupare non sono tutte acqua. L�operazione ritorna un�indicazione di successo
(1) o fallimento (0).

� b.naveVert(x, y, dim)
Come la funzione precedente, ma la nave stavolta � disposta verticalmente con l�estremit� superiore
che occupa la casella di coordinate x,y.

� b.fuoco(x, y)
Operazione che colpisce la (sezione di) nave che si trova sulle coordinate x,y di b, se tale (sezione di)
nave esiste. L�operazione restituisce 1 se � stata colpita una nave, 0 se non � stata colpita nessuna nave
oppure se la (sezione di) nave era gi� stata colpita in precedenza.

� cout << b
Operatore di uscita per il tipo BattagliaNavale. L�uscita ha la forma seguente:
- - - - - -
- - o o o o
- - - - o -
o x o - o -
- - - - x -
- o o - - -
La BattagliaNavale sopra rappresentata ha 6x6 caselle, ognuna delle quali � rappresentata dal carattere
�-� nel caso di acqua, �o� nel caso di (sezione di) nave non colpita, o �x� nel caso di (sezione di) nave
colpita.

� b.maxOriz()
Operazione che restituisce la lunghezza del segmento orizzontale di acqua (cio� non occupato da navi,
colpite o meno) pi� lungo presente in tutta la BattagliaNavale b. Nell�esempio di BattagliaNavale
mostrato sopra, l�operazione restituisce 6, corrispondente al segmento di acqua nella prima riga.

� b.maxVert()
Come la funzione precedente, ma il segmento � verticale. Nell�esempio di BattagliaNavale mostrato
sopra, l�operazione restituisce 4, corrispondente ai segmenti nella quarta e nell�ultima colonna.

� ~BattagliaNavale()
Distruttore.

Mediante il linguaggio C++, realizzare il tipo di dati astratti definito dalle precedenti specifiche.
Individuare le eventuali situazioni di errore, e metterne in opera un corretto trattamento.


 */

#include <iostream>
using namespace std;

enum STATO{ACQUA,NAVE,COLPITA};

class BattagliaNavale{

 friend ostream& operator<<(ostream& ,const BattagliaNavale&);
 STATO STA;
 STATO* cc;
 int dim;

public:

 BattagliaNavale(int = 10);
 BattagliaNavale(const BattagliaNavale&);
 BattagliaNavale& operator=(const BattagliaNavale&);
 int naveOriz(int,int,int);
 int naveVert(int,int,int);
 int fuoco(int, int);
 int maxOriz();
 int maxVert();
 ~BattagliaNavale();
};


BattagliaNavale::BattagliaNavale(int v) {
  dim=(v<2)?2:v;

  cc = new STATO[dim*dim];
  for(int i=0;i<dim*dim;i++) {
   cc[i]=ACQUA;
  }
}

BattagliaNavale::BattagliaNavale(const BattagliaNavale& b){
 dim=b.dim;

 cc = new STATO[dim*dim];
 for(int i=0;i<dim*dim;i++) {
  cc[i]=b.cc[i];
 }
}

BattagliaNavale& BattagliaNavale::operator=(const BattagliaNavale& b) {

 if (this != &b) {
  if (dim=b.dim) {
   delete[]cc;
   cc=new STATO[dim*dim];
  }
  for(int i=0;i<dim*dim;i++)
   cc[i]=b.cc[i];
 }
 return *this;
}

int BattagliaNavale::naveOriz(int x, int y, int lung) {
 int pos=(x-1)*dim+y;
 int vmax=dim-y; //vmax sono gli spazi massimi che mancano
 if (lung>vmax-1) {
  return 0;
 }
 for(int i=0;i<lung;i++) {
  if (cc[pos]!=ACQUA)
   return 0;
  cc[pos]=NAVE;
  pos++;
 }
 return 1;
}

int BattagliaNavale::naveVert(int x, int y, int lung) {
 int pos=(x-1)*dim+y;
 int vmax=dim-x;
 if (lung>vmax-1) {
  return 0;
 }
 for(int i=0;i<lung;i++) {
  if (cc[pos]!=ACQUA)
   return 0;
  cc[pos]=NAVE;
  pos=pos+dim;
 }
 return 1;
}

int BattagliaNavale::fuoco(int x,int y) {
 int pos=(x-1)*dim+y;
 if (cc[pos]!=NAVE)
  return 0;
 cc[pos]=COLPITA;
 return 1;
}

int BattagliaNavale::maxOriz() {
 int maxAcqua=0;
 for(int i=0;i<dim;i++) {
  int cont=0;
  for (int j=0;j<dim;j++) {
   if (cc[j]==ACQUA) {
    cont++;
   }
  }
  if (cont>maxAcqua) {
   maxAcqua=cont;
  }
 }
 return maxAcqua;
}

int BattagliaNavale::maxVert() {
 int maxAcqua=0;
 for(int i=0;i<dim;i++) {
  int cont=0;
  for (int j=0;j<dim;j++) {
   if (cc[j+(dim*(j-1))]==ACQUA) {
    cont++;
   }
  }
  if (cont>maxAcqua) {
   maxAcqua=cont;
  }
 }
 return maxAcqua;
}

BattagliaNavale::~BattagliaNavale() {
 delete[]cc;
}

ostream& operator<<(ostream& os,const BattagliaNavale& b) {
 for(int i=0;i<b.dim;i++) {
  for (int j=0;j<b.dim;j++) {

   if (b.cc[j]==ACQUA)
    os<<'-'<<' ';

   else if(b.cc[j]==COLPITA)
    os<<'x'<<' ';

   else if(b.cc[j]==NAVE)
    os<<'o'<<' ';
  }
  os<<'\n';
 }
 return os;
}



int main() {

};