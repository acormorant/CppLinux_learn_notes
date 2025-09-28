#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

string cstr="infile.txt";
int main(){
    ifstream in(cstr);
    if(!in){
        cerr<<"无法打开文件\n";
        return -1;
    }
    string line;
    vector<string> vstr;
    while (getline(in,line))
    {
         vstr.push_back(line);
    }
    in.close();
    for(auto stritem:vstr){
        //保存string stritem的一个拷贝
        istringstream line(stritem);
        string word;
        //遍历vector对象 每次读取一个单词
        while (line>>word)
        {
            cout<<word<<"---";
        }
        cout<<endl;
        
    }
    return 0;
   

}