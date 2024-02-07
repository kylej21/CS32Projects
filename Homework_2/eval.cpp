#include <iostream>
#include<cassert>
#include<stack>
#include "Map.h"
using namespace std;
int getPrecedence(char c){
    if(c=='+'||c=='-'){
        return 1;
    }
    else if(c=='*'||c=='/'){
        return 2;
    }
    else{
        cout << "precedence called on nonOperator" <<endl;
        exit(1);
        return -1;
    }
}
bool isMapValid(string postfix, const Map& values){
    for(int i=0;i<postfix.length();i++){
        if(islower(postfix[i])){
            int number;
             // fetching the number from the map... If this evaluates to false then the Char is not in the map. 
            if(!values.get(postfix[i],number)){
                return false;
            }
        }
    }
    // if we made it this far, each char is successfully mapped
    return true;
}
bool isInfixValid(string initial){
    if(initial.length()<=1){
        return false;
    }

    
    
    return true;
}
int evaluate(string infix, const Map& values, string& postfix, int& result){
    if(!isInfixValid(infix)){
        return 1;
    }
    postfix="";
    stack<char> operators;
    for(int i=0;i<infix.length();i++){
        char ch=infix[i];
        if(islower(ch)){
            postfix+=ch;
        }
        else if(ch=='('){
            operators.push(ch);
        }
        else if(ch==')'){
            while(operators.top()!='('){
                postfix+=operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
            while(!operators.empty() && operators.top()!='(' && getPrecedence(ch)<=getPrecedence(operators.top())){
                postfix+=operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while(!operators.empty()){
        postfix+=operators.top();
        operators.pop();
    }
    // check Map AFTER all operators are updated
    if(!isMapValid(postfix,values)){
        return 2;
    }
    stack<int> operands;
    for(int i=0;i<postfix.length();i++){
        char ch = postfix[i];
        if(islower(ch)){
            int numVal;
            values.get(ch,numVal);
            operands.push(numVal);
        }else{
            char operand2=operands.top();
            operands.pop();
            if(operands.empty()){
                return 1;
            }
            char operand1=operands.top();
            operands.pop();
            if(ch=='+'){
                operands.push(operand1+operand2);
            }
            else if(ch=='-'){
                operands.push(operand1-operand2); // unsure if operand1-operand2 or o2-o1
            }
            else if(ch=='*'){
                operands.push(operand1*operand2);
            }
            else{
                if(operand2==0){
                    return 3;
                }
                operands.push(operand1/operand2);
            }
        }
    }
    result = operands.top();
    return 0;
}
int main(){
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = {  3,  -9,   6,   2,   4,   1  };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;
    assert(evaluate("a+ e", m, pf, answer) == 0  && pf == "ae+"  &&  answer == -6);
    answer = 999;
            assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
            //assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
            //  // unary operators not allowed:
            //assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a*b", m, pf, answer) == 2  &&
                                    pf == "ab*"  &&  answer == 999);
            assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0  &&
                                    pf == "yoau-*+"  &&  answer == -1);
            answer = 999;
            assert(evaluate("o/(y-y)", m, pf, answer) == 3  &&
                                    pf == "oyy-/"  &&  answer == 999);
            assert(evaluate(" a  ", m, pf, answer) == 0  &&
                                    pf == "a"  &&  answer == 3);
            assert(evaluate("((a))", m, pf, answer) == 0  &&
                                    pf == "a"  &&  answer == 3);
            cout << "Passed all tests" << endl;
}