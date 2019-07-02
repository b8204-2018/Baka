#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
#include "opz.h"

using namespace std;

bool ExpressionParser::isDelimiter(string token) {
    if (token.length() != 1) return false;
    for (int i = 0; i < delimiters.length(); i++) {
        if (token[0] == delimiters[i]) return true;
    }
    for(int i = 0 ; i<operators.size();i++){
        if (token[0] == operators[i].get_name())return true;
    }
    return false;
}

bool ExpressionParser::isOperator(string token) {
    for (int i = 0; i < operators.size(); i++) {
        if (token[0] == operators[i].get_name()) return true;
    }
    return false;
}

int ExpressionParser::priority(string token) {
    if (token == "(") return 1;
    for (int i = 0; i < operators.size() ; ++i) {
        if(token[0] == operators[i].get_name()){ return operators[i].get_priority();}
    }
    return 4;
}

list<string> ExpressionParser::parse(string infix) {
    Operator add('+', 2);
    Operator sub('-', 2);
    Operator adub('~', 2);
    Operator mul('*', 3);
    Operator div('/', 3);
    operators.push_back(add);
    operators.push_back(sub);
    operators.push_back(adub);
    operators.push_back(mul);
    operators.push_back(div);
    list<string> postfix;
    deque<string> stack1;
    string prev = "";
    string currs;

    int i = 0;
    int count_digit = 0;
    int count_operations = 0;

    char curr = infix[i];
    while (curr != 0) {
        curr = infix[i];
        i++;
        if (isOperator(prev) && isOperator(currs.assign(1, curr))) {
            flag = false;
            throw logic_error("Некорректное выражение.");
        }
        if (curr == 0)continue;
        if (currs.assign(1, curr) == " ") continue;
        if (isDelimiter(currs.assign(1, curr))) {
            if (currs.assign(1, curr) == "(") {
                stack1.push_back(currs.assign(1, curr));
                count_operations--;
            }
            else if (currs.assign(1, curr) == ")") {
                count_operations--;
                while (stack1.front() != "(") {
                    postfix.push_back(stack1.front());
                    stack1.pop_front();
                    if (stack1.size() == 0) {
                        flag = false;
                        throw logic_error("Скобки не согласованы.");
                    }
                }
                stack1.pop_front();
            } else {


                while ((stack1.size() != 0) && (priority(currs.assign(1, curr)) <= priority(stack1.front()))) {
                    postfix.push_back(stack1.front());
                    stack1.pop_front();
                }


                stack1.push_front(currs.assign(1, curr));
            }
            count_operations++;
        } else {
            postfix.push_back(currs.assign(1, curr));
            count_digit++;
        }
        prev = curr;
    }


    while (stack1.size() != 0) {
        if (isOperator(stack1.front())) {
            postfix.push_back(stack1.front());
            stack1.pop_front();
        } else {
            flag = false;
            throw logic_error("Скобки не согласованы.");


        }
    }
    if (count_operations + 1 == count_digit) {
        return postfix;
    }
    throw logic_error("Некорректное выражение.");
}


double Calculator::calc(list<string> postfix) {
    stack<double> stack;
    for (string x : postfix) {
        for (int i = 0; i < operators.size() ; ++i) {
            if(x[0] ==operators[i].get_name() ){
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(operators[i].calc(a,b));

            }
        }
        if (x.c_str() != NULL) {
            if (x == ("+")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(a + b);
            } else if (x == ("-")) {
                double b = stack.top();
                stack.pop();
                double a = stack.top();
                stack.push(a - b);
            } else if (x == ("*")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                stack.push(a * b);
            } else if (x == ("/")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                if (a != 0) {
                    stack.push(b / a);
                } else {
                    throw logic_error("Деление на ноль.");
                }
            } else if (x == ("~")) {
                double a = stack.top();
                stack.pop();
                double b = stack.top();
                stack.pop();
                if (b > a) {
                    stack.push(b - a);
                } else {
                    stack.push(b + a);
                }
            } else stack.push(stod(x));
        }
    }
    double result = stack.top();
    stack.pop();
    return result;
}

