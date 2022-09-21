# 第11章 关联容器
- 关联容器中的元素**按关键字**来保存和访问，顺序容器中的元素按他们**在容器中的位置**来保存和访问
- 关联容器包括 map 和 set 。
>**map 和 multimap 在头文件 map 中，set 和 multiset 在头文件 set 中，无序 map 和无序 set 分别在头文件 unordered_map 和 unordered_set 中。**
```cpp
'按关键字有序保存元素'
map;//保存关键字-值对
set;//关键字就是值，只保存关键字
multimap;//关键字可重复出现的map
multiset;//关键字可重复出现的set
'无序集合'
unordered_map;//无序map
unordered_set;//无序set
unordered_multimap;//哈希组织的 map，关键字可重复出现
unordered_multiset;//哈希组织的 set，关键字可重复出现
```

## Q&A
1. 关联容器删除元素有哪些方法？
  
  使用 s.erase 删除元素，erase 除了接受迭代器为参数（返回void，不同于顺序容器）外，**也可以直接接受关键值作为参数（返回删除的元素数量）**。

2. 关联容器添加元素有哪些方法？

 可以使用 insert 函数和 emplace 函数，map 还可以直接通过索引添加。

3. 关联容器定义了哪些类型别名？

 迭代器类型、value_type、reference、const_reference、key_type、mapped_type（只用于 map）

4. 如何使用 decltype 获取函数指针类型
  ```cpp
  后面加上 * 运算符：decltype(comp)* 
  ```

5. pair 的默认构造函数对数据成员进行什么初始化

 值初始化

6. 可以使用花括号列表来对 pair 初始化吗
   
  可以，比如 pair<string,int> p = {"LiLin",17};

7. 定义一个 pair 类型对象的方式
   
  直接定义和使用 makr_pair 两种方法

8. set 的元素可以改变值吗
   
  **不可以，set 的元素即是关键字又是值**。理解：改变关键字实际上就相当于变为了另一个元素，所以不能改变。

9. insert 有哪些应用方式
    
  两种基础应用**是可以直接接受一个元素值或接受一个迭代器范围**
  >注意：添加单一元素的 insert 返回的是一个 pair，这个很有用。其他 insert 都返回 void

10. 循环删除 map 中元素的方式。
    
  **循环内删除时使用 m.erase(iter++)**。
  - **map: erase 迭代器只使被删元素的迭代器失效，但是返回值为 void，所以要采用 erase(iter++) 的方式删除迭代器**
  - **vector: erase 迭代器不仅使所指向被删元素的迭代器失效，而且使被删元素之后的所有迭代器失效，所以不能使用 erase(iter++) 的方式，但是 erase 的返回值为下一个有效的迭代器**

11. map 访问元素的方式？set 访问元素的方式？
    
  map 可以使用**下标和 at() **函数访问元素，注意两者在遇到不包含元素时的不同处理。**set 可以使用 at() 函数访问元素，不能使用下标。**

12. map 和 set 查找元素的方式
    
  可以使用 find 和 count 查找元素，此外还有 lower_bound, upper_bound, equal_range 三个查找大于某个值或等于某个值的元素的方式。

13. **在 multimap 和 multiset 中查找元素的方法**
 比较麻烦，有三种方法：
  - 直接使用 equal_range
  - 使用 find 和 count 配合
  - 使用 lower_bound 和 upper_bound 配合。

14. 无序容器如何使用

  默认情况下，无序容器的关键字只能是内置类型、string、智能指针。无序容器也可以使用 find、insert、迭代器。无序容器还有一些桶相关的操作。 


## 11.1 使用关联容器
- 使用 map
 **map 可以使用范围 for 循环**
 map 的一个经典应用是单词计数程序
```cpp
while(cin>>word)
    ++word_count[word];
```
- 使用 set
 set 也可以使用范围 for 循环。


## 11.2 关联容器概述
**所有的有序、无序关联容器**都支持下面这些通用操作。

关联容器**不支持顺序容器的位置相关的操作**，关联容器中的元素是根据关键字存储的。

