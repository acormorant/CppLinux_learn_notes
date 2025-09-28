#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    vector<int>v1;
    vector<int>v2(10);
    vector<int>v3(10,42);
    vector<int>v4{10};
    vector<int>v5{10,42};
    vector<string>v6{10};
    vector<string>v7{10,"hi"};
    
    for(auto vn1 : v1)
      cout<< vn1<<" ";
      cout<<endl<< v1.size()<<endl;
    for(auto vn2 : v2)
      cout<< vn2<<" ";
      cout<<endl<< v2.size()<<endl;
    for(auto vn3 : v3)
      cout<< vn3<<" ";
      cout<<endl<< v3.size()<<endl;
    for(auto vn4 : v4)
      cout<< vn4<<" ";
      cout<<endl<< v4.size()<<endl;
    for(auto vn5 : v5)
      cout<< vn5<<" ";
      cout<<endl<< v5.size()<<endl;
    for(auto vn6 : v6)
      cout<< vn6<<" ";
      cout<<endl<< v6.size()<<endl;
    for(auto vn7 : v7)
      cout<< vn7<<" ";
      cout<<endl<< v7.size()<<endl;
return 0;
}
