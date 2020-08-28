#include "List.h"
#include <list>
#include <iostream>
using namespace std;
int main() {
    List<int> A;
    A.pushBack(12);
    A.pushBack(123);
    A.pushFront(333);
    A.pushBack(412);
    A.insert(12,723);
    A.insert(1,921);
    A.insert(6,102);
    A.insert(3,11111);
    for(int i = 1; i<=A.size(); i++){
        cout << i << ": " << A[i] << endl;
    }
    A.popBack();
    A.popFront();
    for(int i = 1; i<=A.size(); i++){
        cout << i << ": " << A[i] << endl;
    }
    A.remove(1);
    A.remove(15);
    A.remove(2);
    A.remove(3);
    A.clear();
    A.insert(1,15);
    list<int> B;
    B.insert(B.begin(),12);
    B.insert(B.begin(),333);
    B.clear();
    return 0;
}