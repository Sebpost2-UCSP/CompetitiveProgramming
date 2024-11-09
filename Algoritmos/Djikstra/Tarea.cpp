#include <iostream>
#include <chrono>
#include <vector>
#include <queue> // priority queue
#include <functional> // Para usar greater<T>
using namespace std;

//h



//IMPLEMENTACION DE DIJKSTRA ----------------------------------------------------------------------------------
typedef pair<int, int> Pair;

struct dijkstra {
    int Vertices, peso_i;
    vector<vector<Pair>> Aristas;
    vector<int> dist;
    vector<bool> visitados;
    Pair index;

    //priority queue
    priority_queue<Pair, vector<Pair>, greater<Pair> > PQ;

    //heap fibonacci


    dijkstra() { Vertices = 0; peso_i = 0; }

    dijkstra(int Vertices) {
        this->Vertices = Vertices;
        dist.resize(Vertices);
        visitados.resize(Vertices);
        Aristas.resize(Vertices);
        peso_i = 0;
    }

    void arista(int vertice_1, int peso, int vertice_2) {
        Aristas[vertice_1].push_back(make_pair(peso, vertice_2));
    }

    void normal(int ini) {
        dist[ini] = 0;
        for (int i = 0; i < Vertices - 1; i++) {
            int min = INT_MAX;
            for (int j = 0; j < Vertices; j++) {
                if (visitados[j] == 0 && dist[j] <= min) {
                    min = dist[j];
                    peso_i = j;
                }
            }
            visitados[i] = true;
            for (vector<Pair>::iterator it = Aristas[peso_i].begin(); it != Aristas[peso_i].end(); it++)
                if ((min + (it->first)) < dist[it->second]) {
                    dist[it->second] = min + (it->first);
                }
        }
    }

    void PQs(int ini) {
        dist[ini] = 0;
        PQ.push(make_pair(0, ini));
        while (!PQ.empty()) {
            index = PQ.top();
            PQ.pop();
            ini = index.second;
            peso_i = index.first;

            if (visitados[ini])
                continue;

            visitados[ini] = true;

            for (vector<Pair>::iterator it = Aristas[ini].begin(); it != Aristas[ini].end(); it++)
                if ((peso_i + (it->first)) < dist[it->second]) {
                    dist[it->second] = peso_i + (it->first);
                    PQ.push(make_pair(dist[it->second], it->second));
                }
        }
    }

    void fib() {
    }

    void reset() {
        for (int i = 0; i < Vertices; i++) {
            dist[i] = INT_MAX;
            visitados[i] = false;
        }
    }
};

struct Floyd {
    int size;
    vector<vector<int>> arrayG;
    bool negativecycle;

    Floyd() { size = 0; }
    Floyd(vector<vector<int>> adj) {
        size = adj.size();
        arrayG = adj;
    }
    void Run() {
        for (int k = 0; k < size; k++) {
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (arrayG[i][k] != INT_MAX && arrayG[k][j] != INT_MAX) {
                        arrayG[i][j] = min(arrayG[i][j], arrayG[i][k] + arrayG[k][j]);
                    }
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (arrayG[i][j] == INT_MAX) {
                    cout << "INF ";
                }
                else {
                    cout << arrayG[i][j] << " ";
                }
            }
            cout << "\n";
        }
        cout << "\n";
    }
};

struct bellman {
    int Vertices;
    bool negative;
    vector<pair<int,Pair>> Aristas;
    vector<int> dist;
    vector<bool> visitados;

    bellman() {
        Vertices = 0;
        negative = 0;
    }

    bellman(int Vertices) {
        negative = 0;
        this->Vertices = Vertices;
        dist.resize(Vertices);
        visitados.resize(Vertices);
    }

    void arista(int vertice_1, int peso, int vertice_2){
        Aristas.push_back(make_pair(peso, make_pair(vertice_1, vertice_2)));
    }

    void Run(int ini) {
        for (int i = 0; i < Vertices; i++) {
            dist[i] = INT_MAX;
        }
        dist[ini] = 0;

        for (int i = 1; i < Vertices; i++) {
            for (int j = 0; j < Aristas.size(); j++) {
                int vertice_1 = Aristas[j].second.first;
                int vertice_2 = Aristas[j].second.second;
                int peso = Aristas[j].first;
                if (dist[vertice_1] + peso < dist[vertice_2]) {
                    dist[vertice_2] = dist[vertice_1] + peso;
                }
            }
        }
    }

    void negativo() {
        for (int i = 1; i < Vertices; i++) {
            for (int j = 0; j < Aristas.size(); j++) {
                int vertice_1 = Aristas[j].second.first;
                int vertice_2 = Aristas[j].second.second;
                int peso = Aristas[j].first;
                if (dist[vertice_1] + peso < dist[vertice_2]) {
                    negative = true;
                }
            }
        }
    }

    void print() {
        cout << "Bellman:\n";
        for (int i = 0; i < Vertices; i++) {
            cout << dist[i] << " ";
        }
        cout << endl;
    }
};

int main(void) {

    dijkstra A(6);
    A.arista(0, 5, 1);
    A.arista(0, 10, 3);
    A.arista(1, 2, 2);
    A.arista(1, 10, 5);
    A.arista(1, 5, 4);
    A.arista(2, 1, 3);
    A.arista(2, 5, 4);
    A.arista(2, 3, 0);
    A.arista(4, 2, 5);

    auto start = chrono::steady_clock::now();

    A.PQs(0);

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << chrono::duration <double, nano>(diff).count() << " ns" << endl;
    A.reset();
    start = chrono::steady_clock::now();

    A.normal(0);

    end = chrono::steady_clock::now();
    diff = end - start;
    cout << chrono::duration <double, nano>(diff).count() << " ns" << endl;

    cout << "Camino mas corto desde el inicio " << 0 << ": ";
    for (int i = 0; i < A.Vertices; i++)
        cout << A.dist[i] << " ";
    cout << endl;

    //FLOYD Y BELL
    const int max = INT_MAX;

    vector<vector<int>> graph = {
        {0,5,max,10},
        {max,0,3,max},
        {max,max,0,1},
        {max,max,max,0}
    };

    Floyd B(graph);
    B.Run();
    B.print();

    bellman C(6);

    C.arista(0, 5, 1);
    C.arista(0, 10, 3);
    C.arista(1, 2, 2);
    C.arista(1, 10, 5);
    C.arista(1, 5, 4);
    C.arista(2, 1, 3);
    C.arista(2, 5, 4);
    C.arista(2, 3, 0);   
    C.arista(4, 2, 5);

    C.Run(0);
    C.negativo();
    C.print();
}