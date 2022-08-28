#include<iostream>
#include<string>
using namespace std;

string make_plural(size_t ctr,const string &word,const string &ending="s"){
    return (ctr>1) ? word+ending: word;
}
int main(){
    cout<<"success单数:  "<<make_plural(1,"success","es")<<endl;
    cout<<"success复数:  "<<make_plural(2,"success","es")<<endl;
    cout<<"failure单数:  "<<make_plural(1,"failure")<<endl;
    cout<<"failure复数:  "<<make_plural(2,"failure")<<endl;
    return 0;
}