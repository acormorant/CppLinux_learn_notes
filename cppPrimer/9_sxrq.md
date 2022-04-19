# 顺序容器

## 问题
1. ==基本的顺序容器有 6 种，分别是什么？哪几种容器算是通用型？存储结构分别是什么？==
 vector, deque, list, forward_list, string, array。vector, deque, list 算是最通用的通用型。两个 list 是链式结构，其他都是顺序结构

2. ==顺序容器的通用操作有哪些?==
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
 string 支持快速随机访问、在尾部快速插入删除。

8. string 特点是什么，支持哪些操作?
 array 支持快速随机访问，是固定大小数组。

9. vector, deque, list 应用场景分析:
 一般用 vector，需要头部插入删除用 deque，需要中间插入删除用 list。**元素数量多且单个元素小不用 list**，空间开销很重要不用 list，需要随机访问用 vector,deque。

10. 基本的顺序容器适配器有 3 种，分别是什么？默认底层容器分别是什么？
 queue, priority_queue, stack ，==queue 和 stack 的底层容器是 deque，priority_queue 的底层容器是 vector==

11. 适配器有哪些共同特点？
 ==适配器不能用底层容器的操作。**适配器不支持迭代器。** clear() 是通过迭代器实现的，因此**适配器都不支持 clear()。**==

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
  - insert：包括 insert() 一种，==传入一个迭代器指明位置，再迭代器前插入，可以添加单个元素、多个相同元素、某迭代器范围内的所有元素，花括号列表==

6. 如何在一个位置反复插入元素
```cpp
 iter = c.insert(iter, word);
```

7. 访问容器元素的三类操作分别是什么，用于哪种情况？
 - begin(),end() 返回迭代器
 - **front(), back() 返回元素的引用，back() 返回尾元素**
 - ==**vec.at()，vec[] ：下标访问法。at() 函数可以检查下标越界。可用于 vector，deque，string，array**==

8. 删除元素的三类操作分别是什么？用于哪种情况？
 - pop 类：包括 pop_front(), pop_back() 两种，都返回 void 。单纯的 pop 操作只用于顺序容器适配器。
 - erase 类：包括 erase() 一种，接受迭代器做参数，可以删除一个元素或一个迭代器范围。返回删除元素之后的元素的迭代器
 - clear：清空整个容器。不能用于适配器。

9. farword_list 有哪些操作？
 farword_list 的操作有 ==**erase_after(iter), insert_after(), emplace_after() 。before_begin() 返回一个首前迭代器。**==

10. 控制容器大小的操作有哪些
resize() ：调整容器大小。reserve()：为vector 和 string 预分配内存；capacity(), shrink_to_fit() 

## 问题
1. 获取 string 对象的子序列的方法
 使用** s.substr(pos,n) 来获取从下标 pos 处开始的长度为 n 的子序列**

2. ==**搜索 string 中的字符**==
**string 定义了 6 个相应功能的函数。 find(), rfind(), find_first_of() 等。**

3. 字符串与数值之间进行转换的函数。
to_string() 与 stoi(), stod(), stol 等

## 第九章 顺序容器
### 9.1 顺序容器概述
所有容器都提供**高效的==动态内存==管理**
- **几种顺序容器**
 **vector**：支持快速随机访问。在**尾部**插入/删除速度快。
 **deque**：支持快速随机访问。在**头尾**插入/删除都很快。
 **list**：==**双向链表**==。只支持 ==**双向顺序访问**==。在任何位置插入/删除都很快。
 **forward_list**：单项链表。**只支持单向顺序访问**。在任何位置插入/删除都很快。
 **string**：支持快速随机访问。**在==尾部==插入/删除速度快**。
 **array**：**固定大小数组**。支持快速随机访问。

可以发现：vector\deque\string\array 都是**顺序存储结构**。 list 是**链式存储结构**。但是他们都是顺序容器

list 的==额外内存开销==相比其他大很多。
array 是一种==比内置数组更好==的类型。
==**farward_list 没有 size 操作**==。这种列表与最好的手写链表性能一样好。
**新标准库容器的性能至少与同类手写数据结构一样好或更好，==c++ 程序应该使用标准库容器。
容器选择==**

- **vector/list/deque** 三种容器的比较：
1. ==如果没有特殊的理由，使用 vector 是最好的选择==
2. 如果**有很多小的元素**，不用 list
3. 如果**空间开销很重要**，不用 list
4. 如果需要在中间位置插入/删除，用 list
5. 如果需要在头尾位置插入/删除，用 deque
6. 如果需要随机访问，用 vector 或 deque
7. 如果需要在中间位置插入，而后随机访问：
   - 如果可以通过排序解决，就像插到尾部，而后排序
   - **在输入阶段用 list ，输入完成后拷贝到 vector 中**

### 