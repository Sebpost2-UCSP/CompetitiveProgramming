#include <iostream>
#include <algorithm>

struct median {
    long long n, k, max = 0;
    long long* A;
    median() {
        std::cin >> n >> k;
        A = new long long[n];
        for (long long i = 0; i < n; i++) {
            std::cin >> A[i];
        }
        std::sort(A, A + n);
    }
    int max1(long long a, long long b) {
        if (a > b)
            return a;
        return b;
    }
    void op1() {
        long long ini = A[0], fin=A[n-1]+k;
        while (ini != fin) {
            if (op1_1((ini + fin+1) / 2)) {
                ini = (ini+fin+1) / 2;
            }
            else{
                fin = (ini+fin+1) / 2 - 1;
            }
        }
        std::cout << ini << std::endl;
    }
    bool op1_1(unsigned int k1) {
        long long sum = 0;
        for (int i = n/ 2; i < n; i++) {
            sum += max1(0, (k1-A[i]));
        }
        if (sum > k)
            return 0;
        return 1;
    }
    ~median() {
        delete[] A;
    }
};

int main()
{
    median inst;
    inst.op1();
}
