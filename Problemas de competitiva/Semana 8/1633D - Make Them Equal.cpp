#include <iostream>

using namespace std;

const int N = 200200;
int n, m;
char s[N], t[N];

bool solve() {
	cin>>s>>t;
	n = strlen(s);
	m = strlen(t);
	if (n < m) return false;
	int p = (n - m) & 1;
	int q = 0;
	int k = 0;
	for (int i = p; i < n; i++) {
		if (k == 1) {
			k = 0;
			continue;
		}
		if (q < m && s[i] == t[q]) {
			q++;
		}
		else {
			k++;
		}
	}
	return q == m;
}

int main()
{
	int T;
	cin>>T;
	while (T--) {
		if (solve())
			cout<<"YES\n";
		else
			cout << "NO\n";
	}

}