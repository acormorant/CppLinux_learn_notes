#include<iostream>
#include<vector>
using namespace std;
int main(){
    vector<int> ivec;
    for(vector<int>::size_type i =0; i!= 24;++i)
    ivec.push_back(i);
    while(ivec.size() != ivec.capacity()){
        ivec.push_back(0);
    }
    ivec.push_back(0);
    cout << ivec.size() <<endl;
    cout << ivec.capacity() <<endl;
}
/*
33
64
在本机标准库中vector分配新内存空间时将当前容量翻倍
*/