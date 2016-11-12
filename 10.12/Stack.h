#ifndef STACK_H
#define STACK_H

#include "vector.h"
#include <string>
#include <sstream>
#include <cstdio>
using std::string;
using std::stringstream;
using pep::vector;

// TODO: Your code for question 3 goes here

class Stack {
public:
    Stack() {
        stackData.clear();
    }
    bool empty() const {
        return stackData.empty();
    }
    void push(const double& value) {
        stackData.push_back(value);
    }
    double pop() {
        double topVal = stackData.back();
        stackData.pop_back();
        return topVal;
    }
private:
    vector<double> stackData;
};

double evaluate(const string& expr) {
    string token;
    stringstream ss(expr); //use stringstream to get tokens
    Stack stk;
    //evaluate the expression while getting tokens
    while(ss >> token) {
        if(token == "+") {
            double number2 = stk.pop();
            double number1 = stk.pop();
            stk.push(number1 + number2);
        } else if(token == "-") {
            double number2 = stk.pop();
            double number1 = stk.pop();
            stk.push(number1 - number2);
        } else if(token == "*") {
            double number2 = stk.pop();
            double number1 = stk.pop();
            stk.push(number1 * number2);
        } else if(token == "/") {
            double number2 = stk.pop();
            double number1 = stk.pop();
            stk.push(number1 / number2);
        } else {
            double number = stof(token);
            stk.push(number);
        }
    }
    double answer = stk.pop();
    return answer;
}

// Do not write anything below this line

#endif
