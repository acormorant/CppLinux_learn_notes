#include<list>
#include<deque>
#include<iostream>
using namespace std;

int main(){
    list<int> list1{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    deque<int> odd_deq,even_deq;
    auto iter =list1.begin();
    while(iter != list1.end()){
       if(*iter%2){
         odd_deq.push_back(*iter);
       }
       else{
         even_deq.push_back(*iter);
       }
       iter++;
    }
    for(auto diter1 = odd_deq.begin();diter1 != odd_deq.end();diter1++){
        cout << *diter1 <<endl;
    }
    for(auto diter2 = even_deq.begin();diter2 != even_deq.end();diter2++){
        cout << *diter2 <<endl;
    }
    return 0;
}