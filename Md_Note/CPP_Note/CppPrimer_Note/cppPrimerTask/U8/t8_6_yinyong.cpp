#include<iostream>
#include<fstream>
#include<string>
#include"Sales_data.h"
using namespace std;
/*
- 报错
 error C2280: “std::basic_ifstream<char,std::char_traits>::basic_ifstream(const std::basic_ifstream<char,std::char_traits> &)”: 尝试引用已删除的函数
 解决方法
 若ifstream作为函数形参时，将其改为传址pass by reference。
 ifstream &read(ifstream &is, Sales_data&item)

- 编译后生成.exe文件,我们可以在集成终端打开exe文件,向该文件传递参数
 PS C:\Users\cormorant\Desktop\v\C\cpp\cppexe> .\t8_6 InFile.txt outfile.txt
- 文件名不分大小写
 指定c风格字符串时两种格式都成功.
 (ifstream input;
    input.open("infile.txt");
  //input.open("InFile.txt");
 )
 指定sting对象时两种格式都成功.
 ( string str1="infile.txt";
 //string str1="InFile.txt"; 
   input.open(str1)
 )
- 未解决错误
  - arvg[1]中内容为两种时都不成功.
     (
        argv[1] is: InFile.txt
      //argv[1] is: infile.txt
     )
  - 使用接受istream&类型函数时无法用其对应ifstream调用
     std::istream &read(std::istream &is, Sales_data&item)
     read(input,total)
     //报错
      undefined reference to `read(std::basic_ifstream<char, std::char_traits<char> >&, Sales_data&)'
 
*/
std::istream &read(std::istream &is, Sales_data&item){
    double price;
    is >>item.bookNo >>item.units_sold >>price;
    item.revenue =item.units_sold *price;
    return is;
}
std::ostream &print(std::ostream &os, const Sales_data&item){
    os <<item.isbn() <<" "<<item.units_sold <<" "
       <<item.revenue<<" "<<item.avg_price();
       return os;
}


int main(int argc,char *argv[]){
    cout<<"输入isbn 销售量 单价: \n";
    ifstream input;
    string str1="infile.txt";
    string str2="outfile.txt";
    input.open(str1);
    ofstream output;
    output.open(str2);
    Sales_data total;
    if(read(input,total)){

        Sales_data trans;
        cout<<"请再输入isbn 销售量 单价: \n";
        while (read(input,trans))
        {
            if(total.isbn()==trans.isbn()){
                total.combine(trans);
                cout<<"请再输入isbn 销售量 单价: \n";
            }
            
            else{
                print(output,total);
                // cout<<total<<endl;
                total=trans;
                cout<<"请再输入isbn 销售量 单价: \n";
            }
        }
        print(output,total);
        return 0;
        
    }
    else{
        cerr<<"No data?!"<<endl;
        return -1;
    }
    
}
