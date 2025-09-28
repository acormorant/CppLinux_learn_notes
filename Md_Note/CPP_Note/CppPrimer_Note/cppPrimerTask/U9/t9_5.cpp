#include<iostream>
#include<vector>
using namespace std;

vector<int>::iterator findVlaue(vector<int>::iterator first,vector<int>::iterator last,int vlaue);
int main(){
    vector<int> list1{1,2,3,4,5,6,7,8,9};
    int num;
    cin >> num;
    cout << findVlaue(list1.begin(),list1.end(),num) - list1.begin() <<endl;
    return 0;
}


vector<int>::iterator findVlaue(vector<int>::iterator first,vector<int>::iterator last,int vlaue){
    vector<int>::iterator iter(first);
    while(*first != *last){
        if(*first == vlaue) return first;
        first++;
    }
    return iter;   //搜索失败返回list1.begin(),cout输出零
}