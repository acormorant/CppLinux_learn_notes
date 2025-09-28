#include<vector>
#include<iostream>
using namespace std;
int main(){
    vector<int> v1;
    cout << v1.at(0) <<endl;
//terminate called after throwing an instance of 'std::out_of_range'
//what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)
    cout<< v1[0] <<endl;
//不抛出异常,程序直接退出
    cout << v1.front() <<endl;
//不抛出异常,程序直接退出
    cout << *v1.begin() <<endl;
//不抛出异常,程序直接退出
    return 0;
}