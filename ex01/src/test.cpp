#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>

int evaluateRPN(const std::string& expression) {
    std::istringstream iss(expression);
    std::stack<int> stack;
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            int operand2 = stack.top(); stack.pop();
            int operand1 = stack.top(); stack.pop();

            switch (token[0]) {
                case '+': stack.push(operand1 + operand2); break;
                case '-': stack.push(operand1 - operand2); break;
                case '*': stack.push(operand1 * operand2); break;
                case '/': stack.push(operand1 / operand2); break;
            }
        } else {
            stack.push(std::stoi(token));
        }
    }

    return stack.top();
}

int main(int ac, char av) {
    std::string rpnExpression = "8 9 * 9 - 9 - 9 - 4 - 1 +";
    std::cout << "The result of the RPN expression is: " << evaluateRPN(rpnExpression) << std::endl;

    return 0;
}
