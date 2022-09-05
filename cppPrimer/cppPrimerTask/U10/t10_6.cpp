#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    vector<int> vec{1,2,3,4,5,6,7,8,9};
    fill_n(vec.begin(),vec.size(),0);
    for(auto i: vec) cout << i<<endl;
}