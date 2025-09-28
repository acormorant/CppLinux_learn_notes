# 第12章 动态内存
- 动态分配对象的生存期通过**显式的分配与释放**来控制。
- 动态对象的正确释放是一个极容易出错的地方。
- **`静态内存`用来保存全局变量与局部 static 对象，类 static 数据成员。**
- **`栈内存`用来保存定义在函数内的非 static 对象。**
- **`堆`保存动态分配的对象。**


## 12.0 补充知识
**堆内存和栈内存的比较：**
- 控制权：
 1. 栈由**编译器自动分配和释放**；
 2. 堆由程序员分配和释放;

- 空间大小：
 1. 栈：windows下，**栈是向低地址扩展的**，是**连续的内存区域**，所以**栈顶地址和栈的最大容量**都是确定的，似乎一般是 2M 或 1M
 2. 堆：**堆是`向高地址扩展`的，是`不连续的内存区域`。系统是`用链表来存储空闲地址`的。堆的大小由计算机的有效虚拟内存决定，因此空间大得多。**
   
- 分配效率：
 1. 栈：速度**较快**。
 2. 堆：速度**较慢**，但使用方便。

- 系统响应：
 1. 栈：如果剩余空间不足，**异常提示栈溢出**
 2. 堆：**在记录空闲地址的链表中寻找空间大于所申请空间的堆结点，然后将该结点从空闲节点链表中删除。**一般会在首地址处记录本次分配空间的大小。
   
- 存储内容：
 1. **栈：存储函数的各个参数、局部变量、函数返回地址等。**第一个进栈的就是函数返回地址
 2. 堆：**内容由程序员决定**。


## 12.1 动态内存与智能指针
>**c++ 使用 new 和 delete 管理动态内存:**
- **new**：在堆中为**对象分配空间**并**返回指向该对象的指针**
- **delete**：接受**一个动态对象的指针，销毁该对象并释放内存**。
   - 忘记释放内存会引起内存泄漏，释放了后继续引用指针会引用非法内存。
   - 如果忘记释放内存，在程序结束时会由操作系统自动回收。

**新标准库提供`两种智能指针和一个伴随类`管理动态内存**，都**定义在`头文件 memory` 中**：
 1. **shared_ptr**：允许多个指针指向一个对象
   
 2. **unique_ptr**：独占所指的对象
   
 3. **weak_ptr**：**一种弱引用，指向 shared_ptr 所管理的对象**
>要注意到：**智能指针实际上是一个`类模板`**。但是它的操作与指针十分相似

### 12.1.1 shared_ptr类
智能指针也是模板，类似 vector。在创建模板时，必须**提供指针指向的类型**。
```cpp
shared_ptr<string> p1;       // 可以指向 string
shared_ptr<vector<int>> p2;  // 可以指向 int 的 vector
```
>默认初始化的智能指针中保存着空指针。
```cpp
if(p1 && p1->empty())
    *p1 = "hi";
```

- **定义 shared_ptr 的方式**
> 可以使用另一个 shared_ptr 或一个 unique_ptr 或 new 的指针来初始化一个 shared_ptr。
```cpp
shared_ptr<int> p;              // 默认初始化为空指针
shared_ptr<int> p(q);           // q 也是一个 shared_ptr,p 是 q 的拷贝，!!此操作会递增 q 中的计数器。
shared_ptr<int> p(qnew);        // qnew 是一个 !!!指向动态内存的内置指针（qnew = new int;)）
shared_ptr<int> p(u);           // u 是一个 unique_ptr。p 从 u 接管了对象的所有权，u 被置为空
shared_ptr<int> p(q, deleter);  // q 是一个 !!!内置指针。p 将使用可调用对象 deleter 来代替 delete
shared_ptr<int> p(p2, deleter); // p2 是一个 shared_ptr，p 是 p2 的拷贝，唯一的区别是 p 将可调用对象 deleter 来代替 delete。

auto p = make_shared<int>(10);  //返回一个 shared_ptr，指向一个初始化为 10 的动态分配的 int 对象。注意不同于 make_pair
```
>**shared_ptr<int> p(q);  // q 也是一个 shared_ptr,p 是 q 的拷贝，!!!此操作会递增 q 中的计数器。**

- **shared_ptr 操作**
```cpp
sp              // 智能指针作为 if 的判断条件时检查其是否为空，若 sp 指向一个对象，则为 true
sp->mem;        // 等价于 (*p).mem。 **用于当 sp 指向一个类时**
sp.get();       // 返回 sp 中保存的指针。要小心使用！
swap(p, q);     // 交换 p 和 q 中的指针
p.swap(q);      // 同上

p = q;          // 此操作会递增 q 中的计数器，递减 p 原来的计数器，若其变为 0，则释放。
p.unique();     // 若 p.use_count() 为 1，返回 true，否则返回 false
p.use_count();  // 返回与 p 共享对象的智能指针数量。**可能运行很慢，主要用于调试**

p.reset();     // 将 p 置为空，如果 p 计数值为 1，释放对象。
p.reset(q);    // !!! q 是一个内置指针，令 p 指向 q。
p.reset(q, d); // 调用可调用对象 d 而不是 delete 来释放 q
```
>**p = q;  // 此操作会递增 q 中的计数器，递减 p 原来的计数器，若其变为 0，则释放。**


- **make_shared 函数**
>**这是最安全的分配和使用动态内存的方法**
 **make_shared 类似顺序容器的 emplace 成员**，**用参数来构造对象**。 

 **通常用 auto 来定义一个对象保存 make_shared 的结果**。

 **make_shared `是函数模板，要提供模板参数`**
```cpp
shared_ptr<int> p1 = make_shared<int>(10);
auto p2 = make_shared<string>(10,'s');
```

- **shared_ptr 的拷贝和赋值**
> **每个 shared_ptr 都有一个关联的计数器,通常称之为`引用计数`，如果拷贝一个 shared_ptr，计数器就会递增。**
 例如**初始化**，或**作为参数传递给函数**，或**作为函数返回值**时。

 如果 shared_ptr 的计数器变为 0，就会**自动释放管理的对象**。
```cpp
auto r = make_shared<int>(42);  // r 指向的 int 只有一个引用者
r = q; // 给 r 赋值，令它指向另一个地址。
//这会递增 q 指向的对象的引用计数，并递减 r 原来指向的对象的引用计数。因为 r 原来指向的对象没有已经没有引用者，所以会自动释放。
```

