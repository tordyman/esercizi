#include <iostream>
#include <stdlib.h>
using namespace std;

void errore(const char* s)
{
    cerr << "Ruota: " << s << '\n';
    exit(1);
}

class Ruota {
public:
    enum statoDiSpicchio { TRASPARENTE, OPACO };
    Ruota(int = 1);



};

Ruota::Ruota(int n) {
if (n<=0) {
    errore("dim non valida");
}

}
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
cout<<"ciao";
}