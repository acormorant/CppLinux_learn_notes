#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main(){
    vector<unsigned> scores(11,0);
    
    unsigned grade;
    while(cin>>grade){
        if(grade<=100){
        auto it=scores.begin();
           it+=(grade/10);
            (*it)++;
            

        }
   
    }
     for(auto it =scores.cbegin();it!=scores.cend();it++){
        cout<<*it<<" ";
    }
}