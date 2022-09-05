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