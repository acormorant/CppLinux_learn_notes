#include<iostream>
#include"Sales_data.h"
using namespace std;
/*

关于 read print 
非成员函数如果在概念上属于类而不定义在类中,则它一般应与类声明(而非定义!!!)在同一个头文件内.
当我们在类的外部定义成员函数时,需要与其声明匹配(类外部定义的成员名字需要包含它所属的类名Sales_data::)
非成员函数未声明在类中,故不需要其使用作用域符::进行声明匹配

*/

istream & read(std::istream &is, Sales_data&item){
    double price;
    is >>item.bookNo >>item.units_sold >>price;
    item.revenue =item.units_sold *price;
    return is;
}
ostream &print(std::ostream &os, const Sales_data&item){
    os <<item.isbn() 
       <<" 销售量:  "<<item.units_sold 
       <<" 总销售额: "<<item.revenue
       <<" 均价:   "<<item.avg_price();
       return os;
}


int main(){
    cout<<"输入isbn 销售量 单价: \n";
    Sales_data total;
    if(read(cin,total)){

        Sales_data trans;
        cout<<"请再输入isbn 销售量 单价: \n";
        while (read(cin,trans))
        {
            if(total.isbn()==trans.isbn()){
                total.combine(trans);
                cout<<"请再输入isbn 销售量 单价: \n";
            }
            
            else{
                print(cout,total);
                // cout<<total<<endl;
                total=trans;
                cout<<"请再输入isbn 销售量 单价: \n";
            }
        }
        print(cout,total);
        return 0;
        
    }
    else{
        cerr<<"No data?!"<<endl;
        return -1;
    }
    
}
