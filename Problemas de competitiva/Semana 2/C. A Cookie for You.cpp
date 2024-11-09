#include <iostream>

using std::cin;
using std::cout;
using std::endl;

typedef long long ll;

struct cookie {
    int t;
    ll* a; ll* b; ll* n; ll* m;

    cookie() {
        cin >> t;
        a = new ll[t];
        b = new ll[t];
        m = new ll[t];
        n = new ll[t];
        for (int i = 0; i < t; i++) {
            cin >> a[i] >> b[i] >> n[i] >> m[i];
        }
    }

    void ang() {
        for (int i = 0; i < t; i++) {
            //viendo si hay suficientes galletas.
            if (a[i] + b[i] < m[i] + n[i]) {
                std::cout << "NO"<<std::endl;
                continue;
            }
            //viendo cual es el valor maximo de galletas
            if (a[i] > b[i]) {
                //viendo si hay suficientes galletas para todos
                if (b[i] < m[i]) {
                    std::cout << "NO" << std::endl;
                    continue;
                }
            }
            else {
                if (a[i] < m[i]) {
                    std::cout << "NO" << std::endl;
                    continue;
                }
            }
            std::cout << "YES" << std::endl;

        }
    }

    ~cookie() {
        delete[] a;
        delete[] b;
        delete[] n;
        delete[] m;
    }
};

int main() {
    cookie A;
    A.ang();
    return 0;
}