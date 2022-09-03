#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Stripe{
    int t;
    int* n; int* k;
    char** line;
    vector<int> A;

    Stripe(){
        cin>>t;
        n=new int[t];
        k=new int[t];
        line=new char*[t];
        for (int i=0; i<t; i++){
            cin>>n[i]>>k[i];
            line[i]=new char[n[i]];
            for (int j=0; j<n[i]; j++){
                cin>>line[i][j];
            }
        }
    }
    void seq(){
        for (int i=0; i<t; i++){
            A.resize(n[i]+1,0);
            for (int j=1; j<=n[i]; j++){
                A[j]=A[j-1];
                if(line[i][j-1]=='W')
                    A[j]++;
            }
            int min=1000000000;
            for (int j=k[i]; j<=n[i];j++){
                if (min>A[j]-A[j-k[i]])
                    min=A[j]-A[j-k[i]];
            }
            cout<<min<<std::endl;
        }
    }

    void printvec(){
        for (int i=0; i<A.size(); i++){
            cout<<A[i]<<" l ";
        }
        cout<<std::endl;
    }

    ~Stripe(){
        for (int i=0; i<t; i++){
            delete[] line[i];
        }
        delete[] line;
        delete[] n;
        delete[] k;
    }

};

int main() {
    Stripe A;
    A.seq();
}
