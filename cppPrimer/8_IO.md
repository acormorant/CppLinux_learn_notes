    练习8.2.1节 文件输入输出
    练习8.2.2节 file mode
    练习8.11 8.12 8.13 i/o stringstream


## 8.1 IO类
1.标准库通过**继承机制**使我们忽略设备类型字符大小等流之间的差异.
 >继承关系使我们可以声明一个特定的类继承自另一个类.
 >我们通常可以将一个派生类对象当作其基类对象来使用.

2.**IO对象无法拷贝或复制**。进行IO操作的函数通常以引用方式传递和返回流。

3.IO类定义了一些函数和标志,帮助访问和操纵流的**条件状态**.

 >iostream::iostate;//作为位集合来使用，可以表达流的完整状态。通过位运算符可以一次性检测或设置多个标志位。
 >iostream::badbit; cin.badbit;//表示流已崩溃，是系统及错误或不可恢复的读写错误。流无法再使用。
 >iostream::failbit; cin.failbit;//表示一个 IO 操作失败了，是可恢复错误。修正后流可以继续使用。
 >iostream::eofbit; cin.eofbit;//表示流到达了文件结束
 >iostream::goodbit;//表示流未处于错误状态
 
 **我们将流作为条件使用的代码就等于!fail().**
 而eof和bad操作只能表示特定的错误.

4.刷新输出缓冲区
  flush刷新缓冲区，但不输出任何额外的字符；
  ends向缓冲区插入一个空字符，然后刷新缓冲区。
  unitbuf操纵符,告诉流在每次输出操作后都进行一次flush操作.


   

## 8.2 文件输入输出
| 类 | 作用 |
| ------------ | ---------- |
| ifstream | 从一个给定文件读取数据 |
| ofstream | 从一个给定文件写入数据 |
| fstream | 读写给定文件 |

**C++11 中，文件名可以是 string 类型对象，也可以是 C 风格字符串**

- fstream 定义和初始化
 ```cpp
 fstream fs;                    // 创建一个未绑定的文件流 fs
 fstream fs('data.txt');        // 创建一个绑定到文件 data.txt 的文件流 fs,并打开文件 data.txt
 fstream fs('data.txt', mode);  // 与上一个构造函数类似，但是按指定模式 mode 打开文件
 ```
- fstream 特有操作
 ```cpp
 getline(ifs, s);         // 从一个输入流 ifs 读取一行字符串存入 s 中
 fs.open('data.ext');     // 将 fs 与文件 data.txt 绑定并打开该文件。如果已打开会发生错误。
 fs.close();              // 关闭 fs 绑定的文件。
 fs.is_open();            // 返回一个 bool 值，指出关联文件是否成功打开。
 ```

- fs.open()
 如果 open 失败，failebit 会被置位，建议每次 open 后检测 open 是否成功。
 不能对已打开的文件流调用 open。
 当文件关闭后，可以将文件流关联到另一个文件。
 当一个 fstream 对象被销毁时，close 函数会自动被调用。

- **用 fstream 代替 iostream**
 使用 iostream 类型的引用作为函数参数的地方，都可以使用 fstream 来代替。

###实例 T8_7
**重写T7_7书店管理程序,从文件读取交易记录,将结果保存到文件中.**
(将文件名作为参数传给main)

- 报错
 `error C2280: “std::basic_ifstream<char,std::char_traits>::basic_ifstream(const std::basic_ifstream<char,std::char_traits> &)”: 尝试引用已删除的函数`
 解决方法
 **若ifstream作为函数形参时，将其改为传址pass by reference。**
 ifstream &read(ifstream &is, Sales_data&item)

- 编译后生成.exe文件,我们可以在集成终端打开exe文件,向该文件传递参数
 PS C:\Users\cormorant\Desktop\v\C\cpp\cppexe> **.\t8_6** InFile.txt outfile.txt
- 文件名不分大小写
  - 指定c风格字符串时两种格式都成功.
  ```cpp
     (ifstream input;
     input.open("infile.txt");
     //input.open("InFile.txt");
     )
	 ```
  - 指定sting对象时两种格式都成功.
  ```cpp
     ( string str1="infile.txt";
     //string str1="InFile.txt"; 
      input.open(str1)
     )
  ```
   - arvg[1]中内容为两种时都不成功.
    ```cpp 
      (
      argv[1] is: InFile.txt
      //argv[1] is: infile.txt
      )
     ```
