
#include<iostream>
#include<stdexcept>
using namespace std;
 int main()
{ 
    int ival1, ival2;
    cout<<"依次输入除数被除数"<<endl;
    while (cin>>ival1 >>ival2)
    {
        try{ 
             if(ival2==0)
             throw runtime_error("被除数不能为0");
            
        }catch(runtime_error err){
               cout<< err.what()
                   <<"\n Try Again? Enter y or n"<<endl;
                   char c;
                   cin>>c;
                if(!cin ||c=='n'||c=='N') break;
                else cout<<"依次输入除数被除数"<<endl;
             }
        
        
    }
    cout<<"相除结果为: "<<ival1/ival2<<endl;
    return 0;

   
}
