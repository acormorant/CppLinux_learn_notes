#ifndef SALES_DATA_H
#define SALES_DATA_H
#include<string>


class Sales_data
{
   friend Sales_data add(const Sales_data&,const Sales_data);
   friend std::ostream &print(std::ostream&, const Sales_data&);
   friend std::istream &read(std::istream&, Sales_data&);
   friend std::ofstream &print(std::ofstream &os, const Sales_data&item);
   friend std::ifstream  &read(std::ifstream &is, Sales_data&item);
public:
   Sales_data() =default;
   Sales_data(std::istream &is){read(is,*this);}
   Sales_data(const std::string &s):bookNo(s) {}
   Sales_data(const std::string &s,unsigned num,double price):
             bookNo(s),units_sold(num),revenue(num*price) {}       

/*
   //委托构造函数
   Sales_data(const std::string &s,unsigned num,double price):
             bookNo(s),units_sold(num),revenue(num*price) {std::cout<<"接受四个实参信息\n";}
   Sales_data():Sales_data("",0,0.0){std::cout<<"无须接受任何信息\n";}
   Sales_data(std::istream &is): Sales_data(){read(is,*this);std::cout<<"接受用户输入信息\n";}
   Sales_data(const std::string &s):Sales_data(s,0,0.0) {std::cout<<"接受ISBN\n";}
*/

   std::string isbn() const { return bookNo; }
   Sales_data& combine(const Sales_data &rhs){//把两个ISBN相同的销售记录合并

       units_sold+=rhs.units_sold;
       revenue+=rhs.revenue;
       return *this;
       
   }

private:
    /* data */
    double avg_price() const { //平均售价
        return units_sold?revenue/units_sold : 0;
    }
    std::string bookNo;             //书籍编号
    unsigned units_sold = 0;   //销售量
    double revenue =0.0;    //总销售收入

};
Sales_data add(const Sales_data&,const Sales_data);
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
//  std::ofstream &print(std::ofstream &os, const Sales_data&item);
//  std::ifstream  &read(std::ifstream &is, Sales_data&item);

/*
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
Sales_data add(const Sales_data &lhs,const Sales_data &rhs){
    Sales_data sum;
    sum.combine(rhs);
    return sum;
}
*/

#endif//SALES_DATA_H