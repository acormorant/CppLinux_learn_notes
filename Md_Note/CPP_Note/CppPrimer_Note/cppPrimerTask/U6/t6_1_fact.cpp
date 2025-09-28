#include "Chapter6.h"
#include<iostream>
using namespace std;

int fact(int n){
    if(n<0)return -1;
    int mul=1;
    for (int i = 1; i<n+1; i++)
    {
        mul*=i;
    }
    return mul;
    
}
