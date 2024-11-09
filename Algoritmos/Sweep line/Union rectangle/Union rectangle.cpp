#include <iostream>
#include <algorithm>
using namespace std;

struct evento {
    //id: identificador.
    //estado: si es entrada o salida.
    int id, Estado;
    evento() {}
    evento(int ind, int type){
        this->id = ind;
        this->Estado = type;
    }
};
struct point { int x, y; };

const int CANT_RECT = 30000 + 9;
const int Ini = 0, Fin = 1;
point Rectangulos[CANT_RECT][2];
bool Activados[CANT_RECT];
evento Eventos_v[2 * CANT_RECT], Eventos_h[2 * CANT_RECT];

bool ejeX(evento a, evento b) {
    return Rectangulos[a.id][a.Estado].x < Rectangulos[b.id][b.Estado].x;
}
bool ejeY(evento a, evento b) {
    return Rectangulos[a.id][a.Estado].y < Rectangulos[b.id][b.Estado].y;
}



int main() {
    int test, cases=1;
    cin >> test;
    while (test--) {
        //area que guardaremos.
        long long area = 0;
        //cantidad de rectangulos, y eventos.
        int n = 0, Eventos_total = 0;

        cin >> n;
        for (int i = 0; i < n; ++i) {
            //creamos los rectangulos y los eventos para cada uno (cuando se encuentra el inicio y final)
            cin >> Rectangulos[i][0].x >> Rectangulos[i][0].y >> Rectangulos[i][1].x >> Rectangulos[i][1].y;
            Eventos_v[Eventos_total] = evento(i, Ini), Eventos_v[Eventos_total + 1] = evento(i, Fin);
            Eventos_h[Eventos_total] = evento(i, Ini), Eventos_h[Eventos_total + 1] = evento(i, Fin);
            Eventos_total += 2;
        }
        //hacemos sort para ir de izquierda a derecha y de arriba hacia abajo.
        sort(Eventos_v, Eventos_v + Eventos_total, ejeX);
        sort(Eventos_h, Eventos_h + Eventos_total, ejeY);

        Activados[Eventos_v[0].id] = 1;
        //la linea vertical.
        for (int i = 1; i < Eventos_total; ++i) {
            evento x1 = Eventos_v[i], x2 = Eventos_v[i - 1];
            int contador = 0, y1, valorX, valorY;

            if ((valorX = Rectangulos[x1.id][x1.Estado].x - Rectangulos[x2.id][x2.Estado].x) == 0)
                continue;

            //la linea horizontal.
            for (int j = 0; j < Eventos_total; ++j)
                if (Activados[Eventos_h[j].id]) {
                    if (Eventos_h[j].Estado == Ini) {
                        if (contador++ == 0)
                            y1 = j;
                    }
                    else if (--contador == 0) {
                        valorY = Rectangulos[Eventos_h[j].id][Fin].y - Rectangulos[Eventos_h[y1].id][Ini].y;
                        area += valorX * valorY;
                    }
                }
            Activados[x1.id] = (x1.Estado == Ini);
        }

        cout <<"Case "<<cases<<": " << area << "\n";
        cases++;
    }
    return 0;
}