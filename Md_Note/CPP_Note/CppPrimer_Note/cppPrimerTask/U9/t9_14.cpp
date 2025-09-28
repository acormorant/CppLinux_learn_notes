#include<iostream>
#include<string>
#include<list>
#include<vector>
using namespace std;

int main(){
    list<char*> list1{"Aaa","Bbb","Ccc"};
    vector<string> vstr1;
    vstr1.assign(list1.begin(),list1.end());
    vector<string>::iterator iter=vstr1.begin();
    while(iter != vstr1.end()){
        cout << *iter <<endl;
        iter++;
    }
    return 0;
}