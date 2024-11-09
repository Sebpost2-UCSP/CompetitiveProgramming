#include <iostream>
#include <string>
#include <map>
using namespace std;

int shift_or(string t, string p)
{
    //tam del patron
    int m = p.length();
    long long mat[256];
    long long R = ~1;

    //si no se a dado ningun patron
    if (m == 0)
    {
        return -1;
    }
    if (m > 63)
    {
        cout << "El patron ingresado es demasiado grande.";
        return -1;
    }
    for (int i = 0; i <= 255; ++i)
    {
        mat[i] = ~0;//inicializa la matriz.
    }
    for (int i = 0; i < m; ++i)
    {
        mat[p[i]] &= ~(1L << i);
    }
    for (int i = 0; i < t.length(); ++i)
    {
        R |= mat[t[i]];
        R <<= 1;
        if ((R & (1L << m)) == 0)
        {
            return i - m + 1;
        }
    }
    return -1;
}

void Buscar(string t, string p)
{
    int position = shift_or(t, p);
    if (position == -1)
    {
        cout << "No hay coincidencia." << endl;
    }
    else
    {
        cout << "Patron encontrado en la pos: " << position << endl;
    }
}

int main() {
    string t;
    cin >> t;
    string p;
    cin >> p;
    Buscar(t, p);
}