- ==未解决错误==
  - **arvg[1]中内容为两种时都不成功.**
    ```cpp
     (
        argv[1] is: InFile.txt
      //argv[1] is: infile.txt
     )
	```
  - **使用接受istream&类型函数时无法用其对应ifstream调用**
    ```cpp
     std::istream &read(std::istream &is, Sales_data&item)
     read(input,total)
     //报错
     undefined reference to `read(std::basic_ifstream<char, std::char_traits<char> >&, Sales_data&)'
	  ```
```cpp
#include<iostream>
#include<fstream>
#include"Sales_data.h"
using namespace std;

ifstream &read(ifstream &is, Sales_data&item){
    double price;
    is >>item.bookNo >>item.units_sold >>price;
    item.revenue =item.units_sold *price;
    return is;
}
ofstream &print(ofstream &os, const Sales_data&item){
    os <<item.isbn() 
       <<" 销售量:  "<<item.units_sold 
       <<" 总销售额: "<<item.revenue
       <<" 均价:   "<<item.avg_price()
       <<endl;
       return os;
}

int main(int argc,char *argv[]){
    cout<<"输入isbn 销售量 单价: \n";
    ifstream input;
    string str1="infile.txt";
    string str2="outfile.txt";
    input.open(str1);
    ofstream output;
    output.open(str2);
    Sales_data total;
    if(read(input,total)){

        Sales_data trans;
        cout<<"请再输入isbn 销售量 单价: \n";
        while (read(input,trans))
        {
            if(total.isbn()==trans.isbn()){
                total.combine(trans);
                cout<<"请再输入isbn 销售量 单价: \n";
            }
            
            else{
                print(output,total);
                // cout<<total<<endl;
                total=trans;
                cout<<"请再输入isbn 销售量 单价: \n";
            }
        }
        print(output,total);
        return 0;
        
    }
    else{
        cerr<<"No data?!"<<endl;
        return -1;
    }
    
}

```

[c++输入文件流ifstream用法详解](https://blog.csdn.net/sinat_36219858/article/details/80369255)

### 文件模式
每次打开文件都以某种模式打开，如未指定即以该文件流类型的默认模式打开。
每个流都有一个关联的文件模式，用来指出如何使用文件
>in：以只读方式打开
out：以只写方式打开
app：每次写操作前均定位到文件末尾
ate：打开文件后即定位到文件末尾
trunc：截断文件
binary：以二进制方式进行 IO

- **文件模式的使用：**
   - 每个流对象都有默认的文件模式，ifstream 默认 in 模式打开文件，ofstream 默认 out，fstream 默认 in 和 out。
   - 对 ifstream 对象不能设置 out 模式，对 ofstream 对象不能设置 in 模式
   - 只有设置了 out 才能设置 trunc 模式，**只设置 out 模式会默认也设置 trunc 模式**
   - 设置了 trunc 就不能再设置 app 模式
   - **默认情况下以 out 模式打开文件会使文件内容被清空，如果要保留文件内容需要同时指定 app 模式或 in 模式。**
   - app 模式下，会将写入的数据追加写到文件末尾
```cpp
ofstream fout("file1.txt");                                  // 以输出模式打开文件并截断文件（即清空文件内容）
ofstream fout("file1.txt", ofstream::app);                   // 显示指定 app 模式（+隐含的 out 模式）
ofstream fout("file1.txt", ofstream::app | ofstream::out);   // 同上，只是将 out 模式显式地指定了一下。
fout.open("file1.txt", ofstream::out);
```

## 8.3 string流
| 类 | 作用 |
| ------ | -------- |
| istringstream | 从string读取数据 |
| ostringstream | 向string写入数据 |
| stringstream | 既可从string读数据也可以向string写数据 |	
sstream 定义了 istringstream, ostringstream, stringstream 来读写 string。
- sstream 定义和初始化
```cpp
 stringstream strm();     // 定义一个未绑定的 stringstream 对象
 stringstream strm(s);    // 定义一个 stringstream 对象 strm，strm 中保存着 string s 的拷贝。
```

### 8.3.1 使用istringstream
- stringstream 特有操作
```cpp
strm.str();   // 返回 strm 中保存的 str 的拷贝
strm.str(s);  // 将 string s 拷贝到 strm 中，返回 void
```

### 8.3.2 使用ostringstream
理解：
1.istringstream 是输入流，即读操作，要将流中的内容输入到字符串中，因此**定义和使用 istringstream 时流内必须有内容，所以在使用前要提前在流内保存一个字符串.**
2.ostringstream 是输出流，即写操作，将流中的内容输出到字符串中，ostringstream **可以在定义时即在流中保存一个字符串，也可以通过 << 操作符获得字符串。**