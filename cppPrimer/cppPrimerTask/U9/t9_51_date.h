#ifndef T9_51_DATE_H
#define T9_51_DATE_H
/*
一月-- --January -- --Jan.

二月-- --February -- --Feb.

三月-- --March -- --Mar.

四月-- --April -- --Apr.

五月-- --May -- --May.

六月-- --June -- --Jun.

七月-- --July -- --Jul.

八月-- --August -- --Aug.

九月-- --September -- --Sept.

十月-- --October -- --Oct.

十一月-- --November -- --Nov.

十二月-- --December -- --Dec. 
*/
#include<string>
#include<iostream>
using namespace std;

const string month_name[]={"January","February","March","April","May","June","July","August","September","October","November","December","dec"};
const string month_abbr[]={"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sept","Oct","Nov","Dec"};


class t9_51_date {
    friend ostream& operator<<(ostream&,const t9_51_date&);
    public:
    t9_51_date()=default;
    t9_51_date(string &s){
        bool bitem = false;
        string::size_type i;
        string::size_type j;
            for(i=0;i<12;i++){                         //月份简写匹配
                for( j=0;j < month_abbr[i].size();j++)
                    if(s[j] != month_abbr[i][j])
                    break;
                if(j == month_abbr[i].size()){
                    bitem = true;
                    month = i+1;
                }
                
            }
            for(i=0;i<12;i++){                         //月份名称匹配
                for( j=0;j < month_name[i].size();j++)
                    if(s[j] != month_name[i][j])
                    break;
                if(j == month_name[i].size()){
                    bitem = true;
                    month = i+1;
                }
            }    

        if(bitem){//通过多次查找并获得子序列从而将输入中的非数字字符排除以得到正确的数字子字符串并转换
            s=s.substr(s.find_first_of("0123456789"));
            string sday=s.substr(0,s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_of("0123456789"));
            string syear=s;
            day=stoi(sday);
            year=stoi(syear);
        }
        else{
            string sday =s.substr(0,s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_of("0123456789"));
            string smonth=s.substr(0,s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_not_of("0123456789"));
            s=s.substr(s.find_first_of("0123456789"));
            string syear=s;
            day=stoi(sday);
            month=stoi(smonth);
            year=stoi(syear);
        }

    }
    unsigned y () const {return year; }
    unsigned m () const {return month; }
    unsigned d () const {return day; }

    private:
    unsigned year=0;
    unsigned month=0;
    unsigned day=0;
};

ostream& operator<<(ostream& out,const t9_51_date& d){
    out << d.y() << "年" << d.m() << "月" << d.d() << "日" << endl;
    return out;
}
#endif