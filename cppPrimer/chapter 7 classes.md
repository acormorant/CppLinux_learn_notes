
# 类
**类的基本思想是数据抽象和封装。**

**抽象是一种依赖于接口和实现分离的编程技术。**

**封装实现了类的接口和实现的分离。**
## Q&A
1. class 和 struct 的区别
   唯一一点区别就是默认访问权限不同。
   当希望类的所有成员是 public 时，用struct
2. 委托构造函数是什么？如何使用
   **借助另一个已有的构造函数定义新构造函数的一种方式**。student():student(int n, 10){}
   (当一个构造函数委托给另一个构造函数时，受委托的构造函数的初始值列表和函数体会优先执行，然后再执行委托者的函数体。)
3. 什么是友元？如何声明？
   允许其访问类的私有成员的东西为类的友元。在类内声明，可以在类内任何位置声明，但是最好在开始或结束位置。**声明方式为用 friend 来修饰一个正常的声明，比如 friend class StrBlobPtr; 或 friend void func();**
4. **声明友元函数/类要注意什么？**
   友元声明并不是通常意义上的访问声明。**必须要在==类外且是类的前面==声明该函数/类。**
5. 声明重载函数为友元需要注意什么?
   每个版本的重载都要声明一遍
6. 类的什么成员必须初始化
   引用和 const 成员
7. 类的静态成员如何声明和定义
   **在类内用 static 声明，在类外定义和初始化，类外不加 static**
8. const 成员函数的使用需要注意什么
   不能在 const 成员函数内调用类的其他非 const 成员函数。

## 7.1 定义抽象数据类型
1.this任何对类成员的直接访问都被看作this的隐式引用。
 `std::string isbn() const {return bookNo;}`
 等价于
 `std::string isbn() const {return this->bookNo;}`

2.在类的外部定义成员函数类外部定义的成员的名字必须包含它所属的类名。
```cpp
 double Sales_data::avg_price() const {
	if (units_sol)
		return revenue/units_sols;
	else
		return 0;
}
```
3.构造函数
 >定义: 类通过一个或几个特殊的成员函数来控制其对象的初始化过程，这些函数叫做构造函数。

 - 构造函数没有返回类型；构造函数的名字和类名相同。
 - 类通过一个特殊的构造函数来控制默认初始化过程，这个函数叫做默认构造函数。
 - 编译器创建的构造函数被称为合成的默认构造函数。
 - **只有当类没有声明任何构造函数的时，编译器才会自动的生成默认构造函数**。
  **一旦我们定义了一些其他的构造函数，除非我们再定义一个默认的构造函数，否则类将没有默认构造函数**



## 7.2 访问控制与封装
1.访问控制
 **public:**  使用public定义的成员，在整个程序内可被访问，public成员定义类的接口。 
 **private:** 使用private定义的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private部分封装了类的实现细节。 

2.友元
 友元类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元。
 以friend关键字标识。友元不是类的成员，不受访问控制级别的约束。
 **友元的声明仅仅制定了访问的权限，而非通常意义的函数声明。
 必须在友元之外再专门对函数进行一次声明。**

---

## 7.3 类的其他特性
1.重载成员变量Screen myScrren
```cpp
 char ch = myScreen.get();
 ch = myScreen.get(0,0);
```
2.类数据成员的初始化类内初始值**必须使用=或者{}**的初始化形式
```cpp
class Window_mgr{
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
}
```
3.**基于const的重载**
- 从const成员函数返回*this的引用
  此时它的返回类型将是常量引用,则我们不能将此成员函数嵌入到一组动作的序列当中去;
  故我们可以通过区分成员函数是否是const的,对其重载;
```cpp
class Screen {
public:
	// display overloaded on whether the object is const or not
    Screen &display(std::ostream &os) 
                  { do_display(os); return *this; }
    const Screen &display(std::ostream &os) const
                  { do_display(os); return *this; }
private:
    void do_display(std::ostream &os) const {os<<contents;} 
};
```
- 当某个对象调用display的时候，该对象是否是const决定了应该调用display的哪个版本。

4.类类型对于一个类来说，在我们创建他的对象之前该类必须被定义过，而不能仅被声明。