**关联容器的迭代器都是`双向`的。**
```cpp
'类型别名'
iterator
const_iterator
value_type //容器元素类型。定义方式： vector<int>::value_type
reference //元素类型的引用。定义方式： vector<int>::reference
const_reference //元素的 const 左值类型

'构造函数'-'三种通用的构造函数：同类拷贝、迭代器范围初始化、列表初始化'
C c1;                          // 默认构造函数，构造空容器。
C c1 (c2);                    // 拷贝构造函数，容器类型与元素类型必须都相同
C c1 (c2.begin(), c2.end());  // 要求两种元素类型可以转换即可。
C c1 {a, b, c, ...};          // 使用初始化列表，容器的大小与初始化列表一样大
        // 只有顺序容器的构造函数可以接受大小参数，关联容器不行。

'赋值与swap'
c1 = c2;
c1 = {a,b,c,....}
a.swap(b);
swap(a,b);//两种 swap 等价

'大小'
c.size();
c.max_size();//c 可以保存的最大元素数目，是整个内存层面的容量，不是已分配内存。不同于 caplity, caplity 只能用于 vector，queue，string
c.empty();

'添加/删除元素（不适用于array）'
c.insert(args); //将 args 中的元素拷贝进 c，args 是一个迭代器或迭代器范围
c.emplace(inits);//使用 inits 构造 c 中的一个元素
c.erase(args);//删除指定的元素，args 是一个迭代器或迭代器范围
c.clear();

'关系运算符'
==; !=; <; <=; >; >=  //所有容器都支持相等和不等运算符。无序关联容易不支持大于小于运算符。

'获取迭代器'
c.begin(); c.end(); 
c.cbegin(); c.cend(); //返回 const_iterator

'反向容器的额外成员'
reverse_iterator //逆序迭代器，这是一个和 iterator 不同的类型
const_reverse_iterator 
c.rbegin();c.rend();
c.crbegin();c.crend();
```
>**上面是关联容器和顺序容器的通用操作，下面是关联容器的额外操作**
```cpp
'类型别名'
key_type //关键字类型
mapped_type //每个关联的类型，只适用于 map
value_type //对于 set，与 key_type 相同，对于 map，为 pair<const key_type,mapped_type>
```

### 11.2.1 定义关联容器
只有顺序容器的构造函数可以接受大小参数，关联容器不行。

关联容器的初始化可以使用直接初始化（使用小括号）、列表初始化（使用花括号）、拷贝初始化（使用等号）。

使用迭代器范围进行直接初始化时，**如果迭代器范围中有重复关键字，生成的 set 和 map 会`自动去除重复的元素`**。

- **值初始化**
 >除了三种构造函数外，关联容器可以进行值初始化。初始化器必须能转换为容器中元素的类型。
```cpp
set<string> ss = {"the","and"};
map<string, string> sm = { {"LiLin","男"},{"HeFan","男"} };
```
 **初始化 map 时，将关键字-值对包括在一个花括号中 {key, value} 就可以构成 map 的一个元素。**

- 初始化 multiset 和 multimap
  
 使用迭代器范围进行直接初始化时，无论有没有重复关键字，都会生成包含所有元素的 multiset 和 multimap。

