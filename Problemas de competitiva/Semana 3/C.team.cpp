#include <iostream>

using namespace std;

int main()
{
    typedef long long ll;
    ll o, z, temp;
    bool zero=0, greater=0;
    cin >> z >> o;
    if (z - 1 > o || o > 2 * (z + 1)) {
        cout << "-1" << endl;
        return 0;
    }
    if (o == z - 1) {
        zero = 1;
        temp = z - 1;
    }
    else if (o == z) {
        temp = z;
    }
    else {
        temp = z + 1;
        greater = 1;
    }
    ll iterations = o % temp;
    if (iterations == 0 && o!=temp) {
        iterations = z + 1;
    }
    temp = z;
    if (zero) {
        cout << "0";
    }
    while (temp!=0) {
        if (temp != o) {
            if (iterations > 0) {
                cout << "110";
            }
            else {
                cout << "10";
            }
            iterations--;
        }
        temp--;
    }
    if (greater) {
        if (iterations > 0) {
            cout << "11";
        }
        else {
            cout << "1";
        }
    }
    if (o == z) {
        cout << "10";
    }
}