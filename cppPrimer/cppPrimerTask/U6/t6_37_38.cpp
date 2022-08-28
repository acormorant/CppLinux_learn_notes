#include<iostream>
#include<string>
using namespace std;
string  (&func())[10]; 
/*
using arr=string[10] //类型别名
 arr& func();  

auto func() -> string (&)[10] //尾置返回类型

string str[10];  //decltype关键字
decltype(str) &func();
*/
int odd[]={1,3,5,7,9};
int even[]={0,2,4,6,8};

decltype(odd) &arrptr(int i){
    return (i%2)?odd :even;
}

int main(){
    for (int i = 0; i <5; i++)
    {   
        cout<<odd[i] <<"    "<<even[i]<<endl;
        arrptr(i)[i]=100;
        
        
    }
    for (int i = 0; i <5; i++)
        cout<<"odd["<<i<<"]: "<<odd[i] <<endl;
    for (int i = 0; i <5; i++)
        cout<<"even["<<i<<"]: "<<even[i] <<endl;   
        
        
    
    return 0;
}


