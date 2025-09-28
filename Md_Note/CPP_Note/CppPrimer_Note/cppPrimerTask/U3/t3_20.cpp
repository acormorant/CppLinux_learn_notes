#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    vector<int>vn;
    int num;
    while(cin>>num)
    vn.push_back(num);
    auto it =vn.cbegin();
    auto itend =vn.cend();
/* while(it!=vn.end()){
       cout<< *it+*(++it)<<endl; 
    }
//相邻元素相加 
*/
   itend--;
   while ( it<itend )
   {   
       cout<<*it+ *itend <<endl;
       it++;
       itend--;
      }
    if(it==itend)
    cout<<*it<<endl;
      
       
   
   
   
    return 0;

}