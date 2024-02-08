#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;
int getPrecedence(char c)
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    else
    {
        exit(1);
        return -1;
    }
}
bool isMapValid(string postfix, const Map &values)
{
    for (int i = 0; i < postfix.length(); i++)
    {
        if (islower(postfix[i]))
        {
            int number;
            // fetching the number from the map... If this evaluates to false then the Char is not in the map.
            if (!values.get(postfix[i], number))
            {
                return false;
            }
        }
    }
    // if we made it this far, each char is successfully mapped
    return true;
}
bool isInfixValid(string rawInitial)
{   
    // replacing whitespace since it is ignored
    string initial="";
    for(int i=0;i<rawInitial.length();i++){
        if(rawInitial[i]!=' '){
            initial+=rawInitial[i];
        }
    }
    // checking valid strings length
    if (initial.length() == 0)
    {
        return false;
    }
    if (initial.length() == 1)
    {
        if(islower(initial[0])){
            return true;
        }
        return false;
    }
    // checking valid parenthesis and invalid chars
    stack<char> parens;
    for (int i = 0; i < initial.length(); i++)
    {
        if (initial[i] == '(')
        {
            parens.push('(');
        }
        else if (initial[i] == ')')
        {
            if (parens.empty())
            {

                return false;
            }
            else
            {
                parens.pop();
            }
        }
        else if (!islower(initial[i]) && initial[i] != '+' && initial[i] != '-' && initial[i] != '*' && initial[i] != '/' && initial[i] != ' ')
        {
            return false;
        }
    }
    if (!parens.empty())
    {
        return false;
    }
    for(int i=0;i<initial.length();i++){
        if(initial[i]==' '){
            continue;
        }
        //handles start
        if(i==0){
            if(initial[i]=='+'||initial[i]=='-'||initial[i]=='*'||initial[i]=='/'||initial[i]==')'){
                return false;
            }
            if(islower(initial[i])){
                if(initial[i+1]=='('||initial[i+1]==')'||islower(initial[i+1])){
                    return false;
                }
            }
            if(initial[i]=='('){
                if(initial[i+1]==')'){
                    return false;
                }
            }
        }
        //handles end
        else if(i==initial.length()-1){
            if(initial[i]=='+'||initial[i]=='-'||initial[i]=='*'||initial[i]=='/'||initial[i]=='('){
                return false;
            }
            return true;
        }
        //handles middle
        if(islower(initial[i])){
            if(islower(initial[i+1])||initial[i]=='('){
                
                return false;
            }
        }
        else if(initial[i]=='+'||initial[i]=='-'||initial[i]=='*'||initial[i]=='/'){
            if(initial[i+1]=='+'||initial[i+1]=='-'||initial[i+1]=='*'||initial[i+1]=='/'||initial[i+1]==')'){
                return false;
            }
        }
        else if(initial[i]=='('){
            if(initial[i+1]=='+'||initial[i+1]=='-'||initial[i+1]=='*'||initial[i+1]=='/'||initial[i+1]==')'){
                return false;
            }
        }
         else if(initial[i]==')'){
            if(islower(initial[i+1])||initial[i+1]=='('){
                return false;
            }
        }
        
    }
    return true;
}
int evaluate(string infix, const Map &values, string &postfix, int &result)
{
    if (!isInfixValid(infix))
    {
        return 1;
    }
    postfix = "";
    stack<char> operators;
    for (int i = 0; i < infix.length(); i++)
    {
        char ch = infix[i];
        if (islower(ch))
        {
            postfix += ch;
        }
        else if (ch == '(')
        {
            operators.push(ch);
        }
        else if (ch == ')')
        {
            while (operators.top() != '(')
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/')
        {
            while (!operators.empty() && operators.top() != '(' && getPrecedence(ch) <= getPrecedence(operators.top()))
            {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty())
    {
        postfix += operators.top();
        operators.pop();
    }
    // check Map AFTER all operators are updated
    if (!isMapValid(postfix, values))
    {
        return 2;
    }
    stack<int> operands;
    for (int i = 0; i < postfix.length(); i++)
    {
        char ch = postfix[i];
        if (islower(ch))
        {
            int numVal;
            values.get(ch, numVal);
            operands.push(numVal);
        }
        else
        {
            char operand2 = operands.top();
            operands.pop();
            if (operands.empty())
            {
                return 1;
            }
            char operand1 = operands.top();
            operands.pop();
            if (ch == '+')
            {
                operands.push(operand1 + operand2);
            }
            else if (ch == '-')
            {
                operands.push(operand1 - operand2); // unsure if operand1-operand2 or o2-o1
            }
            else if (ch == '*')
            {
                operands.push(operand1 * operand2);
            }
            else
            {
                if (operand2 == 0)
                {
                    return 3;
                }
                operands.push(operand1 / operand2);
            }
        }
    }
    result = operands.top();
    return 0;
}
int main()
        {
            char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
            int  vals[] = {  3,  -9,   6,   2,   4,   1  };
            Map m;
            for (int k = 0; vars[k] != '#'; k++)
                m.insert(vars[k], vals[k]);
            string pf;
            int answer;
            assert(evaluate("a+ e", m, pf, answer) == 0  &&
                                    pf == "ae+"  &&  answer == -6);
            answer = 999;
            assert(evaluate("", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a+", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a i", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("ai", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("()", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("()o", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("y(o+u)", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("y(*o)", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("a+E", m, pf, answer) == 1  &&  answer == 999);
            assert(evaluate("(a+(i-o)", m, pf, answer) == 1  &&  answer == 999);
              // unary operators not allowed:
            assert(evaluate("-a", m, pf, answer) == 1  &&  answer == 999);
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