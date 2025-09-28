#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iterator>
#include<algorithm>
using namespace std;

int main(int argc,char *argv[]){
    ifstream input;
    input.open(argv[1]);
    istream_iterator<string> is(input),eof;
    vector<string> svec;
    while(is != eof){
       svec.push_back(*is++);
    }
    for(auto iter = svec.begin();iter != svec.end();iter ++) cout << *iter <<" ";
    cout << endl;    

}

/*
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> g++ .\t10_29.cpp -o t10_29.exe  
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> .\t10_29.exe infile.txt
003a 1 1 003a 2 8 002a 3 10 002a 3 11 002a 4 18 001a 5 90 001a 6 75 001a 10 100
*/