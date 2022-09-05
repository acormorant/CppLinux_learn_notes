# 第10章 泛型算法
标准库提供了一组算法，用来处理不同的容器

## Q&A
1. 算法的操作对象是什么？

迭代器表示的范围

2. 算法在**哪两个头文件**中？

**algorithm 和 numeric**

3. 算法处理两个序列的元素类型有什么要求？

**可以互相比较**

4. 算法关于输入参数的两个假定

**参数为三个迭代器时假定第二个范围不小于第一个，参数为 1 个迭代器时假定范围不小于 n**

5. **常见的只读算法：求和、判等、按条件查找分别如何调用**
```cpp
sum = accumulate(vec.begin(),vec.end(),sum0); 
bool F = equal(vec1.begin(),vec1.end(),vec2.begin());
auto iter = find_if(vec.begin(),vec.end(),可调用对象)；
```

6. 常见的写算法：填充、按长度填充、拷贝、替代、替代拷贝、遍历执行；分别如何调用

**`fill、fill_n、copy、replace、replace_copy、for_each`**

7. 常见的重排算法：排序、稳定排序、去重复排序；分别如何调用

**`sort、stable_sort、unique`**

8. **插入器和插入迭代器是什么？如何使用？**

>插入迭代器：绑定到容器上，可以来向容器插入元素.
>插入器:是一种迭代器适配器，它接受一个容器，生成一个迭代器，能实现向给定容器添加元素。**实际上是一个函数.**
**注意 back_inserter 是插入器，back_insert_iterator<vector<int>> 是插入迭代器类型。back_inserter(v) 返回绑定到容器 v 的 back_insert_iterator，并实现其自增。**

**`auto iter = back_inserter(vec);`**

1. **谓词是什么？有几种？**
    
**`谓词是一个可调用表达式,返回一个可用作条件的值`**,有一元谓词和二元谓词两种.

10. **可调用对象有几种？分别是什么？**

**四种：函数、函数指针、重载了函数运算符的类、`lambda表达式`**

11. lambda表达式**适用于什么情况**？
    
适合那种只在一两个地方使用的简单操作;
当**编写函数完成操作需要的参数,超出了算法对谓词的限制时**,lambda表达式是一种解决方法

12. lambda表达式有几个组成部分？分别是什么？哪两个必不可少？

四个组成部分：捕获列表、参数列表、返回值、函数体。**捕获列表和函数体不能省略**
**`[capture list](parameter list)->return type {function body}`**

13. **lambda 如何使用？**

auto f = []{return 0;} ;   f();

14. 捕获列表的元素是什么？如何使用捕获列表?

**`lambda 所在函数的非 static 变量。`**
捕获列表可以进行值传递和引用传递，如果是值传递直接写变量的名字即可，如果是引用传递就在变量名前加一个 &。

15. [&]{return s;} 是什么含义？[=]{return s;}是什么含义
**[&]表示隐式的引用传递，这时可以在函数体内直接使用外层函数的所有非 static 变量**，函数体中的 s 必然是外层函数中的一个局部变量。[=] 表示隐式的值传递。

16. accumulate求出的和的类型由什么决定

由第三个参数类型决定。

17. **bind 函数有什么作用？如何使用？**
**bind 函数可以改变函数的参数数量和顺序，`函数返回改变参数后的新调用对象`，常用于泛型算法中**。**bind 中的占位符定义在命名空间 placeholders 中。**
```cpp
//基于lambda的find_if调用
auto wc= find_if(txtVec.begin(),txtVex.end(),[sz](const string& s){ return s.size()>sz;});
//可用bind版本替换
auto wc= find_if(txtVec.begin(),txtVex.end(),bind(check_size(),_1,sz));
```

18. 插入迭代器常用于什么地方？
插入迭代器常用于泛型算法中，可以用来向一个序列中插入元素，解决了泛型算法不能向序列添加元素的问题。
**`常用于形参为alg(beg, end, dest, other args);的泛型算法; `**

19. 区分插入器和插入迭代器
**插入器是 back_inserter, front_inserter, inserter 等函数，这些函数会返回一个插入迭代器。**

20. 什么是流迭代器？有什么用
**流迭代器包括 istream_iterator 和 ostream_iterator 两类。**
流迭代器绑定到一个流，常用于一部分泛型算法，从流对象读取数据和写入数据。

21. 反向迭代器如何颠倒？

使用 **base() 成员函数**： auto iter = riter.base()。返回的正向迭代器指向靠后一个元素。

22. 泛型算法命名规范中，同类算法不同版本的三种扩展方式

**同一函数的重载版本多传递一个谓词参数；_if 版本的算法，_copy 版本的算法。**

23. 链表 list 因为其链式结构的特殊性，定义了一些独有的算法版本作为成员函数，有哪些

**合并两个链表 merge，移除等于某个值的元素 remove，排序 sort，删除重复元素 unique，移动元素 splice**

24. bind中如果要传递引用或该参数类型不能拷贝（如 os）怎么办？
    
**使用 ref 函数。**


## 10.1 概述
- **`大多数算法定义在头文件 algorithm 中，部分在 numeric 中`**
- **`这些算法不直接操作容器，而是遍历两个迭代器指定的一个元素范围来进行操作`**。
- **`算法不会改变容器的大小。`**


## 10.2 初识泛型算法
标准库提供了超过100个算法。

标准库算法都对一个范围内的元素进行操作，此元素范围称为“输入范围”

部分算法从两个序列中读取元素，两个序列不必相同（如vector和list），序列中的元素也不必相同（如double和int），要求是**只要能比较两种元素即可**。
- **几种假定**
1. 操作两个序列的算法有的接受三个迭代器：前两个表示第一个序列的元素范围，第三个表示第二个序列的元素范围。**这种情况假定第二个序列至少与第一个一样长。**

