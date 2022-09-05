#include<iostream>
#include<list>
#include<algorithm>
#include<string>
using namespace std;

/*
本题要使用链表专用的sort和unique 算法，与泛型算法的不同点有如下两点：

1．它们是以链表类的成员函数形式实现的，因此使用方式是在链表对象上调用它们，也并不需要迭代器参数指出处理的序列。

2．由于是以成员函数形式实现的，是直接操作容器而非通过迭代器访问容器元素，因此这些算法具有修改容器的能力（添加、删除元素）。
例如，unique 会调用erase 直接真正删除重复元素，容器的大小会变小，而不是像泛型 unique 算法那样只是覆盖重复元素，并不改变容器大小。因此程序已不再需要调用erase了。
*/
void elimDups(list<string> &txtList){
    txtList.sort();
    txtList.unique();
}

int main(){
    list<string> txtList{"Eeeeee","Bbbbbb","Aa","Bb","Ccc","Aa","Ddd","Ccc"};
    elimDups(txtList);
    for(auto iter = txtList.begin();iter != txtList.end();iter++) cout << *iter <<" ";
}