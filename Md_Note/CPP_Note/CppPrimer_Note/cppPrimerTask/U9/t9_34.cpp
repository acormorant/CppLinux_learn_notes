#include<list>
#include<iostream>
#include<vector>
using namespace std;
 
int main(){
    list<int> l1{1,2,3,4,5,6,7,8,9};
    string tmp;
    auto iter = l1.begin();
    while(iter != l1.end()){
        if(*iter & 1)
            iter = l1.insert(iter,*iter);   
            
        for(auto iter1 = l1.begin();iter1 != l1.end(); iter1++){
            cout << *iter1 <<" ";
    } 
         cout << endl;
         cin >> tmp;  //为了让程序暂停,有时间观察输出,若要继续执行程序,随意输入字符即可
    }
    iter++;

}
/*
1 1 2 3 4 5 6 7 8 9 
1 1 1 2 3 4 5 6 7 8 9 
1 1 1 1 2 3 4 5 6 7 8 9 
1 1 1 1 1 2 3 4 5 6 7 8 9 
1 1 1 1 1 1 2 3 4 5 6 7 8 9 
*/