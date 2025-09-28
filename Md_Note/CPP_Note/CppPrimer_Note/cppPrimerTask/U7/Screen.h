 #ifndef SCREEN_H
 #define SCREEN_H
#include<iostream>
#include<string>

class Screen
{
friend class Window_mgr;
public:
using pos=std::string::size_type;

Screen()=default;
Screen(pos hei,pos wid):height(hei),width(wid),contents(hei*wid,' '){}
Screen(pos hei,pos wid,char c):height(hei),width(wid),contents(hei*wid,c){}

char get(){return contents[cursor];}
char get(pos r,pos c){return contents[r*width+c];}
Screen &set(pos ,pos ,char );
Screen &set(char );
Screen &move(pos r,pos c);
Screen &display(std::ostream &os){do_display(os); return *this;}
const Screen &display(std::ostream &os) const {do_display(os); return *this;}
pos size() const{return height*width;}

private:
    pos height=0,width=0;
    pos cursor=0;
    std::string contents;
    void do_display(std::ostream &os) const {os<<contents;}
   
};
Screen & Screen::set(char c){
  contents[cursor]=c;
  return *this;
}

Screen & Screen::set(pos r,pos col,char c){
  contents[r*width+col]=c;
  return *this;
}

Screen & Screen::move(pos r,pos c){//类外定义成员函数: 函数名需要声明匹配
  pos pow=r*width;
  cursor =pow+c;
  return *this;
}


 #endif//SCREEN_H