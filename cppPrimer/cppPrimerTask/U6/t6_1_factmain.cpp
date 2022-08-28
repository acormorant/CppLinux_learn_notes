#include "Chapter6.h"
#include<iostream>
using namespace std;
int main(){
    cout<<"输入整数: "<<endl;
    int val;
    cin>>val;
    cout<<"整数"<<val<<"的阶乘为:  "<<fact(val)<<endl;
    return 0;
}
/*
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer>   g++ -c t6_1_factmain.cpp t6_1_fact.cpp
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer>   g++ t6_1_factmain.o t6_1_fact.o -o main
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer>   ./main.exe
输入整数: 
5
整数5的阶乘为:  120
*/