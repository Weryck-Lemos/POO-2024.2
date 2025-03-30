#include <bits/stdc++.h>
using namespace std;

int c=0;

void prog1(int n){
    if(n==1)c+=2;

    else{
        c+=3;
        prog1(n-1);
        prog1(n-1);
    }

}
