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