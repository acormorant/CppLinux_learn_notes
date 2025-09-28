#include<iostream>
#include<vector>
#include<iterator>

using namespace std;
//t10_34 使用reverse_iterator逆序打印vector
//t10_35 用普通迭代器逆序打印vector
int main(){
    vector<int> vec{1,2,3,4,5,6,7,8,9};
    for(auto iter=vec.crbegin();iter!=vec.crend();iter++){
        cout << *iter <<endl;
    }
    for(auto iter=vec.cend();iter!=vec.cbegin();iter--){
        cout << *(iter-1) <<endl;
    }
}