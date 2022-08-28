#include<iostream>
#include<vector>
#include<list>
using namespace std;

int main(){
    int ia[]{0,1,1,2,3,5,8,13,21,55,89};
    vector<int> v1;
    list<int> l1;
    v1.assign(ia,ia+ sizeof(ia)/sizeof(ia[0]) ); //sizeof(ia)：返回数组所占内存空间的字节数
    l1.assign(ia,ia+ sizeof(ia)/sizeof(ia[0]) ); //故: 数组的总内存空间除以每个数据需要占的内存空间可以获得数组的长度
    
    auto viter = v1.begin();
    while(viter != v1.end()){
       if(*viter & 1) viter=v1.erase(viter); //删除值为奇数
       else viter++;
       /*
       if(*viter & 1) v1.erase(viter);
       viter++;
       不能这样改变vector容器大小时迭代器将失效
       */
    }

    auto liter = l1.begin();
    while(liter != l1.end()){
       if(!(*liter & 1)) liter=l1.erase(liter);   //删除值为偶数
       else liter++;
    }


    for(auto iter1 = v1.begin();iter1 != v1.end(); iter1++){
        cout << *iter1 <<" ";
    }
    cout <<endl;
    for(auto iter2 = l1.begin();iter2 != l1.end(); iter2++){
        cout << *iter2 <<" ";
    }
    return 0;
}