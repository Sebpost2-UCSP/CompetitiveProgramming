#include <iostream>
#include <vector>
#include <algorithm>

struct mice {
	int t,n,k;
	int* res;

	mice() {
		std::cin >> t;
		res = new int[t];
		for (int i = t; i > 0; i--) {
			std::cin >> n >> k;
			std::vector<int> A(k);
			for (int j = 0; j < k; j++) {
				std::cin >> A[j];
			}
			std::sort(A.begin(), A.end(), std::greater<int>());
			int R = 0, it = 0;
			while (it < k && R + n - A[it] < n)
			{
				R += n - A[it];
				it++;
			}
			res[t-i] = it;
		}
	}
	void print() {
		for (int i = 0; i < t; i++) {
			std::cout << res[i] << std::endl;
		}
	}
	~mice() {
		delete[] res;
	}
};

int main()
{
	mice inst;
	inst.print();
}