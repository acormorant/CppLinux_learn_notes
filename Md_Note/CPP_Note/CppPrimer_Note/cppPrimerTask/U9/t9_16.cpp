#include<iostream>
#include<vector>
#include<list>
using namespace std;

bool swap_ListVector(list<int> &list1,vector<int> &vector1){
    if(vector1.size() != list1.size()) return false;
    list<int>::iterator liter =list1.begin();
    vector<int>::iterator viter =vector1.begin();
    while(liter != list1.end()){
        if(*liter != *viter)return false;
        liter++;
        viter++;
    }
    return true;

}
int main(){
 list<int> l1{1,2,3,4,5};
 list<int> l2{1,2,3,4,5,6};
 vector<int> v1{1,2,3,4,5};
 vector<int> v2{1,2,3,4,5,6};
 cout << swap_ListVector(l1,v1) <<endl;
 cout << swap_ListVector(l1,v2) <<endl;
 cout << swap_ListVector(l2,v1) <<endl;
 cout << swap_ListVector(l2,v2) <<endl;
}