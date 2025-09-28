#include<forward_list>
#include<iostream>
using namespace std;

int main(){
   forward_list<int> fl1{0,1,2,3,4,5,6,7,8,9};
   auto fiter1 = fl1.before_begin();
   auto fiter2 = fl1.begin();
   while(fiter2 != fl1.end()){
    if(*fiter2 & 1){
     fiter2 = fl1.erase_after(fiter1);//容器元素为奇数时,删除fiter1指向元素的下一位,删除后fiter1不变,fiter2加一
    } 
    else{                             //容器元素不为奇数时,两迭代器加一
     fiter1 = fiter2;
     fiter2++;
    }
   }
    for(auto iter1 = fl1.begin();iter1 != fl1.end(); iter1++){
        cout << *iter1 <<" ";
    }
    return 0;
}