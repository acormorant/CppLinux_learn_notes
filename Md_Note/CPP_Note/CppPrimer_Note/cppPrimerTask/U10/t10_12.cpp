#include"Sales_data.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

bool compareIsbn(Sales_data item1,Sales_data item2){
    return item1.isbn() < item2.isbn();
}

istream &read(istream &is, Sales_data&item){
    double price;
    is >>item.bookNo >>item.units_sold >>price;
    item.revenue =item.units_sold *price;
    return is;
}
ostream &print(ostream &os, const Sales_data&item){
    os <<item.isbn() <<" "<<item.units_sold <<" "
       <<item.revenue<<" "<<item.avg_price()<<endl;
       return os;
}

int main(){
    vector<Sales_data> sales_vec;
    ifstream input;
    input.open("InFile.txt");
    Sales_data item1;
    Sales_data item2;
    //通过Sales_data(std::istream &is){read(is,*this);}此构造函数从文本中逐行构造sales_data类
    if(read(input,item1)){
         while(read(input,item2)){
          if(item1.isbn()==item2.isbn()){//若isbn相同则合并
                item1.combine(item2);
            }
            
            else{
                sales_vec.push_back(item1);
                item1=item2;//更新item1的isbn
            }
    }
    sales_vec.push_back(item1);
    /*
    使用lambda表达式代替函数compareIsbn
    sort(sales_vec.begin(),sales_vec.end(),[](Sales_data s1,Sales_data s2){return s1.isbn()>s2.isbn();});
    */
    sort(sales_vec.begin(),sales_vec.end(),compareIsbn);
    for(vector<Sales_data>::size_type i=0; i<sales_vec.size(); i++){
        print(cout,sales_vec[i]);
    }
    }
   
}