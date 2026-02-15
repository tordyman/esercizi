#include <iostream>
using namespace std;
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.
int main() {
    int v[4];
    *v = 1; // v ⇔ &v[0], *v ⇔ v[0]
    *(v + 1) = 10; // *(v + i) ⇔ v[i], *(v + 1) ⇔ v[1]
    int *p = v;
    p += 3;
    *(p - 1) = 100;
    *p = 1000;
    p = v;
    cout << '[' << 4 << "]<" << *p;
    for (int i = 1; i < 4; i++) // [4] <1, 10, 100, 1000>
        cout << "," << *(p + i);
    cout << ">\n";
    int u[4] = { 1, 7, 3, 4 };
    int *p1 = &u[1], *p2 = &u[4];
    cout << p2 - p1 << '\n'; // 2 (elementi)
   //cout << long int(p2) - long int(p1) << '\n'; // 8 (byte)

}