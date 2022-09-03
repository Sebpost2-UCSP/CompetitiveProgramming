#include <iostream>

using std::cin;
using std::cout;
using std::endl;

struct cookie{
    int t;
    int* a; int* b; int* n; int* m;

    cookie(){
        cin>>t;
        a=new int[t];
        b=new int[t];
        n=new int[t];
        m=new int[t];
        for (int i=0; i<t; i++){
            cin>>a[i]>>b[i]>>n[i]>>m[i];
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
