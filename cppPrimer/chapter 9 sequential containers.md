---
    练习9.4/9.5 迭代器范围
    练习9.14 赋值与swap
    练习9.18/9.19/9.20 向顺序容器添加操作
    练习9.24 访问元素
    练习9.26 删除元素
    练习9.27/9.28 特殊的forward_list操作
    练习9.31/9.34 容器操作可能导致迭代器失效
    练习9.38 vector对象是如何增长的
    练习9.43 9.44/9.45 9.46 改变string方法拓展
    练习9.51 数值转换kv
    练习9.52 容器适配器
---




# 顺序容器

## 问题
1. **`基本的顺序容器有 6 种，分别是什么？哪几种容器算是通用型？存储结构分别是什么？`**

   vector, deque, list, forward_list, string, array。vector, deque, list 算是最通用的通用型。两个 list 是链式结构，其他都是顺序结构

2. **`顺序容器的通用操作有哪些?`**

   **empty(), size(), swap(), clear(), "=", assign()**
   (注意：仅限于顺序容器通用，适配器不行)--------例外：forward_list 不支持 size()

3. **vector 特点是什么，支持哪些操作?**
 vector 支持快速随机访问、在尾部快速插入删除。
 支持: 
 - **front(),back()**
 - push_back(), **pop_back()**
 - capcity()
 - emplace_back(), emplace(p,args)
 - insert(p, t) 

4. **deque 特点是什么，支持哪些操作?**
 deque 支持快速随机访问、在头尾快速插入删除。
 支持:
 - **front(),back()**
 - **push_front(), push_back(), pop_front(), pop_back()**
 - empace_back(), emplace_front(),emplace(p,args)
 - insert(p,t)

5. **list 特点是什么，支持哪些操作?**
 list 支持双向顺序访问，在任何位置插入删除都很快。缺点是额外内存开销很大。
 支持:
 - front(),back()
 - **push_front(), push_back(), pop_front(), pop_back()**
 - empace_back(), emplace_front(),emplace(p,args)
 - insert(p,t)

6. forward_list 特点是什么，支持哪些操作?

 forward_list 支持正向顺序访问，在任何位置插入删除都很快。

7. array 特点是什么，支持哪些操作?

 array 支持快速随机访问，是固定大小数组。

8. string 特点是什么，支持哪些操作?

 string 支持快速随机访问、在尾部快速插入删除。

9. vector, deque, list 应用场景分析:

 一般用 vector，需要头部插入删除用 deque，需要中间插入删除用 list。**元素数量多且单个元素小不用 list**，空间开销很重要不用 list，需要随机访问用 vector,deque。

10. 基本的顺序容器适配器有 3 种，分别是什么？默认底层容器分别是什么？

 queue, priority_queue, stack ，**`queue 和 stack 的底层容器是 deque，priority_queue 的底层容器是 vector`**

11. **适配器有哪些共同特点**？

 适配器不能用底层容器的操作。**适配器不支持迭代器。** clear() 是通过迭代器实现的，因此**适配器都不支持 clear()。**

12. queue 特点是什么，支持哪些操作?

queue：先进先出。支持 front(), back(), push(), pop(), **emplace(args) ；empty(), size(), swap()；**

13. priority_queue 特点是什么，支持哪些操作?

priority_queue：最高优先级出。支持 top(), push(), pop(), emplace(args) ；**empty(), size(), swap()；**

14. stack 特点是什么，支持哪些操作?

stack：先进后出。支持 top(), push(), pop()，**emplace(args) ；empty(), size(), swap()；**

## 问题
1. 所有的迭代器都支持什么操作？

都支持 ++iter，除了 forward_list 都支持 --iter，包括顺序容器和关联容器

2. array 使用时要注意什么？

array 的类型和大小是捆绑的，定义: ` array<int, 10> arr;`

3. swap 操作的特点: 

对于 array 以外的其他容器，swap 只交换数据结构，不交换元素，所以非常快，运行常数时间。对于 array，swap 交换两个容器的元素值

4. max_size 返回值是什么?

返回一个大于等于该容器所能容纳最大元素数量的值

5. **可以向容器添加元素的三类函数分别是什么，分别可以用于哪种情况？**
 push, emplace, insert 三类：
  - ==**push：包括 push_back(), push_front() 两种，单纯的 push() 操作只用于三种顺序容器适配器，一次只能添加一个元素**==
  - emplace：包括 emplace(), emplace_back(), emplace_front() 三种，用参数来构造元素，一次只能添加一个元素
  - insert：包括 insert() 一种，**`传入一个迭代器指明位置，再迭代器前插入，可以添加单个元素、多个相同元素、某迭代器范围内的所有元素，花括号列表`**

6. 如何在一个位置反复插入元素
```cpp
 iter = c.insert(iter, word);
```

7. 访问容器元素的三类操作分别是什么，用于哪种情况？
 - begin(),end() 返回迭代器
 - **front(), back() 返回元素的引用，back() 返回尾元素**
 - **`vec.at()，vec[] ：下标访问法。at() 函数可以检查下标越界。可用于 vector，deque，string，array`**

8. 删除元素的三类操作分别是什么？用于哪种情况？
 - pop 类：包括 pop_front(), pop_back() 两种，都返回 void 。单纯的 pop 操作只用于顺序容器适配器。
 - erase 类：包括 erase() 一种，接受迭代器做参数，可以删除一个元素或一个迭代器范围。**返回删除元素之后的元素的迭代器**
 - clear：清空整个容器。不能用于适配器。

9. **farword_list 有哪些操作？**

 farword_list 的操作有 **`erase_after(iter), insert_after(), emplace_after() 。before_begin() 返回一个首前迭代器。`**

10. 控制容器大小的操作有哪些

resize() ：调整容器大小。reserve()：为vector 和 string 预分配内存；capacity(), shrink_to_fit() 

## 问题
1. 获取 string 对象的子序列的方法

 使用**s.substr(pos,n) 来获取从下标 pos 处开始的长度为 n 的子序列**

2. **`搜索 string 中的字符`**

**string 定义了 6 个相应功能的函数。 find(), rfind(), find_first_of() 等。**

3. 字符串与数值之间进行转换的函数。

to_string() 与 stoi(), stod(), stol 等

## 第九章 顺序容器
### 9.1 顺序容器概述
所有容器都提供**高效的`动态内存`管理**
- **几种顺序容器**
 **vector**：支持快速随机访问。在**尾部**插入/删除速度快。
 **deque**：支持快速随机访问。在**头尾**插入/删除都很快。
 **list**：**`双向链表`**。只支持 **`双向顺序访问`**。在任何位置插入/删除都很快。
 **forward_list**：单项链表。**只支持单向顺序访问**。在任何位置插入/删除都很快。
 **string**：支持快速随机访问。**在`尾部`插入/删除速度快**。
 **array**：**固定大小数组**。支持快速随机访问。

