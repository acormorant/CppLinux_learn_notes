//设运算符只有加减法和括号以减少优先级处理的步骤
/*
1．读入了一个运算数v。
a）若栈空或栈顶是左括号，则v是第一个运算数，直接压栈即可。
b）否则，v前必须是一个运算符，再之前是另一个运算数v＇，从栈顶弹出这两项，将计算结果压栈即可；否则，就抛出一个“缺少运算符”异常。

2．读入了一个左括号，直接压栈。

3．读入了一个运算符，
a）若栈空或栈顶不是一个运算数，则抛出一个“缺少运算数”异常。注意，若运算符之前是一个右括号，之前也已处理完毕，栈顶是其计算结果，仍应该是运算数，不影响此逻辑。
b）否则，运算符压栈。

4．读入了一个右括号，
a）若栈空，表明之前没有与之配对的左括号，抛出“未匹配右括号”异常。
b）若栈顶是左括号，表明括号对之间无表达式，抛出“空括号”异常。
c）若栈顶不是运算数，表明括号内缺少一个运算数，抛出一个异常。
d）**弹出此运算数 v，若栈空或栈顶不是左括号，仍抛出“未匹配右括号”异常：否则弹出左括号，把v作为新运算数，执行1中的逻辑**
(边输入边计算,所以输入右括号时若无异常括号内运算已结束,栈顶只剩一个运算数)。

5．以上均不是，则出现了非法输入，会在转换为数值时产生异常。

6．当字符串处理完毕后，判断栈中是否有且仅有一个运算数，若是，此值即为表达式运算结果，输出它；否则，表达式非法。

**值得注意的是，为了在栈中保存括号、运算符和运算数三类对象，程序中定义了枚举类型obj＿type。栈中每个对象都保存了类型t和数值v**（如果t是VAL的话）。
*/
#include<iostream>
#include<deque>
#include<stack>
#include<string>
using namespace std;

enum obj_type{LP,RP,ADD,SUB,VAL};
struct obj
{
   obj(obj_type type,double value=0){t=type;v=value;} 
   obj_type t;
   double   v; 
};

inline void skipws(string& s,string::size_type& p){
   p = s.find_first_not_of(" ",p);
}

inline void new_val(stack<obj> &so,double v){
//a）若栈空或栈顶是左括号，则v是第一个运算数，直接压栈即可。
//b）否则，v前必须是一个运算符，再之前是另一个运算数v，从栈顶弹出这两项，将计算结果压栈即可；否则，就抛出一个“缺少运算符”异常。
   if( so.empty() || so.top().t == LP){          //空栈或左括号 !!!判断空栈必须在前否则向空栈运行so.top().t == LP语句会导致程序异常退出且不报错!!! 
      so.push(obj(VAL,v));
      cout << "push " << v <<endl;
   }
   else if(so.top().t == ADD|| so.top().t == SUB){
      obj_type type = so.top().t;
      so.pop();
      //if(so.top().t != VAL)throw  多余;运算符前是否是运算数 的判断应该交给运算符入栈时代码段
      if(type == ADD){
        cout << "pop +" <<endl;
        cout << "pop " <<so.top().v <<endl;
        v +=so.top().v;
        so.pop();
        so.push(obj(VAL,v)); 
        cout << "push "<< v <<endl;
      }
      else{
        cout << "pop -" <<endl;
        cout << "pop " <<so.top().v <<endl;
        v =so.top().v - v;
        so.pop();
        so.push(obj(VAL,v)); 
        cout << "push "<< v <<endl;
      }
   }
   else{
      throw invalid_argument("缺少运算符");
   }
}

int main(){
/*
1．读入了一个运算数v。
a）若栈空或栈顶是左括号，则v是第一个运算数，直接压栈即可。
b）否则，v前必须是一个运算符，再之前是另一个运算数v＇，从栈顶弹出这两项，将计算结果压栈即可；否则，就抛出一个“缺少运算符”异常。

2．读入了一个左括号，直接压栈。

3．读入了一个运算符，
a）若栈空或栈顶不是一个运算数，则抛出一个“缺少运算数”异常。注意，若运算符之前是一个右括号，之前也已处理完毕，栈顶是其计算结果，仍应该是运算数，不影响此逻辑。
b）否则，运算符压栈。

4．读入了一个右括号，
a）若栈空，表明之前没有与之配对的左括号，抛出“未匹配右括号”异常。
b）若栈顶是左括号，表明括号对之间无表达式，抛出“空括号”异常。
c）若栈顶不是运算数，表明括号内缺少一个运算数，抛出一个异常。
d）**弹出此运算数 v，若栈空或栈顶不是左括号，仍抛出“未匹配右括号”异常：否则弹出左括号，把v作为新运算数，执行1中的逻辑**
(边输入边计算,所以输入右括号时若无异常括号内运算已结束,栈顶只剩一个运算数)。

5．以上均不是，则出现了非法输入，会在转换为数值时产生异常。

6．当字符串处理完毕后，判断栈中是否有且仅有一个运算数，若是，此值即为表达式运算结果，输出它；否则，表达式非法。

**值得注意的是，为了在栈中保存括号、运算符和运算数三类对象，程序中定义了枚举类型obj＿type。栈中每个对象都保存了类型t和数值v**（如果t是VAL的话）。
*/
stack<obj> so;
string exp;
string::size_type p=0;
string::size_type q;
double v;

cout << "请输入表达式:  ";
getline(cin,exp);

while (p < exp.size())
{   
    skipws(exp, p);
    if(exp[p] == '('){
        so.push(obj(LP));
        cout << "push (" <<endl;
        p++;
    }
    else if(exp[p] == '+'||exp[p] == '-'){
        if(so.top().t !=VAL || so.empty()){ //空栈或之前不是运算数
            throw invalid_argument("缺少运算数");
        }

        if(exp[p] == '+'){
            so.push(obj(ADD));
            cout << "push +" <<endl;
            p++;
        }else{
            so.push(obj(SUB));
            cout << "push -" <<endl;
            p++;
        }

    }
    else if(exp[p] == ')'){
        p++;
        if(so.empty()){
            throw invalid_argument("未配对右括号");
        }
        if(so.top().t == LP){
            throw invalid_argument("空括号");
        }
        if(so.top().t != VAL ){
            throw invalid_argument("缺少运算数");
        }
        v = so.top().v;
        so.pop();
        cout << "pop "<< v <<endl;
        if(so.top().t != LP|| so.empty()){
            throw invalid_argument("未配对右括号");
        }
        so.pop();
        cout << "pop (" <<endl;
        //so.push(obj(VAL,v)); 可能有其他错误
        new_val(so,v);
    }
    else{
        v = stod(exp.substr(p),&q);//返回 子串 的起始子串的数值。参数 p 用来保存 从下标p开始的子串 中第一个非数值字符的下标，默认为 0，即不保存下标。
        p += q; 
        new_val(so,v);
    }
}
    //字符串处理完毕后，判断栈中是否有且仅有一个运算数，若是，此值即为表达式运算结果，输出它；否则，表达式非法。
    if(so.empty() || so.size()!= 1 || so.top().t != VAL){
        throw invalid_argument("表达式非法");
    }
    cout << "表达式结果: " << so.top().v <<endl;
    return 0;
}


















