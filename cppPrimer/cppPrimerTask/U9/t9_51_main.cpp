#include<iostream>
#include<string>
#include"t9_51_date.h"

using namespace std;

int main(){
    string dates[]={"Jan 1,2022","February/1/2022","29/1/2022","30*1   2021","Feb*1*1999"};
    for(auto s :dates){
        t9_51_date d1(s);
        cout << d1;
    }
}