#include<iostream>
#include<iterator>
#include<algorithm>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

void distinguish_odd_even(string infile,string odd_outfile,string even_outfile){
       ifstream input;
       input.open(infile);
       istream_iterator<int> is(input),eof;
       ofstream odd_out,even_out;
       odd_out.open(odd_outfile);
       even_out.open(even_outfile);
       ostream_iterator<int> odd_iter_out(odd_out," "),even_iter_out(even_out,"\n");
       while(is != eof){
        if(*is & 1){
           odd_iter_out = *is++;
        }
        else{
            even_iter_out = *is++;
        }
       }
}

int main(int argc,char* argv[]){
    distinguish_odd_even(argv[1],argv[2],argv[3]);
}
/*
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> g++ .\t10_33.cpp -o t10_33.exe
PS C:\Users\cormorant\Desktop\v\C\cpp\cppPrimer\U10> .\t10_33.exe intfile.txt odd_intfile.txt even_intfile.txt
*/