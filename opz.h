#ifndef OPZ_FROM_JAVA_OPZ_H
#define OPZ_FROM_JAVA_OPZ_H
#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
#include <vector>
using namespace std;
class Operator{
protected:
    char name;
    int priority;
public:
    Operator(const char a,int b){
        name=a;
        priority=b;
    }
    char get_name(){
        return name;
    }
    int get_priority(){
        return priority;
    }

    double calc(double a, double b){

    }
};
class ExpressionParser{
private:
    vector<Operator> operators;
    string delimiters = "() ";
public:
    bool flag =true ;
    bool isDelimiter(string token);
    bool isOperator(string token);
    int priority(string token);
    list<string> parse(string infix);
};
class Calculator{
public:
    vector<Operator> operators;
    double calc(list<string> postfix);

};


#endif //OPZ_FROM_JAVA_OPZ_H