#ifndef OPZ_FROM_JAVA_OPZ_H
#define OPZ_FROM_JAVA_OPZ_H

#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
using namespace std;
class ExpressionParser{
private:
    string operators = "+-*/";
    string delimiters = "() " + operators;
public:
    bool flag =true ;
    bool isDelimiter(string token); //проаерка на разделитель
    bool isOperator(string token); // проверка на оператора
    int priority(string token); // узнает приоритеты
    list<string> parse(string infix); // храниться строка на вход
};
class Calculator{
public:
    double calc(list<string> postfix);

};


#endif //OPZ_FROM_JAVA_OPZ_H
