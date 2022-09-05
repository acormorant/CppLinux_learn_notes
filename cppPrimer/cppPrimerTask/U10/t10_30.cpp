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