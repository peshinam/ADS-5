// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int getPriority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result;

    for (size_t i = 0; i < inf.length(); ++i) {
        char c = inf[i];

        if (c == ' ') continue;

        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result += inf[i];
                ++i;
            }
            result += ' ';
            --i;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.empty() && stack.top() != '(') {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            if (!stack.empty() && stack.top() == '(') {
                stack.pop();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.empty() && stack.top() != '(' && 
                   getPriority(stack.top()) >= getPriority(c)) {
                result += stack.top();
                result += ' ';
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.empty()) {
        result += stack.top();
        result += ' ';
        stack.pop();
    }

    if (!result.empty() && result.back() == ' ') {
        result.pop_back();
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.length(); ++i) {
        char c = post[i];

        if (c == ' ') continue;

        if (isdigit(c)) {
            int num = 0;
            while (i < post.length() && isdigit(post[i])) {
                num = num * 10 + (post[i] - '0');
                ++i;
            }
            stack.push(num);
            --i;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            if (stack.empty()) return 0;
            int b = stack.top();
            stack.pop();

            if (stack.empty()) return 0;
            int a = stack.top();
            stack.pop();

            int result = 0;
            switch (c) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': 
                    if (b != 0) result = a / b;
                    else return 0;
                    break;
            }
            stack.push(result);
        }
    }

    if (stack.empty()) return 0;
    return stack.top();
}
