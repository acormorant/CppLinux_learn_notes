#include<iostream>
#include<string>
#include<deque>
using namespace std;

int main(){
    string str1;
    deque<string> deq1;
    auto iter = deq1.begin();
    while(cin >> str1){
       iter=deq1.insert(iter,str1); //类似deq1.push_front(str1)
       iter++; //使其迭代器指向添加的元素之后
       //deq1.push_back(str1); (更简便)
    }
    iter = deq1.begin();
    while (iter != deq1.end())
    {
        cout << *iter << endl;
        iter++;
    }
    return 0;
}
