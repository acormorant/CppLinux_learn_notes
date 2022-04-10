    练习8.2.1节 文件输入输出
    练习8.2.2节 file mode
    练习8.11 8.12 8.13 i/o stringstream


## 8.1 IO类
1.标准库通过**继承机制**使我们忽略设备类型字符大小等流之间的差异.
 >继承关系使我们可以声明一个特定的类继承自另一个类.
 >我们通常可以将一个派生类对象当作其基类对象来使用.

2.**IO对象无法拷贝或复制**。进行IO操作的函数通常以引用方式传递和返回流。

3.IO类定义了一些函数和标志,帮助访问和操纵流的**条件状态**.
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

## 8.3 string流
| 类 | 作用 |
| ------ | -------- |
| istringstream | 从string读取数据 |
| ostringstream | 向string写入数据 |
| stringstream | 既可从string读数据也可以向string写数据 |	
```cpp
    // will hold a line and word from input, respectively
	string line, word;

	// will hold all the records from the input
	vector<PersonInfo> people;

	// read the input a line at a time until end-of-file (or other error)
	while (getline(is, line)) {       
		PersonInfo info;            // object to hold this record's data
	    istringstream record(line); // bind record to the line we just read
		record >> info.name;        // read the name
	    while (record >> word)      // read the phone numbers 
			info.phones.push_back(word);  // and store them
		people.push_back(info); // append this record to people
	}
	// for each entry in people
	for (vector<PersonInfo>::const_iterator entry = people.begin();
				entry != people.end(); ++entry) {    
		ostringstream formatted, badNums; // objects created on each loop
```
```cpp

		// for each number
		for (vector<string>::const_iterator nums = entry->phones.begin();
				nums != entry->phones.end(); ++nums) {  
			if (!valid(*nums)) {           
				badNums << " " << *nums;  // string in badNums
			} else                        
				// ``writes'' to formatted's string
				formatted << " " << format(*nums); 
		}
		if (badNums.str().empty())      // there were no bad numbers
			os << entry->name << " "    // print the name 
			   << formatted.str() << endl; // and reformatted numbers 
		else                   // otherwise, print the name and bad numbers
			cerr << "input error: " << entry->name 
			     << " invalid number(s) " << badNums.str() << endl;
	}
```
