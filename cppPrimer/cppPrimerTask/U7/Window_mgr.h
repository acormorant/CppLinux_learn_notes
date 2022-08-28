#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H
#include<vector>
#include"Screen.h"
class Window_mgr
{
public:
 using ScreenIndex = std::vector<Screen>::size_type;
 void clear(ScreenIndex);

private:
    //默认情况下,一个window_mgr包含一个标准尺寸的空白Screen
    std::vector<Screen> screens{screen(24,80)};
    
};
void Window_mgr::clear(ScreenIndex i){
    Screen &s =screens[i];
    //s为引用,指向我们想清空的那个screen
    s.contents=std::string(s.height*s.width,' ');
}

#endif//WIDOW_MGR_H