5.友元友元类如果一个类指定了友元类，则友元类的成员函数可以访问此类包括非公有成员在内的所有成员。
```cpp
class Screen {
	// Window_mgr的成员可以访问Screen类的私有部分
	friend class Window_mgr;
}
```
令成员函数作为友元
```cpp
class Screen {
	// Window_mgr::clear必须在Screen类之前被声明
	friend void Window_mgr::clear(ScreenIndex);
}
```
友元关系不具有传递性。
重载函数名字相同，但是是不同的函数。如果想把一组重载函数声明为类的友元，需要对每一个分别声明。

6.可变数据成员
const 成员函数不能修改成员变量。
但是用 **mutable 将成员修饰为可变数据成员**，就可以修改了。


## 7.4 类的作用域
一个类就是一个作用域。

## 7.5 构造函数再探
1.构造函数的初始值有时必不可少
- 如果成员是const、引用，或者属于某种未提供默认构造函数的类类型化。我们必须通过构造函数初始值列表为这些成员提供初值。
```cpp
class ConstRef{
public:
	ConstRef (int i);
private:
	int i;
	const int ci;
	int &ri;
};

ConstRef:ConstRef(int ii) : i(ii), ci(ii), ri(i){  }
```
2.**成员初始化的顺序成员初始化的顺序与它们在类定义中出现的顺序一致。**

3.委托构造函数使用它所述类的其他构造函数执行它自己的初始化过程。

4.如果去抑制构造函数定义的隐式转换？在类内声明构造函数的时候使用explicit关键字。


## 7.6 类的静态成员
1.声明静态成员在成员的声明之前加上关键词static。类的静态成员存在于任何对象之外，对象中不包含任何与静态成员有关的数据。
```cpp
class Account{
    public:
    void caculate(){ amount += amount *interestRate; }
    static double rate(){ return interestRate; }
    private: 
    double amount;
    static double interestRate;
}
```
2.使用类的静态成员

- 使用作用域直接访问静态成员
  ```cpp
  double r;
  r = Account::rate();
  ```
- 使用类的对象,引用,指针
  ```cpp
  Account ac1;
  Account *ac2=&ac1;
  r=ac1.rate();
  r=ac2->rate();
  ```
- 成员函数不通过作用域运算符就能直接使用静态成员
  ```cpp
  class Account{
    public:
    void caculate(){ amount += amount *interestRate; }
    private: 
    static double interestRate;
  }
  ```

---
## 习题

    Sales_data类
    练习
    7.2/7.6/封装/7.11构造函数/7.21友元/7.26
    7.41 委托构造函数重写Sales_data
    7.7 交易处理系统

    Person类
    练习
    7.4/7.5/7.9read print/7.15构造函数/7.19封装/7.22/7.50explicit

    Screen类 /Window_mgr类
    练习
    7.23/7.24/7.25/7.27/7.29/7.32/7.33


### Sales_data类
#### 7.2/7.6/封装/7.11构造函数/7.21友元/7.26
```cpp
#ifndef SALES_DATA_H
#define SALES_DATA_H
#include<string>

class Sales_data
{
   friend Sales_data add(const Sales_data&,const Sales_data);
   friend std::ostream &print(std::ostream&, const Sales_data&);
   friend std::istream &read(std::istream&, Sales_data&);
public:
   Sales_data() =default;
   Sales_data(std::istream &is){read(is,*this);}
   Sales_data(const std::string &s):bookNo(s) {}
   Sales_data(const std::string &s,unsigned num,double price):
             bookNo(s),units_sold(num),revenue(num*price) {}       

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
std::ostream &print(std::ostream&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);

#endif//SALES_DATA_H
```
#### 7.41 委托构造函数重写Sales_data
```cpp
   //委托构造函数
   Sales_data(const std::string &s,unsigned num,double price):
   bookNo(s),units_sold(num),revenue(num*price)
   {std::cout<<"接受四个实参信息\n";}

   Sales_data():Sales_data("",0,0.0)
   {std::cout<<"无须接受任何信息\n";}

   Sales_data(std::istream &is): Sales_data()
   {read(is,*this);std::cout<<"接受用户输入信息\n";}

   Sales_data(const std::string &s):Sales_data(s,0,0.0) 
   {std::cout<<"接受ISBN\n";}

```
```cpp
int main(){
    Sales_data s1;
    Sales_data s2("123s");
    string str("1234s");
    Sales_data s3(str);
    Sales_data s4(str,1,976.88);
    Sales_data s5(cin);
}
```

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
**s5:
接受四个实参信息
无须接受任何信息
k 1 90
接受用户输入信息**

