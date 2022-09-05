#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

bool compareStrlen(string str){
    return str.size() > 5;
}

int main(){
    vector<string> words{"Aaa","Bbb","Cccccc","Dddddddd","ABCDEaaa"};
    auto end_greater = partition(words.begin(),words.end(),compareStrlen);
    for(auto i=words.begin();i < end_greater;i++) cout << *i <<endl;//  < 而不是 <= 是因为partition返回最后一个使谓词为true的元素!!!之后!!!的位置(第二组的第一个元素)
    for(auto i=words.begin();i < words.end();i++) cout << *i <<endl;
}
/*
输出:
ABCDEaaa
Dddddddd
Cccccc
说明partition() 函数只会根据筛选条件将数据进行分组，并不关心分组后各个元素具体的存储位置。
partition() 函数分组后   前者中的各个元素都符合筛选条件，而后者则都不符合。
*/