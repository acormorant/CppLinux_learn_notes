#include<iostream>
#include<vector>
using namespace std;
bool findValue(vector<int>::iterator first,vector<int>::iterator last,int vlaue);
int main(){
     vector<int>list1{1,2,3,4,5,6,7,8,9};
     int num;
     cin >> num;
     cout<< findValue(list1.begin(),list1.end(),num) << endl;
     
}


bool findValue(vector<int>::iterator first,vector<int>::iterator last,int vlaue){
    while(*first != *last){
        if(*first == vlaue)
        return 1;
        first++;
    }
    return 0;
}