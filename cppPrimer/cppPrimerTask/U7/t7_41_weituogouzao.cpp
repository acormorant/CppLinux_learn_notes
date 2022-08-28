#include<iostream>
#include"Sales_data.h"
using namespace std;

/*委托构造函数实验
   Sales_data(const std::string &s,unsigned num,double price):
             bookNo(s),units_sold(num),revenue(num*price) {std::cout<<"接受四个实参信息\n";}
   Sales_data():Sales_data("",0,0.0){std::cout<<"无须接受任何信息\n";}
   Sales_data(std::istream &is): Sales_data(){read(is,*this);std::cout<<"接受用户输入信息\n";}
   Sales_data(const std::string &s):Sales_data(s,0,0.0) {std::cout<<"接受ISBN\n";}
*/
int main(){
    Sales_data s1;
    Sales_data s2("123s");
    string str("1234s");
    Sales_data s3(str);
    Sales_data s4(str,1,976.88);
    Sales_data s5(cin);

}
/*

s1: 
接受四个实参信息
无须接受任何信息
s2: 
接受四个实参信息
接受ISBN
s3: 
接受四个实参信息
接受ISBN
s4:
接受四个实参信息
!!!!!!!!!!!!!!!!!!!!!
s5:
接受四个实参信息
无须接受任何信息
k 1 90
接受用户输入信息
!!!!!!!!!!!!!!!!!!!!!
*/