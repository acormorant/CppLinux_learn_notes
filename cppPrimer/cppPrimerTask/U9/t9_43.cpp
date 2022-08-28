#include<vector>
#include<string>
#include<iostream>
using namespace std;

void replace_word (string &s,const string &oldval,const string &newval){
    if(! oldval.size()) return;
    if(s.size()<oldval.size()) return;
    auto iter =s.begin();
    while(iter!=s.end()){    
        if(*iter == *oldval.begin()){
            auto siter =iter;
            auto olditer = oldval.begin();
            while(*siter==*olditer && olditer!=oldval.end()){
                siter++;
                olditer++;
            }
            if(olditer == oldval.end()){
              iter= s.erase(iter,siter);
              auto newiter = newval.end();
              while(newiter !=newval.begin()){
              iter = s.insert(iter,*(--newiter));
            }
        }
    }
        iter++;
  }

}

int main(){
    string s="tho thru tho!";
    replace_word(s,"thru","through");
    cout << s << endl;
    replace_word(s,"tho","though");
    cout << s << endl;
    replace_word(s,"through"," ");
    cout << s << endl;
}