- **shared_ptr 自动销毁所管理的对象**
>shared_ptr **通过析构函数来完成销毁**。
 它的**析构函数会递减对象的引用计数，如果计数变为 0，则销毁对象并释放内存**。


- **shared_ptr 自动释放相关联的内存**
 由于最后一个 shared_ptr 销毁前内存都不会释放，所以要保证 shared_ptr 无用之后就不要再保留了。

 如果忘记销毁不再需要的 shared_ptr，程序不会出错，但会浪费内存。

 一种**常用的情况是将 shared_ptr 存放在一个容器中，后来其中有一部分元素不再用到了，这时要注意用 erase 删除不需要的元素**。


- **析构函数**
 **每个类都有析构函数。析构函数控制对象销毁时执行什么操作。**

 析构函数**一般用来释放对象分配的资源**。如 vector 的析构函数销毁它的元素并释放内存。

- **使用动态内存的三种情况**
 1. **不知道需要使用多少对象。例如容器类**

 2. **不知道对象的准确类型。**

 3. **需要在`多个对象间共享内存`。**

- **使用动态内存在多个对象间共享内存**
 **定义一个类，类的数据成员为一个 shared_ptr。使用此 shared_ptr 来管理一个 vector，即可实现在多个类对象间共享同一个 vector。**
 > 当所有类对象都被销毁时 vector 才会被销毁。
 >**注意一个类只会与它的拷贝共享一个 vector，单独定义的两个类是不共享的。**

#### 一个实例：StrBlob类
StrBlob 类是一个使用动态内存在多个对象间共享内存的例子。
>StrBlob 类中仅有一个 shared_ptr 成员，这个 shared_ptr 指向一个 string 的 vector。
```cpp
#ifndef STRBLOB_H
#define STRBLOB_H

#include<iostream>
#include<vector>
#include<memory>
#include<string>
#include<initializer_list>
using namespace std;

class StrBlob{
    using size_type = vector<string>::size_type;      // 灵活使用类型别名
    public:
    StrBlob();
    //定义了一个接受初始化列表的转换构造函数（注意不是 explicit 的）
    StrBlob(initializer_list<string> il);
    size_type size() const { return data.size();}
    bool empty() const { return data.empty();}
    void push_back(const string& s) { data.push_back(s);} 
    void pop_back();
    string& front();
    string& back();
    //在普通的 front()和back() 函数外又重载了一个 const 的版本
    const string& front() const;
    const string& back() const;
    private:
    shared_ptr<vector<string>> data;

    
    //定义了一个 check 函数来检查索引是否超出边界,如果data[i]不合法,抛出一个异常
    void check(size_type i,const string&msg) const;

}
StrBlob::StrBlob() : data(make_shared<vector<string>>()) { }
StrBlob::StrBlob(initializer_list<vector<string>> il) : data(make_shared<vector<string>>(il)) { }

void StrBlob::check(size_type i,const string&msg) const {
    if(i >= data.size()) throw out_of_range(msg);
}

string & StrBlob::front(){
    check(0,"front on empty StrBlob");
    return data->front;
}
string & StrBlob::back(){
    check(0,"back on empty StrBlob");
    return data->back;
}
const string& front() const{
    check(0,"front on empty StrBlob");
    return data->front;
}
const string& back() const{
    check(0,"back on empty StrBlob");
    return data->back;
}

string & StrBlob::pop_back(){
    check(0,"pop_back on empty StrBlob");
    return data->pop_back();
}


#endif //STRBLOB_H
```
- **在实现上面这个类时要注意的几点：**
 1. **对于不改变类的成员的函数，要声明为 const 的。**
   
 2. 对于 front(), back() 等返回成员的函数，**既要定义返回普通引用的版本，也要定义返回常量引用的版本。返回常量引用的版本要声明为 const 的，这样才能成功地进行重载**，不然只有返回值类型不同，编译器无法区分。

 3. check 函数不检查 i 是否小于 0 是因为 i 的类型是 size_type，是无符号类型，如果 i<0 会被自动转换为大于 0 的数

 4. 这里的接受 initializer_list 的转换构造函数**没有定义为 explicit** 的，这样的**好处是使用方便，可以进行隐式的转换。缺点是不易调试。**

### 12.1.2 直接管理内存
>可以使用 new 和 delete 来直接管理内存。相比于智能指针，它们非常容易出错。
自己直接管理内存的类不能依赖默认合成的拷贝控制成员，通常都需要自己定义。**而使用了智能指针的类则可以使用默认合成的版本。**

- **使用new动态分配和初始化对象**

 **new 无法为分配的对象命名，只是返回一个指针。**

 **默认情况下，动态分配的对象被默认初始化**。可以用**直接初始化或列表初始化或值初始化初始动态分配的对象。**
```cpp
int* p = new int;   //默认初始化
string* sp = new string(10,'g');//直接初始化
vector<int>* vp = new vector<int>{0,1,2,3};//列表初始化
```

- **区分值初始化和默认初始化**
 
 **对于类来说，值初始化与默认初始化没有什么区别，`对于内置类型来说，值初始化对象会有一个良好的值，默认初始化对象值未定义`。**
 >**值初始化只需加括号即可。**
```cpp
int* p1 = new int;   // 默认初始化，p1 所指对象的值是未定义的
int* p2 = new int(); // 值初始化，p2 所指对象的值初始化为 0
```
 **建议对动态分配的对象进行值初始化**，如同变量初始化一样。

- **使用 auto**
 >**当用括号提供了`单个初始化器`，就可以使用 auto（`前后都用 auto`）**
```cpp
auto p1 = new auto(a);        // p1 指向一个与 a 类型相同的对象，该对象用 a 初始化
auto p1 = new auto{a, b, c};  // 错误，不是单一初始化器，有多个。
```

- **动态分配的 const 对象**
 >**可以使用 new 分配 const 对象，`前后都要加 const`**
```cpp
const int* pci = new const int(10);
```
**动态分配的 const 对象必须初始化，类类型可以隐式初始化。**

- **内存耗尽**
  
 如果没有可用内存了，new 就会失败。

 **默认情况下，如果 new 失败，会爆出一个 bad_alloc 类型的异常。**

 使用`定位 new` 可以向 new 传递参数，**传递 nothrow 可以阻止 new 在分配失败的情况下抛出异常。**
 >bad_alloc 和 nothrow 都定义在头文件 new 中