####  7.7 交易处理系统

- **关于 read print:** 
  - 非成员函数如果在概念上属于类而不定义在类中,则它一般应与类声明(**而非定义!!!**)在同一个 头文件内.
  - 当我们在类的外部定义**成员函数**时,需要与其**声明匹配**(类外部定义的成员名字需要包含它所属的类名Sales_data:: )
  - **非成员函数未声明在类中,故不需要其使用作用域符::进行声明匹配**

```cpp
#include<iostream>
#include"Sales_data.h"
using namespace std;
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

```
### Person类
**7.4/7.5/7.9read print/7.15构造函数/7.19封装/7.22/7.50explicit**
```cpp
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
```

### Screen类 /Window_mgr类
**7.23/7.24/7.25/7.27/7.29/7.32/7.33**
```cpp
 #ifndef SCREEN_H
 #define SCREEN_H
#include<iostream>
#include<string>

class Screen
{
friend class Window_mgr;
public:
using pos=std::string::size_type;

Screen()=default;
Screen(pos hei,pos wid):height(hei),width(wid),contents(hei*wid,' '){}
Screen(pos hei,pos wid,char c):height(hei),width(wid),contents(hei*wid,c){}

char get(){return contents[cursor];}
char get(pos r,pos c){return contents[r*width+c];}
Screen &set(pos ,pos ,char );
Screen &set(char );
Screen &move(pos r,pos c);
Screen &display(std::ostream &os){do_display(os); return *this;}
const Screen &display(std::ostream &os) const {do_display(os); return *this;}
pos size() const{return height*width;}

private:
    pos height=0,width=0;
    pos cursor=0;
    std::string contents;
    void do_display(std::ostream &os) const {os<<contents;}
   
};
Screen & Screen::set(char c){
  contents[cursor]=c;
  return *this;
}

Screen & Screen::set(pos r,pos col,char c){
  contents[r*width+col]=c;
  return *this;
}

Screen & Screen::move(pos r,pos c){//类外定义成员函数: 函数名需要声明匹配
  pos pow=r*width;
  cursor =pow+c;
  return *this;
}


 #endif//SCREEN_H
```
```cpp
#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H
#include<vector>
#include"Screen.h"
class Window_mgr
{
public:
 using ScreenIndex = std::vector<Screen>::size_type;
 void clear(ScreenIndex);

private:
    //默认情况下,一个window_mgr包含一个标准尺寸的空白Screen
    std::vector<Screen> screens{screen(24,80)};
    
};
void Window_mgr::clear(ScreenIndex i){
    Screen &s =screens[i];
    //s为引用,指向我们想清空的那个screen
    s.contents=std::string(s.height*s.width,' ');
}

#endif//WIDOW_MGR_H
```
#### T7_27 返回*this的成员函数
如果 move、set和display 函数的返回类型不是Screen＆而是 Screen，将会发生什么情况？
```cpp
#include"Screen.h"
#include<iostream>
using namespace std;
int main(){
    Screen myscreen(5,5,'X');
    myscreen.move(4,0).set('#').display(cout);
    cout<<endl;
    myscreen.display(cout);
    cout<<endl;
}
```
 返回类型Screen&:
XXXXXXXXXXXXXXXXXXXX#XXXX
XXXXXXXXXXXXXXXXXXXX#XXXX
 返回类型Screen: 
XXXXXXXXXXXXXXXXXXXX#XXXX
XXXXXXXXXXXXXXXXXXXXXXXXX

【出题思路】

函数的返回值如果是引用，则表明函数返回的是对象本身；函数的返回值如果不是引用，则表明函数返回的是对象的副本。

【解答】

**返回引用的函数是左值的，意味着这些函数返回的是对象本身而非对象的副本。
如果我们把一系列这样的操作连接在一起的话，所有这些操作将在同一个对象上执行**。

在上一个练习中，move、set和display函数的返回类型都是Screen＆，表示我们首先移动光标至（4，0）位置，然后将该位置的字符修改为＇＃＇，最后输出myScreen的内容。

相反，如果我们把move、set和display 函数的返回类型改成Screen，则上述函数各自只返回一个临时副本，不会改变myScreen的值。
