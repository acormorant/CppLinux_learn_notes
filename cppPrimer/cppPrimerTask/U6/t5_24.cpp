#include<iostream>
#include<stdexcept>
using namespace std;
 int main()
{   cout<<"依次输入除数被除数"<<endl;
    int ival1, ival2;
    cin>> ival1>> ival2;
    if(ival2==0)
    {
      throw runtime_error("被除数不能为0");
    }
    cout<<"相除结果为: "<<ival1/ival2<<endl;

    return 0;
}
