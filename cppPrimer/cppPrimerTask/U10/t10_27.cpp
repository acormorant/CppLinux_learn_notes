#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

int main(){
    vector<string> sVec{"Aaaa","Bbbb","Bbbb","Dddd","Cccc","Dddd"};
    list<string> slist;
    sort(sVec.begin(),sVec.end());
    unique_copy(sVec.begin(),sVec.end(),back_inserter(slist));//改为 inserter(slist,slist.begin()) 也可
    for(auto iter = slist.begin();iter != slist.end();iter ++) cout << *iter <<" ";
    cout << endl;
}