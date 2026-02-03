#include <iostream>
using namespace std;

enum seme {PICCHE,CUORI,QUADRI,FIORI};

class MazzoDaGioco {
    int mazzo[10][4];
    friend ostream& operator<<(ostream&, const MazzoDaGioco&);

public:
    MazzoDaGioco() {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                mazzo[i][j]=0;
            }
        }

    }
    MazzoDaGioco(seme s,int v) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                mazzo[i][j]=0;
            }
        }
        if (v>=1 && v<=10) {
        mazzo[v-1][s]=1;
        }
    }
    MazzoDaGioco(seme s) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                mazzo[i][j]=(s==j)?1:0;
            }
        }
    }

    MazzoDaGioco(int v) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                mazzo[i][j]=(v-1==i)?1:0;
            }
        }
    }

    MazzoDaGioco& operator+=(const MazzoDaGioco& m) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                mazzo[i][j]+=m.mazzo[i][j];
            }
        }
        return  *this;
    }

    MazzoDaGioco& operator-=(const MazzoDaGioco& m) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                if (mazzo[i][j]>=m.mazzo[i][j]) {
                    mazzo[i][j]-=m.mazzo[i][j];
                }
                else
                    mazzo[i][j]=0;
            }
        }
        return  *this;
    }

    MazzoDaGioco& operator%=(seme s) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                if (j!= s) {
                    mazzo[i][j]=0;
                }
            }
        }
        return  *this;
    }

    MazzoDaGioco& operator%=(int v) {
        for(int i=0;i<10;i++) {
            for(int j=PICCHE;j<FIORI;j++) {
                if (i!= v-1) {
                    mazzo[i][j]=0;
                }
            }
        }
        return  *this;
    }

};

ostream& operator<<(ostream& os, const MazzoDaGioco& m) {

    int somma=0;

    for(int i=0;i<10;i++) {
        for(int j=PICCHE;j<FIORI;j++) {

            somma+=m.mazzo[i][j];


            return os<<somma;
        }
    }
}

int main() {

}