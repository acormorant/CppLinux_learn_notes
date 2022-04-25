
    
# 函数
## 异常处理
1.throw表达式:**异常检测部分**用throw抛出异常.
2.try语句块:**异常处理部分**用try语句块处理异常,try中抛出的异常通常被某个catch子句处理.
3.一套异常类:用于在throw表达式和相关的catch子句间传递异常的具体信息.
    
    exception是C++中异常类的基类，基本上所有异常都继承于它。
    stdexcept头文件包含9个异常类，均从exception类派生。

###  T5_25 除法异常

```cpp
#include<stdexcept>
 while (cin>>ival1 >>ival2)
 {
     try{ 
          if(ival2==0)
          throw runtime_error("被除数不能为0");
         //runtime_error为标准库异常类型,提供一个string或c风格字符串初始化其对象
     }catch(runtime_error err){
         //关键字catch后括号内为异常声明,它指明了当前的 catch 可以处理什么类型的异常
            cout<< err.what()
         //what为runtime_error类的成员函数,返回初始化具体对象时所用的string对象副本
                <<"\n Try Again? Enter y or n"<<endl;
                char c;
                cin>>c;
             if(!cin ||c=='n'||c=='N') break;
             else cout<<"依次输入除数被除数"<<endl;
          }
     
 }
```
[拓展: C++异常类型以及多级catch](http://c.biancheng.net/cpp/biancheng/view/3283.html)

---
## 分离式编译
###  T6_9 编译和链接多个源文件
**fact函数:** 
  **声明于chapter6.h**

```cpp
#ifndef CHAPTER6_H
#define CHAPTER6_H
int fact(int );
#endif //CHAPTER6_H
```


  **定义于 fact.cpp**
```cpp
#include "Chapter6.h"
int fact(int n){
    if(n<0)return -1;
    int mul=1;
    for (int i = 1; i<n+1; i++)
    {
        mul*=i;
    }
    return mul;
}
```


**当factmain.cpp中main函数调用fact函数:**
```cpp
#include "Chapter6.h"
int main(){
    std::cout<<"输入整数: "<<std::endl;
    int val;
    std::cin>>val;
    std::cout<<"整数"<<val<<"的阶乘为:  "<<fact(val)<<std::endl;
    return 0;
}
```

1.将.cpp文件**编译**为对象文件(包含.cpp文件的机器码)
   使用g++命令行选项-c ,产生fact.o factmain.o
   ` g++ -c t6_1_factmain.cpp t6_1_fact.cpp`

2.将对象文件**链接**为可执行文件
   ` g++ t6_1_factmain.o t6_1_fact.o -o main`
   如果改变了factmain.cpp文件，我们只需要重新编译再链接就行了

3.运行main函数
  `./main.exe`

拓展:
[C++语言 如何用G++进行编译和运行程序](https://xuanweiace.blog.csdn.net/article/details/109297446?spm=1001.2014.3001.5506)
[分离式编译](https://blog.csdn.net/weixin_30710457/article/details/95972923?spm=1001.2014.3001.5506)

---

## main:处理命令行选项
### T6_25 将main给定实参连接为一个string对象并输出
```cpp
int main(int argc,char *argv[]){
string str;
for (int i = 0; i != argc; i++){
    str+=argv[i];
    cout<<"argv["<<i<<"] is: "<<argv[i]<<endl;
}
 
cout<<str<<endl;
return 0;

}
```

命令行的使用:(怎样输入命令行选项)
[c/c++ main 函数命令行参数的使用 知识小结](https://blog.csdn.net/wu_lai_314/article/details/8454394)

---

## Const_cast与重载
const_cast (expression)
const_cast标准转换运算符转换符是用来移除变量的const或volatile限定符。
```cpp
//比较两个string对象的长度,返回较短的那个引用
const string &shorterString(const stirng &s1,const string &s2){
    return s1.size()<=s2.size?s1:s2;
}
```
对两个非常量的实参调用这个函数返回结果任是const string的引用
需要当实参不为常量时返回普通引用,则使用const_cast
```cpp
string &shorterString(string &s1,string &s2){
    auto &r =shorterString(const_cast<const stirng &>(s1),
                           const_cast<const stirng &>(s2));
    return const_cast<string &>(r);
}
```
先强制转换为const string引用,然后调用shorterString的const版本
再将其返回值转换为普通引用.

[拓展: C++标准转换运算符const_cast ](https://www.cnblogs.com/ider/archive/2011/07/22/cpp_cast_operator_part2.html)

---

## 返回数组指针
数组不可拷贝,但可返回其数组指针或引用
1.使用类型别名
``` cpp
 typedef int arrT[10] //等价using arrT=int[10]
 arrT* func(int i);   //返回一个指向含有10个整数的数组的指针
```
2.牢记数组维度
```cpp
 int (*p2)[10]=*arr;//p2指向含有10个整数的数组
```
 由此类比出,数组的名字应该在其维度前,而其形参列表应该在两者之间.
```cpp
 Type(*function(parameter_list))[dimension]
```
3.使用尾置类型
```cpp
 auto func(int i) -> int(*)[10]
```
4.使用decltype :知道函数返回指针指向哪个数组
 decltype**不负责转换数组类型为指针类型**,函数声明时应该加*

### T6_37编写返回string数组引用的函数
```cpp
string  (&func())[10]; //Type(*function(parameter_list))[dimension]

using arr=string[10] //类型别名
 arr& func();  

auto func() -> string (&)[10] //尾置返回类型

string str[10];  //decltype关键字
decltype(str) &func();
```
---

## 默认实参
- 一旦某个形参背负默认值,它后面所有形参都必须也有.
- 函数调用时实参按位置解析,默认实参填补尾部缺口.
- 若多次声明,则后续函数声明只能为之前无默认值的实参添加默认实参;
- **用作默认实参的名字在函数声明的作用域内解析,而这些名字的求值过程发生在函数调用时**
  (可以改变默认实参的值)

### T6_42用默认实参输出给定单词单数和复数形式
```cpp
string make_plural(size_t ctr,const string &word,const string &ending="s"){
    return (ctr>1) ? word+ending: word;
}
int main(){
    cout<<"success单数:  "<<make_plural(1,"success","es")<<endl;
    cout<<"success复数:  "<<make_plural(2,"success","es")<<endl;
    cout<<"failure单数:  "<<make_plural(1,"failure")<<endl;
    cout<<"failure复数:  "<<make_plural(2,"failure")<<endl;
    return 0;
}
```
---

## 函数指针
**函数名自动转换为指针,指针无须取地址符与解引用**
```cpp
 pf=func;  //pf指向名为func的函数
 pf=&func; //等价的赋值语句:取地址符可选

 bool b1=pf("hello","bye");    //调用func函数
 bool b2=(*pf)("hello","bye"); //等价的调用: 无须提前解引用指针
 bool b3=func("hello","bye");  //等价的调用
```
### T6_56 编写加减乘除函数并用vector保存其指针并调用
```cpp

int func(int ,int );
int func1(int a,int b){
    return a+b;
}
int func2(int a,int b){
    return a-b;
}
int func3(int a,int b){
    return a*b;
}
int func4(int a,int b){
    return a/b;
}

 inline void compute(int a,int b,int(*p)(int ,int )){
    cout<<p(a,b)<<endl;
}

int main(){
    int a=5,b=10;
    decltype(func)*p1=func1,*p2=func2,*p3=func3,*p4=func4;
    //decltype不负责转换函数类型为指针类型,函数声明时应该加*
    vector<decltype(func)*> vf{p1,p2,p3,p4};
    for(auto p:vf){
        
        compute(a,b,p);
         // cout<<p(5,10)<<endl;
    }
    return 0;
}
```
---

    练习5.6.3节 异常处理（throw try/catch）  
    练习6.1.2节+2.6.3节 头文件编写  
    练习6.1.3节 分离式编译（编译和链接）  
    练习6.2.5节 main:处理命令行选项  
    练习6.3.3节 返回数组指针  
    练习6.4.2 默认实参  
    练习6.7节 函数指针