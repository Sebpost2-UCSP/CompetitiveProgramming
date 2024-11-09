#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int, int> Pair;

struct graph {
    //Usaremos para leer un txt
    ifstream myfile;
    int vertices;
    //Representa los padres de los vertices, sirve para hallar el camino que tomamos
    vector<int> Padres;
    //Muestra maximo flujo de una arista
    vector<int> flujo_actual;
    //Muestra capacidad y flujo de una arista
    vector<vector<Pair>> flujo;
    //Lista de adyacencia del grafo
    vector<vector<int>> grafo;
    int maxh;

    //Lee un txt y construye grafo.
    /*graph(string txt) {
        myfile.open("Matrices/"+txt);
        myfile >> vertices;
        int t;
        myfile >> t;
        int t1, t2, t3;
        grafo.resize(vertices);
        Padres.resize(vertices);
        flujo.resize(vertices);
        flujo_actual.resize(vertices);
        for (int i = 0; i < vertices; i++) {
            flujo[i].resize(vertices);
        }
        for (int i = 0; i < t; i++) {
            myfile >> t1 >> t2 >> t3;
            grafo[t1].push_back(t3);
            grafo[t3].push_back(t1);
            flujo[t1][t3] = make_pair(0, t2);
        }
    }*/

    graph() {
        maxh=0;
        cin >> vertices;
        int t;
        cin >> t;
        int t1, t2, t3;
        grafo.resize(vertices);
        Padres.resize(vertices);
        flujo.resize(vertices);
        flujo_actual.resize(vertices);
        for (int i = 0; i < vertices; i++) {
            flujo[i].resize(vertices);
        }
        for (int i = 0; i < t-2; i++) {
            cin >> t1 >> t2 >> t3;
            if (t3 > maxh) {
                maxh = t3;
            }
            grafo[t1].push_back(t3);
            grafo[t3].push_back(t1);
            flujo[t1][t3] = make_pair(0, t2);
        }
    }

    //haya minimo
    int min(int a, int b) {
        if (a < b)
            return a;
        else
            return b;
    }

    //recorrido bfs, termina cuando encuentra un camino aumentado
    int bfs(int s, int t) {
        queue<int> q;
        //Para cada bfs cambiamos el vertice de padres
        for (int i = 0; i < vertices; i++) {
            Padres[i] = -1;
        }
        Padres[s] = -2;
        q.push(s);
        flujo_actual[s] = INT_MAX;

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = 0; i < grafo[u].size(); i++) {
                int v = grafo[u][i];
                if (Padres[v] == -1)
                {
                    if (flujo[u][v].second - flujo[u][v].first > 0)
                    {
                        // Actualizando el nodo del padre.
                        Padres[v] = u;
                        // Viendo capacidad minima de la arista residual
                        flujo_actual[v] = min(flujo_actual[u], flujo[u][v].second - flujo[u][v].first);
                        // Si el bfs encuentra el nodo t, termina
                        if (v == t) return flujo_actual[v];

                        // Agrega nodo adyacente a la cola
                        q.push(v);
                    }
                }
            }
        }
        return 0;
    }

    //Encontramos un camino aumentado
    int max_flow(int source, int sink) {
        int max = 0;
        while (1) {
            int flujo_a = bfs(source, sink);
            // Si no hay mas caminos, devuelve 0
            if (flujo_a == 0)
                break;
            int t = sink;
            max += flujo_a;
            // Encontramos el flujo de la matriz
            while (t != source)
            {
                flujo[Padres[t]][t].first += flujo_a;
                flujo[t][Padres[t]].first -= flujo_a;
                t = Padres[t];
            }
        }
        return max;
    }

    //Encuentra todos los caminos aumentados, suma los flujos, halla flujo maximo.
    int EdmondsKarp(int s,int t)
    {
        int flujo_a = 0;
        while (true)
        {
            int flujo_c = max_flow(s,t);
            if (flujo_c == 0) 
                break;
            else 
                flujo_a += flujo_c;
        }
        return flujo_a;
    }
};

int main()
{
    graph a;
    int max=a.EdmondsKarp(1, a.maxh);
    cout << max << endl;
}