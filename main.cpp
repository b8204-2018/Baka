#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <vector>
#include <stack>
#include <exception>

using namespace std;

class Reader {
public:

    int ExampleFormat(string path) {
        size_t ex_form;
        ifstream myFile(path);
        if (myFile.is_open()) {
            myFile >> ex_form;
            myFile.close();
            return ex_form;
        } else {
            cout << "File not found!";
            myFile.close();
        }

    };

    string Example(string path) {

        string takeExample;
        ifstream myFile(path);
        const int maxStringLengh = 20;
        int numStringsToSkip = 1; //кол-во пропускамых строк перед чтением
        if (myFile.is_open()) {
            for (int i = 0;
                 i < numStringsToSkip; i++) // пропускаем не нужные нам строки (читаем и ничего с ними не делаем)
            {
                char *tmp = new char[maxStringLengh];
                myFile.getline(tmp, maxStringLengh);
                delete[] tmp;
            }
            myFile >> takeExample;
            myFile.close();
            return takeExample;
        } else {
            cout << "File not found!";
            myFile.close();
        }
    }


};

class Parser {
public:
    double *ParseringNumbs(string example) {
        size_t length_ex = example.length();
        double *result = new double[length_ex];
        int num = 0;
        bool neg = false;
        string sty;
        int i = 0, j = 0;
        for (int k = 0; k < length_ex; k++) {
            result[k] = 0;
        }

        while ((i < length_ex)) {
            if (isdigit(example[i]) && i > 0) {

                if (example[i - 1] == '-') {
                    neg = true;
                }
            }

            while (isdigit(example[i])) {
                i++;
            }
            if (i > j) {
                sty = example.substr(j, i - j);
                if (neg == false) {
                    result[num] = stof(sty);
                } else {
                    result[num] = stof(sty)*(-1);
                    neg=false;
                }
                num++;
            } else if (example[i] == 'x') {

                result[num] = 1;
                num++;
            }
            if ((example[i] == 'x') && (isdigit(example[i + 1]))) {
                i += 2; //перепрыгиваем икс и степень
            } else i++;
            j = i;
        }

        return result;
    }

};

class Tasks {
public:
    virtual double *calculateTask(double *var) = 0;
};

class FirstTask : public Tasks {
public:
    double *calculateTask(double *var) override {
        double *solve = new double[3];

        if ((var[1] * var[1] - 4 * var[0] * var[2]) >= 0) {
            solve[0] = (-1 * var[1] + sqrt(var[1] * var[1] - 4 * var[0] * var[2])) / (2 * var[0]);
            solve[1] = (-1 * var[1] - sqrt(var[1] * var[1] - 4 * var[0] * var[2])) / (2 * var[0]);
        } else {
            return nullptr;

        }
        return solve;
    }
};

class SecondTask : public Tasks {
public:
    double *calculateTask(double *var) override {
        double *solve = new double[2];
        solve[0] = (var[0] + var[1]);
        return solve;
    }
};

class ThirdTask : public Tasks {
public:
    double *calculateTask(double *var) override {
        double *solve = new double[2];
        if (var[1]>0){
            solve[0] = (var[0] - var[1]);
        } else {
            solve[0] = (var[0] + var[1]);
        }
        return solve;
    }
};

class FourthTask : public Tasks {
public:
    double *calculateTask(double *var) override {
        double *solve = new double[2];
        solve[0] = (var[0] * var[1]);
        return solve;
    }
};

class FifthTask : public Tasks {
public:
    double *calculateTask(double *var) override {
        double *solve = new double[2];
        solve[0] = (var[0] / var[1]);
        return solve;
    }
};

class SolutionsLib {
private:
    vector<Tasks *> allSolutions;
public:
    void addSolution(Tasks *solution) {
        allSolutions.push_back(solution);
    }

    Tasks *returnSolution(int exNumb) {
        return allSolutions[exNumb - 1];
    }
};

class Printer {
public:
    void print(double *result, int ex_numb, string exprestion) {
        if (ex_numb == 1) {
            cout << exprestion << endl;
            if (result == nullptr) {
                cout << "Net kornei" << endl;
            } else {
                cout << "x1 = " << result[0] << endl << "x2 = " << result[1] << endl;
            }
        } else {
            if (result == nullptr) {
                cout << "Net reshenii" << endl;
            } else {
                cout << exprestion << " = " << result[0] << endl;
            }
        };
    }

};

class Calculator {
    SolutionsLib *solutionsLib;
    Reader reader;
    Printer printer;
    Parser parser;
public:
    Calculator(SolutionsLib *solutionsLib, Reader reader, Printer printer, Parser parser)
            : solutionsLib(solutionsLib), reader(reader), printer(printer), parser(parser) {
    }

    Tasks *setSolution(string str) {
        size_t exNumb = reader.ExampleFormat(str);
        return solutionsLib->returnSolution(exNumb);
    }

    void calcSolution(string str) {
        Tasks *exSolution;
        exSolution = setSolution(str);
        double *answ = exSolution->calculateTask(parser.ParseringNumbs(reader.Example(str)));
        printer.print(answ, reader.ExampleFormat(str), reader.Example(str));
    }
};

int main() {
    Reader readFile;
    Printer printer;
    Parser parser;
    string path1 = "d:\\ProgramData\\Projects\\primer\\files\\first.txt";
    string path2 = "d:\\ProgramData\\Projects\\primer\\files\\second.txt";
    string path3 = "d:\\ProgramData\\Projects\\primer\\files\\third.txt";
    string path4 = "d:\\ProgramData\\Projects\\primer\\files\\fourth.txt";
    string path5 = "d:\\ProgramData\\Projects\\primer\\files\\fifth.txt";

    FirstTask exam1;
    SecondTask exam2;
    ThirdTask exam3;
    FourthTask exam4;
    FifthTask exam5;

    SolutionsLib solutionsLib;

    solutionsLib.addSolution(&exam1);
    solutionsLib.addSolution(&exam2);
    solutionsLib.addSolution(&exam3);
    solutionsLib.addSolution(&exam4);
    solutionsLib.addSolution(&exam5);

    Calculator calculator(&solutionsLib, readFile, printer, parser);
    calculator.calcSolution(path1);
    calculator.calcSolution(path2);
    calculator.calcSolution(path3);
    calculator.calcSolution(path4);
    calculator.calcSolution(path5);

    return 0;
}