[t11_3](#t11_3)
[t11_7](#t11_7)

### 11.2.2 关键字类型的要求
- **有序容器的关键字类型**
有序容器的关键字类型**必须定义元素比较的方法**，标准库**默认使用 < 来比较**关键字。可以使用如 vector 等容器的迭代器来作为有序容器的关键字。

>**重载了 < 运算符的类可以直接用作关键字。**
 可以向算法提供一个**自己定义的比较操作**，操作必须在关键字类型上定义一个**严格弱序**，类似小于等于但不一样：
  - 两个关键字不能同时”小于等于“对方。
  - 该操作有传递性。
  - 如果两个关键字互不”小于等于“对方，那么两个就是等价的。容器将它们看做相等。
 当两个关键字是等价的，map 只能存储一个，但是也可以通过另一个关键字来访问值。

- **使用关键字类型的比较函数**
**当自己定义了比较操作，必须在定义关联容器时指出来，自定义的操作类型（`函数指针类`型）应在尖括号中紧跟元素类型给出。并将`函数名`作为参数传递给构造函数。**

比较函数应该返回 bool 值，两个参数的类型应该都是容器的关键字类型。当第一个参数小于第二个参数时返回真。
```cpp
'比较函数的定义方式'
bool comp(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

'定义容器对象'
multiset<Sales_data,decltype(comp)*> bookstore(comp);
'不用decltype重新定义bookstore'
//首先用typedef定义与comp相容的函数指针类型,然后用此类型声明multiset
typedef bool (*pf)(const Sale_data &, const Sales_data &);
multiset<Sales_data,pf> bookstore(comp);
'bookstore迭代器类型'
//t11_19
multiset<Sales_data,pf>::iterator it = bookstore.begin();
```
>这表示当我们向bookstore添加元素时,通过调用comp来为元素排序
>可以**用comp代替&comp作为构造函数的参数**,因为当我们使用一个 函数的名字时,需要的情况下它会自动转化为一个指针
>**注意当使用 decltype 获取函数指针时要加上 * 运算符。**


- **map<list<int>::iterator,int>m2; 错误,因为list元素不是连续存储,其迭代器不支持比较操作**
  
[t11_9](#t11_9)

### 11.2.3 pair类型
**pair 类型`定义在头文件 utility`中。**

pair 也是一个模板。

- **pair 定义**
pair 的默认构造函数对数据成员进行**值初始化**，因此 string，vector 等类型会默认为空，int 会默认为 0。
```cpp
'直接定义'
pair<string, int> p;//默认初始化
pair<string, int> p(str, i);
pair<string, int> p{"LiLin", 17};
pair<string, int> p = {"LiLin", 17};

'使用 make_pair'
auto p = make_pari(v1, v2);//pair 的类型根据 v1 和 v2 的类型推断。
pair 操作
p.first  //返回 p 的第一个成员
p.second //返回 p 的第二个成员
p1 < p2;   //当 p1.first < p2.first && p1.second < p2.second 时为真。
p1<=p2; p1>p2; p1>=p2;
p1 == p2;//当 first 和 second 成员都相等时，两个 pair 相等。
p1 != p2;
```

- 创建 pair 类型的返回值

如果一个函数返回一个 pair，可以对返回值进行列表初始化或隐式构造返回值
```cpp
pair<string,int> process(bool a){
    if(a) 
        return {"LiLin",17};//列表初始化
    else 
        return pair<string,int>();//隐式构造返回值
}
```
[t11_12](#t11_12)
[t11_14](#t11_14)

## 11.3 关联容器操作
>关联容器除了上面列出的类型别名，还有如下三种
```cpp
'类型别名'
key_type //关键字类型
mapped_type //每个关联的类型，只适用于 map
value_type //对于 set，与 key_type 相同，对于 map，为 pair<const key_type,mapped_type>
```
注意 set 的 key_type 类型不是常量，pair 的 first 成员也不是常量，只有 map 的 value_type 中的 first 成员是常量。

###  11.3.1 关联容器迭代器
解引用关联容器迭代器得到的是 value_type 的引用。
- set 的迭代器

  - **set 的关键值`与 map 的关键值一样`，都是不能改变的。**
  - **可以用 set 的迭代器读取元素值，但不能修改。**

- 遍历关联容器
  
  - map和set都支持begin,end操作,可以类似vector遍历容器
  - **使用一个迭代器遍历map,multimap,set,multiset时,迭代器按关键字升序遍历元素**

- 关联容器和算法
  - 关键字是const意味着不能将关联容器传递给修改或重排容器元素的算法
  - 当对关联容器使用泛型算法时，一般要么把它作为源序列，要么把它作为目的序列。比如从关联容器拷贝元素，向关联容器插入元素等。

>假定c是一个string的multiset，v是一个string的vector， 解释下面的调用。指出每个调用是否合法：
```cpp
copy(v.begin(),v.end(), inserter(c, c.end())); 
copy(v.begin(), v.end(), back_inserter(c)); 
copy(c.begin(), c.end(), inserter(v, v.end())); 
copy(c.begin(), c.end(),back_inserter(v)); 
```
 **set的迭代器是const的，因此只允许访问set中的元素，而不能改变set**。 

 **与map一样，set的关键字也是const，因此也不能通过迭代器来改变 set 中元素的值**。

 因此，前两个调用试图将中的元素复制到set中，是非法的。而后两个调用将set中的元素复制到vector中，是合法的。 
 
[t11_16](#t11_16)

### 11.3.2 添加元素
插入容器中**已存在的元素对 map 和 set 没有影响**。

- **使用 insert 添加元素`(两个版本,分别接收一对迭代器,或是一对初始化器列表)`**
 关联容器添加元素一般使用 insert 成员，可以添加一个元素也可以添加一个元素范围，或者初始化列表。
 ```cpp
set<int> s;
s.insert(10);                     // 插入一个元素（s中没有关键字时才插入）。返回一个pair，pair包含一个迭代器指向具有指定关键字的元素，和一个表明是否插入成功的 bool 值
s.insert(vec.begin(), vec.end();  // 插入迭代器范围(表示一个s::value_type类型值的范围)。返回 void
s.insert({1, 2, 3});              // 插入初始化列表。返回 void
s.insert(iter, 10);               // 类似于 insert(10),iter 是一个迭代器，提示从哪里开始搜索新元素应该存储的位置。返回一个迭代器，指向具有制定关键字的元素。
```
- **向 map 添加临时构造的元素**
 >插入的元素类型是pair
```cpp
map<string, int> m;
'四种方法'
m.insert({str, 1});                    //最简单的方法，直接使用花括号
m.insert(make_pair(str, 1));
m.insert(pair<string, int>(str, 1));   //pair 类型直接定义
m.insert(map<string, int>::value_type(str, 1));
```
- 使用 emplace 添加元素
 >对于map和set,只有当元素的关键字不在s中时才插入(或构造)元素.
```cpp
s.emplace(args);//args用来构造一个元素，其他和 s.insert(10) 相同
s.emplace(iter, args);//除了 args 其他和 s.insert(iter, 10) 相同
```
- 检测 insert 的返回值
>注意 insert 返回的值不是固定的，**依赖于容器类型和参数**
  - **对于不重复的map和set，添加的单一元素的 insert 和 emplace 都返回一个 pair，`pair中first元素是具有给定关键字的元素的迭代器,second元素是一个 bool 值(指出插入成功还是元素已存在)`**
  - 对于不重复的map和set，添加多个元素返回 void,插入单个元素的 insert 返回一个指向新元素的迭代器。
  - 在向 map 或 set 添加元素时，检测 insert 的返回值可以很有用，要灵活使用。
```cpp
while(cin>>word){
    auto ret = word_count.insert({word,1});
    if(ret.second = false)
        ++ret.first->second; //递增计数器 等同与++((ret.first)->second)
}
```
- 向 multiset 或 multimap 添加元素
>在 multiset 或 multimap 上调用 insert 总会插入元素。
>**插入单个元素的 insert 返回一个指向新元素的迭代器。**

[t11_16](#t11_16)
[t11_31](#t11_31)


###  11.3.3 删除元素
关联容器定义了**一个额外版本的 erase** 和两个**与顺序容器相似**版本的 erase

1. **额外版本：输入参数为`关键字`**（注意不是关键字的迭代器），返回删除的元素数量，对于非重复关键字的容器，返回值总是 1 或 0。
   
2. **与顺序容器相似版本：注意顺序容器会返回删除元素后一个元素的迭代器，而这里的 erase 返回 void**
```cpp
'与顺序容器相似版本的 erase'
s.erase(iter);          // 删除一个元素，返回 void
s.erase(iter1, iter2)   // 删除一个范围，返回 void
'额外版本'
auto cnt = s.erase("LiLin");//
```
- **删除关联容器的最后一个元素**
```cpp
m.erase(--m.end());   // 正确！m 的迭代器支持自增与自减
m.erase(m.rbegin());  // 错误！
```
- **遍历容器删除元素**

注意 map 和 vector 的不同

  - **map: erase 迭代器只使被删元素的迭代器失效，但是返回值为 void，所以要采用 erase(iter++) 的方式删除迭代器**
  - **vector: erase 迭代器不仅使所指向被删元素的迭代器失效，而且使被删元素之后的所有迭代器失效，所以不能使用 erase(iter++) 的方式，但是 erase 的返回值为下一个有效的迭代器**
```cpp
'map'
map<int, int> m;
for(auto iter = m.begin(); iter != m.end(); ){
    if(iter->second == 0)
        m.erase(iter++); //这是循环map删除指定元素的唯一方式。利用了 i++ 的原理
    else
        iter++;    
}
'vector'
vector<int> v;
for(auto iter = v.begin(); iter != v.end(); ){
    if(*iter == 0)
        iter = v.erase(iter);//vecotr 的 erase 操作返回所删除元素之后的迭代器
    else
        iter++;    
}
```

### 11.3.4 map的下标操作
- **`map 和 unordered_map` 都支持下标操作和对应的 at 函数。**
- **set 类型则不支持下标。multimap 和 unordered_multimap 不支持下标操作。**
- map 的**下标操作会返回一个 `mapped_type` 对象**。而**解引用迭代器返回一个 `value_type` 对象**。
- **如果关键字不在 map 中，会创建一个元素并插入到 map 中，关联值将进行值初始化**。
 >注意：因为关联值是值初始化，所以在单词计数程序中，可以直接 map[word]++ ，不必特意插入元素。
 >注意：**map 的下标操作只能返回非常量引用**（不同于顺序容器的下标操作），如果 map 本身是常量，则无法使用下标访问元素，这时要用 at() 函数。
- at 函数
 m.at(k) 会访问关键字为 k 的元素，**带参数检查**；如果 k 不在 m 中，抛出一个 out_of_range 异常。

### 11.3.5 访问与查找元素
- **访问元素**

>map  可以通过下标或 at() 函数访问元素。 set 只能通过迭代器来访问元素。
```cpp
'基本的访问操作'
c[k];
c.at(k);
```
>访问 map/set 的最后一个元素：m.rbegin() 或 --m.end()。

- **查找元素**

关联容器查找一个指定元素的方法有多种。一般 **find 是最佳选择**。
> **对于不允许重复关键字的容器，find 和 count 差别不大，对于允许重复关键字的容器，count 会统计有多少个元素有相同的关键字。**
```cpp
'查找操作'
c.find(k);//返回一个迭代器，指向关键字为 k 的元素，如果 k 不在容器中，返回尾后迭代器。
c.count(k);//返回关键字等于 k 的元素数量。
c.lower_bound(k);//返回一个迭代器，指向第一个关键字大于等于 k 的元素。
c.upper_bound(k);//返回一个迭代器，指向第一个关键字大于 k 的元素。
c.equal_range(k);//返回一个迭代器 pair，表示关键字等于 k 的元素范围。若干 k 不存在，pair 的两个成员相等，指向可以安全插入 k 的位置(c.end())
```

- 检查元素是否存在
> 检查元素是否存在用 find 或 count。
```cpp
if(word_count.find("LiLin") == word_count.end())
if(word_count.count("LiLin") == 0)
```

- 在 multimap 或 multiset 中查找元素

要在 multimap 或 multiset 中查找所有具有给定关键字的元素比较麻烦，有三种方法:

1. **使用 find 和 count 配合**，找到第一个关键字为 k 的元素和所有关键字为 k 的元素数目，遍历完成。
2. **使用 lower_bound 和 upper_bound 配合**。注意当关键字 k 不存在时，这两个函数返回相同的迭代器，可能是尾后迭代器也可能不是。
```cpp
 for(auto beg = authors.lower_bound(search_item),
          end = authors.upper_bound(search_item);
    beg != end; ++beg)
     cout << beg->second;
```
3. **使用 equal_range**。最直接的方法
```cpp
  for(auto pos = authors.equal_range(search_item); pos.first != pos.second; ++pos.first)
     cout << pos.first->second;
```

[t11_33](#t11_33)


## 11.4 无序容器
4 个无序容器**使用`哈希函数`和`关键字类型的 == 运算符`来组织元素**，而非比较运算符。

无序容器用于关键字类型不好排序的情况。

- **使用无序容器**
  **无序容器也有 find，insert，迭代器等操作。**

  **在大多数情况下，可以用无序容器替换对应的有序容器，反之亦然。但是注意无序容器中元素未按顺序存储。
- **管理桶**
  **无序容器`在存储上组织为一组桶`，每个桶保存零个或多个元素。**
  
  无序容器**使用哈希函数将元素映射到桶**，并将**具有一个特定哈希值的所有元素保存在相同的桶中**。如果容器允许重复关键字，那所有具有相同关键字的元素也都在同一个桶中。不同关键字的元素也可能映射到相同的桶。
  
  对于相同的参数，哈希函数总是产生相同的结果。
  
  当一个桶中保存了多个元素，需要顺序搜索这些元素来查找想要的那个。计算一个元素的哈希值和在桶中搜索通常都很快。
- **管理桶的函数**
```cpp
'桶接口'
c.bucket_count();      //返回正在使用的桶的数目
c.max_bucket_count();  //返回容器能容纳的最多的桶的数量
c.bucket_size(n);      //返回第 n 个桶中有多少个元素
c.bucket(k);           //返回关键字为 k 的元素所在的桶

'桶迭代'
local_iterator         //类型别名，可以用来访问桶中元素的迭代器类型
const_local_iterator   //类型别名，桶迭代器的常量版本
c.begin(n), c.end(n)  //返回桶 n 的首元素迭代器和尾后迭代器
c.cbegin(n),c.cend(n) 

'哈希策略'
c.load_factor();      //返回每个桶的平均元素数量，类型为 float
c.max_load_factor();  //返回 c 试图维护的平均桶大小，类型为 float。c 会在需要时添加新的桶，始终保持 load_factor <= max_loat_factor
c.rehash(n);          //重组存储，使得 bucket_count >= n 且 bucket_count > size / max_load_factor
c.reserve(n);         //重组存储，使得 c 可以保存 n 个元素而不必 rehash。
```

- **无序容器对关键字的要求**
  **默认情况下，无序容器使用 == 运算符比较关键字，使用用一个 hash<key_type> （hash 模板）类型的对象来生成每个元素的哈希值。**
  >标准库为内置类型（包括指针）和 string、智能指针等都定义了 hash，因此**内置类型，string 和智能指针类型都能直接用来作为无序容器的关键字**。
  
  对于**自定义的类类型，不能直接用来作为无序容器的关键字**，因为他们不能直接使用 hash 模板，**除非提供自己的 hash 模板版本**。
```cpp
'定义自己的 hash 模板版本'
size_t hasher(const Sales_data &sd){
    return hash<string>() (sd.isbn());//这里采用了标准库的 hash 类型对象来计算 isbn 成员的哈希值，作为整个 Sale_data 对象的哈希值。
}
'重载比较函数（这里是相等）'
bool eq(const Sales_data &lhs, const Sales_data &rhs){
    return lhs.isbn() == rhs.isbn();
}
'定义 unordered_multiset'
unordered_multiset< Sales_data, decltype(hasher)*, decltype(eq)* > sals;
``` 
>无论是有序容器还是无序容器，具有相同关键字的元素都是相邻存储的。
[t11_38](#t11_38)

## 习题
### t11_3
> 单词计数程序
```cpp
//t11_4 忽略大小写与标点("Example","example","example."为同一关键字)
int main(int argc,char *argv[]){
    ifstream in("infile.txt");
    if(!in){
        cerr << "打开输入文件失败";
        return -1;
    }
    map<string,size_t> count;
    string word;
    while(in>>word){
        for(string::size_type i=0;i<word.size();i++){
            if(word[i]<='Z'&&word[i]>='A') word[i] -=('A'-'a');
            else if(word[i]<='z'&&word[i]>='a') ;
            else if(word[i]=='.'||word[i]==','||word[i]=='/')word.erase(i--,1);  //先删除word[i]这个不为字母的符号;再i--保证下次循环元素正确
        }

        ++count[word];
        /*
        //t11_20 用insert代替下标操作,插入成功则返回pair的second元素为1,插入不成功则通过返回pair的first元素将其次数加一
        auto ret =count.insert({word,1});
        if(!ret.second) ++ret.first->second;
        //语法应用:等同于前两行语句
        ++ count.insert({word,0}).first ->second;
        */
    }
    
    
    for(const auto& w:count){
        cout << w.first << " occurs"<< w.second <<((w.second>1)?" times":" time") <<endl;
    }
    
    /*
    //t11_18 不用auto decltype,用迭代器打印count
    //答案为pair<string,size_t>::iterator iter =count.begin();但报错pair类无iterator
    for(map<string,size_t>::iterator iter =count.begin();iter!=count.end();iter++){
        cout << iter->first <<" occurs"<< iter->second << "times"<<endl;
    }
    */
}
```

### t11_7
> 定义map,key_type是家庭名,mapped_type是vector,保存孩子们的名. 编写代码实现添加新家庭和向已有家庭添加新孩子.
```cpp
int main(){
    map<string,vector<string>> family;
    vector<string> children;
    string family_name;
    string child_name;
    cout <<"输入家庭名:(退出请输入end)\n";    
    while(getline(cin,family_name)){
      if(family_name == "end") break;
      if(family.find(family_name) == family.end()){
        cout <<"输入成员名: (退出请输入end)\n";
        while(getline(cin,child_name)){
          if(child_name == "end") break;
          children.push_back(child_name);
        }
        family[family_name]=children;
        children.clear();
      }
      else{
        cout <<"输入成员名: (退出请输入end)\n";
        while(getline(cin,child_name)){
          if(child_name == "end") break;
          family[family_name].push_back(child_name); 
          //fmaily[famliy_name] 获取其vector,,再调用vector成员函数push_back添加字符串         
        }
      }
       cout <<"输入家庭名:(退出请输入end)\n";
    }
    for(auto & item : family){
        cout << "家庭名: "<< item.first <<endl;
        cout << "家庭成员名: ";
        for(auto str : item.second)
         cout << str <<" ";
        cout <<endl;
    }
}
 
```

### t11_9
>定义一个map,将单词与一个行号的list关联,list中保存的是单词所出现的行号
```cpp

int main(){
    map<string,list<int>> word_lineno;
    ifstream in;
    in.open("infile.txt");
    string itstr;
    int lineno=1;
    while(getline(in,itstr)){
        istringstream line(itstr);
        string word;
        while(line>>word){
            word_lineno[word].push_back(lineno);
        }
        lineno++;
    }

    for(const auto &w:word_lineno){
        cout << w.first <<"所在行: ";
        for(const auto &i:w.second)
            cout << i <<" ";
        cout<<endl;    
    }
}
```

### t11_12
>读入string和int的序列,将每个string和int存入一个pair中,pair保存在一个vector中
```cpp

int main(){
    ifstream in;
    in.open("infile.txt");
    if(!in) cout<< "文件未打开\n";
    string str;
    int value;
    vector<pair<string,int>> data;
    while(in>>str&&in>>value){
        data.push_back(make_pair(str,value));
        //data.push_back(pair<string,int>(str,value));
        //data.push_back({str,value});
    }
    for(const  auto & item : data){
        cout << item.first <<" " <<item.second <<endl;
    }
}
```

### t11_14
>扩展t11_3程序,添加一个pair的vector,保存孩子的名字和生日
```cpp

int main(){
    map<string,vector<pair<string,string>>> family;
    vector<pair<string,string>> children;
    string family_name;
    string child_name;
    string child_birth;
    cout <<"输入家庭名:(退出请输入end)\n";    
    while(getline(cin,family_name)){
      if(family_name == "end") break;
      if(family.find(family_name) == family.end()){
        cout <<"输入成员名和生日: (退出请输入end)\n";
        while(getline(cin,child_name)&&getline(cin,child_birth)){
          if(child_name == "end") break;
          children.push_back({child_name,child_birth});
        }
        family[family_name]=children;
        children.clear();
      }
      else{
        cout <<"输入成员名: (退出请输入end)\n";
        while(getline(cin,child_name)){
          if(child_name == "end"||child_birth == "end") break;
          family[family_name].push_back({child_name,child_birth}); 
          //fmaily[famliy_name] 获取其vector,,再调用vector成员函数push_back添加字符串         
        }
      }
       cout <<"输入家庭名:(退出请输入end)\n";
    }
    for(auto & item : family){
        cout << "家庭名: "<< item.first <<endl;
        cout << "家庭成员名和生日: \n";
        for(auto str : item.second)
         cout << str.first <<" "<<str.second<<endl;;
        cout <<endl;
    }

    
}
```

### t11_16
>map迭代器的使用
```cpp

int main(){
    map<string,int>map1;
    auto it=map1.begin();
    it->second = 0;
}
```

### t11_23
>用multimap重写t11_3
```cpp

void add_child(multimap<string,string> &familes ,string family,string child){
   familes.insert({family,child});
}

int main(){
    multimap<string,string> familes;
    add_child(familes,"Wang","Yong");
    add_child(familes,"Cheng","Siyi");
    add_child(familes,"Wang","Zhuzhu");

    for(auto f:familes){
        cout<<f.first<<" "<< f.second <<endl;
    }
}


```

### t11_31
>定义一个作者及作品multimap,使用find在multimap中查找元素并用erase删除;确保关联容器中无元素时也可运行.
```cpp

void finderase_multimap(multimap<string,string>& authors,string searchName){
    if(authors.equal_range(searchName).first == authors.equal_range(searchName).second)
       cout << "未找到作者"<<searchName<<endl;
    else
      authors.erase(authors.equal_range(searchName).first,authors.equal_range(searchName).second);
}

void print_books(multimap<string,string> & authors){
    cout << "当前书目包括: \n";
    for(auto &book : authors)
       cout << book.first <<", <<"<<book.second<<">>"<<endl;
    cout <<endl;
       
}
int main(){
    multimap<string,string> books;
    books.insert({"Barth,John","Sot-Weed Factor"});
    books.insert({"Barth,John","Lost inthe Funhouse"});
    books.insert({"wy","Aaaaaa"});
    books.insert({"wy","Bbbbbb"});
    print_books(books);
    finderase_multimap(books,"张三");
    finderase_multimap(books,"wy");
    print_books(books);
    return 0;
}
```

### t11_33
>单词转换程序
```cpp

map<string,string> buildMap(ifstream &map_file){
    map<string,string> trans_map;
    string key,value;
    while(map_file>>key && getline(map_file,value)){
        if(value.size()>1)
            trans_map[key] = value;
            //trans_map.insert({map,value})
        else
            throw runtime_error("no rule for"+key);
        
    }
    return trans_map;
}

string transform(string word,const map<string,string> &trans_map){
        auto map_iter = trans_map.find(word);
        if(map_iter != trans_map.end()){
            return map_iter->second;
        }
        else
         return  word;
}

void word_transform(ifstream &map_file, ifstream &input){
    auto trans_map = buildMap(map_file);
    string line;
    while(getline(input,line)){
        istringstream in(line);
        string word;
        bool isfirst_word = true;
        while (in>>word){
           if(isfirst_word) isfirst_word = false;
           else cout<<" ";
           cout << transform(word,trans_map);  
        }
        cout <<endl;        
    }
}

int main(){
    ifstream input,map_file;
    input.open("infile.txt");
    map_file.open("map_file.txt");
    word_transform(map_file,input);
    return 0;
}
```

### t11_38
>用unordered_map重写单词计数程序
```cpp

void count_words(ifstream &input){
    unordered_map<string,int> count;
    string word;
    while(input >> word){
        ++ count[word];
    }
    for(auto item: count){
        cout<<item.first<<" occurs "<<item.second<<" times"<<endl;
    }

}

int main(){
    ifstream in;
    in.open("infile.txt");
    count_words(in);
    return 0;
}
```