2. 向目的位置迭代器写入 n 个数据的算法假定目的位置足够大（大于等于 n）

### 10.2.1 只读算法
>对于只读算法，最好使用 cbegin() 和 cend()。
```cpp
int sum = accumulate(vec.cbegin(),vec.cend(),val);//对输入范围内的元素在 val 的基础上求和。可以对字符串“+”。注意元素是加在val上，如果元素是double，val是int，和会被转换成int
bool F = equal(vec1.cbegin(),vec1,end(),vec2.cbegin());//比较两个序列的元素是否全部相等（假定第二个序列至少与第一个序列一样长）,本质上使用==运算符比较两个序列中元素
                                                       //string重载了==,而c风格字符串本质比较char*中地址
auto iter = find_if(vec.begin(),vec.end(),'一元谓词');//查找符合某条件的元素，返回迭代器，如果没有就返回尾迭代器
```

### 10.2.2 写容器元素的算法
```cpp
fill(vec.begin(),vec.end(),val);//将 val 赋予输入序列中的每一个元素
fill(vec.begin(),vec.begin() + vec.size()/2,10);//将一个容器的前一半的值写为10
//向给定输入序列中写入,只要传递有效输入序列,则写入操作安全

fill_n(dest,n,val);//将 val 赋予从 dest 开始的连续 n 个元素。假定dest开始的序列有至少 n 个元素
fill_n(vec.begin(),vec.size(),0);//将 vec 的所有元素重置为0
//fill_n不检查写操作,如果容器元素小于n或为空,语句结果未定义(保证算法有足够空间容纳输出数据的方法是使用插入迭代器insert_iterator)

for_each(vec.begin(),vec.end(),'可调用对象');
//对输入范围内的每一个元素执行可调用对象的内容。注意：可调用对象是一元谓词，参数类型是迭代器指向的类型
```
[t10_6](#t10_6)
- **插入迭代器**
**`插入迭代器是`一种向容器中添加元素的迭代器。**

当通过插入迭代器向容器赋值时，一个新的元素被添加到容器中。

>函数 back_inserter 定义在头文件 iterator 中。
```cpp
vector<int> vec;
auto it = back_inserter(vec);//it 即为vec新加的插入迭代器
*it = 24;//给 it 赋值后，vec 现在有一个元素为 24(赋值运算符调用push_back)
```
**`可以用 back_inserter() 函数的返回值作为算法的目的位置`**
```cpp
fill_n(back_inserter(vec),10,0);//添加 10 个元素到 vec
```
- **拷贝算法**
>传递给copy的目的序列至少要包含与输入序列一样多的元素.
```cpp
int a2[sizeof(a1)/sizeof(*a1)];//a2大小与a1一样
auto ret = copy(begin(a1),end(a1),begin(a2));//把数组 a1 的内容拷贝给 a2，返回的是目的位置迭代器（递增后）的值

replace(ilst.begin(),ilst.end(),0,42);//把输入范围内所有值为 0 的元素改为 42
replace_copy(ilst.begin(),ilst.end(),dest,0,42);//把输入范围内所有值为 0 的元素改为 42 并拷给 dest 开头的序列。
```


### 10.2.3 重排容器元素的算法
```cpp
sort(words.begin(),words.end());//默认按字典序从小到达排列输入范围内的元素。重复的元素会相邻
auto end_unique = unique(words.begin(),words.end());
//将输入范围内的元素重排，将重复的元素里不是第一次出现的元素都放到序列的后端。返回指向序列后端重复元素中的第一个重复元素的迭代器。
words.erase(end_unique,words.end());//删除重复的元素。erase()函数可以接受两个相等的迭代器作为参数。
```


## 10.3 定制操作
可以使用自定义操作符来替代默认运算符。

### 10.3.1 向算法传递函数
**`谓词是一个可调用的表达式，返回结果是一个可以作为条件的值`**，如返回一个 bool 值。

谓词的参数类型必须是元素类型可以转换到的类型。**谓词的实参是输入序列的元素（是元素本身不是迭代器）**

谓词分为**一元谓词和二元谓词**，分别接受一个参数和两个参数。不同的标准库算法会接受不同的谓词作为参数。
[t10_12](#t10_12)
[t10_13](#t10_13)

### 10.3.2 lambda表达式
一个lambda函数表示一个 **`可调用的代码单元`**,可以将其理解为**一个未命名的内联函数**.

>lambda 表达式适合那种只在一两个地方使用的简单操作。

**`可以向一个算法传递任何类别的可调用对象。`**

总共有四种可调用对象：**函数、函数指针、重载了函数调用运算符的类、lambda表达式**

**lambda表达式组成部分：捕获列表、参数列表、返回类型、函数体**

**`[capture list](parameter list)->return type {function body}`**

- **捕获列表的内容为 lambda所在函数中定义的局部变量**（直接写局部变量的名字即可，通常为空）。**捕获列表只用于局部非 static 变量**。
- **参数列表和返回类型都可以省略。如果忽略返回类型，则根据 return 语句推断返回类型（此时函数体必须只有 return 语句）。**
```cpp
auto f = []{ return 42};//定义了一个可调用对象 f，返回 42
```
- lambda表达式的**调用方式也是使用调用运算符**，内含实参。
- lambda 没有默认参数。

**当操作需要的参数,超出了算法对谓词的限制时**,lambda表达式是一种解决方法:
```cpp
//通过find_if找到vector<string> words 中第一个长度大于sz 的元素 
//(find_if接受一元谓词,words和sz若通过编写函数需要两个参数)
auto wc= find_if(words.begin(),words.end(),
                 [sz](string str){return str.size()>sz });

```
[t10_21](#t10_21)
### 10.3.3 lambda捕获和返回
**`定义一个 lambda 时，编译器生成一个与 lambda 对应的未命名的类类型。`**

当向一个函数传递一个 lambda 时，**同时定义了一个新类型和该类型的一个对象：传递的参数实际上就是此编译器生成的类类型的未命名对象**。
>**类似，auto f = [ ]{ return 42; } 实际上定义了一个类类型的对象。**

默认情况下，从 lambda 生成的类都包含一个对应该 lambda 所捕获的变量的数据成员。

**lambda 捕获变量的方式分为`值捕获`和`引用捕获`，`类似参数传递`**。
- **值捕获**
   - 注意**采用值捕获的前提是变量可以拷贝**。（iostream 等类型不可拷贝）
   - 被值捕获的变量的值是**在 lambda 创建时拷贝，而非调用时拷贝**。`因此在 lambda 创建后改变被捕获的变量不会影响 lambda 中对应的值。`

- **引用捕获**
   - 采用引用捕获时，在捕获列表中的变量名前加上引用符即可。
   - 注意采用引用捕获**必须确保被引用的对象在 lambda 执行时是存在**的。
   - lambda 捕获的都是上层函数的局部变量，在函数结束后就都不复存在了。
   - **引用捕获可以用于捕获变量是 IO 类型时。**

- **使用 lambda**
   - lambda 和含有可调用对象的类对象都可以作为函数的返回值，**要注意此时 lambda 不能包含引用捕获**。
   - **应该尽量减少捕获的数据量，同时尽量避免捕获指针或引用。**
   - 捕获列表中可以同时有值捕获的变量和引用捕获的变量

- **隐式捕获**
  一般在捕获列表中显式地列出所有的捕获变量，但也可以采用隐式捕获。**隐式捕获情况下，编译器会根据 lambda 中的代码来推断要使用的变量。**
>**`隐式捕获只需在捕获列表中写一个 & 或 = 即可，& 表示采用引用捕获，= 表示采用值捕获。`**
```cpp
wc = find_if(words.begin(), words.end(), [=](const string& s){ return s.size()>=sz; });
```

- **混合显式捕获与隐式捕获**
  可以通过混合使用隐式捕获和显示捕获来实现对一部分变量使用值传递，而另一部分使用引用传递。

  **混合捕获时捕获列表中的第一个元素必须是一个 & 或 =：**
>**如果是 &，表示采用隐式的引用捕获，此时后面显式捕获的变量必须都采用值捕获。**
>**如果是 =，表示采用隐式的值捕获，此时后面显式捕获的变量必须都采用引用捕获。**
```cpp
for_each(words.begin(), words.end(), [&,c](const string& s){ os<<s<<c; });   // 这里的 os 是通过隐式的引用捕获得到的。
for_each(words.begin(), words.end(), [=, &os](cosnt string& s){ os<<s<<c;}); // 这里的 c 是通过隐式的值捕获得到的。
```

- **捕获列表**
总结可得，捕获列表可以有六种形式
```cpp
[],[参数序列]             // 空列表与显式捕获
[=],[&]                  // 隐式值捕获与隐式引用捕获
[=,参数列表],[&,参数列表] // 混合捕获
```

- **可变 lambda**
默认情况下，通过值捕获拷贝的变量，lambda 不会改变其值。如果希望改变，必须在参数列表后加上关键字 **`mutable`**。

**引用捕获的变量是否可以修改依赖于引用指向的是 const 还是非 const 类型。**

- **指定 lambda 返回类型**
如果 lambda 中只包含一个单一的 return 语句，可以省略返回类型。

**如果 lambda 中除了 return 还有其他语句，`则编译器假定此lambda返回void`, 此时应该使用`尾置返回`指明返回类型。**

### 10.3.4 参数绑定
**`lambda 表达式适合那种只在一两个地方使用的简单操作`**。如果操作需要很多语句或要在很多地方使用，通常应该定义一个函数。

>**对于捕获列表为空的 lambda，通常可以用函数来代替**。对于捕获列表不为空的 lambda，不容易使用函数替换。

**`标准库 bind 函数:`**
**bind 函数接受一个可调用对象，生成一个新的调用对象来“适应”原对象的参数列表。**
>**bind 函数定义在头文件 functional 中。**
```cpp
//调用bind的一般形式为
auto newCallable =bind(callable,arg_list);
```
- **bind 使用示例**
```cpp
//比较string长度和给定大小
bool check_size(const string& s,string::size_type sz){
        return s.size() >sz;
}
//基于lambda的find_if调用
auto wc= find_if(txtVec.begin(),txtVex.end(),[sz](const string& s){ return s.size()>sz;});
//可用bind版本替换
auto wc= find_if(txtVec.begin(),txtVex.end(),bind(check_size(),_1,sz));
```
>要将 comp2 绑定到 comp1。
```cpp
//函数comp1 比较两个 int 的大小，comp2 相当于第二个参数的默认实参为 6 的 comp1。
comp1(5, 6);//比较 5 和 6 的大小
auto comp2 = bind(comp1, _1, 6);//bind 中第一个参数是 comp1 的函数名，后面的参数是 comp1 的参数列表。bind 的返回值是新生成的可调用对象
        //_1 表示 comp2 的第一个参数，这里表示将 comp2 的第一个参数和 comp1 的第一个参数绑定在了一起。
comp2(7);//使用 comp2 比较 7 和 6 的大小。在调用 comp2(7) 时会将其映射为 comp1(7,6);
```
- **bind 占位符**
**_1,_2,_n 等占位符分别表示新可调用对象的第 1,2,n 个参数**，将 _n 放在 bind 中不同的参数位置，表示将新可调用对象的第 n 个参数和旧可调用对象在该位置的参数绑定在了一起。

>**_1,_2 等定义在命名空间 placeholders 中，placeholders 这个名字定义在 std 中。placeholders 的实现定义在 functional 头文件中。**
```cpp
using namespace std::placeholders;//使用 _1,_2 前要先声明使用命名空间 placeholders。
```
- **bind 绑定的主要功能有两个：**
 `可以减少参数数目。（减少掉的参数被设为一个固定值）`

 `可以改变参数顺序。`
```cpp
auto g = bind(f, a, b, _2, c, _1); // g 只有两个参数，两个参数分别传递给 f 的第 5 个和第 3 个参数

sort(words.begin(),words.end(),bind(isShrter,_2,_1));//用bind重排参数顺序,此语句意为按单词长度 由长至短排序.
```
- **将 bind 用于算法的谓词**
因为算法的谓词只能是一元谓词或二元谓词，所以除了使用 lambda 外，也**可以使用 bind 来将函数的参数缩减为 1 个或 2 个来作为谓词使用。**
```cpp
auto wc = find_if(words.begin(), words.end(), bind(comp2, _1, 6));
```
- **绑定引用参数**
**默认情况下，bind 的那些不是占位符的参数是值传递，被拷贝到 bind 返回的可调用对象中。**

如果要传递引用或该参数类型不能拷贝（如 os）怎么办？**`使用 ref 函数`**。

ref 函数接受一个参数，返回一个可以拷贝的对象，该对象含有参数的引用。cref 生成保存 const 引用的类。ref 和 cref 也定义在头文件 functional 中。
```cpp
//替换一个引用捕获ostream的lambda:
for_each(words.begin(),words.end(),[&os,c](const string& s){ os << s << c;});
//可以很容易编写函数完成相同操作
ostream &print(ostream &os , const string& s,char c){
        return os << s << c;
}
//但是不能直接用bind代替对os的捕获
bind(print, os, _1, '\n');       // 错误，os 不能拷贝
bind(print, ref(os), _1, 'n');   // 正确

for_each(words.begin(),words.end(),bind(print, ref(os), _1, c));
```
- **bind接受几个参数?**
bind是可变参数的。

它接受的第一个参数是一个可调用对象，即实际工作函数A，返回供算法使用的新的可调用对象B。

若A接受x个参数，则bind的参数个数应该是x+1，

**即除了A外，其他参数应一一对应A所接受的参数。这些参数中有一部分来自于B（_n），另外一些来自于所处函数的局部变量。**

### 应用: 对于容器中单词的处理程序
> 对容器中单词删除重复单词,按给定要求排序输出
```cpp
//t10_9 elimDups   (个人认为unordered_set 更为便捷)
//t10_11 要求vector<string>中单词按长度排序,长度相同者按字典序排序
//t10_16 用lambda表达式 计算满足size >= sz的元素数目并输出
//t10_18 用partition代替find_if,重写biggies
//t10_20 用count_if重写统计有多少单词长度超过sz的部分
//t10_22 重写统计长度小于等于sz的单词数的程序 使用bind代替lambda
//t10_42 用list代替vector重写
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

void elimDups(vector<string> &txtVec){
    sort(txtVec.begin(),txtVec.end());
    auto end_unique = unique(txtVec.begin(),txtVec.end());
    txtVec.erase(end_unique,txtVec.end());
}


//通过向稳定排序算法传递二元谓词(以长度排序)
bool isShorter(string s1,string s2){
    return s1.size() < s2.size() ;
}

/* 
//t10_22
bool check_size(const string& s,string::size_type sz){
    return s.size() > sz;
}
//biggies函数中
auto count=count_if(txtVec.begin(),txtVec.end(),bind(check_size,_1,sz));
*/

void biggies(vector<string> &txtVec,vector<string>::size_type sz){
    elimDups(txtVec);//按字典序排序,删除重复单词
    stable_sort(txtVec.begin(),txtVec.end(),
                [](const string &s1,const string &s2){return s1.size() < s2.size();});//按长度排序,长度相同者维持字典序排序
    auto wc = find_if(txtVec.begin(),txtVec.end(),
            [sz](const string &str){return str.size()>sz;});//获取一个迭代器,指向第一个满足要求的元素
    /*
    //t10_18
    如果用partition代替find_if,需要删除不需要的stable_sort,计算满足条件数目和打印语句做些调整
    auto wc = partition(txtVec.begin(),txtVec.end(),
            [sz](const string &str){return str.size()>sz;});
    auto count = wc - txtVec.end();
    for_each(txtVec.end(),wc,[](const string &s){cout << s <<" ";});
    */
    auto count = txtVec.end() - wc;//计算满足size >= sz的元素数目
    /*
    //t10_20
    count_if对范围中每一个元素执行谓词,返回一个计数值,表示谓词多少次为真
    auto count = count_if(txtVec.end(),wc,[sz](const string& s){return s.size()>sz;});
    */
    cout<<"容器中满足size大于"<<sz<<"的元素个数为"<<count<<endl;
    for_each(wc,txtVec.end(),[](const string &s){cout << s <<" ";});//打印长度大于给定值的单词
    cout <<endl;
}

int main(){
    vector<string> txtVec{"Eeeeee","Bbbbbb","Aa","Bb","Ccc","Aa","Ddd","Ccc"};
    biggies(txtVec,4);
    for(auto iter = txtVec.begin();iter != txtVec.end();iter++) cout << *iter <<" ";
}
```

## 10.4 再探迭代器
>除了每个容器各自的迭代器外，标准库在**头文件 iterator** 中定义了四种迭代器：
- 插入迭代器：**绑定到容器上**，可以来向容器插入元素。
- 流迭代器：**绑定到输入或输出流上**，可以用来遍历所关联的 IO 流。
- 反向迭代器：这些迭代器向后移动，除了 forward_list 外的标准库容器都有反向迭代器。
- 移动迭代器：移动迭代器不拷贝其中的元素，而是移动他们。

### 10.4.1 插入迭代器
插入器是一种**迭代器适配器**，`它接受一个容器，生成一个迭代器`，能实现向给定容器添加元素。

**插入器实际上是一个函数。**

**注意 back_inserter 是插入器，back_insert_iterator<vector<int>> 是插入迭代器类型。back_inserter(v) 返回绑定到容器 v 的 back_insert_iterator，并实现其自增。**

- **插入器的三种类型:**
1. **back_inserter：**创建一个使用 push_back 的迭代器。
   >只有容器支持 push_back 才能使用 back_inserter。

2. **front_inserter：**创建一个使用 push_front 的迭代器。
   >只有容器支持 push_front 才能使用 front_inserter。

3. **inserter：**创建一个使用 insert 的迭代器。此函数接受第二个参数，这个参数必须是一个指向给定容器的迭代器，元素将被插入到给定迭代器所表示的元素之前。
  - **front_inserter始终插入首元素前,而inserter始终插入给定迭代器前**,即使传递给它的位置指向容器.begin(),只要在此元素前插入,此元素不再是容器首元素.
  
  - **`(因此,front_inserter生成的迭代器会将插入的元素序列的顺序颠倒,而inserter和back_inserter不会)`**

- **插入迭代器的定义:**

 **有两种方式，一种是`直接定义`，另一种是`通过插入器生成`.**
```cpp
vector<int> v;
'使用插入器生成'
auto bIn = back_inserter(v);  // bIn 是一个绑定到 v 的插入迭代器。
'直接定义'
back_insert_iterator<vector<int>> bIn(v);        // bIn 是一个绑定到 v 的插入迭代器。
insert_iterator<vector<int>> iIn(v, v.begin());  // iIn 是一个绑定到 v 的插入迭代器
```

- **插入迭代器的操作:**

 有实际意义的插入迭代器操作只有一种，就是**赋值操作**。

 当通过插入迭代器赋值时，插入迭代器调用容器操作来向给定容器的指定位置插入一个元素。
```cpp
*bIn = 30;//在 bIn 所绑定的容器的尾元素之后插入一个 30
*iIn = 10;//在 iIn 所绑定的容器的相应元素之前插入一个 10
```
- **插入器 inserter 与函数 insert 的不同:**
 下面的 1 和 2 的效果是一样的。

 **插入迭代器是恒定指向同一个元素的。而 insert 返回的是指向所插入元素的迭代器**
```cpp
'1'
auto iIn = inserter(v, v.begin());
*iIn = 10;
'2'
iter = v.insert(v.begin(), 10);
++iter;//递增iter使其指向原来的元素
```

- **插入迭代器的使用:**
```cpp
vector<int> v1,v2;
*back_inserter(v1) = 1;    // 在 v1 的尾元素之后插入一个 1
*inserter(v1, v1.begin()) = 3; // 在 v1 的首元素之前插入一个 3
copy(v1.begin(),v1.end(),back_inserter(v2)); // 将 v1 的所有元素按顺序拷贝到 v2 的尾元素之后。
copy(v1.begin(),v1.end(),inserter(v2,v2.begin())); // 将 v1 的所有元素按顺序拷贝到 v2的首元素之前
```

- **一个vector中保存1到9共9个值，将其拷贝到三个其他容器中。分别使用 inserter、back＿inserter 和 front＿inserter 将元素添加到三个容器中。对每种 inserter，估计输出序列怎样.**
 若三个目的容器均为空，则显然inserter和back＿inserter的输出结果是＂123456789＂，而front＿inserter的结果是＂987654321＂。

 但如果目的容器不空，则inserter的结果取决于传递给它的第二个参数（一个迭代器）指向什么位置。
[t10_27](#t10_27)


### 10.4.2 iostream迭代器
iostream 有两类:

`istream_iterator：读取输入流。`

`ostream_iterator：向输出流写数据。`

**流迭代器可以绑定到 iostream,fstream,stringstream。它将对应的流当作一个元素序列来处理。**

>流迭代器的**主要作用是辅助使用泛型算法从流对象读取数据和写入数据。**
>创建流迭代器时，必须指定迭代器将要读写的对象类型。
- istream_iterator 的定义
可以为任何具有输入运算符的（>>）类型定义 istream_iterator，即所有内置类型和重置了 >> 的类。

创建流迭代器时，有**两种情况**：
1. **绑定到一个流**
2. **默认初始化：采用这种方式创建的迭代器可以当作尾后值使用，可以在 for 循环中作为终止条件。**
```cpp
istream_iterator<int> iInt(cin);//创建了一个流迭代器 iInt，iInt 从 cin 读取 int
istream_iterator<int> intEof;//尾后迭代器。当关联的流遇到文件尾或遇到错误，迭代器的值就与尾后迭代器相等。
```
- **istream_iterator 操作**
```cpp
in1 == in2; in1 != int2;//首先 in1 和 in2 必须读取相同类型。如果 in1 和 in2 都是尾后迭代器或绑定到相同的输入，则两者相等。
*in;//返回从流中读取的值
++in;in++;//递增操作,使用元素类型所定义的>>运算符从输入流读取下一个值
```
- **istream_iterator 的使用:**
 >用istream从标准输入读取数据,存入vector:
```cpp
istream_iterator<int> inInt(cin),eof;
'1'
while(inInt != eof)
    vec.push_back(*inInt++);
'2'
vector<int> vec(inInt,eof);//和上面效果相同，当遇到文件尾或遇到第一个不是 int 的数据停止。  
```  

 >流迭代器可以用于一部分泛型算法。
```cpp
istream_iterator<int> in(cin),eof;
cout << accumulate(in,eof,0) << endl;
```

- **ostream_iterator 定义**

可以为任何**具有输出运算符的（<<）类型**定义 ostream_iterator，**即所有内置类型和重置了 << 的类**。
```cpp
ostream_iterator<T> out(os);//out 将类型为 T 的值写到输出流 os 中
ostream_iterator<T> out(os,d);//out 将类型为T 的值写到 os 中，在输出每个元素后都会打印d,d为c风格字符串(字符串字面常量或空字符结尾的字符数组的指针)。
```
>不允许空的或表示尾后的ostream_iterator



- ostream_iterator 操作
 ostream_iterator 的赋值操作等价于输出流的输出操作。每赋一次值，输出一次。
```cpp
out = 3val;//等价于 os<<val。将 val 写入到 out 绑定的输出流中。
*out; ++out; out++;//这些运算符存在但没有意义。
```


- **ostream_iterator 的使用**

**输出值的序列:**
```cpp
for(auto e:vec)  out = e;//赋值语句将元素写到 cout，每赋一次值，写操作就会被提交一次。

for(auto e:vec) *out++ = e;//与上面的语句实际效果相同，看起来更清晰。(在这种写法中,流迭代器与其他迭代器的使用保持一致,修改方便)    

//也可以使用 copy 来打印 vec 中的元素，更为简单。
copy(vec.begin(),vec.end(),out);//将 vec 中的元素写入到了 out 绑定的输出流中
```
[t10_29](#t10_29)
[t10_30](#t10_30)
[t10_33](#t10_33)

### 10.4.3 反向迭代器
除了 forward_list 外，其他容器都支持反向迭代器。

反向迭代器支持**递增和递减操作**。注意**流迭代器不支持递减操作**。

- **反向迭代器的颠倒**
**函数 riter.base() 返回相应的正向迭代器，正向迭代器指向靠后一个元素。(反应了左闭合区间的特性)**
```cpp
auto riter = string.rbegin()//反向迭代器 riter 指向 string 的尾元素
auto iter = riter.base();//正向迭代器 iter 指向 string 的尾后元素
```
[t10_34](#t10_34)
[t10_36](#t10_36)
[t10_37](#t10_37)

## 10.5 泛型算法结构
### 10.5.1 5类迭代器
算法所要求的迭代器操作可以分为 5 类，**每个算法都会为它的迭代器参数指明需提供哪类迭代器:**

 1. **输入迭代器**：只读，不写；`单遍扫描，只能递增`。
 
 3. **输出迭代器**：只写，不读；`单遍扫描，只能递增`。

 4. **前向迭代器**：可读写；`多遍扫描，只能递增`。

 5. **双向迭代器**：可读写；`多遍扫描，可递增递减`。

 6. **随机访问迭代器**：可读写，`多遍扫描，支持全部迭代器运算`。

迭代器根据支持的操作的多少分层。**C++ 标准指明了泛型算法的每个迭代器参数的最小类别。**

- **输入迭代器**
输入迭代器只用于顺序访问，只能用于单遍扫描算法，如**算法 find 和 accumulate。**
>Istream_iterator 是一种输入迭代器。
- **输出迭代器**
只能向一个输出迭代器赋值一次，只能用于顺序访问的单遍扫描算法。如 **copy 函数的第三个参数**。
>ostream_iterator 是一种输出迭代器。
- **前向迭代器**
可以读写元素。只能在序列中沿一个方向移动，可以多次读写同一个元素。
**可以保存前向迭代器的状态，使用前向迭代器的算法可以对序列多遍扫描。**
>算法 replace 要求前向迭代器，forward_list 的迭代器是前向迭代器。
- **双向迭代器**
可以正向/反向读写序列中的元素。**支持递增递减运算符**。
>算法 reverse 要求双向迭代器。list 的迭代器是双向迭代器。
- **随机访问迭代器**
提供在**常量时间内访问序列中任意元素**的能力。
   - **支持以下操作**：
      支持 <, <=, >, >= 等关系运算符。
      支持迭代器与整数的加减。
      支持两个迭代器之间的相减。
      支持下标运算符。iter[n] 和 *(iter[n]) 含义相同。
>算法 sort 要求随机访问迭代器。**array, deque, vector, string 的迭代器是随机访问迭代器**。

### 10.5.2 算法形参模式
算法的形参一般是以下 4 种模式之一:
```cpp
alg(beg, end, other args); 

alg(beg, end, dest, other args); 
/* 
如果dest是一个直接指向容器的迭代器,那么算法将输出数据到已存在的元素内(算法假定目标空间足够大);
更常见的情况是,dest 是一个插入迭代器或一个 ostream_iterator，他们都能确保不管写多少元素都肯定是安全的(插入迭代器调用容器操作插入,ostream将数据写入输出流)。
*/

alg(beg, end, beg2, other args);
/*
假定beg2开始的序列和beg与end所表示的范围至少一样大
*/

alg(beg, end, beg2, end2, other args);
```

### 10.5.3 算法命名规范
算法遵循一同命名和重载规范。
- **重载谓词的算法**
一些算法使用重载形式传递一个谓词，来代替 < 或 ==。
```cpp
unique(beg, end);          // 使用 == 比较元素
unique(beg, end, comp);    // 使用 comp 比较元素
```
- **_if 版本的算法**
**接受一个元素值的算法通常有另一个不同名的 _if 版本。**
```cpp
find(beg, end, val);       // 查找范围内 val 第一次出现的版本。
find_if(beg, end, pred);   // 查找第一个令 pred 为真的元素。
```
- **拷贝版本的算法**
默认情况下，**重排元素的算法会将重排后的元素写回给定的输入序列中。拷贝版本则将元素写到一个给定的位置。**
```cpp
reverse(beg, end);             // 反转序列中的元素。
reverse_copy(beg, end, dest);  // 将元素按逆序拷贝到 dest。

remove_if(v1.begin(), v1.end(), [](int i){return i%2;});                         // 从 v1 中删除奇数元素。
remove_copy_if(v1.begin(), v1.end(), back_inserter(v2), [](int i){return i%2;}); // 将去掉了奇数元素的 v1 序列拷到 v2 中。
```


### 10.6 特定容器算法
链表类型 list 和 forward_list 定义了几个成员函数形式的算法。**`它们定义了独有的 sort, merge, remove, reverse 和 unique。`**
>**通用版本的 sort 要求随机访问迭代器，而 list 和 forward_list 分别提供双向迭代器和前向迭代器，因此不能用于 list 和 forward_list。**
>其他链表类型定义的算法的通用版本可以用于链表，但是性能差很多，应该**优先使用成员函数版本**的算法。

- 成员函数版本的算法:
```cpp
lst.merge(lst2);        // 将 lst2 的元素合并入 lst。两者必须都是有序的，合并后 lst2 将变为空。使用 < 比较元素。
lst.merge(lst2,comp);   // 上面的 merge 的重载版本，用给定的 comp 代替 <

lst.remove(val);        // 调用 erase 删除掉与给定值相等的每个元素。
lst.remove_if(pred);    // pred 是个一元谓词，删除掉 lst 中使 pred 为真的每个元素。

lst.reverse();          // 反转 lst 中元素的顺序。

lst.sort();             // 使用 < 给元素排序
lst.sord(comp);         // 重载版本

lst.unique();          // 调用 erase 删除同一个值的连续拷贝。
lst.unique(pred);      // pred 是个二元谓词，删除使 pred 为真的连续拷贝。
```
[t10_42](#t10_42)

- splice算法
>链表类型定义了 splice 算法，此算法是链表特有的，没有通用版本。
**splice 算法用来在两个链表间移动元素或在一个链表中移动元素的位置。**
```cpp
lst.splice(p, lst2); flst.splice_after(p, lst2);              // p 是一个指向 lst 中元素的迭代器，或一个指向 flst 首前位置的迭代器。
        // 函数将 lst2 中的所有元素移动到 lst 中 p 之前的位置或 flst  中 p 之后的位置。
lst.splice(p, lst2, p2); flst.splice_after(p, lst2, p2);      // p2 是一个指向 lst2 中位置的迭代器。
        // 函数将 p2 指向的元素移动到 lst 中，或将 p2 之后的元素移动到 flst 中,lst2 可以是与 lst 或 flst 相同的链表。
lst.splice(p, lst2, b, e); flst.splice_after (p, lst2, b, e); // b 和 e 表示 lst2 中的合法范围。
        // 将给定范围中的元素从 lst2 移动到 lst 中。lst2 可以是与 lst 或 flst 相同的链表，但是 p 不能指向 b 和 e 之间的元素。
```  

### 习题
#### t10_6
>使用fill_n将一个序列中int都设置为0
```cpp
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int main(){
    vector<int> vec{1,2,3,4,5,6,7,8,9};
    fill_n(vec.begin(),vec.size(),0);
    for(auto i: vec) cout << i<<endl;
}
```

#### t10_12
>编写函数比较sales_data对象的isbn()成员,用此函数排序一个vector<sales_data>
```cpp
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
```

#### t10_13
>使用partiton函数划分txtVec,打印长度大于5的元素
```cpp
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
using namespace std;

bool compareStrlen(string str){
    return str.size() > 5;
}

int main(){
    vector<string> words{"Aaa","Bbb","Cccccc","Dddddddd","ABCDEaaa"};
    auto end_greater = partition(words.begin(),words.end(),compareStrlen);
    for(auto i=words.begin();i < end_greater;i++) cout << *i <<endl;//  < 而不是 <= 是因为partition返回最后一个使谓词为true的元素!!!之后!!!的位置(第二组的第一个元素)
    for(auto i=words.begin();i < words.end();i++) cout << *i <<endl;
}
/*
输出:
ABCDEaaa
Dddddddd
Cccccc
说明partition() 函数只会根据筛选条件将数据进行分组，并不关心分组后各个元素具体的存储位置。
partition() 函数分组后   前者中的各个元素都符合筛选条件，而后者则都不符合。
*/
```

#### t10_21
>编写lambda捕获局部int变量,且递减变量值,直至0;一旦变量为0,再调用lambda应该不再递减;返回bool值指出捕获变量是否为0.
```cpp
#include<iostream>
using namespace std;
int main(){
    int i=5;
    auto f =[i]()mutable -> bool {if(i>0){--i;return false;}else return true;};
    for(int j=0;j<6;j++){
        cout <<f()<<" ";
    }
}
```

#### t10_27
>使用unique_copy将vector中不重复的元素拷贝到一个初始为空的list中
```cpp
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

int main(){
    vector<string> sVec{"Aaaa","Bbbb","Bbbb","Dddd","Cccc","Dddd"};
    list<string> slist;
    sort(sVec.begin(),sVec.end());
    unique_copy(sVec.begin(),sVec.end(),back_inserter(slist));//改为 inserter(slist,slist.begin()) 也可
    for(auto iter = slist.begin();iter != slist.end();iter ++) cout << *iter <<" ";
    cout << endl;
}
```

#### t10_29
>流迭代器读取文本文件存入vector
```cpp
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

int main(int argc,char *argv[]){
    ifstream input;
    input.open(argv[1]);
    istream_iterator<string> is(input),eof;
    vector<string> svec;
    while(is != eof){
       svec.push_back(*is++);
    }
    for(auto iter = svec.begin();iter != svec.end();iter ++) cout << *iter <<" ";
    cout << endl;    

}

/*
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> g++ .\t10_29.cpp -o t10_29.exe  
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> .\t10_29.exe infile.txt
003a 1 1 003a 2 8 002a 3 10 002a 3 11 002a 4 18 001a 5 90 001a 6 75 001a 10 100
*/
```

#### t10_30
>使用流迭代器,sort和copy从标准输入中读取一个整数序列,将其排序,并将结果写到标准输出
```cpp
//t10_31 改copy为unique_copy打印不重复元素
#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
using namespace std;

int main(){
    istream_iterator<int> is(cin),eof;
    vector<int> vec;
    while(is != eof){
        vec.push_back(*is++);
    }
    sort(vec.begin(),vec.end());
    ostream_iterator<int> out(cout," ");
    unique_copy(vec.begin(),vec.end(),out);
}
```

#### t10_33
>流迭代器读取文件,根据奇偶输出到两个文件中;奇数每个值后跟空格,偶数每个值独占一行
```cpp
#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

void distinguish_odd_even(string infile,string odd_outfile,string even_outfile){
       ifstream input;
       input.open(infile);
       istream_iterator<int> is(input),eof;
       ofstream odd_out,even_out;
       odd_out.open(odd_outfile);
       even_out.open(even_outfile);
       ostream_iterator<int> odd_iter_out(odd_out," "),even_iter_out(even_out,"\n");
       while(is != eof){
        if(*is & 1){
           odd_iter_out = *is++;
        }
        else{
            even_iter_out = *is++;
        }
       }
}

int main(int argc,char* argv[]){
    distinguish_odd_even(argv[1],argv[2],argv[3]);
}
/*
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> g++ .\t10_33.cpp -o t10_33.exe
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> .\t10_33.exe intfile.txt odd_intfile.txt even_intfile.txt
*/
```

#### t10_34
>reverse_iterator逆序打印一个vector
```cpp
#include<iostream>
#include<vector>
#include<iterator>

using namespace std;
//t10_34 使用reverse_iterator逆序打印vector
//t10_35 用普通迭代器逆序打印vector
int main(){
    vector<int> vec{1,2,3,4,5,6,7,8,9};
    for(auto iter=vec.crbegin();iter!=vec.crend();iter++){
        cout << *iter <<endl;
    }
    for(auto iter=vec.cend();iter!=vec.cbegin();iter--){
        cout << *(iter-1) <<endl;
    }
}
```

#### t10_36
>使用find在一个int的list中查找最后一个值为0的元素
```cpp
#include<algorithm>
#include<list>
#include<iostream>
#include<iterator>

using namespace std;

int main(){
    list<int> li{1,1,1,2,2,2,3,0};
    auto last_z = find(li.rbegin(),li.rend(),0);
    //返回一个输入迭代器，当 find() 函数查找成功时，其指向的是在 [first, last) 区域内查找到的第一个目标元素；如果查找失败，则该迭代器的指向和 last 相同。(若无0此处为首前迭代器)
    //list不连续存储,迭代器不支持算术运算,故用一个循环计数位置
    //程序计数正向位置编号,故last_z需转换为普通迭代器
    if(last_z.base()==li.begin()){
    cerr <<"没有值为0的元素" <<endl;
    return -1;        
    } 
    list<int>::size_type i=0;
    for(auto iter =li.begin();iter != last_z.base();i++,iter++);
    cout <<"最后一个值为0的元素是第"<< i <<"位元素"<<endl;
    
}
```

#### t10_37
>将包含10元素vector的位置3到7之间元素按逆序输出到一个list中
```cpp
#include<algorithm>
#include<list>
#include<vector>
#include<iostream>
#include<iterator>

using namespace std;

int main(){
    vector<int> sum_ten{0,1,2,3,4,5,6,7,8,9};
    list<int> li;
    copy(sum_ten.rbegin()+3,sum_ten.rend()-2,back_inserter(li));
    /*
    也可以通过定义普通迭代器再转换为反向迭代器,更直观展现出迭代器左闭合区间的范围概念
    vector<int>::reverse_iterator re(sum_ten.begin()+2);
    vector<int>::reverse_iterator rb(sum_ten.begin()+7);
    copy(rb,re,back_inserter(li));    
    */

    for(auto i:li) cout << i <<" ";
    cout <<endl;
}
```

#### t10_42
>用list实现elimDups
```cpp
#include<iostream>
#include<list>
#include<algorithm>
#include<string>
using namespace std;

/*
本题要使用链表专用的sort和unique 算法，与泛型算法的不同点有如下两点：

1．它们是以链表类的成员函数形式实现的，因此使用方式是在链表对象上调用它们，也并不需要迭代器参数指出处理的序列。

2．由于是以成员函数形式实现的，是直接操作容器而非通过迭代器访问容器元素，因此这些算法具有修改容器的能力（添加、删除元素）。
例如，unique 会调用erase 直接真正删除重复元素，容器的大小会变小，而不是像泛型 unique 算法那样只是覆盖重复元素，并不改变容器大小。因此程序已不再需要调用erase了。
*/
void elimDups(list<string> &txtList){
    txtList.sort();
    txtList.unique();
}

int main(){
    list<string> txtList{"Eeeeee","Bbbbbb","Aa","Bb","Ccc","Aa","Ddd","Ccc"};
    elimDups(txtList);
    for(auto iter = txtList.begin();iter != txtList.end();iter++) cout << *iter <<" ";
}
```