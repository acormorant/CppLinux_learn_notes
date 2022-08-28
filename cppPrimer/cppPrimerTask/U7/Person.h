#ifndef PERSON_H
#define PERSON_H
#include<string>
#include<iostream>

class Person
{
friend std::istream read(std::istream &,Person &);
friend std::ostream print(std::ostream &,const Person &);

private:
    std::string strName;
    std::string strAddress;
public:
    Person() =default;
    explicit Person(std::istream &is){return read(is,&this);}
    /*
    Person 类的最后一个构造函数 Person（std：：istream ＆is）；
   只接受一个 参数，默认情况下它会把读入的数据自动转换成 Person 对象。
   我们更倾向于严格控制Person 对象的生成过程，如果确实需要使用Person对象，可以明确指定；
   在其他情况下则不希望自动类型转换的发生。所以应该把这个构造函数指定为explicit的。
    */
    Person(const std::string &name ,const std::string &add): strName(name),strAddress(add) {}
    std::string get_name()    const{ return strName; }    //返回姓名
    std::string get_address() const{ return strAddress; } //返回地址
    

};
std::istream read (std::istream &,Person &);
std::ostream print(std::ostream &,const Person &);



std::istream &read(std::istream &is,Person &per){
    is>> per.strName >> per.strAddress;
    return is;
}

std::ostream &print(std::ostream &os,const Person &per){
    os<<"个人姓名: "<<per.strName<<" "
      <<"个人地址: "<<per.strAddress<<std::endl;
    return os;
}

#endif //PERSON_H