#include <iostream>

using namespace std;

struct carray {
    int n, q;
    int* a, * t;
    int ini = 0,fin;

    carray(){
        cin >> n >> q;
        fin=n;
        a = new int[n];
        t = new int[q];
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < q; i++) {
            cin >> t[i];
        }
    }

    void change(int i) {
        if (i == 0) {
            return;
        }
        int temp = 0, temp2=0, temp3=0;
        temp = a[i];
        temp2 = a[0];
        for (int it = 1; it < i+1; it++) {
            temp3 = a[it];
            a[it] = temp2;
            temp2 = temp3;
        }
        a[0] = temp;
    }

    void activate() {
        int j = 0;
        for (int i = 0; i < q; i++) {
            while (true) {
                if (t[i] == a[j]) {
                    change(j);
                    cout << j+1 << " ";
                    j = 0;
                    break;
                }
                j++;
            }
            //print();
        }
    }

    void print() {
        for (int i = 0; i < fin; i++) {
            cout << a[i] << " | ";
        }
    }
};

int main()
{
    carray T;
    T.activate();
}
