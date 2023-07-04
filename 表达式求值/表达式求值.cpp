#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 定义一个函数，用于计算两个数的加减乘除
double calc(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    default: throw runtime_error("Unknown operator: " + op);
    }
}

// 定义一个函数，用于计算一个中缀表达式的值
double eval(string expr) {
    stack<double> nums; // 存放数字的栈
    stack<char> ops; // 存放操作符的栈

    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        if (isdigit(ch)) { // 如果是数字
            double num = ch - '0';
            i++;
            while (i < expr.length() && isdigit(expr[i])) {
                num = num * 10 + (expr[i] - '0');
                i++;
            }
            i--;
            nums.push(num);
        }
        else if (ch == '(') { // 如果是左括号
            ops.push(ch);
        }
        else if (ch == ')') { // 如果是右括号
            while (ops.top() != '(') {
                double b = nums.top();
                nums.pop();
                double a = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                double res = calc(a, b, op);
                nums.push(res);
            }
            ops.pop(); // 弹出左括号
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') { // 如果是操作符
            while (!ops.empty() && (ops.top() == '*' || ops.top() == '/') && ch != '(') {
                double b = nums.top();
                nums.pop();
                double a = nums.top();
                nums.pop();
                char op = ops.top();
                ops.pop();
                double res = calc(a, b, op);
                nums.push(res);
            }
            ops.push(ch);
        }
        else {
            throw runtime_error("Invalid character: " + ch);
        }
    }

    while (!ops.empty()) { // 处理剩余的操作符
        double b = nums.top();
        nums.pop();
        double a = nums.top();
        nums.pop();
        char op = ops.top();
        ops.pop();
        double res = calc(a, b, op);
        nums.push(res);
    }

    return nums.top();
}

// 程序入口
int main() {
    string expr;
    cout << "**输入表达式：";
    getline(cin, expr);
    double res = eval(expr);
    cout <<"***表达式的值为："<< res;
    return 0;
}