```cpp
int* p = new(nothrow) int;//如果分配失败，返回一个空指针
```

- **释放动态内存**
 >使用 delete 表达式来释放动态内存，包括动态分配的 const 对象也是直接 delete 即可。
  - delete执行两个动作：
     1. 销毁指针所指对象（**但没有销毁指针本身**）
   
     2. 释放对应内存
```cpp
delete p; // p 必须指向一个动态分配的对象或是一个空指针

int i, *pil = &i, *pi2 = nullptr;
double *pd = new double(33), *pd2 = pd;
delete i;   //错误: i不是一个指针
delete pil; //未定义:pil指向一个局部变量
delete pd;  // 正确
delete pd2; //未定义:pd2指向的内存已经被释放了
delete pi2; //正确: 释放一个空指针没有错误
```
 **释放一个不是动态分配的指针和相同的指针释放多次的行为都是未定义的。**

 **通常编译器不能分辨 delete 的对象是动态还是静态分配的对象，也不能分辨一个指针所指的内存是否已被释放**。

 对于一个**内置指针管理的动态对象直到被显式释放前都是存在的**。

   - 两种特殊情况：
     1. 指针不在内存还在
         当指针是一个局部变量，因超出作用域而被销毁时，其指向的动态内存不会自动释放。当没有指针指向这块内存时，就无法再释放了。**这就是忘记 delete 产生的内存泄漏的问题。**
     2. 指针还在内存不在
         a. **delete一个指针后，指针值已经无效，但是指针还是保存着地址，此时就变成了空悬指针**. 有两个解决方法:
             i. **delete 之后将指针置为空指针**
             ii. **在指针作用域的末尾 delete**
            
     如果有**多个指针指向同一块动态内存，只能 delete 一个指针，因为 delete 的是空间**，如果 delete 两个指针，可能会破坏自由空间。**但必须将多个指针都重置。**

   - 使用 new 和 delete 的三个常见错误：
     1. 忘记 delete 内存：内存泄漏。
     2. 使用已释放的的对象。
     3. 同一块内存释放两次。

    - **内存泄漏: 直接管理内存和智能指针差别**
