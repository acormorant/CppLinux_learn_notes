# CONST
## 常量引用(reference to const)绑定非常量时的一些状态
(不存在 const reference 因为引用不是对象)
1. 当引用的类型与其所引用的类型一致时
 常量引用仅对引用可参与的操作做出了限定,对于引用的对象本身是否常量不作限定,故允许通过其他途径改变它的值,**此时常量引用绑定在其引用对象上,值与其一同更改.**
 ```cpp
#include<iostream>
using namespace std ;
int main()
{
    int i = 10 ;
    int &j = i ;// j refers to i;
    i = 11 ;// change the value of variable,i .
    cout << "i = " << i << endl ;
    cout << "j = " << j << endl ;
    /*-------------------------------------------*/
    int m = 10 ;
    const int &k = m ;// constant k refers to noconst object
    m = 13 ;
    cout << "m = " << m << endl ;
    cout << "k = " << k << endl ;
    return  0 ;
}
/*
实验结果：
i = 11
j = 11
m = 13
k = 13
*/
 ```
2. 当引用的类型与其所引用的类型不一致时(可转换成引用的类型)
 会生成一个临时对象，**此时常量引用绑定的对象其实是这个临时对象(此时被引用对象的状态与常量引用无关)**，对这个临时对象操作并不会影响到被引用的对象，所以c++一般规定编译器自行构造的临时对象都是const的，这个也是c++禁止为非常量引用生成临时对象的原因(若存在,非常量引用修改值时实际修改为临时变量的值而非被引用对象的值,与修改初衷相悖)。
 ```cpp
#include<iostream>
using namespace std ;
int main()
{

    double m = 10.1 ;
    const int &k = m ;// constant k refers to noconst object
    m = 13 ;
    cout << "m = " << m << endl ;
    cout << "k = " << k << endl ;
    return  0 ;
}
/*
实验结果：
m = 13
k = 10
*/
 ```

-------

## 指针和CONST
### 指向常量的指针(pointer to const)(底层const)
类似于reference to const,不能用于改变其所指对象的值(可通过其他途径修改),可指向非常量对象.
### const指针(const pointer)(顶层const)
常量指针必须初始化,不变的是指针本身的值(地址)而非指向的对象,故可以用于改变其所指的值.(不可以指向常量,除非是指向常量的常量指针(const pointer to const)).
### C++ 类型别名为指针类型时，const的修饰情况
如果类型别名指代的是复合类型，那么把它用到声明语句中产生的效果会和预想的不一样（预想的就是把别名替换为所指代的内容，再判断其数据这  类型）.
**使用typedef**
```cpp
	typedef char * pstring;
	pstring a = 0;          //char*

	const pstring cstr = 0; //char* const
	const char * cstr1 = 0; //const char*

	const pstring *ps = 0;  //char* const*
	const char ** ps1 = 0;  //const char**
```
**使用using**
将第一句替换为using pstring = char*，与上面效果一样。

-------

## CONST成员函数
**this的类型是指向类类型非常量版本的常量指针.**
故不能绑定this到一个常量对象上,这使得我们不能在一个常量对象上调用普通的成员函数.此时应该**将this指针声明成指向常量的常量指针( const Sales_data *const )**,这有助于提高函数的灵活性.
**声明的方式为: 将const关键字放在成员函数的参数列表之后.**
这样使用const的成员函数被称为常量成员函数.
```cpp
std::string isbn() const { return bookNo; }
//可以看作(下为伪代码,因为不能显示定义自己的this指针)
std::string Sales_data::isbn() (const Sales_data *const this) { return this->bookNo; }
```

-------

## 基于const的重载
### 从const成员函数返回*this
```cpp
class Screen{
    public:
     Screen &set(char);
}

inline Screen &Screen::set(char c){
    contents[cursor] = c;
    return *this;
}
```
当继续添加一个display操作打印Screen的内容,令其为const成员,则其this指针为指向常量的常量指针,其返回*this为一个常量对象的引用.
这造成不能将display嵌入到一组动作的序列中(常量对象不能调用普通成员函数).
```cpp
Screen myScreen;
myScreen.display(cout).set('*');
//此操作错误,即使myScreen为非常量对象,但display的const版本返回常量引用,我们无法set一个常量对象.
```
### 基于const的重载
1. 因为非常量版本的函数对于常量对象不可用,所以只能在常量对象上调用const成员函数.
2. 另一方面,虽然可以在非常量对象上调用常量版本和非常量版本,但显然此时非常量版本是一个更好的匹配.
   
所以,我们定义一个do_display的私有成员,由它负责打印Screen的实际操作.
```cpp
class Screen{
    public:
     //根据对象是否const重载display函数
    Screen &display(std::ostream &os){
        do_display(os);
        return *this;
    }
    const Screen &display(std::ostream &os) const {
        do_display(os);
        return *this;
    }
    private:
    void do_display(std::ostram &os) const {os << contents;}
}
```
- **当一个成员调用另外一个成员时,this指针在其中隐式的传递**
1. **因此,当display的非常量版本调用do_display时,它的this指针将隐式从指向非常量的常量指针转换成指向常量的常量指针;**
2. **当do_display完成后,display函数各自返回解引用this所得的对象;非常量版本中,this指向一个非常量对象,因此display返回一个普通的非常量引用;**

-------













