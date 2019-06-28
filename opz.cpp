#include <iostream>
#include <stack>
#include <string.h>
#include <cstdlib>
#include <list>
#include <deque>
#include "opz.h"

using namespace std;

// curr = текущ элент в виде char
// currs = текущ элент в виде string

bool ExpressionParser::isDelimiter(string token) {
    if (token.length() != 1) return false; // проверка на двойную операцию
    for (int i = 0; i < delimiters.length(); i++) {
        if (token[0] == delimiters[i]) return true; // token = массив с разделителями
    }
    return false;
}

bool ExpressionParser::isOperator(string token) {
    for (int i = 0; i < operators.length(); i++) {
        if (token[0] == operators[i]) return true;
    }
    return false;
}

int ExpressionParser::priority(string token) { // смотрим приоритеты
    if (token == "(") return 1;
    if ((token == "+") || (token == "-")) return 2;
    if ((token == "*") || (token == "/")) return 3;
    return 4;
}

list<string> ExpressionParser::parse(string infix) {
    list<string> postfix; // создаем лист string'of
    deque<string> stack1; // сохдаем очередь для операций
    string prev = "";

    string currs;
    int i = 0;

    char curr = infix[i]; // проверка каждого элемента строки
    while (curr != 0) {
        curr = infix[i];
        i++;
        if (isOperator(prev) && isOperator(currs.assign(1, curr))) { // если предыдущий и текущий сымволы операторы, то ошибка
            flag = false;
            throw logic_error("Некорректное выражение.");
        }

        // continue - если условие соблюдено, то возвращается в начало цикла

        if (curr == 0)continue;
        if (currs.assign(1, curr) == " ") continue;       // копируем один элем. curr в currs и сравниваем с " "
        if (isDelimiter(currs.assign(1, curr))) {                                                  // копируем один элем. curr в currs и проверяем на разделитель
            if (currs.assign(1, curr) == "(") stack1.push_back(currs.assign(1, curr));  // проверка на скобки
            else if (currs.assign(1, curr) == ")") {
                while (stack1.front() != "(") {
                    postfix.push_back(stack1.front()); // убираем эл-т сверху
                    stack1.pop_front();
                    if (stack1.size() == 0) {
                        flag = false;
                        throw logic_error("Скобки не согласованы.");
                    }
                }
                stack1.pop_front();
            }
            else {
                while ((stack1.size() != 0) && (priority(currs.assign(1, curr)) <= priority(stack1.front()))) {
                    postfix.push_back(stack1.front());
                    stack1.pop_front();
                }

                stack1.push_front(currs.assign(1, curr));
            }

        } else {
            string buff = ""; // временная буферная строка для n-значных чисед
            while (isdigit(curr) != false) {
                buff += curr;
                curr = infix[i];
                i++;
            }
            postfix.push_back(buff);
        }
        prev = curr;
    }


    while (stack1.size() != 0) {  //проверяет, не осталось ли ничего лишнего в строке
        if (isOperator(stack1.front())) {
            postfix.push_back(stack1.front());
            stack1.pop_front();
        } else {
            cout << "Скобки не согласованы.";
            flag = false;
            return postfix;
        }
    }
    return postfix;
}


double Calculator::calc(list<string> postfix) {
    stack<double> stack;
    for (string x : postfix) {  //for each - проходим по всем объектам класса (x - каждый элемент постфикса)
        const char *buff = x.c_str(); // c_str превращает string в const char* (для дебага)
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

                stack.push(b / a);
            } else stack.push(stod(x)); //srt to double - последний элемент строки окажется в стеке
        }
    }
    double result = stack.top();
    stack.pop();
    return result;
}

