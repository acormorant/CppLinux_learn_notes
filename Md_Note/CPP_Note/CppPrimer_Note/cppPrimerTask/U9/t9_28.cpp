#include<iostream>
#include<forward_list>
#include<string>
using namespace std;

void insert_str(forward_list<string>& flstr,const string dropstr,const string insertstr){
   auto fiter1 = flstr.before_begin();
   auto fiter2 = flstr.begin();
   bool inserted= false;
   while(fiter2 != flstr.end()){
    if(*fiter2 == dropstr){
        fiter2 = flstr.insert_after(fiter2,insertstr);
        inserted= true;
    }
    else{
        fiter1 = fiter2;
        fiter2 ++;
    }
    if(!inserted){                //未查找到dropstr,插入末尾
        flstr.insert_after(fiter1,insertstr);
    }
   }
}

int main(){
   forward_list<string> fl1{"Aaaa","Bbbb","Aaaa","Cccc"};
   string str1{"Aaaa"};
   string str2{"Dddd"};
   insert_str(fl1,str1,str2);
    for(auto iter1 = fl1.begin();iter1 != fl1.end(); iter1++){
        cout << *iter1 <<" ";
    }
    return 0;
}
//PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U9> cd "c:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U9\" ; if ($?) { g++ t9_28.cpp -o C:/Users/cormorant/Desktop/v/C/cpp/cppexe/t9_28 } ; if ($?) { C:/Users/cormorant/Desktop/v/C/cpp/cppexe/t9_28 }
//Aaaa Dddd Bbbb Aaaa Dddd Cccc 