[《C++ primer》学习笔记整理](https://www.cnblogs.com/xsqblogs/p/14681536.html)

# 1.杂记
### 指针与引用的不同：
1. 指针是一个对象而引用不是；
2. 指针可以重定向引用不可以；
3. 有指向指针的指针无引用的引用；
4. 指针不需要在定义时赋初值而引用需要。


-------

# 2.CONST
## 2.1. 常量引用(reference to const)绑定非常量时的一些状态
(不存在 const reference 因为引用不是对象)
1. **当引用的类型与其所引用的类型一致时:**
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

2. **当引用的类型与其所引用的类型不一致时: (可转换成引用的类型)**
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

## 2.2. 指针和CONST
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

## 2.3. constexpr和常量表达式
常量表达式是指**值不会改变**并且**在编译过程就能得到计算结果**的表达式。
**字面值属于常量表达式，由常量表达式初始化的 const 对象也是常量表达式。**
```cpp
const int a = 32;          // 是常量表达式
const int b = a + 1;       // 是常量表达式
const int sz = get_size(); // 不是常量表达式，因为虽然 sz 是常量，但它的具体值等到运行时才知道。
```
### cosntexpr变量
在实际应用中很难分辨一个初始值是否是常量表达式，通过将变量声明为 constexpr 类型即可由编译器来检查。
**由 constexpr 声明的变量必须用常量表达式初始化。**
建议：如果认定一个变量是常量表达式，就把它声明为 constexpr 类型。
新标准允许定义 constexpr，这种函数应该足够简单以使得编译时就可以计算其结果。
不能用普通函数初始化 constexpr 变量，但可以使用 constexpr 函数初始化 constexpr 变量。
```cpp
constexpr int sz = size(); //只有当 size() 是一个 constexpr 函数时这才是一条正确的声明语句。
```
### 字面值类型
算术类型、引用、指针都属于字面值类型，自定义类则不属于。
cosntexpr 指针的初始值必须是 nullptr 或 0 或存储于固定地址的对象。函数体之外的对象和静态变量的地址都是固定不变的。
#### 指针和constexpr
注意区分 constexpr 和 const 。constexpr 都是顶层 const，仅对指针本身有效。
```cpp
const int *p = nullptr;     // p 是一个指向整型常量的指针
constexpr int *q = nullptr; // q 是一个指向整数的常量指针
```
### 区分const和constexpr

- **constexpr 限定了变量是编译器常量，即变量的值在编译器就可以得到。**
- **const 则并未区分是编译器常量还是运行期常量。即 const 变量可以在运行期间初始化，只是初始化后就不能再改变了。**
- **constexpr 变量是真正的“常量”，而 const 现在一般只用来表示 “只读”。**


-------

## 2.4. CONST成员函数
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

## 2.5. 基于const的重载
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

### 2.6. 在多个文件间共享 const 对象
如果想在多个文件间共享const对象，**必须在变量的定义前添加extern关键字并在本文件中声明。声明和定义都要加extern**  (p54)

-------

## 3. Chap3 字符串,向量和数组 部分笔记
### 3.1 Q&A
1. 使用加号连接字符串/string时要注意什么
   **加号两边至少有一个是 string 类型，不能都是字符串**
2. string 的索引是什么类型，s.size() 返回什么类型
   都是 ==string::size_type== 类型，是无符号值。
3. **如何方便地判断 string 中的某个字符的类型（比如是数字还是字母）以及转换某个字符的大小写。**
   使用**cctype 头文件**中的 isalnum(),  isalpha(), isdigit(), isupper(), islowwer(), ispunct(), isspace(), tolower(), toupper() 等类型。
4. **值初始化的结果是怎样的**
   ==值初始化会将内置类型初始化为 0，类类型由类自己来默认初始化。==
5. 定义 c 风格数组时数组维度的限制条件
   ==**维度必须是个常量表达式，即在编译阶段就可以确定值**。（因为数组维度是数组的类型的一部分，而**C++ 是静态语言，即在编译阶段就要确定类型**）==
6. 如何使用数组来初始化 vec
   ```cpp
   vector<int> vec(begin(arr),end(arr));
   ```
7. string 类型可以隐式转化为 c 风格字符串（即字符数组）吗？
   不可以（从 C 风格字符串到 string 的转换是用了 string 的转换构造函数，而 string 并没有定义到 C 风格字符串的类型转换运算符）
8. 如何将 string 类型转化为 c 风格字符串
   **使用 c_str() 函数**
9.  使用 getline() 函数从输入流读取字符串存到 string 中，存储的内容有换行符吗？
    **没有换行符。**
10. 使用范围for循环要注意什么？
    如果要修改循环变量的值要将其声明为引用类型：auto &

### 3.2  string::size_type 类型
**string 的 size() 成员函数返回一个 ==string::size_type== 类型的值。**
大多数标准库类型都定义了几种配套的类型，**这些配套类型体现了标准库与机器无关的特性**。
在具体使用时，**通过作用域操作符(string::)来表明 size_type 是在类 string 中定义的**。
string::size_type 是**无符号值**，可以确定的是它足够存放任何 string 对象的大小。
C++11 允许**通过 auto 和 decltype 来获得此类型**。
```cpp
auto len = s.size();// len 的类型是 string::size_type
```
不要在同一个表达式中混用 size_type 和 int 类型。

### 3.3 数组
- 数组下标常用size_t类型
  (size_t 是一些C/C++标准在stddef.h中定义的，size_t 类型表示**C中任何对象所能达到的最大长度**，它是**无符号整数**。)
- 指向数组元素的指针等价于vector中的迭代器
#### 使用范围for语句处理多维数组
- ==注意：使用范围 for 循环处理多维数组时，**除了最内层的循环外，其他所有循环的控制变量都应该是引用类型**。==
因**为如果不声明为引用类型，编译器会自动将控制变量转换为指向数组首元素的指针**，就不能在内层继续使用范围 for 循环处理该控制变量了。

```cpp
for(auto& row : arr)
    for(auto col : row)
```

**使用 3 种方式来输出 arr 的元素:**
```cpp
// 范围 for 语句-不使用类型别名
for (const int (&row)[4] : arr)
    for (int col : row)
        cout << col << " ";
cout << endl;
// 范围 for 语句-使用类型别名
using int_array = int[4];
for (int_array &p : ia)
    for (int q : p)
        cout << q << " ";
cout << endl;
// 普通 for 循环
for (size_t i = 0; i != 3; ++i)
    for (size_t j = 0; j != 4; ++j)
        cout << arr[i][j] << " ";
cout << endl;
// 指针
for (int (*row)[4] = arr; row != arr + 3; ++row)
    for (int *col = *row; col != *row + 4; ++col)
        cout << *col << " ";
cout << endl;
```

-------

## 4. Chap4 表达式 部分笔记
### 4.1 Q&A
1. 左值与右值的不同
   ==使用左值使用的是**对象的身份（在内存中的位置）**，使用右值使用的是**对象的值（内容）**。需要右值的地方可以用左值代替，反之不行。==
2. 左值与右值对 decltype 的影响
   **如果 decltype 中的表达式返回的是左值，那么 decltype 得到是一个引用类型。**
3. 整数除法的结果是如何舍入的
   **向零舍入**
4. 理解运算符的返回值
   采用运算符进行各类运算时，把运算符理解为函数，返回值是运算符函数的返回值，cin>>10 的返回值是运算符 >> 的返回值
5. 区分递增运算符的前置与后置版本。
   前置版本直接返回改变后的运算对象，后置版本返回的是运算对象改变前的原始值的副本。**对迭代器使用后置递增消耗很大。**
6. 位运算符的使用要注意什么
   **建议使用位运算符处理无符号类型**。C++中使用位运算符处理带符号数的运算结果依赖于机器。
7. 运算符的结合顺序是怎样的
   如果优先级相同，除了赋值运算符，其他运算符都是从左向右结合。
8. sizeof 运算符的返回值是什么
   **sizeof 也是运算符，它返回一条表达式或一个类型所占的==字节数==。**
9.  常见的隐式类型转换的方式
    算数运算中小整型（bool,char,short）提升为大整型（int）、整型转换为浮点型，条件里非布尔值转换为布尔值，初始化时初始值转换为变量的类型，赋值时右侧转换为左侧类型，**算术运算或关系运算的运算对象被转换为同一种类型**。**数组和函数转换为指针**，指向非常量的指针转换为指向常量的指针，c风格字符串转换为string，**cin>>s 返回的的 cin 转换为 bool 值**。
10. 四种显式类型转换是什么
```cpp
    static_cast<type>(expression), const_cast, dynamic_cast, reinterpret_cast(不要用它)。
```
11. 常见的如 int 转换为 double 这样的转换用什么
    使用 static_cast<double>(num) 来转换。
12. ==**const_cast 用于什么时候**==
    **const_cast 用于移除或增加对象的底层 const，即用于使不能修改引用对象值的引用和不能修改指向对象值的指针变成可以修改的，或者反过来。**
13. 旧式的两种强制类型转换方式
       旧式的强制类型转换本质上采用 const_cast、static_cast 或 reinterpret_cast 的一种。
       旧式与新式相比没那么清晰明了，如果出现问题，追踪困难。
```cpp
int(a);// 函数形式的强制类型转换
(int)a;// c 语言风格的强制类型转换
```
14.  需要记住的典型运算符的优先级
    作用域运算符优先级是最高的，成员访问运算符(. 和 ->)的优先级高于括号，也是非常高的。递增和递减的优先级也很高，是括号之下最高的。
### 4.2 赋值运算符
- **赋值运算符的左侧运算对象必须是一个可修改的左值**
- 赋值运算符满足右结合律
### 4.3 递增和递减运算符
前置版本：首先将运算对象加 1，**然后将改变后的对象作为求值结果**。
后置版本：也是将运算对象加 1，**但是求值结果是运算对象==改变之前==那个值的==副本==**。
前置版本将对象本身作为左值返回，后置版本将对象的原始值的副本返回。
如无必要，不要使用后置版本。
前置版本直接返回改变了的运算对象，**后置版本需要将原始值保存下来以便于返回，是一种浪费**。
后置版本对于整数和指针来说影响不大，**对于迭代器而言消耗巨大**。
#### 在一条语句中混用解引用和递增运算符
**==*p++==** : p++将 p 的值加一，然后返回 p 的初始值的副本作为求值结果用于解引用。(递增运算符优先级高于解引用)
**这是一种提倡的写法**，更加简洁，应该习惯于这种写法。
```cpp
auto pbeg = v.begin();
while(pbeg != v.end())
    cout << *pbeg++ << endl;
```
### 4.4 类型转换
#### 隐式转换
1. 比 int 类型小的整型值首先提升为较大的整数类型
2. 在条件里，把非布尔值转换成布尔值
3. 初始化过程中，初始值转换为变量的类型
4. 赋值时，右侧运算对象转换成左侧类型
5. 算数运算或关系运算的运算对象有多种类型，转换成一种。
#### 其他隐式类型转换
- **数组转换成指针**
大多数情况下数组自动转换成指向数组首元素的指针。（**decltype关键字参数、取地址符(&)、sizeof、typeid 都不会发生这种转换**）
- **指针的转换**
0 或 nullptr 都能转换成任意指针类型。**指向非常量的指针能转换成 void*。指向所有对象的指针都能转换成 const void***。
- **转换成常量**
指向非常量的指针转换成指向相应常量类型的指针
- **类类型定义的转换**
```cpp
while(cin>>s);//将 cin 转换为 bool 值
string s = "value";//将 c 风格字符串转换为 string
```
### 显示转换
**显示转换即使用强制类型转换**。
强制类型转换非常危险，尽量避免使用。如果使用了，应反复思考是否可以用其他方式代替。
`castname<type>(expression);`
castname 有四种：**static_cast、dynamic_cast、const_cast、reinterpret_cast** 。它指定了执行哪种转换。
**static_cast :**
==任何类型转换，只要不包含底层 const，都可以用 static_cast==
```cpp
double slope = static_cast<double>(j)/i; //将 j 转换成 double 以便执行浮点数除法
```
当把较大的类型转换为较小的类型时，static_cast 很有用。这时**它告诉读者和编译器：我们知道且不在乎精度损失**。平时编译器会给警告，显式转换后就不警告了。

**const_cast :**
const_cast 只能改变对象的底层 const。可以去掉或增加 const 性质。
==**只有**== const_cast 能**改变表达式的常量属性**，其他都不行。
cosnt_cast 常用于**有函数重载的上下文中**。
```cpp
string& s;
const_cast <const string&> (s);// 将 s 转换为常量引用
const_cast <string&> (s);// 将 s 转换回非常量引用
```
reinterpret_cast
它依赖于机器，使用门槛很高，且使用时充满风险，==**不要用它**==。

## 5. Chpt 语句 部分笔记
### 5.1 范围for语句
范围 for 语句用来**遍历容器或其他序列的所有元素。**
```cpp
for(declaration : expression)
    statement
```
expression 表示的==必须是一个序列，可以是花括号括起来的初始值列表==。这些序列的共同的是都可以返回迭代器的 begin 和 end 成员。
declaration 定义一个能从序列中元素转换过来的==**变量（不是迭代器）**==。最简单的方法是使用 auto 类型说明符。

如果需要**对容器中的元素执行写操作**，==**必须将循环变量声明成引用类型**==。
==**循环变量可以声明为对常量的引用，不需要写时最好都声明为常量引用**==
**每次迭代都会重新定义循环控制变量**，并将其初始化为序列的下一个值。
范围 for 语句不能改变序列的元素数量。因为**其预存了 end() 的值**，改变元素数量后 end() 的值就可能失效了。












