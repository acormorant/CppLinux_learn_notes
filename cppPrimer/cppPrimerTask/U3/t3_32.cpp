#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    int a[10]{0,1,2,3,4,5,6,7,8,9};
    vector<int> vr(a,a+10);
    vector<int> vr2(vr);
    for(auto vn : vr2)
      cout<< vn<<" ";
}