可以发现：vector\deque\string\array 都是**顺序存储结构**。 list 是**链式存储结构**。但是他们都是顺序容器

- list 的`额外内存开销`相比其他大很多。
- array 是一种**`比内置数组更好`**的类型。
- **`farward_list 没有 size 操作`**。这种列表与最好的手写链表性能一样好。
- **新标准库容器的性能至少与同类手写数据结构一样好或更好，`c++ 程序应该使用标准库容器。`**

- 容器选择:
  - **vector/list/deque** 三种容器的比较：
  > 1. **`如果没有特殊的理由，使用 vector 是最好的选择`**
  > 2. 如果**有很多小的元素**，不用 list
  > 3. 如果**空间开销很重要**，不用 list
  > 4. 如果需要在**中间**位置插入/删除，用 list
  > 5. 如果需要在**头尾**位置插入/删除，用 deque
  > 6. 如果需要随机访问，用 vector 或 deque
  > 7. 如果需要在中间位置插入，而后随机访问：
      - *如果可以通过排序解决，就像向**vector尾部追加数据，然后再调用标准库的sort重排元素**,以避免在中间位置添加元素*
      - **在输入阶段用 list ，输入完成后拷贝到 vector 中**

### 9.2 容器库概览
- 通用容器操作
```cpp
 '类型别名'
iterator             // 此容器类型的迭代器类型
const_iterator       // 不能修改元素的迭代器类型
size_type            // 无符号整数类型,足够保存此种容器类型最大可能容器的大小
difference_type      // 带符号整数类型,足够保存两个迭代器之间的距离
value_type           // 容器元素类型。定义方式： vector<int>::value_type
reference            // 元素类型的引用: 与vlaue_type&含义相同 。定义方式： vector<int>::reference
const_reference      // 元素的 const 左值类型

'构造函数'-'三种通用的构造函数：同类拷贝、迭代器范围初始化、列表初始化'
C c1(c2);            // 拷贝构造函数，容器类型与元素类型必须都相同
C c1(c2.begin(),c2.end());   // 要求两种元素类型可以转换即可。
C c1{a,b,c,...};    // 使用初始化列表，容器的大小与初始化列表一样大

C c(n);             // 这两种接受大小参数的初始化方式只有顺序容器能用，且 string 无法使用
C c(n,t);

'赋值与swap'
c1 = c2;
c1 = {a,b,c,....}
a.swap(b);
swap(a, b);         // 两种 swap 等价

'大小'
c.size();
c.max_size();       // c 可以保存的最大元素数目，是整个内存层面的容量，不是已分配内存。不同于 caplity, caplity 只能用于 vector，queue，string
c.empty();

'添加/删除元素（不适用于array）'
c.insert(args);    // 将 args 中的元素拷贝进 c
c.emplace(inits);  // 使用 inits 构造 c 中的一个元素
c.erase(args);     // 删除指定的元素
c.clear();

'关系运算符'
==; !=; <; <=; >; >=   // 所有容器都支持相等和不等运算符。无序关联容器不支持大于小于运算符。

'获取迭代器'
c.begin(); c.end(); 
c.cbegin(); c.cend();  // 返回 const_iterator

'反向容器的额外成员'
reverse_iterator       // 逆序迭代器,按逆序寻址元素的迭代器(这是一个和 iterator 不同的类型)
const_reverse_iterator 
c.rbegin();c.rend();   // 返回指向c的尾元素和首元素之前位置的迭代器
c.crbegin();c.crend();
```

#### 9.2.1 迭代器
 用两个迭代器表示的范围都是 **`左闭合空间`**，即 [begin,end), **如果 begin 和 end 相等，则为空**。
 
 **所有迭代器都可以递增，forward_list 不可以递减**
