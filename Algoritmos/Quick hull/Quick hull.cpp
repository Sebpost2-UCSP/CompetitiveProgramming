#include <vector>
#include <iostream>
#include <set>

using namespace std;

#define Pair pair<int, int>
set<Pair> hull;
int LHull(Pair p1, Pair p2, Pair p)
{
    int val = (p.second - p1.second) * (p2.first - p1.first) -
        (p2.second - p1.second) * (p.first - p1.first);
    if (val > 0)
        return 1;
    if (val < 0)
        return -1;
    return 0;

}
//Distancia entre puntos
int Distancia(Pair p, Pair q)
{
    return (p.second - q.second) * (p.second - q.second) +
        (p.first - q.first) * (p.first - q.first);
}
//Distancia del punto p a la linea de p1 a p2
int LineaDistancia(Pair p1, Pair p2, Pair p)
{
    return abs((p.second - p1.second) * (p2.first - p1.first) -
        (p2.second - p1.second) * (p.first - p1.first));
}


void quickHull(Pair a[], int n, Pair p1, Pair p2, int Lado)
{
    int ind = -1;
    int Max = 0;
    //Encontrando punto con maxima distancia
    for (int i = 0; i < n; i++)
    {
        int temp = LineaDistancia(p1, p2, a[i]);
        if (LHull(p1, p2, a[i]) == Lado && temp > Max)
        {
            ind = i;
            Max = temp;
        }
    }

    //Si no encontramos mas puntos, agregamos los ultimos
    if (ind == -1)
    {
        hull.insert(p1);
        hull.insert(p2);
        return;
    }

    //Recurrencia para las dos partes divididas por a[ind]
    quickHull(a, n, a[ind], p1, -LHull(a[ind], p1, p2));
    quickHull(a, n, a[ind], p2, -LHull(a[ind], p2, p1));

}
void printHull(Pair vec[], int n)
{
    if (n < 3)
    {
        cout << "No existe\n";
        return;
    }
    //Hallando puntos con minimo y maximo en eje x
    int min_x = 0, max_x = 0;
    for (int i = 1; i < n; i++)
    {
        if (vec[i].first < vec[min_x].first)
            min_x = i;
        if (vec[i].first > vec[max_x].first)
            max_x = i;
    }

    //Recursivamente hallamos los puntos de un lado de
    //la linea que une los puntos vec[min_x] y vec[max_x]

    quickHull(vec, n, vec[min_x], vec[max_x], 1);

    //Ahora el otro lado

    quickHull(vec, n, vec[min_x], vec[max_x], -1);

    cout << "Los puntos son: ";
    while (!hull.empty())
    {
        cout << "(" << (*hull.begin()).first << ", "
            << (*hull.begin()).second << ") ";
        hull.erase(hull.begin());
    }

}
// Driver code
int main()
{
    Pair vec[] = { {0, 2}, {1, 1}, {2, 2}, {3, 4},
    {0, 0}, {1, 2}, {3, 1}, {3, 3} };
    printHull(vec, sizeof(vec) / sizeof(vec[0]));
    return 0;
}