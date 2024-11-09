#include <iostream>
#include <string>

using namespace std;

int tests;
string* s, * t;

/*
bool res(string a, string b, int an, int bn, int count) {
    if (count == b.length()) {
        return 1;
    }
    else if (an == 0 || bn == 0) {
        return 0;
    }
    else  if (a[an] == b[bn]) {
        return res(a, b, an - 1, bn - 1,count+1);
    }
    else {
        return res(a, b, an - 1, b.length(), 0);
    }
}*/
bool res(int i, int an, int bn, int count) {
    cout << "count: " << count << " t=" << t[i].length()-1 << endl;
    cout << "s[i]=" << s[i][an] << " t[i]=" << t[i][bn] << endl;
    cout << "an: " << an << " bn: " << bn << endl;
    if (count == t[i].length()-1 && s[i][an]==t[i][bn]) {
        return 1;
    }
    else if (an == 0 ) {
        return 0;
    }
    else  if (s[i][an] == t[i][bn]) {
        return res(i, an - 1, bn - 1, count + 1);
    }
    else {
        return (res(i, an - 1, t[i].length()-1, 0) || res (i,an-1,bn,count));
    }
}

int main()
{
    cin >> tests;
    s = new string[tests];
    t = new string[tests];

    for (int i = 0; i < tests; i++) {
        cin >> s[i];
        cin >> t[i];
    }
    for (int i = 0; i < tests; i++) {
        if (t[i] == " ") {
            cout << "YES\n";
            continue;
        }
        int an = s[i].length()-1;
        int bn = t[i].length()-1;
        if (res(i, an, bn, 0)) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

}
