#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    vector<string>vr;
    string word;
    while(cin>> word)
    vr.push_back(word);
    for(decltype(vr.size()) vsize=0;vsize<vr.size();++vsize){
    if(!vr[vsize].empty())
     for(auto &i: vr[vsize]){
       i =toupper(i);
     }
     cout<< vr[vsize]<<endl;
    }
    
    return 0;
}