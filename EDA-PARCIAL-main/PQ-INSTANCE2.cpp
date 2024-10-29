#include<iostream>
#include "PriorityQueue.hpp"

#include <stdlib.h>    
#include <time.h>


int main()
{
    //PRUEBA 1
    PQ < double, 1> A;
    for (int i = 0; i < 13; i++) {
        A.push(i);
    }
    char a;
    double ad;
    A.print();
    while (1) {
        cout << "\n\nInsert: i\nPop: r\nfind: f\ntop/front: t\n";
        cout << "\nIngrese el char: ";
        cin >> a;
        cout << "\n";
        if (a == 'i') {
            cin >> ad;
            A.push(ad);
            A.print();
            a = '1';
        }
        else if (a=='r') {
  
            A.pop();
            A.print();
            a = '1';
        }
        else if (a == 'f') {
            cin >> ad;
            A.find(ad,1);
            a = '1';
        }
        else if (a == 't') {
            cout << "\nEl numero con mayor prioridad es " << A.front() << "\n";
            a = '1';
        }
        else {
            continue;
        }
    }
}

