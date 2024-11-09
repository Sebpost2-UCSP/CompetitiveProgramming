#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
#define mod 1000000007

vector<int> adj[400005];
int arr[400005];

ll power(ll x, ll n)
{
    if (n == 0) {
        return 1;
    }
    else if (n == 1) {
        return x;
    }
    else if (n % 2) {
        return (x * power((x * x) % mod, n / 2)) % mod;
    }
    else {
        return (power((x * x) % mod, n / 2));
    }
}

void dfs(int x)
{
    arr[x] = 1;
    for (auto i : adj[x])
    {
        if (arr[i]==0)
        {
            dfs(i);
        }
    }
}

void solucion()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int x = 0;
        for (int i = 1; i < n; i++) {
            adj[i].clear();
        }

        for (int i = 1; i <= n; i++) {
            arr[i] = 0;
        }

        int* a,*b;
        a = new int[n + 1];
        b = new int[n + 1];
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> b[i];
        }

        for (int i = 1; i <= n; i++){
            adj[a[i]].push_back(b[i]);
            adj[b[i]].push_back(a[i]);
        }

        for (int i = 1; i <= n; i++){
            if (arr[i]==0){
                x++;
                dfs(i);
            }
        }
        delete[] a;
        delete[] b;

        cout << power(2, x) << endl;

    }
}

int main()
{
    solucion();
}