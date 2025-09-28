#include<vector>
#include<string>
#include<iostream>
using namespace std;

void replace_word (string &s,const string &oldval,const string &newval){
    if(! oldval.size()) return;
    if(s.size()<oldval.size()) return;
    auto iter =s.begin();
    while(iter!=s.end()){    
        if(*iter == *oldval.begin()){
            auto siter =iter;
            auto olditer = oldval.begin();
            while(*siter==*olditer && olditer!=oldval.end()){ //逐个字符比较是否相等
                siter++;
                olditer++;
            }
            if(olditer == oldval.end()){
              iter= s.erase(iter,siter);
              auto newiter = newval.end();
              while(newiter !=newval.begin()){
              iter = s.insert(iter,*(--newiter));
            }
        }
    }
        iter++;
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
由于要求使用迭代器，因此使用如下算法：
1．用迭代器iter 遍历字符串s。注意，对于s末尾少于oldVal长度的部分，已不可能与o1dVal相等，因此无须检查。
2．对每个位置，用一个循环检查s中字符是否与oldVa1中的字符都相等。
3．若循环是因为olditer ==o1dVal.end而退出，表明s中iter开始的子串与oldVa1相等。则调用erase将此子串删除，接着用一个循环将newVa1复制到当前位置中，
   返回迭代器的insert只支持单个字符插入。由于insert 将新字符插入到当前位置之前，并返回指向新字符的迭代器，因此，逆序插入newVa1字符即可。
   最后将iter移动到新插入内容之后，继续遍历s。
4．否则，iter开始的子串与oldVal不等，递增iter，继续遍历s。

*/