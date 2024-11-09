#include <queue>
#include <vector>
#include <iostream>

using namespace std;

const int N = 300010;

priority_queue<int, vector<int>, greater<int> > PQ;
vector<int> Aristas[N];
vector<int> Secuencia;
bool vis[N];
int n, m;

int main() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int u, v;
		cin >> u >> v;
		Aristas[u].push_back(v);
		Aristas[v].push_back(u);
	}

	vis[1] = true;
	PQ.push(1);
	while (!PQ.empty()) {
		int now = PQ.top();
		PQ.pop();
		Secuencia.push_back(now);
		for (auto p : Aristas[now]) {
			if (!vis[p]) {
				PQ.push(p);
				vis[p] = true;
			}
		}
	}

	for (auto p : Secuencia) {
		cout<<p<<" ";
	}
	return 0;
}