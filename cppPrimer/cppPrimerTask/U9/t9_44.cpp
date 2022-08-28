#include<vector>
#include<string>
#include<iostream>
using namespace std;

void replace_word (string &s,const string &oldval,const string &newval){
    if(! oldval.size()) return;
    if(s.size()<oldval.size()) return;
    string::size_type pos =0;
    while ((pos = s.find(oldval,pos)) != string::npos)
    {
        s.replace(pos,oldval.size(),newval); //replace(range,args)中range是一个下标和一个长度而不是起始和结束下标值
        // ++pos;错误: 当newval中包含oldval时可能造成重复循环添加
        pos += newval.size();    
    }
    

}

int main(){
    string s="tho thru tho!";
    replace_word(s,"thru","through");
    cout << s << endl;
    replace_word(s,"tho","though");
    cout << s << endl;
    replace_word(s,"through"," ");
    cout << s << endl;
}
/*
tho through tho!
though through though!
though   though!
*/