```cpp
int *q = new int (42), *r = new int (100);
r = q;
auto q2 = make_shared<int>(42), r2 = make_shared<int>(42);
r2 = q2;
/*
这段代码非常好地展示了智能指针在管理内存上的优点。

对于普通指针部分，首先分配了两个int型对象，指针分别保存在p和r中。 接下来，将指针q的值赋予了r，这带来了两个非常严重的内存管理问题：

1．首先是一个直接的内存泄漏问题，r和q一样都指向42的内存地址，而r中原来保存的地址——100的内存再无指针管理，变成“孤儿内存”，从而造成内存泄漏。

2．其次是一个“空悬指针”问题。由于r和q指向同一个动态对象，如果程序编写不当，很容易产生释放了其中一个指针，而继续使用另一个指针的问题。继续使用的指针指向的是一块已经释放的内存，是一个空悬指针，继续读写它指向的内存可能导致程序崩溃甚至系统崩溃的严重问题。

而shared_ptr则可很好地解决这些问题。首先，分配了两个共享的对象，分别由共享指针r2和q2指向，因此它们的引用计数均为1。接下来，将q2赋予r2,赋值操作会将q2指向的对象地址赋予r2，并将r2原来指向的对象的引用计数减1， 将q2指向的对象的引用计数加1。这样，前者的引用计数变为0，其占用的内存空间会被释放，不会造成内存泄漏。而后者的引用计数变为2，也不会因为r2和q2之一的销毁而释放它的内存空间，因此也不会造成空悬指针的问题。
*/
```
[t12_6](#t12_6)

### 12.1.3 shared_ptr和new结合使用
 >可以使用 new 初始化智能指针。但是最好还是用 make_shared

 **接受指针参数的智能指针构造参数是 `explicit` 的，`不能将内置指针隐式地转换为智能指针`。因此不能使用赋值，只能用直接初始化**
```cpp
shared_ptr<double> p1(new int(42));  // 正确：使用直接初始化形式
shared_ptr<double> p2 = new int(42); // 错误：拷贝构造函数是 explicit 的，不能隐式转换

shared_ptr<int> clone(int p){
    return new int(p); //错误:隐式转换为shared_ptr<int>
    return shared_ptr<int>(new int(p));//正确: 显示的用int* 创建shared_ptr<int>
}
```
 **默认情况下用于初始化智能指针的普通指针只能指向动态内存，因为智能指针默认使用 delete 释放对象。**

 如果**将智能指针绑定到一个指向其他类型资源的指针**上，**要定义自己的删除器(函数) 来代替 delete**

- **建议不要混用智能指针和普通指针**
>**shared_ptr 可以协调对象的析构，但仅限于自身的拷贝之间。这就是推荐使用 make_shared 而不是 new 的原因。**

 使用普通指针（即 new 返回的指针）来创建一个 shared_ptr 有两个易错之处：
     1. 使用普通指针创建 shared_ptr 后，又使用该普通指针访问动态对象。普通指针并不知道该对象何时被 shared_ptr 所释放，随时**可能变成空悬指针**。
     2. 使用**同一个普通指针创建了多个 shared_ptr ，这就将同一块内存绑定到多个独立创建的 shared_ptr 上了。**
   
 **当将一个 shared_ptr 绑定到一个普通指针后，就不要再用内置指针来访问所指内存了。**
```cpp
void process(shared_ptr<int> ptr){ }

//正确使用方法是传递给它一个shared_ptr:
shared_ptr<int> p(new int(42));//引用计数为1
process(p); //拷贝p会递增其引用计数,在process中为2
int i = *p; //正确: 引用计数为1

//传递临时的shared_ptr可能导致错误
int *x(new int(42));
process(x); //错误:不能将一个int*转换为一个shared_ptr<int>
process(shared_ptr<int>(x)); //合法的,但内存会被释放
int j= *x;  // 未定义的: x是一个空悬指针!

//正确的临时shared_ptr
//shared_ptrint<int> p(new int(42));
process(shared_ptr<int>p); 
/*
此调用是正确的，利用p创建一个临时的shared
ptr赋予process的参数 ptr，p和ptr都指向相同的int对象，引用计数被正确地置为2。process 执行完毕后，ptr被销毁，引用计数减1，这是正确的——只有p指向它。
*/
```

- **不要使用 get 初始化另一个智能指针或为智能指针赋值**
>智能指针的 get 函数返回一个内置指针。
```cpp
shared_ptr<int> p(new int(42));
int* q = p.get();   // 这是正确的，但是要极小心地使用，这会非常容易出错。
```
 注意：不要使用 get 初始化另一个智能指针或为智能指针赋值。**也不能通过 get 返回的指针来 delete 此指针。**

 **shared_ptr 的关联计数只应用于自己的拷贝，如果使用某智能指针的 get 函数初始化另一个智能指针，两个指针的计数是不关联的，销毁一个就会直接释放内存使另一个成为空悬指针。**

 **一个错误的例子**
```cpp
auto sp = make_shared<int>();
auto p = sp.get();//用get获取了sp指向的int对象的地址
delete p;         //释放了这个地址,意味着sp的引用计数仍为1,但指向的int对象已经释放了.sp成为了空悬shared_ptr.
```

### 12.1.4 智能指针和异常
>使用**异常处理的程序能在异常发生后令程序流程继续**，它需要**确保在异常发生后资源能被正确地释放**，一种简单的方法是使用智能指针。

 使用智能指针时发生异常，智能指针管理的内存会被释放掉，而如果是直接管理内存时，在 new 和 delete 之间发生了异常，则内存不会被释放。
- **智能指针和哑类**
>所有标准库类都定义了析构函数，负责清理对象使用的资源。
  但是那些**为 C 和 C++ 两种语言设计的类，通常都没有良好定义的析构函数，必须显式释放资源**。

 如果在资源分配和释放之间发生了异常，或程序员忘记释放资源，程序也会发生资源泄漏。

 例如网络连接中的在释放连接前发生了异常，那么连接就不会被释放了。

- **使用自己的释放操作**

 默认情况下，shared_ptr 假定它们指向的是动态内存，在销毁时会使用 delete 操作。

 但也可以使用 shared_ptr 管理其他对象，如网络连接，这时就需要定义一个相应的删除器函数来代替 delete。

 **可以定义一个函数来代替 delete，称为删除器。**
```cpp
share_ptr<T> p(&t, deleter);  //deleter 必须是一个接受一个 T* 类型参数的函数
使用 shared_ptr 管理网络连接
shared_ptr<connection> p(&c, end_connection);// end_connection 是 p 的删除器，它接受一个 connection* 参数
```
[t12_14](#t12_14)

- **智能指针陷阱**
 1. 不使用相同的内置指针值初始化或 reset 多个智能指针

 2. 不 delete get() 返回的指针

 3. 不使用 get() 初始化或 reset 另一个智能指针

 4. 如果使用 get() 返回的指针，当最后一个对应的智能指针被销毁后，指针就变为无效的了

 5. 如果智能指针管理的不是 new 分配的内存，记住传递给它一个删除器

### 12.1.5 unique_ptr
 **同一时刻只能有一个 unique_ptr 指向一个给定对象。**

 **当 unique_ptr 被销毁时，指向对象也被销毁**。

 **定义 unique_ptr 时，需要`绑定到一个 new 返回的指针上`（不同于 shared_ptr)。**
     >**c++14 中加入了 make_unique<T>**

 **类似 shared_ptr，初始化 unique_ptr 必须采用直接初始化。（这里指使用 new 初始化）**

 因为 unique_ptr 独有它指向的对象，所有它**不支持拷贝和赋值**操作。
     >**实际上 unique_ptr 的拷贝构造函数被定义为删除的。**

- **unique_ptr 定义和初始化**
```cpp
unique_ptr<int> u1;             // 定义一个空 unique_ptr
unique_ptr<int> u1(new int());  // 正确
unique_ptr<int,deleter> u;      // 定义一个空 unqiue，用可调用对象 deleter 代替 delete
unique_ptr<int,deleter> u(d);   // 空 unique，用类型为 deleter 的对象 d 代替delete
unique_ptr<int,decltype(d)*> u(new int(42),d);

unique_ptr<int> u2(u1);         // 错误：不支持拷贝
```
>注意 **unique_ptr 管理删除器的方式与 shared_ptr 不一样。`unique_ptr 将删除器放在尖括号中`**
- **unique_ptr 操作**
```cpp
u.get();
u1.swap(u2);swap(u1,u2);

u = nullptr;             // 释放 u 指向的对象并将 u 置为空
auto u2 = u.release();   // u 放弃对指针的控制权，返回 u 中保存的内置指针，并将 u 置为空，注意 u2 的类型是内置指针，而不是 unique_ptr
u.reset();               // 释放 u 指向的对象
u.reset(nullptr);        // 释放 u 指向的对象，并将 u 置为空，等价于 u = nullptr;
u.reset(q);              // 令 u 指向内置指针 q 指向的对象
```
**可以通过 release 或 reset 将指针的所有权从一个 unique_ptr 转移给另一个 unique**
```cpp
unique_ptr<int> u2(u1.release());  // 控制器转移给 u2，u1 置为空
u3.reset(u1.release());            // 释放 u3 原来指向的内存，u3 接管 u1 指向的对象。
```
- **release的使用**
 >release 返回的指针通常用来初始化其他智能指针或给其他智能指针赋值。
 **release 返回的指针不能空闲，必须有其他指针接管对象**。如果是一个内置指针接管了 release 返回的指针，那么程序就要负责资源的释放。
```cpp
u.release();             // 错误：release 不会释放内存，没有其他指针接管内存。
auto u2 = u1.release();  // 正确，但必须记得 delete u2
```
  - shared_ptr为什么没有release成员?
     unique_ptr独占对象所有权,不能拷贝和赋值;release操作用来进行对象所有权的转移,而shared_ptr需要共享时可以简单拷贝和赋值;

- **传递unique_ptr参数和返回unique_ptr**
 >不能拷贝 unique_ptr 参数的规则有一个例外：**可以拷贝或赋值一个将要被销毁的 unique_ptr。如从函数返回一个 unique_ptr**
```cpp
unique_ptr<int> clone(int p) {
    unique_ptr<int> ret(new int(p));
    return ret;
}
```
 上面这种情况，编译器知道要返回的对象将要被销毁，在此情况下，编译器执行一种特殊的拷贝。

- **向 unique_ptr 传递删除器**

 类似 shared_ptr，unique_ptr 默认情况下使用 delete 释放它指向的对象。可以重载 unique_ptr 中默认的删除器。

 但 **unique_ptr 管理删除器的方式与 shared_ptr 不一样。unique_ptr 将删除器放在尖括号中**,`创建或reset`这种unique_ptr类型的对象时,必须提供一个`指定类型的可调用对象`(删除器).

 因为对于 unique_ptr 来说，**删除器的类型是构成 unique_ptr 类型的一部分**。
```cpp
void f(destination &d){
    connection c = connect(&d);
    unique_ptr<connection, decltype(end_connection)*>
        p(&c, end_connection);
}
```
 

- **auto_ptr**
 auto_ptr 是标准库的较早版本包含的一个类，它具有 unique_ptr 的部分特性。相比于 unique_ptr，不能在容器中保存 auto_ptr，也不能从函数返回 auto_ptr。
  - 错误案例
```cpp
int ix = 1024, *pi = &ix, *pi2 = new int(2048);
unique_ptr<int> p0(ix);      // 错误：从 int 到 unique_ptr<int> 的无效的转换
unique_ptr<int> p1(pi);      // 运行时错误：当 p1 被销毁时会对 pi 调用 delete，这是一个对非动态分配返回的指针调用 delete 的错误。
unique_ptr<int> p2(pi2);     // 不会报错，但当 p2 被销毁后会使 pi2 成为一个悬空指针
unique_ptr<int> p3(new int(2048));   // 正确，推荐的用法
```

### 12.1.6 weak_ptr
 >**weak_ptr 指向一个由 shared_ptr 管理的对象，它不控制所指向对象的生存期。**
 将一个 weak_ptr 绑定到 shared_ptr **不会改变 shared_ptr 的引用计数**。

 如果 shared_ptr 都被销毁，即使还有 weak_ptr 指向对象，对象依然会释放（因此**不能使用 weak_ptr 直接访问对象**）。

- **weak_ptr 初始化**
 >创建 weak_ptr 时，要用 shared_ptr 来初始化它。
```cpp
weak_ptr<T> w;         // 默认初始化，定义一个空 weak_ptr w，w 可以指向类型为 T 的对象
w = p;                 // p 可以是一个 shared_ptr 或 weak_ptr，赋值后 w 与 p 共享对象
weak_ptr<T> w(sp);     // 定义一个与 shared_ptr sp 指向相同对象的 weak_ptr。T 必须能转换成 sp 指向的类型（不必相同）
```
- **weak_ptr 操作**
 >因为 weak_ptr 的对象可能被释放的，因此不能直接访问对象，必须调用 lock()。lock() 检查 weak_ptr 所指的对象是否仍存在，如果存在，返回一个指向共享对象的 shared_ptr。

 理解：返回的这个 shared_ptr 会使引用计数加 1。
```cpp
w = p;            // p 可以是一个 shared_ptr 或 weak_ptr。赋值后 w 与 p 共享对象。
w.reset();        // 将 w 置为空
w.use_count();    // 返回与 w 共享对象的 shared_ptr 的数量
w.expired();      // 若 w.use_count() 为 0，返回 true，否则返回 false。expired 是 “过期的” 意思
w.lock();         // 如果 w.expired 为 true，返回一个空 shared_ptr；否则返回一个指向 w 的对象的 shared_ptr
```
- **weak_ptr 操作的应用**
```cpp
if(shared_ptr<int> np = wp.lock())  // 如果 np 不为空则条件成立
```

#### 一个实例：StrBlobPtr类
 >StrBlobPtr 类起到一个充当 StrBlob 迭代器的作用，指向 StrBlob 管理的容器中的某个元素。
 StrBlobPtr 构造函数接受的是 StrBlob 的非常量引用，因此无法使用 const StrBlob，如果想要使用，那需要再定一个 ConstStrBlobPtr 类。

- notes: 
     - **类A和类B需要彼此互相引用，这样必然有一个类会先被定义，而另外一个类后被定义，这样在先被定义的类引用后被定义的类的时候，就导致了所谓的超前引用。** `class StrBlobPtr;`
     - **!注意: 使用其他类时,若只使用类名,则可超前引用;若使用具体成员,相同头文件中需要在被使用成员的类定义完成后再定义对应函数,不同头文件中需要#include"被引用类头文件"**
```cpp
class StrBlobPtr{
    friend bool eq (const StrBlobPtr&, const StrBlobPtr&);
    using size_type = vector<string>::size_type;      // 灵活使用类型别名
    public:
    StrBlobPtr(): curr(0) {}
    StrBlobPtr(StrBlob &a, size_type sz = 0): wptr(a.data), curr(sz) {}
    string& deref() const ;//解引用:返回curr位置上的元素值
    StrBlobPtr& incr();//前缀递增: 返回递增后对象的引用
    StrBlobPtr& decr();

    private:
    //若检查成功,返回一个指向vector的shared_ptr
    shared_ptr<vector<string>> check(size_type, const string&) const;
    weak_ptr<vector<string>> wptr;
    size_type curr; //在数组中的当前位置
};

shared_ptr<vector<string>> StrBlobPtr::check(size_type i, const string& msg) const{
    auto ret = wptr.lock();
    if(!ret)
        throw runtime_error("unbound StrBlobPtr");
    if(i >= ret->size())
        throw out_of_range(msg);
    return ret;
}

string& StrBlobPtr::deref() const{
    auto p = check(curr, "dereference past end");
    return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr(){
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}

StrBlobPtr& StrBlobPtr::decr(){
    check(curr, "decrement past end of StrBlobPtr");
    --curr;
    return *this;
}

inline StrBlobPtr StrBlob::begin(){
    return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end(){
    return StrBlobPtr(*this, data->size());
}

inline bool eq(const StrBlobPtr& lhs,const StrBlobPtr& rhs){
    auto l = lhs.wptr.lock(), r = rhs.wptr.lock();
    // 若底层vector是一个
    if(l == r)
        // 则两个指针皆空,或指向相同元素时,它们相等
        return ((!r&&!l) || lhs.curr == rhs.curr);
    else
        return false;

}
```
>StrBlob类也有对应改动
```cpp
class StrBlobPtr;//超前引用, 友元声明中需要
class StrBlob{
    friend class StrBlobPtr;
    using size_type = vector<string>::size_type;      // 灵活使用类型别名
    public:
    StrBlob();
    //定义了一个接受初始化列表的转换构造函数（注意不是 explicit 的）
    StrBlob(initializer_list<string> il);
    size_type size() const { return data->size();}
    bool empty() const { return data->empty();}
    void push_back(const string& s) { data->push_back(s);} 
    void pop_back();
    string& front();
    string& back();
    //在普通的 front()和back() 函数外又重载了一个 const 的版本
    const string& front() const;
    const string& back() const;

    //提供给StrBlobPtr的接口
    //StrBlobPtr begin() {return StrBlobPtr(*this);} //错误!!!定义StrBlobPtr后才能定义这个函数!!!
    StrBlobPtr begin(); //!!!定义StrBlobPtr后才能定义这个函数
    StrBlobPtr end();

    private:
    shared_ptr<vector<string>> data;
    //定义了一个 check 函数来检查索引是否超出边界,如果data[i]不合法,抛出一个异常
    void check(size_type i,const string&msg) const;

};
```
[StrBlob.h](#StrBlob.h)

## 12.2 动态数组

 new 和 delete 运算符一次分配/释放一个对象。

 C++ 中提供了两种**一次分配一个对象数组**的方法：

   1. 使用如 **new int[10]** 来分配一个对象数组；
   
   2. **使用`allocator 类`。allocator 类的优点是可以实现`内存分配与对象构造的分离`，更灵活地管理内存。**

一般不需要使用动态分配的数组，而是使用如 vector 之类的 STL 容器。使用容器的类可以使用默认版本的拷贝、赋值、析构等操作，而分配动态数组的类必须定义自己版本的函数在相关操作时管理内存。

### 12.2.1 new和数组

 使用方括号来分配一个对象数组，new 分配成功后返回指向第一个对象的指针。

 方括号中的大小**必须是整型，但不必是常量**。
```cpp
int *pia = new int[get_size()];   // pia 指向第一个 int
```
 也可以使用一个表示数组类型的类型别名来分配一个数组。
```cpp
typedef int arrT[42];   // arrT 表示 42 个 int 的数组类型。
int *p = new arrT;      //分配一个包含 42 个 int 的数组；p 指向第一个 int
```

- **分配一个数组得到一个元素类型的指针**

 虽然常把 new T[] 分配的内存叫做动态数组，但是**实际上它并不是一个数组，而只是返回`第一个元素的指针`。**
 >理解：数组类型是包含其维度的，**而 new 分配动态数组时提供的大小不必是常量，这正是因为它并非分配了一个“数组类型”**。

 因为动态数组不是数组类型所以**不能对它调用 begin() 或 end() 函数**（这两个函数**根据数组维度**返回指向首元素和尾后元素的指针），也**不能使用范围 for 语句**来处理动态数组。

- **初始化动态分配对象的数组**

 默认情况下 new 分配的对象不管是单个的还是动态数组，**都是默认初始化**的。

 可以对动态数组进行**值初始化和列表初始化**
```cpp
int *pia = new int[10];       // 10 个未初始化的 int
int *pia2 = new int[10]();    // 10 个值初始化为 0 的 int
int *pia3 = new int[10]{0, 1, 2, 3, 4, 5};  // 前 5 个元素用给定的值初始化，剩余的进行值初始化
```
 可以用空括号对数组中的元素进行值初始化，但**不能在括号中给出初始化器**，因此也不能使用 auto 分配数组。

 因为值初始化时不能提供参数，所以**没有默认构造函数的类是无法动态分配数组的**。

- **动态分配一个空数组是合法的**
 虽然不能创建一个大小为 0 的数组对象，但当 n=0 时，调用 new int[n] 是合法的，它返回一个合法的非空指针。此指针保证与 new 返回的其他任何指针都不相同。

 对零长度的数组来说，此指针就像尾后指针一样，不能解引用，但是可以用在循环的终止条件判断中。

- **释放动态数组**
 >使用 delete [] 来释放动态数组
```cpp
delete p;           // p 必须指向一个动态分配的对象或为空
delete [] pa;       // pa 必须指向一个动态分配的数组或为空
```
 使用 delete [] 会将动态数组中的元素按逆序销毁并释放内存。

 如果在 delete 一个指向动态数组的指针时**忽略了方括号，行为是未定义**的。

- **智能指针和动态数组-unique_ptr**
 标准库提供了一个可以管理 new 分配的数组的 unique_ptr 版本。这一版本的 unique_ptr 自动使用 delete[] 来释放数组。
```cpp
unique_ptr<int[]> up(new int[10]);          // up 指向一个包含 10 个未初始化 int 的数组
for(size_t i=0; i!=10; ++i)   up[i] = i;    // 可以通过 up 使用下标运算符来访问数组中的元素
up.release();                               // 自动使用 delete[] 销毁其指针
```
 >指向数组的 unique_ptr 不支持成员访问运算符（点和箭头），但支持通过下标访问数组中的元素。
```cpp
unique_ptr<T[]> u      // u 可以指向一个动态分配的数组，数组元素类型为 T
unique_ptr<T[]> u(p)   // u 指向内置指针 p 所指向的动态分配的数组，p 必须能转换为类型 T*
u[i]                   // 返回 u 拥有的数组中位置 i 处的对象
```
[t12_23](#t12_23)
[t12_24](#t12_24)
- **智能指针和动态数组-shared_ptr**
>shared_ptr 不支持直接管理动态数组。**如果希望使用 shared_ptr 管理动态数组，需要为它提供一个删除器。**
```cpp
shared_ptr<int> sp(new int[10], [](int* p) { delete[] p; });
sp.reset();    //使用上面提供的 lambda 释放数组
```
 如果不提供删除器，shared_ptr 将会使用 delete 来销毁动态数组，这种行为是未定义的。

 **shared_ptr 不直接支持动态数组管理，所以要访问数组中的元素需要使用 get()**
```cpp
for(size_t i = 0; i != 10; ++i)
    *(sp.get() + i) = i;    // 使用 get() 获取一个内置指针，然后来访问元素。
```

### 12.2.2 allocator类
 new 有一个**局限性是它将内存分配和对象构造结合在了一起**，对应的 delete 将**对象析构和内存释放结合在了一起**。

 **标准库 allocator 类定义在头文件 memory 中**，可以实现内存分配与对象构造的分离。

 **allocator 是一个类模板**。定义时需指出这个 allocator 可以分配的对象类型，它会根据对象类型来分配恰当的内存。
- **allocator 的定义与操作**
>下面的 string 可以替换为其他类型。
```cpp
allocator<string> alloc;            // 定义一个可以分配 string 的 allocator 对象
auto const p = alloc.allocate(n);   // 分配 n 个未初始化的 string，返回一个 string* 指针
alloc.construct(p, args);           // p 是一个 string* 指针，指向原始内存。arg 被传递给 string 的构造函数，用来在 p 指向的内存中构造对象。
alloc.destory(p);                   // p 是一个 string* 指针，此算法对 p 指向的对象执行析构函数 
alloc.deallocate(p, n);             // 释放从 p 开始的长度为 n 的内存。p 是一个 allocate() 返回的指针，n 是 p 创建时要求的大小。
                                    // 在 deallocate 之前必须先 destory 掉这块内存中创建的每个对象。  
``` 
 理解：定义的 allocator 对象是一个工具，这个工具可以管理指定类型的内存分配、对象构造、对象销毁、内存释放四种操作，且这四种操作是分开的，分别对应一个函数。

- **allocator 分配未构造的内存**
  
 allocator 分配的内存是**未构造的**，需要**使用 `construct 成员函数`按需在内存中构造对象**。

 construct 成员函数接受**一个指针和零个或多个额外参数**，在给定位置构造一个元素，额外参数用来初始化构造的对象。
```cpp
alloc.construct(q++);               // 在 q 指向的位置构造一个空字符串并递增 q。q 应该指向最后构造的元素之后的位置。
alloc.construct(q++, 5, 'c');       // 在 q 指向的位置构造一个 “ccccc” 并递增 q。
```
>还未构造对象就使用原始内存的结果是未定义的，可能造成严重后果。

- **destory 销毁对象**

 使用完对象后，必须对每个构造的元素都调用 destory 来摧毁它们。

 **destory 接受一个指针，对指向的对象执行析构函数。`注意只能对构造了的元素执行` destory 操作。**

 元素被销毁后可以**重新在这块内存构造对象也可以释放掉内存**。

 construct 和 destory 一次都只能构造或销毁一个对象，要想完成对所有元素的操作，需要通过指针来遍历对每个元素进行操作。

- **deallocate 释放内存**
>传递给 deallocate 的 p 必须指向由 allocate 分配的内存，大**小参数 n 必须与 allocate 分配内存时提供的大小参数一样。**
```cpp
alloc.deallocate(p, n);
```

- **拷贝和填充未初始化内存的算法**
>除了使用 construct 构造对象外，标准库还提供了两个伴随算法，定义在头文件 memory 中，他们在给定的位置创建元素。
```cpp
uninitialized_copy(b, e, b2);     // 从迭代器 b 和 e 指定的输入范围中拷贝元素到从迭代器 b2 开始的未构造的原始内存中。b2 指向的内存需要足够大。
uninitialized_copy_n(b, n, b2);   // 从迭代器 b 指向的元素开始，拷贝 n 个元素到 b2 开始的内存中。
uninitialized_fill(b, e, t);      // 在 b 和 e 指定的范围内创建对象，对象均为 t 的拷贝
uninitialized_fill_n(b, n, t);    // 在从 b 开始的 n 个位置创建对象，对象均为 t 的拷贝。
```
 uninitialized_copy 函数**返回指向构造的最后一个元素之后位置的指针**。

  - 比如希望将一个 vector 拷贝到动态内存中，并对后一半空间用给定值填充。
```cpp
allocator<int> alloc;
auto p = alloc.allocate( v.size() * 2 );
auto q = uninitialized_copy( v.begin(), v.end(), p );
uninitialized_fill_n( q,v.size(),42);
```


## 12.3 使用标准库：文本查询程序

 文本查询程序要实现的功能：允许用户在一个给定文件中查询单词。查询结果是单词在文件中出现的次数及其所在行的列表（包括行号及对应文本），如果一个单词在一行中出现多次，此行只列出一次。

### 12.3.1 文本查询程序设计
- **需求分析**
  
 要实现以上功能，此文本查询程序要做的工作：
   1. 程序读取输入文件时，需要记住单词出现的每一行，并将每一行分解为独立的单词。
   
   2. 程序生成输出时，需要能提取每个单词关联的行号，行号按升序出现且无重复，且能打印给定行号中的文本。

- **数据结构设计**

 使用以下成员存储所需数据：

   1. 一个 vector<string>：按行存储从文件中读取的文本，每一个 string 元素代表一行。
   
   2. 使用 istringstraem 来将行文本分解为单词。

   3. 一个 map<string, set<int>>：存储文件中的每个单词及其对应的行号列表，键 string 为单词，键值 set<int> 为对应的行号列表，set 保证每行只出现一次且行号按升序保存。

- **类的设计**

 定义两个类：一个类 TextQuery 负责保存从输入文件读取到的内容，提供 “读取输入文件” 和 “查询内容” 两个接口；

 此外，**因为我们要的返回结果包含多种内容**（单词出现次数、所有关联行号及对应文本），**为了一次性地将查询结果返回（而不是一个又一个的变量），还要定义一个类 QueryResult 用来保存所有查询结果**。这个类有一个 print 函数，完成结果打印工作。

- **在类之间共享数据**
 进一步地设计：
  1. QueryResult 要包含的内容包括单词出现次数、所有关联行号及对应文本，如果这些数据都拷贝得话会浪费时间，因此最好通过获取指针来避免拷贝操作。
  2. 使用了指针后 QueryResult 就和 TextQuery 共享了数据，这时如果 TextQuery 先销毁了就会导致 QueryResult 引用不存在地数据。因此应该使用 shared_ptr 来共享数据。
   
- **使用TextQuery类**
设计一个类时，在真正实现类的成员前先编写使用这个类的程序，是一种非常有用的方法。这可以看到类是否具有我们所需要的操作。
```cpp
void runQueries(ifstream& infile) {
    TextQuery tq(infile);  // 用指向文件的输入流初始化类，初始化时完成保存文件、建立查询 map 的工作。
    while(true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        if(!(cin >> s) || s == "q") break;
        print(cout, tq.query(s)) << endl; // 查询并打印结果
    }
}
```

### 12.3.2 文本查询程序类的定义
- **TextQuery的定义**
```cpp
class TextQuery
{
    friend class QueryResult;
    using line_no = std::vector<std::string>::size_type;

public:
    TextQuery(std::ifstream &in_file);
    ~TextQuery() = default;
    
    QueryResult query(const std::string &word) const;

private:
    std::shared_ptr<std::vector<std::string>> text_lines_;
    std::map<std::string, std::shared_ptr<std::set<line_no>>> word_indexs_;
};
```

- **TextQuery构造函数**
```cpp
TextQuery::TextQuery(std::ifstream &in_file) : text_lines_(std::make_shared<std::vector<std::string>>())
{
    std::string line_temp;
    while (std::getline(in_file, line_temp))
    {
        text_lines_->push_back(line_temp);
        int line_num = text_lines_->size() - 1; // 当前行号

        std::istringstream in_line(line_temp);
        std::string word;
        while (in_line >> word) // 读取空格分隔的单词直接用 >> 运算符即可
        {
            auto &lines = word_indexs_[word];         // lines 是一个 shared_ptr 的引用
            if (!lines)                               // 如果 word_indexs_ 中不存在 word，那么 lines 会是一个空指针
                lines.reset(new std::set<line_no>()); // 分配一个新的 set
            lines->insert(line_num);                  // 插入当前行号
        }
    }
}
```

- **QueryResult的定义**
```cpp
class QueryResult
{
    friend std::ostream &print(std::ostream &os, const QueryResult &qr);
    using line_no = std::vector<std::string>::size_type;

public:
    QueryResult(std::string word,
                std::shared_ptr<std::set<line_no>> word_index,
                std::shared_ptr<std::vector<std::string>> text_lines) : word_(word), word_index_(word_index), text_lines_(text_lines) {}

private:
    std::string word_;
    std::shared_ptr<std::set<line_no>> word_index_;
    std::shared_ptr<std::vector<std::string>> text_lines_;
};
```

- **query函数**
>直接返回 QueryResult 即可，不必将其作为参数传入其中。
```cpp
QueryResult TextQuery::query(const std::string &word) const // 注意：函数定义时也要加 const
{
    if (word_indexs_.find(word) == word_indexs_.end())
        return QueryResult(word, std::make_shared<std::set<line_no>>(), text_lines_);
    else
        return QueryResult(word, word_indexs_.at(word), text_lines_);
}
```

- **打印结果**
 >print 函数的定义遵循了标准库中 print 函数的惯例，第一个参数和返回值都是流。
```cpp
std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.word_ << " occurs " << qr.word_index_->size() << " times " << std::endl;
    for (auto num : *qr.word_index_)
        os << "\t(line " << num + 1 << ") " << *(qr.text_lines_->begin() + num) << std::endl;
    return os;
}
```

## 列题
### t12_6
>三个函数 创建,输入,打印vector<int>
```cpp
#include<iostream>
#include<memory>
#include<vector>
#include<initializer_list>

using namespace std;

//t12_7 用shared_ptr
shared_ptr<vector<int>> new_vec(void){
    return make_shared<vector<int>>();
}

void read_vec(shared_ptr<vector<int>> spv){
    int item;
    while(cin >> item)
        spv -> push_back(item);
}

void print_vec(shared_ptr<vector<int>> spv){
    for(auto item:*spv){
        cout<<item<<" ";
    }
    cout<<endl;
}


int main(){
    auto spv = new_vec();
    read_vec(spv);
    print_vec(spv);
    //在主函数末尾不需要主动释放内存
}

/*
//t12_6 用new和delete直接管理内存
vector<int> *new_vec(void){
    return new(nothrow) vector<int>;
}

vector<int> *read_vec(vector<int> *vi){
    int item;
    while(cin >> item)
        vi->push_back(item);
    return vi;
}

void print_vec(vector<int> *vi){
    for(auto item:*vi){
        cout<<item<<" ";
    }
    cout<<endl;
}

int main(){
    vector<int> *vi = new_vec();
    read_vec(vi);
    print_vec(vi);

    delete vi; 
    vi = nullptr;
}
*/
```

### t12_14
>编写用shared_ptr管理connection的函数,使用lambda表达式
```cpp
#include<iostream>
#include<memory>
#include<algorithm>

using namespace std;
struct destination{};//链接目标
struct connection{};//链接信息
connection connect(destination *pd){//打开连接
   cout <<"打开链接" <<endl;
   return connection();
}
void disconnect(connection){//关闭给定链接
   cout <<"关闭链接" <<endl;
}

void f(destination &d/*其他参数*/){
    connection c = connect(&d);
    shared_ptr<connection> p(&c,[](connection *p){ disconnect(*p); });
    //忘记调用disconnect
}

int main(){
    destination d;
    f(d);
}
```

### t12_23
>字符串产量与标准库string对象,保存进动态数组中
```cpp
int main(){
    const char* s1{"Hello"};
    const char* s2{"World"};
    char* p = new char[strlen(s1)+strlen(s2)+1];
    strcpy(p, s1);
    strcat(p, s2);
    cout << p <<endl;

    string s3 ="hello";
    string s4 ="world";
    strcpy(p,(s3+s4).c_str());
    cout << p <<endl;
    delete[] p;
}
```

### t12_24
>标准输入读取字符串存入动态分配字符数组,有变长输入处理
```cpp
int main(){
    char *p = new char[20];
    string str;
    getline(cin,str);
    if(str.size() >= 19)
        throw out_of_range("Invalid str.size()>=19");
    else
        strcpy(p,str.c_str());
    cout << *p <<endl;
    delete[] p;
}
```

### t12_26
> allocator分配内存,输入输出string
```cpp
int main(){
    allocator<string> pstr;
    auto piter = pstr.allocate(100);
    auto q = piter;
    string s;
    while(cin>>s && q!=piter+100){
        pstr.construct(q++,s);
    }
    const size_t size = q - piter;
    for(size_t i=0;i<size;i++)
        cout<< piter[i]<<" ";
    cout<<endl;
    while(q!=piter){
        pstr.destroy(q--);
    }
    pstr.deallocate(piter, 100);
}
```