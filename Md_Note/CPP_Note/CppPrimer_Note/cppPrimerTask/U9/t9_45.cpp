#include<string>
#include<iostream>
using namespace std;

void  name_string(string& s,const string& prefix,const string& suffix){
    string::size_type pos =0 ;
    //s.append(suffix);
    s.insert(s.size(),suffix);
    s.insert(pos,prefix);
}

int main(){
    string s="James Bond";
    name_string(s,"Mr. "," II");
    cout << s <<endl;
    return 0;
}