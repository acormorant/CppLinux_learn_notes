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