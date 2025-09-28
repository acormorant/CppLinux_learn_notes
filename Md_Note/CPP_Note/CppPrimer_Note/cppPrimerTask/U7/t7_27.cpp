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
/*
如果 move、set和display 函数的返回类型不是Screen＆而是 Screen，将会发生什么情况？

 返回类型Screen&:
XXXXXXXXXXXXXXXXXXXX#XXXX
XXXXXXXXXXXXXXXXXXXX#XXXX
 返回类型Screen: 
XXXXXXXXXXXXXXXXXXXX#XXXX
XXXXXXXXXXXXXXXXXXXXXXXXX

【出题思路】

函数的返回值如果是引用，则表明函数返回的是对象本身；函数的返回值如果不是引用，则表明函数返回的是对象的副本。

【解答】

返回引用的函数是左值的，意味着这些函数返回的是对象本身而非对象的副本。如果我们把一系列这样的操作连接在一起的话，所有这些操作将在同一个对象上执行。

在上一个练习中，move、set和display函数的返回类型都是Screen＆，
表示我们首先移动光标至（4，0）位置，然后将该位置的字符修改为＇＃＇，最后输出myScreen的内容。

相反，如果我们把move、set和display 函数的返回类型改成Screen，
则 上述函数各自只返回一个临时副本，不会改变myScreen的值。



*/