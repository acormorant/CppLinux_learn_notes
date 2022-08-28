#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    vector<int> v1(10);
    for(decltype(v1.size()) vi=0;vi<v1.size();vi++ )
    cin>>v1[vi];
    auto it=v1.begin();
    while(it!=v1.end()){
        *it*=2;
        cout<<*it<<" ";
        it++;
        
    }
    return 0;
}