```cpp
vector<int>::iterator iter = vec.begin();   // 准确定义迭代器的方式。
```
对应练习:
[t4](#t9_4)
[t5](#t9_5)


#### 9.2.3 begin和end 成员
Q:begin 和 cbegin两个函数有什么不同?

cbegin是c++引入用来与auto结合使用,返回const_iterator迭代器而不管容器类型;
begin是重载函数,依赖容器类型是否为const类型而返回对应迭代器.


#### 9.2.4 容器定义和初始化
- **将一个容器初始化为另一个容器的拷贝**
  1. 直接拷贝整个容器(类型及其元素类型必须匹配)
  2. **拷贝由一个迭代器对组成的元素范围`(不要求元素类型相同也不要求容器类型相同,只要能将要拷贝的元素转换为要初始化的容器的元素类型即可)`**
```cpp
vector<const char*> articles = {"a", "an", "the"};
list<string> words(articles.begin(), articles.end());  // 正确， const char* 类型可以转换成 string类型
```

- **array初始化**
 **定义一个array，既需要指定元素类型，也需要==指定大小==**
```cpp
   array<int,42>;              // 定义一个有 42 个 0 的数组
   array<int,42>::size_type  i;   // 定义数组类型也需要包括元素类型和大小
```
   - array的所有元素默认初始化为 0；
   - array 列表初始化时，列表元素个数小于等于 array 大小，剩余元素默认初始化为 0 
   - **array ==只能默认初始化或列表初始化==，如果定义的数组很大并且需要初始化，可以先默认初始化然后用 fill 函数填充值**。
- array赋值
 **==不能对内置数组拷贝或赋值，但是 array 可以==。**
 **使用一个 array 对另一个 array 赋值**，需要两个array 元素类型与大小都相同。
 不能用花括号列表对 array 赋值（==只可以初始化==）

#### 9.2.5 赋值和swap
- **“=”赋值**
  对容器使用赋值运算符（除 array 外），将会使该容器的 **`所有元素`** 被替换。**如果两个容器大小不等，赋值后都与右边容器的原大小相同。**
  **array要求赋值前大小就必须一样。**
- **`assign`**
  assign 是赋值操作，可以用于顺序容器。
  “=” 要求两边类型相同， assign 要求只要**可以转换**即可
  **assian适用于内置数组**
```cpp
 lst.assign(vec.begin(), vec.end()); // 使用迭代器范围赋值
 lst.assign(il);                     // il是一个花括号包围的元素值列表

 lst.assign(n, t);                   // 将 lst 的元素替换为 n 个 t 
 //'操作等价于'
 lst.clear();
 lst.insert(lst.begin(), n, t);
 
 lst.assign(ia, ia+sizeof(ia)/sizeof(ia[0]) ); //数组的总内存空间除以每个数据需要占的内存空间可以获得数组的长度
```
[对应练习: t9_14](#t9_14)
[assign内置数组应用](#t9_26)
- **swap**
   - 对 array ，swap 交换两个 array 中的元素值。**指针、引用和迭代器绑定的元素不变（值变）**。
   - **对于其他容器，`swap 不交换元素，只交换数据结构，因此 swap 操作非常快`。**
   - 对于 string，swap 后，指针、引用和迭代器会失效。**对于其他容器，交换后指针指向了另一个容器的相同位置。**
   - **建议统一使用 swap(a,b)**，而非 a.swap(b)
   - 对于 array，swap 操作的时间与元素数目成正比，**对于其他容器，swap 操作的时间是常数**。


#### 9.2.6 容器大小操作
max_size 返回一个大于或等于该类型容器所能容纳的最大元素数的值。


#### 9.2.7 关系运算符
- 关系运算符左右对象**必须是相同类型的容器.**
- 比较两容器实际上是进行元素的逐对比较
   - **'=' 两容器具有相同大小且所有元素两两对应相等**
   - **'<' 大小不同,较小容器为较大容器前缀子序列**
   - **'>' 若都不为另一方前缀子序列,则大小取决于第一个不相等的元素**
[对应练习: t9_16](#t9_16)

### 9.3 顺序容器操作
#### 9.3.1 添加元素
主要是三类函数：**push、emplace 和 insert。**
注意 **`向 vector、string 或 deque 插入元素会使所有指向容器的迭代器、引用和指针失效`**。
添加的都是元素的拷贝，不是元素本身。
头尾添加返回 void，**中间添加返回指向新添加元素的迭代器**
- **push**
 **vector 和 string** 不支持 push_front 和 emplace_front；
 **forward_list** 不支持 push_back 和 emplace_back；
```cpp
 c.push_back(t);   // 尾部添加一个 t
 c.push_front(t);  // 头部添加一个 t
```
- **emplace(c++11 新标准)**
 push 和 insert 传递的是元素类型的对象，**emplace 则将`参数`传递给元素类型的`构造对象`。**
 即 **emplace参数即为元素类型构造函数的参数**，因此一般可以为空（默认初始化）。
 **emplace 返回值是指向添加元素的迭代器**
```cpp
 c.emplace_back(args);  // 在尾部添加一个由 args 构建的元素
 c.emplace_front(args); // 在头部添加一个由 args 构建的元素
 c.emplace(p,args);     // 在迭代器 p 所指元素 之前 添加一个由 args 构建的元素
```

- **insert**
  **`insert 返回值是指向添加的元素中第一个元素的迭代器`**
  **由于迭代器可能指向容器尾后不存在元素的位置,且在容器开始位置插入元素是很有用的功能,所以insert函数将元素插入到迭代器所指定的位置`之前`**
```cpp
 c.insert(p, t);       // 在迭代器 p 所指元素之前添加一个 t
 c.insert(p, n, t);    // 在迭代器 p 所指元素之前添加 n 个 t
 c.insert(p, b, e);    // 在迭代器 p 所指元素之前添加迭代器范围 [b,e) 中的元素。注意不能是自己的子序列
 c.insert(p, il);      // 在迭代器 p 所指元素之前添加花括号列表
```
- **应用**
  **`在一个位置反复插入元素`**
```cpp
 while(cin>>word)
    iter = lst.insert(iter,word);
```
[对应练习: t9_18](#t9_18)
[对应练习: t9_20](#t9_20)


#### 9.3.2 访问元素
**访问容器应首先确保容器非空**
- **begin/end**
 begin()/end() 返回迭代器
- **front/back**
 front()/back() 返回元素的 **`引用`**
```cpp
 c.front();
 c.back();   //返回的是尾元素的引用（注意不同于尾后迭代器）
```
- **at/下标**
  **可以快速随机访问的容器都可以使用下标**。
  **使用下标一定要保证下标不越界，`可以用 at 函数。当下标越界，at 函数会抛出一个 out_of_range 异常`**
```cpp
 c[n]       //返回下标为 n 的元素的引用
 c.at(n);   //返回下标为 n 的元素的引用
```

- **如果要通过 auto 获得元素的引用，定义时一定要记得加上引用符号**
  理解：c.front() 返回的是引用，**因此可以通过 c.front() = 32; 来给 c 的首元素赋值。而 auto b = c.front() 得到的 b 是等号右端元素的拷贝，不是引用**
```cpp
 auto &v1 = c.back();  // v1 是元素的引用
 auto v2 = c.back();   // v2 是元素的拷贝
```
[对应练习: t9_24](#t9_24)


#### 9.3.3 删除元素
**三类删除操作：pop/ erase/ clear**

头尾删除返回 void，**`特定位置删除返回被删除元素之后元素的迭代器`**

**vector/string 不支持 pop_front，forward_list 不支持 pop_back。**

forward_list 有自己特殊版本的 erase。
```cpp
c.pop_back();   // 注意没有返回值，如果想要需要提前保存
c.pop_front();

c.erase(p);     // 删除迭代器 p 所指元素
c.erase(b, e);  // !!!!! 删除迭代器范围 [b, e) 内的元素 若e本身就是尾后迭代器,则函数也返回尾后迭代器
```
- **删除元素之前应确保元素存在。**
 删除 deque 种除首尾之外的任何元素都会使所有迭代器、引用和指针失效。删除 vector 或 string 中的元素会使指向删除点之后位置的迭代器、引用和指针失效。删除 list 中的元素不会影响指向其他位置的迭代器、引用、指针。

- **删除多个元素**
```cpp
 c.clear();
 c.erase(c.begin(), c.end());  // 和 c.clear() 等价 
```
[对应练习: t9_26](#t9_26)


#### 9.3.4 特殊的forward_list操作
forward_list 是**单向链表**，添加和删除操作都会**同时改变前驱和后继结点**，因此一般的添加和删除都不适用于 forward_list,因此原因,**forward_list中添加删除操作通过改变给定元素`之后的元素`来完成的。**

forward_list 定义了 **首前迭代器** ：**before_begin()** 可以返回首前迭代器，用来删除首元素。
```cpp
lst.insert_after(p,t);     // 在迭代器 p 之后添加一个元素 t；insert_after 与 insert 的差别只在于是插入在元素前还是元素后
lst.insert_after(p,n,t);
lst.insert_after(p,b,e);
lst.insert_after(p,il);

lst.emplace_after(p,args); // 在 p 之后构建新元素。

lst.erase_after(p);        // 删除 p 之后的(一个)元素，注意 p 不能是尾元素和尾后迭代器,否则函数行为未定义。
lst.erase_after(b,e);      // !!!!! 删除迭代器返回 (b,e) 中的元素，注意不包含 b 和 e
```
[对应练习: t9_27](#t9_27)
[对应练习: t9_28](#t9_28)


#### 9.3.5 改变容器大小
**resize() 用来增大或缩小容器。**

如果要求的大小小于当前大小，**尾部会被删除**

如果要求的大小大于当前大小，**会把新元素添加到尾部**
```cpp
list<int> lst(10,42);  // 10 个 42
lst.resize(15);        // 添加 5 个 0 到末尾
lst.resize(25,-1);     // 添加 10 个 -1 到末尾
lst.resize(5);         // 把后面 20 个元素都删除
```


#### 9.3.6 容器操作可能使迭代器失效
==添加和删除元素都可能使指针、引用、迭代器失效。使用失效的指针、引用、迭代器是很严重的错误。==
- **编写改变容器的循环程序**
 必须保证**每次改变容器后都`更新迭代器`**。
   - insert 和 erase 都会返回迭代器，更新很容易。
     **调用 erase 后，`不需要`递增迭代器，调用 insert 后，需要`递增两次`。**
- **`不要保存 end() 返回的迭代器`**
    push、pop、首尾 emplace 操作**都没有返回值，但是都会改变尾后迭代器**，因此不能保存 end() 返回值。
    **（也因此速度会略慢，当不改变容器大小时，采用下标更快）**
[对应练习: t9_31](#t9_31)


### 9.4 vector对象是如何增长的
vector 和 string 是连续存储的，为了避免每增加一个元素就要重新分配一次空间，在每次必须获取新的内存空间时，**通常会分配比新的空间需求更大的内存空间**。容器预留多的空间作为备用。
这种方法在实现时性能恨好，虽然**每次重新分配内存都要移动所有元素**，但是其**扩张操作通常比 list 和 deque 还快**。

- **管理容量**
 **c.capacity(), c.reserve(), c.shrink_to_fit** 都适用于** vector 和 string**，c.shrink_to_fit 还另外适用于 deque。
```cpp
 c.capacity();       // 不重新分配内存空间的话，c 可以保存多少元素。
 c.reserve(n);       // 分配至少能容纳 n 个元素的空间（只预分配内存）
 c.shrink_to_fit();  // 请求将 capacity() 减少为与 size() 相同大小。
```
 c.reserve(n) **不会减小容量，只会增大容量**，当需求容量大于当前容量，才会分配内存，否则什么都不做。
 c.shrink_to_fit() **只是一个请求，实现时标准库可能会不执行**。
- **每次分配新内存空间时具体增加值依赖于标准库实现**
[对应练习: t9_31](#t9_31)


### 9.5 额外的string操作
string 提供了一些额外的操作，主要是用于 **`C风格字符数组`** 和 **`下标访问`** 两方面

#### 9.5.1 构造string的其他方法
##### 构造string的基础方法
**注意：string 不支持在初始化时接受一个数字以指定 string 的大小。**

如果想要指定大小，可以先默认初始化，再**调用 resize() 函数调整大小**。
```cpp
C c1(c2);           
C c1(c2.begin(), c2.end());  
C c1{a, b, c, ...};   
```
##### 构造string的其他方法
- string 的构造函数可以**接受一个 `string 或 const char*` 参数用来指定开始位置，然后接受一个`计数值`用来指定范围。**
- **如果没有传递计数值用来确定范围，拷贝操作遇到空字符停止（因此此时必须要有空字符）**
- 开始位置必须保证是在拷贝对象的范围内，**计数值也没有上限要求**，当计数值指定的范围大于拷贝对象，就**最多拷贝到结尾**。
```cpp
string s(cp, n);          // cp 是一个字符数组，s 是 cp 指向的字符数组前 n 个字符的拷贝。
string s(s2, pos2);       // s2 是一个 string 对象，s 是从 s2 的下标 pos 处开始到最后的字符的拷贝。
string s(s2, pos2, len2); // s 是从 s2 的下标 pos2 处开始的 len2 个字符的拷贝。
```
- **`从vector<char>初始化string`**
```cpp
vector<char> vc;
string s(vc.data(),vc.size());
```

##### substr
**s.substr(pos,n) 返回 s 的一个子序列**，范围由参数指定。
```cpp
string s2 = s1.substr(0,5);  // 返回从下标 0 开始，长度为 5 的子序列
string s2 = s1.substr(6);    // 返回从下标 6 开始到最后的子序列
```
如果 pos 的值超过了 string 的大小，则 substr 函数会抛出一个 out_of_range 异常；若 pos+n 的值超过了 string 的大小，则 substr 会调整 n 的值，只拷贝到 string 的末尾。


#### 9.5.2 改变string的其他方法
string 支持顺序容器的 assign、insert、erase 操作，此外还增加了两个额外的操作
1. **接受下标版本的 insert 和 erase**

3. 接受 C 风格字符数组的 insert 和 assign

5. **append 和 replace 函数**
6. 
##### 接受下标的 insert 和 erase
- insert 和 erase 接受下标的版本**返回的是一个指向 s 的引用**（区别于迭代器版本返回指向第一个插入字符的迭代器）。
- insert 的所有版本都是第**一部分参数为 pos，后面的参数为待插入的字符**
- erase 的所有版本的参数都是 pos，**pos 分为 起始位置 和 终止位置/长度**
```cpp
s.insert(s.size(), 5, '!');       // 在 s 末尾（s[s.size()]之前）插入 5 个感叹号，注意实际上不存在 s[s.size()];
s.insert(0, s2, 3, s2.size()-3);  // 在 s[0] 之前插入 s2 第四个字符开始的 s2.size()-3 个字符
s.erase(s.size()-5, 5);           // 从 s 删除最后 5 个字符
```
##### 接受 C 风格字符数组的 insert 和 assign
**assign 的所有版本的参数都是要赋的值，由 起始位置 + 终止位置/长度 组成**

**replace 的所有版本的参数都是第一部分参数为要删除的范围，第二部分为要插入的字符。**
```cpp
const char* cp = "stately,plump Buck";
s.assign(cp, 7);             // 用从 cp 开始的前 7 个字符向 s 赋值
s.insert(s.size(), cp+7);    // 将从 cp+7 开始到 cp 末尾的字符插入到 s 末尾
```
##### append 和 replace
**append：在 string 末尾进行插入操作的简写形式**

**replace：调用 erase 和 insert 操作的简写形式**
```cpp
s.append(" 4th Ed.");        // 等价于 s.insert(s.size()," 4th Ed.");
s.replace(11, 3, "Fifth");   // 从下标 11 开始，删除三个字符并插入 5 个新字符
```
[对应练习: t9_43](#t9_43)
[*对应练习: t9_44](#t9_44)
[对应练习: t9_45](#t9_45)


#### 9.5.3 string搜索操作
- string 类提供了 **6 个不同的搜索函数**，每个函数有 4 个重载版本。
   - 搜索操作返回 **string::size_type 类型，代表匹配位置的下标**。
   - **搜索失败则返回一个名为 string::npos 的 static 成员，值初始化为 -1**。因为 npos 是一个 unsigned 类型，这个初始值意味着 npos 等于任何 string 最大的可能大小。

注意：find 和 rfind 查找的是给定的整个 args，而剩下的查找的是给定的 args 中包含的任意一个字符。
```cpp
s.find(args);               // 查找 s 中 args 第一次出现的位置
s.rfind(args);              // 查找 s 中 args 最后一次出现的位置
s.find_first_of(args);      // 查找 s 中 args 的任意一个字符第一次出现的位置
s.find_last_of(args);       // 查找 s 中 args 的任意一个字符最后一次出现的位置
s.find_first_not_of(args);  // 查找 s 中第一个不在 args 中的字符
s.find_last_not_of(args);   // 查找 s 中最后一个不在 args 中的字符

'args为以下形式'
c,pos         // 字符，pos 为搜索开始位置
s2,pos       // 字符串
cp,pos       // 以空字符结尾的 c 风格字符串
cp,pos,n     // c 风格字符串的前 n 个字符
```
- **`使用 pos 循环查找所有 str 包含的字符的位置`**
```cpp
string::size_type pos = 0;
while((pos=s.find_first_of(str,pos)) != string::npos ){
    cout << pos << endl;
    ++pos;}
```


#### 9.5.4 compare函数
用于比较两个字符串，**可以是比较整个或一部分字符串**,**`也可以字符串与c风格字符数组比较`** 。

**小于返回负数，大于返回正数，等于返回零**
```cpp
int F = s.compare(s2);
int F = s.compare(pos1,n1,s2);          // 将 s 中 pos1 开始的前 n1 个字符与 s2 比较
int F = s.compare(pos1,n1,s2,pos2,n2);  // 将 s 中 pos1 开始的前 n1 个字符与 s2 中从 pos2 开始的 n2 个字符进行比较
int F = s.compare(cp);                   // 将 s 与 cp 指向的字符数组比较
int F = s.compare(pos1,n1,cp);
int F = s.compare(pos1,n1,cp,n2);
```


#### 9.5.5 数值转换
有多个函数可以实现数值数据与标准库 string 之间的转换

stoi 中要转换的 string 的第一个非空白符必须是**数字或 "+"、"-"、"."**
```cpp
to_string(val);  // 数值转换为字符串

stoi(s, p, b);   // 返回 s 的起始子串的数值。参数 p 用来保存 s 中第一个非数值字符的下标，默认为 0，即不保存下标。参数 b 默认为 10，表示十进制
stol();stoul();stoll();stoull();

stof(s, p);      // 返回 s 的起始子串的数值。
stod();stold();
```
**`例子`**
```cpp
string s2 = "pi = 3.14";
double d = stod(s2.substr(s2.find_first_of("+-.0123456789")));
            // 先使用查询方法找出第一个数值字符，返回下标后截取这一个子串，将子串转换为 double
```
[*对应练习: t9_51](#t9_51)


### 9.6 容器适配器
标准库定义了三个**顺序容器适配器:stack、queue、priority_queue**。
**适配器**是一种机制，是某种事物的行为看起来像另一种事物。
##### 适配器类型
```cpp
size_type;
value_type;
container_type;  // 实现适配器的底层容器类型。
```
##### 初始化操作
默认情况下，**stack 和 queue 是基于 deque** 实现的， **priority_queue 是在 vector 之上实现**的。
因此**可以直接用一个 `deque 来初始化 stack 和 queue`。注意：是直接使用容器对象，不是使用迭代器表示的范围**。
priority_queue 不能使用无序的 vector 初始化。
```cpp
deque<int> deq;
stack<int> sta(deq);  // 用 deq 初始化 sta
```
**如果要使用其他顺序容器实现适配器，要在创建适配器时用一个顺序容器作为第二个类型参数。**
```cpp
stack<int, vector<int>> sta;  // 定义基于 vector 实现的 stack
```
- stack 可以构造于 **vector, list, deque** 之上。
- queue 可以构造于 **list, deque** 之上。
- priority_queue 可以构造于 **vector、deque** 之上。

##### 栈适配器：stack
**stack类型定义在`头文件stack`中**

栈的操作
```cpp
s.pop();
s.push(item);
s.emplace(args);  // 由 args 构造元素并压入栈顶
s.top();
s.size();
s.empty();
swap(s, s2); s.swap(s2);
```
[*对应练习: t9_52](#t9_52)

##### 队列适配器：queue
**queue 和 priority_queue 都定义在`头文件 queue` 中**

队列适配器的操作
```cpp
q.pop();          // 删除 queue 的首元素
q.push(item);     // 在 queue 末尾插入一个元素
q.emplace(args);  // 构造元素

q.front();        // 返回首元素
q.back();         // 返回尾元素。

q.size();
q.empty();
swap(q,q2);q.swap(q2);
```
queue 为先进先出队列。
##### 优先队列：priority_queue
**queue 和 priority_queue 都定义在==头文件 queue== 中**

创建 stack, queue, priority_queue 时都可以用一个顺序容器作为第二个类型参数;

此外创建 priority_quque 时还可以额外传递第三个参数：一个函数对象来决定如何对 priority_queue 中的元素进行排序。

- **大根堆和小根堆**
 priority_queue 默认采用的是 less<Type> ，默认情况下 q.top() 是最大的元素，即大根堆。
```cpp
  priority_queue <int> q;      // 默认采用 vector 作为容器，采用 less<Type> 比较元素，是大根堆
 priority_queue <int, vector<int>, greater<int> > q;  // 采用 greater<Type> 比较元素，生成小根堆
```

其他操作：
```cpp
q.pop();          // 删除 priority_queue 的最高优先级元素
q.push(item);     // 在 priority_queue 适当的位置插入一个元素
q.emplace(args);  // 构造元素
q.top();          // 返回最高优先级元素
q.size();
q.empty();
swap(q, q2); q.swap(q2);
```
- priority_queue 为元素建立优先级。新加入的元素排在所有优先级比它低的元素之前。
- **priority_queue 元素可以重复**
- priority_queue 不能使用无序的 vector 初始化。

## 练习
### t9_4
>编写函数接收一对指向vector<int>的迭代器和一个int值,在两个迭代器范围中查找给定值
```cpp
bool findValue(vector<int>::iterator first,vector<int>::iterator last,int vlaue);
int main(){
     vector<int>list1{1,2,3,4,5,6,7,8,9};
     int num;
     cin >> num;
     cout<< findValue(list1.begin(),list1.end(),num) << endl;
     
}


bool findValue(vector<int>::iterator first,vector<int>::iterator last,int vlaue){
    while(*first != *last){
        if(*first == vlaue)
        return 1;
        first++;
    }
    return 0;
}
```

### t9_5
>同t9_4,返回一个迭代器指向找到的元素,且必须有未找到情况的处理
```cpp
vector<int>::iterator findVlaue(vector<int>::iterator first,vector<int>::iterator last,int vlaue);
int main(){
    vector<int> list1{1,2,3,4,5,6,7,8,9};
    int num;
    cin >> num;
    cout << findVlaue(list1.begin(),list1.end(),num) - list1.begin() <<endl;
    return 0;
}


vector<int>::iterator findVlaue(vector<int>::iterator first,vector<int>::iterator last,int vlaue){
    vector<int>::iterator iter(first);
    while(*first != *last){
        if(*first == vlaue) return first;
        first++;
    }
    return iter;   //搜索失败返回list1.begin(),cout输出零
}
```

### t9_14
>将list中的char*指针元素赋值给一个vector中的string
```cpp
int main(){
    list<char*> list1{"Aaa","Bbb","Ccc"};
    vector<string> vstr1;
    vstr1.assign(list1.begin(),list1.end());
    vector<string>::iterator iter=vstr1.begin();
    while(iter != vstr1.end()){
        cout << *iter <<endl;
        iter++;
    }
    return 0;
}
```

### t9_16
>比较list<int>和vector<int>是否相等
```cpp
bool swap_ListVector(list<int> &list1,vector<int> &vector1){
    if(vector1.size() != list1.size()) return false;
    list<int>::iterator liter =list1.begin();
    vector<int>::iterator viter =vector1.begin();
    while(liter != list1.end()){
        if(*liter != *viter)return false;
        liter++;
        viter++;
    }
    return true;
}
```

### t9_18
>从标准输入读取string序列,存入deque
```cpp
int main(){
    string str1;
    deque<string> deq1;
    auto iter = deq1.begin();
    while(cin >> str1){
       iter=deq1.insert(iter,str1); //类似deq1.push_front(str1)
       iter++; //使其迭代器指向添加的元素之后
       //deq1.push_back(str1); (更简便)
    }
    iter = deq1.begin();
    while (iter != deq1.end())
    {
        cout << *iter << endl;
        iter++;
    }
    return 0;
}
```

### t9_20
>从一个list<int>中按奇偶拷贝其元素到两个deque中
```cpp
int main(){
    list<int> list1{1,2,3,4,5,6,7,8,9,10};
    deque<int> odd_deq,even_deq;
    auto iter =list1.begin();
    while(iter != list1.end()){
       if(*iter%2){
         odd_deq.push_back(*iter);
       }
       else{
         even_deq.push_back(*iter);
       }
       iter++;
    }
    for(auto diter1 = odd_deq.begin();diter1 != odd_deq.end();diter1++){
        cout << *diter1 <<endl;
    }
    for(auto diter2 = even_deq.begin();diter2 != even_deq.end();diter2++){
        cout << *diter2 <<endl;
    }
    return 0;
}
```

### t9_24
>测试分别使用at,下标运算符,front,begin提取一个空vector的第一个元素
```cpp
int main(){
    vector<int> v1;
    cout << v1.at(0) <<endl;
//terminate called after throwing an instance of 'std::out_of_range'
//what():  vector::_M_range_check: __n (which is 0) >= this->size() (which is 0)
    cout<< v1[0] <<endl;
//不抛出异常,程序直接退出
    cout << v1.front() <<endl;
//不抛出异常,程序直接退出
    cout << *v1.begin() <<endl;
//不抛出异常,程序直接退出
    return 0;
}
```

### t9_26
>ia内置数组拷贝到一个vector和list中,使用单迭代器版本的erase删除vector中奇数元素,list中偶数元素
```cpp
int main(){
    int ia[]{0,1,1,2,3,5,8,13,21,55,89};
    vector<int> v1;
    list<int> l1;
    v1.assign(ia,ia+ sizeof(ia)/sizeof(ia[0]) ); //sizeof(ia)：返回数组所占内存空间的字节数
    l1.assign(ia,ia+ sizeof(ia)/sizeof(ia[0]) ); //故: 数组的总内存空间除以每个数据需要占的内存空间可以获得数组的长度
    
    auto viter = v1.begin();
    while(viter != v1.end()){
       if(*viter & 1) viter=v1.erase(viter); //删除值为奇数
       else viter++;
       /*
       if(*viter & 1) v1.erase(viter);
       viter++;
       不能这样改变vector容器大小时迭代器将失效
       */
    }

    auto liter = l1.begin();
    while(liter != l1.end()){
       if(!(*liter & 1)) liter=l1.erase(liter);   //删除值为偶数
       else liter++;
    }


    for(auto iter1 = v1.begin();iter1 != v1.end(); iter1++){
        cout << *iter1 <<" ";
    }
    cout <<endl;
    for(auto iter2 = l1.begin();iter2 != l1.end(); iter2++){
        cout << *iter2 <<" ";
    }
    return 0;
}
```

### t9_27
>查找并删除forward_list<int>中奇数元素
```cpp
int main(){
   forward_list<int> fl1{0,1,2,3,4,5,6,7,8,9};
   auto fiter1 = fl1.before_begin();
   auto fiter2 = fl1.begin();
   while(fiter2 != fl1.end()){
    if(*fiter2 & 1){
     fiter2 = fl1.erase_after(fiter1);//容器元素为奇数时,删除fiter1指向元素的下一位,删除后fiter1不变,fiter2加一
    } 
    else{                             //容器元素不为奇数时,两迭代器加一
     fiter1 = fiter2;
     fiter2++;
    }
   }
    for(auto iter1 = fl1.begin();iter1 != fl1.end(); iter1++){
        cout << *iter1 <<" ";
    }
    return 0;
}
```

### t9_28
> 在 forward_list<string>中查找一个string,并将第二个string插入紧接着第一个之后的位置;若没有查找到,则将第二个string插入到链表末尾
```cpp
void insert_str(forward_list<string>& flstr,const string dropstr,const string insertstr){
   auto fiter1 = flstr.before_begin();
   auto fiter2 = flstr.begin();
   bool inserted= false;
   while(fiter2 != flstr.end()){
    if(*fiter2 == dropstr){
        fiter2 = flstr.insert_after(fiter2,insertstr);
        inserted= true;
    }
    else{
        fiter1 = fiter2;
        fiter2 ++;
    }
    if(!inserted){                //未查找到dropstr,插入末尾
        flstr.insert_after(fiter1,insertstr);
    }
   }
}

int main(){
   forward_list<string> fl1{"Aaaa","Bbbb","Aaaa","Cccc"};
   string str1{"Aaaa"};
   string str2{"Dddd"};
   insert_str(fl1,str1,str2);
    for(auto iter1 = fl1.begin();iter1 != fl1.end(); iter1++){
        cout << *iter1 <<" ";
    }
    return 0;
}
//PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U9> cd "c:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U9\" ; if ($?) { g++ t9_28.cpp -o C:/Users/cormorant/Desktop/v/C/cpp/cppexe/t9_28 } ; if ($?) { C:/Users/cormorant/Desktop/v/C/cpp/cppexe/t9_28 }
//Aaaa Dddd Bbbb Aaaa Dddd Cccc 
```

### t9_31
>删除偶数值元素复制奇数值元素list/forward_list
- list/forward_list迭代器不支持加减运算(链表元素并非在内存中连续存储),应多次调用迭代器自增实现iter+=2;效果
- list
```cpp
int main(){
    list<int> l1{0,1,2,3,4,5,6,7,8,9};
    auto iter = l1.begin();
    while(iter != l1.end()){
        if(*iter & 1){
            iter = l1.insert(iter,*iter);
            iter ++;
            iter ++;
        }
        else{
            iter = l1.erase(iter);
        }
    }
     for(auto iter1 = l1.begin();iter1 != l1.end(); iter1++){
        cout << *iter1 <<" ";
    }
}
```
- forward_list
```cpp
int main(){
    forward_list<int> l1{0,1,2,3,4,5,6,7,8,9};
    auto iter = l1.begin();
    auto biter= l1.before_begin();
    while(iter != l1.end()){
        if(*iter & 1){
            iter = l1.insert_after(iter,*iter);//返回新插入元素的迭代器
            biter=iter;
            iter++;
        }
        else{
            iter = l1.erase_after(biter);
        }
    }
     for(auto iter1 = l1.begin();iter1 != l1.end(); iter1++){
        cout << *iter1 <<" ";
    }
}
```

### t9_38
>探究vector增长策略
```cpp
int main(){
    vector<int> ivec;
    for(vector<int>::size_type i =0; i!= 24;++i)
    ivec.push_back(i);
    while(ivec.size() != ivec.capacity()){
        ivec.push_back(0);
    }
    ivec.push_back(0);
    cout << ivec.size() <<endl;
    cout << ivec.capacity() <<endl;
}
/*
33
64
在本机标准库中vector分配新内存空间时将当前容量翻倍
*/
```

### t9_43
>编写函数,接收三个string参数,s,oldval,newval,将s中所有oldval替换成newval; 本题使用迭代器以及insert和erase函数.
```cpp
void replace_word (string &s,const string &oldval,const string &newval){
    if(! oldval.size()) return;
    if(s.size()<oldval.size()) return;
    auto iter =s.begin();
    while(iter!=s.end()){    
        if(*iter == *oldval.begin()){
            auto siter =iter;
            auto olditer = oldval.begin();
            while(*siter==*olditer && olditer!=oldval.end()){
                siter++;
                olditer++;
            }
            if(olditer == oldval.end()){
              iter= s.erase(iter,siter);
              auto newiter = newval.end();
              while(newiter !=newval.begin()){
              iter = s.insert(iter,*(--newiter));
            }
        }
    }
        iter++;
  }

}
```

### t9_44
>编写函数,接收三个string参数,s,oldval,newval,将s中所有oldval替换成newval; 本题使用一个下标和replace.
```cpp
void replace_word (string &s,const string &oldval,const string &newval){
    if(! oldval.size()) return;
    if(s.size()<oldval.size()) return;
    string::size_type pos =0;
    while ((pos = s.find(oldval,pos)) != string::npos)
    {
        s.replace(pos,oldval.size(),newval); 
        //replace(range,args)中range是一个下标和一个长度而不是起始和结束下标值
        //++pos;   错误: 当newval中包含oldval时可能造成重复循环添加
        pos += newval.size();    
    }
    

}

int main(){
    string s="tho thru tho!";
    replace_word(s,"thru","through");
    cout << s << endl;
    replace_word(s,"tho","though");
    cout << s << endl;
    replace_word(s,"through"," ");
    cout << s << endl;
}
/*
tho through tho!
though through though!
though   though!
*/
```

### t9_45
>编写函数,接收三个string参数,s,prefix,suffix,给s添加前后缀;
```cpp
void  name_string(string& s,const string& prefix,const string& suffix){
    string::size_type pos =0 ;
    //s.append(suffix);
    s.insert(s.size(),suffix);
    s.insert(pos,prefix);
}

int main(){
    string s="James Bond";
    name_string(s,"Mr. "," II");
    cout << s <<endl;
    return 0;

}
```

### t9_51
>设计类,有三个unsigned成员为年月日;为其编写构造函数使其支持不同数据格式,包括 January,1,1900 ; 1/1/1999 ; Jan 1 1990 等
**t9_51_date.h**
```cpp
#ifndef T9_51_DATE_H
#define T9_51_DATE_H
/*
一月-- --January -- --Jan.
二月-- --February -- --Feb.
三月-- --March -- --Mar.
四月-- --April -- --Apr.
五月-- --May -- --May.
六月-- --June -- --Jun.
七月-- --July -- --Jul.
八月-- --August -- --Aug.
九月-- --September -- --Sept.
十月-- --October -- --Oct.
十一月-- --November -- --Nov.
十二月-- --December -- --Dec. 
*/
#include<string>
#include<iostream>
using namespace std;

const string month_name[]={"January","February","March","April","May","June","July","August","September","October","November","December","dec"};
const string month_abbr[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};


class t9_51_date {
    friend ostream& operator<<(ostream&,const t9_51_date&);
    public:
    t9_51_date()=default;
    t9_51_date(string &s){
        bool bitem = false;
        string::size_type i;
        string::size_type j;
            for(i=0;i<12;i++){                         //月份简写匹配
                for( j=0;j < month_abbr[i].size();j++)
                    if(s[j] != month_abbr[i][j])
                    break;
                if(j == month_abbr[i].size()){
                    bitem = true;
                    month = i+1;
                }
                
            }
            for(i=0;i<12;i++){                         //月份名称匹配
                for( j=0;j < month_name[i].size();j++)
                    if(s[j] != month_name[i][j])
                    break;
                if(j == month_name[i].size()){
                    bitem = true;
                    month = i+1;
                }
            }    

        if(bitem){     //!!!通过多次查找并获得子序列从而将输入中的非数字字符排除以得到正确的数字子字符串并转换
            s=s.substr(s.find_first_of("0123456789"));
            string sday=s.substr(0,s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_of("0123456789"));
            string syear=s;
            day=stoi(sday);
            year=stoi(syear);
        }
        else{
            string sday =s.substr(0,s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_of("0123456789"));
            string smonth=s.substr(0,s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_of("0123456789"));
            string syear=s;
            day=stoi(sday);
            month=stoi(smonth);
            year=stoi(syear);
        }

    }
    unsigned y () const {return year; }
    unsigned m () const {return month; }
    unsigned d () const {return day; }

    private:
    unsigned year=0;
    unsigned month=0;
    unsigned day=0;
};

ostream& operator<<(ostream& out,const t9_51_date& d){
    out << d.y() << "年" << d.m() << "月" << d.d() << "日" << endl;
    return out;
}
#endif
```
**t9_51_main.cpp**
```cpp
#include<iostream>
#include<string>
#include"t9_51_date.h"

using namespace std;

int main(){
    string dates[]={"Jan 1,2022","February/1/2022","29/1/2022","30*1   2021","Feb*1*1999"};
    for(auto s :dates){
        t9_51_date d1(s);
        cout << d1;
    }
}
/*
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U9> cd "c:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U9\" ; if ($?) { g++ t9_51_main.cpp -o C:/Users/cormorant/Desktop/v/C/cpp/cppexe/t9_51_main } ; ippexe/t9_51_main } ; if ($?) { C:/Users/cormorant/Desktop/v/C/cpp/cppexe/t9_51_main }
2022年1月1日
2022年2月1日
2022年1月29日
2021年1月30日
1999年2月1日
*/
```
    
### t9_52
>使用stack 处理括号化的表达式。当你看到一个左括号，将其记录下来。当你在一个左括号之后看到一个右括号，从stack中pop对象，直至遇到左括号，将左括号也一起弹出栈。然后将一个值（括号内的运算结果）push 到栈中，表示一个括号化的（子）表达式已经处理完毕，被其运算结果所替代。

```cpp
    
//设运算符只有加减法和括号以减少优先级处理的步骤
#include<iostream>
#include<deque>
#include<stack>
#include<string>
using namespace std;

enum obj_type{LP,RP,ADD,SUB,VAL};
struct obj
{
   obj(obj_type type,double value=0){t=type;v=value;} 
   obj_type t;
   double   v; 
};

inline void skipws(string& s,string::size_type& p){
   p = s.find_first_not_of(" ",p);
}

inline void new_val(stack<obj> &so,double v){
//a）若栈空或栈顶是左括号，则v是第一个运算数，直接压栈即可。
//b）否则，v前必须是一个运算符，再之前是另一个运算数v，从栈顶弹出这两项，将计算结果压栈即可；否则，就抛出一个“缺少运算符”异常。
   if( so.empty() || so.top().t == LP){          //空栈或左括号 !!!判断空栈必须在前否则向空栈运行so.top().t == LP语句会导致程序异常退出且不报错!!! 
      so.push(obj(VAL,v));
      cout << "push " << v <<endl;
   }
   else if(so.top().t == ADD|| so.top().t == SUB){
      obj_type type = so.top().t;
      so.pop();
      //if(so.top().t != VAL)throw  多余;运算符前是否是运算数 的判断应该交给运算符入栈时代码段
      if(type == ADD){
        cout << "pop +" <<endl;
        cout << "pop " <<so.top().v <<endl;
        v +=so.top().v;
        so.pop();
        so.push(obj(VAL,v)); 
        cout << "push "<< v <<endl;
      }
      else{
        cout << "pop -" <<endl;
        cout << "pop " <<so.top().v <<endl;
        v =so.top().v - v;
        so.pop();
        so.push(obj(VAL,v)); 
        cout << "push "<< v <<endl;
      }
   }
   else{
      throw invalid_argument("缺少运算符");
   }
}

int main(){
/*
1．读入了一个运算数v。
a）若栈空或栈顶是左括号，则v是第一个运算数，直接压栈即可。
b）否则，v前必须是一个运算符，再之前是另一个运算数v＇，从栈顶弹出这两项，将计算结果压栈即可；否则，就抛出一个“缺少运算符”异常。

2．读入了一个左括号，直接压栈。

3．读入了一个运算符，
a）若栈空或栈顶不是一个运算数，则抛出一个“缺少运算数”异常。注意，若运算符之前是一个右括号，之前也已处理完毕，栈顶是其计算结果，仍应该是运算数，不影响此逻辑。
b）否则，运算符压栈。

4．读入了一个右括号，
a）若栈空，表明之前没有与之配对的左括号，抛出“未匹配右括号”异常。
b）若栈顶是左括号，表明括号对之间无表达式，抛出“空括号”异常。
c）若栈顶不是运算数，表明括号内缺少一个运算数，抛出一个异常。
d）**弹出此运算数 v，若栈空或栈顶不是左括号，仍抛出“未匹配右括号”异常：否则弹出左括号，把v作为新运算数，执行1中的逻辑**
(边输入边计算,所以输入右括号时若无异常括号内运算已结束,栈顶只剩一个运算数)。

5．以上均不是，则出现了非法输入，会在转换为数值时产生异常。

6．当字符串处理完毕后，判断栈中是否有且仅有一个运算数，若是，此值即为表达式运算结果，输出它；否则，表达式非法。

**值得注意的是，为了在栈中保存括号、运算符和运算数三类对象，程序中定义了枚举类型obj＿type。栈中每个对象都保存了类型t和数值v**（如果t是VAL的话）。
*/
stack<obj> so;
string exp;
string::size_type p=0;
string::size_type q;
double v;

cout << "请输入表达式:  ";
getline(cin,exp);

while (p < exp.size())
{   
    skipws(exp, p);
    if(exp[p] == '('){
        so.push(obj(LP));
        cout << "push (" <<endl;
        p++;
    }
    else if(exp[p] == '+'||exp[p] == '-'){
        if(so.top().t !=VAL || so.empty()){ //空栈或之前不是运算数
            throw invalid_argument("缺少运算数");
        }

        if(exp[p] == '+'){
            so.push(obj(ADD));
            cout << "push +" <<endl;
            p++;
        }else{
            so.push(obj(SUB));
            cout << "push -" <<endl;
            p++;
        }

    }
    else if(exp[p] == ')'){
        p++;
        if(so.empty()){
            throw invalid_argument("未配对右括号");
        }
        if(so.top().t == LP){
            throw invalid_argument("空括号");
        }
        if(so.top().t != VAL ){
            throw invalid_argument("缺少运算数");
        }
        v = so.top().v;
        so.pop();
        cout << "pop "<< v <<endl;
        if(so.top().t != LP|| so.empty()){
            throw invalid_argument("未配对右括号");
        }
        so.pop();
        cout << "pop (" <<endl;
        //so.push(obj(VAL,v)); 可能有其他错误
        new_val(so,v);
    }
    else{
        v = stod(exp.substr(p),&q);//返回 子串 的起始子串的数值。参数 p 用来保存 从下标p开始的子串 中第一个非数值字符的下标，默认为 0，即不保存下标。
        p += q; 
        new_val(so,v);
    }
}
    //字符串处理完毕后，判断栈中是否有且仅有一个运算数，若是，此值即为表达式运算结果，输出它；否则，表达式非法。
    if(so.empty() || so.size()!= 1 || so.top().t != VAL){
        throw invalid_argument("表达式非法");
    }
    cout << "表达式结果: " << so.top().v <<endl;
    return 0;
}
```
