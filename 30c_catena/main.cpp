#include <iostream>
using namespace std;
enum metallo{RAME,ARGENTO,ORO};
class catena {

    struct elem {
        metallo val;
        elem *next;
    };
    elem *testa;
    elem *coda;
    int num;
public:

    catena();
    catena (const catena& );
    catena & operator=(const catena&);
    void inserisci(metallo);
    int estrai();
    int estrai(metallo);
};

catena::catena() {
    testa=NULL;
    coda=NULL;
    }

void catena::inserisci(metallo v) {
    elem *tmp = new elem;

}



int main() {
    cout<<"ciao"<<endl;
}