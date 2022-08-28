#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

struct PersonInfo
{
    string name;
    vector<string> phones;

};

string format(const string &s){return s;}

bool valid(const string &s){
// 如何验证电话号码将在第17章介绍
//现在简单返回true
return true;
}

string sfile="data.txt";
int main(){
    string line,word;
    vector<PersonInfo> people;
    ifstream in(sfile);
    istringstream record;
    if(!in){
        cerr<<"无法打开文件\n";
        return -1;
    }

    while(getline(in,line)){
       PersonInfo info;
       record.clear();   // 重复使用字符串流时，每次都要调用clear
       record.str(line); // 将记录绑定到刚读入的行 
       //以单词为单位读取名字和电话号码
       record >> info.name; 
       while (record >> word)
       {
           info.phones.push_back(word);
       }
       people.push_back(info); //将此记录追加到people末尾 
       
    }
    ostringstream os;
    for(const auto &entry:people){ //对people中每一项 
        ostringstream formatted,badNums;
        for(const auto &nums:entry.phones){ //对每个数
            if(!valid(nums))
            badNums<<" "<<nums;
            else
            formatted<<" "<<format(nums);
        }
            if(badNums.str().empty())//没有错误的数 
            os<<entry.name<<" "//打印名字 
            <<formatted.str()<<endl;//和格式化的数
            else//否则，打印名字和错误的数
              cerr<<"input error:"<<entry.name
              <<" invalid number(s) "<<badNums.str()<< endl; 
        }
    cout << os.str() <<endl; return 0;
    return 0;
        
    
}