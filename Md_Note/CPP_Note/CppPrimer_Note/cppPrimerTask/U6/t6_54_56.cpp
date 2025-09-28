#include<iostream>
#include<string>
#include<vector>
using namespace std;
int func(int ,int );
int func1(int a,int b){
    return a+b;
}
int func2(int a,int b){
    return a-b;
}
int func3(int a,int b){
    return a*b;
}
int func4(int a,int b){
    return a/b;
}

 inline void compute(int a,int b,int(*p)(int ,int )){
    cout<<p(a,b)<<endl;
}

int main(){
    int a=5,b=10;
    decltype(func)*p1=func1,*p2=func2,*p3=func3,*p4=func4;
    vector<decltype(func)*> vf{p1,p2,p3,p4};
    for(auto p:vf){
        
        compute(a,b,p);
         // cout<<p(5,10)<<endl;
    }
    return 0;
}
 
