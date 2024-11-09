#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct kosaraju {
    //Guarda el nodo y sus nodos adyacentes, junto con la version transversa del grafo.
    pair<vector<int>, vector<int>> *Nodo;

    //Stack que usaremos para el algoritmo
    stack < int > Stack;

    //Nodos visitados (para los dfs).
    bool *Visitados;

    //Conjunto de componentes en una SSC, para el cout
    int *Nodo_in;
    vector < int > *Componentes;

    //Guardando cantidad de nodos para no recorrer todos los arrays de visitados.
    int nodes;

    //Ingresamos valores
    kosaraju(int rel,int nodes) {
        this->nodes = nodes;
        Nodo = new pair<vector<int>, vector<int>>[nodes];
        Visitados = new bool[nodes];
        Nodo_in = new int[nodes];
        Componentes = new vector<int>[nodes];
        for (int i = 0; i < nodes; i++) {
            Visitados[i] = 0;
            Nodo_in[i] = 0;
        }
        int cin1, cin2;
        while (rel--) {
            cin >> cin1 >> cin2;
            Nodo[cin1].first.push_back(cin2);
            Nodo[cin2].second.push_back(cin1);
        }
    }

    //Recorre el array y lo pone en la pila.
    void dfsStack(int x) {
        Visitados[x] = true;
        for (int i = 0; i < Nodo[x].first.size(); i++) {
            if (!Visitados[Nodo[x].first[i]]) {
                dfsStack(Nodo[x].first[i]);
            }
        }
        Stack.push(x);
    }

    //Recorre la cola y saca dfs del array transpuesto
    void dfsTransverse(int x, int total) {
        Nodo_in[x] = total;
        Visitados[x] = true;
        Componentes[total].push_back(x);
        cout << x << " ";
        for (int i = 0; i < Nodo[x].second.size(); i++) {
            if (!Visitados[Nodo[x].second[i]]) {
                dfsTransverse(Nodo[x].second[i], total);
            }
        }
    }

    //Limpia el vector de visitados
    void clear(int nodes) {
        for (int i = 0; i < nodes; i++) {
            Visitados[i] = 0;
        }
    }

    //Ejecuta kosaraju
    void execute() {
        //Pone los nodos en la pila.
        for (int i = 0; i < nodes; i++)
            if (!Visitados[i]) {
                dfsStack(i);
            }

        clear(nodes);
        int total = 0;

        //Usa la pila para recorrer el grafo transverso.
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();
            if (!Visitados[v]) {
                cout << "{ ";
                dfsTransverse(v, total);
                cout <<" }" << endl;
            }
        }
    }
};

int main() {

    int nodes, rel;
    cin >> nodes >> rel;

    kosaraju A(rel,nodes);
    A.execute();
}