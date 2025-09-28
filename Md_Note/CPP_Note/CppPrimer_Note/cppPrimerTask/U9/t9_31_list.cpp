#include<list>
#include<iostream>
#include<vector>
using namespace std;
 
int main(){
    list<int> l1{0,1,2,3,4,5,6,7,8,9};
    auto iter = l1.begin();
    while(iter != l1.end()){
        if(*iter & 1){
            iter = l1.insert(iter,*iter);
            iter ++;
            iter ++;
        }
        else{
            iter = l1.erase(iter);
        }
    }
     for(auto iter1 = l1.begin();iter1 != l1.end(); iter1++){
        cout << *iter1 <<" ";
    }
}