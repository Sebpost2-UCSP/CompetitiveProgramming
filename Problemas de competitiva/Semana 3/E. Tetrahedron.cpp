#include <iostream>

using namespace std;

int main()
{
	typedef long long ll;
	int n;
	cin >> n;

	ll mod = 1000000007;
	ll** arr = new ll* [2];
	for (int i = 0; i < 2; i++) {
		arr[i] = new ll[n + 1];
	}
	arr[1][0] = 1;
	arr[0][0] = 0;
	for (int j = 1; j <= n; j++) {
		arr[1][j] = 3 * arr[0][j - 1] % mod;
		arr[0][j] = (2 * arr[0][j - 1] + arr[1][j - 1]) % mod;
	}
	ll res = arr[1][n];
	for (int i = 0; i < 2; i++) {
		delete[] arr[i];
	}
	delete[] arr;

	cout << res;
}
