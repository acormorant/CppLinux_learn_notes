#include<fstream>
#include<vector>
#include<string>
#include<iostream>

#include <cassert>

using namespace std;
int main(){
    ifstream infile; 
    infile.open("InFile.txt");   //将文件流对象与文件连接起来 
    assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

    vector<string> strs;
    string line;
    while (infile>>line)//以单词为单位输出
    //getline(infile,line)以行为单位输出
    {
        strs.push_back(line);
    }
    for(auto i:strs){
        cout<<i<<endl;
    }
    return 0;
}