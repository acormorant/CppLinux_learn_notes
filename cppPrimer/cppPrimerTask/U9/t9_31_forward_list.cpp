#include<forward_list>
#include<iostream>
using namespace std;

int main(){
    forward_list<int> l1{0,1,2,3,4,5,6,7,8,9};
    auto iter = l1.begin();
    auto biter= l1.before_begin();
    while(iter != l1.end()){
        if(*iter & 1){
            iter = l1.insert_after(iter,*iter);//返回新插入元素的迭代器
            biter=iter;
            iter++;
        }
        else{
            iter = l1.erase_after(biter);
        }
    }
     for(auto iter1 = l1.begin();iter1 != l1.end(); iter1++){
        cout << *iter1 <<" ";
    }
}
