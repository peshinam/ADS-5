// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include <cctype>
#include "tstack.h"

int priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

std::string infx2pstfx(const std::string& inf) {
    TStack<char, 100> stack;
    std::string result = "";

    for (size_t i = 0; i < inf.length(); i++) {
        char c = inf[i];

        if (isdigit(c)) {
            while (i < inf.length() && isdigit(inf[i])) {
                result = result + inf[i];
                i++;
            }
            result = result + ' ';
            i--;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.getTop() != '(') {
                result = result + stack.pop();
                result = result + ' ';
            }
            if (!stack.isEmpty() && stack.getTop() == '(') {
                stack.pop();
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            while (!stack.isEmpty() && stack.getTop() != '(' &&
                   priority(stack.getTop()) >= priority(c)) {
                result = result + stack.pop();
                result = result + ' ';
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        result = result + stack.pop();
        result = result + ' ';
    }

    if (result.length() > 0 && result[result.length() - 1] == ' ') {
        result.resize(result.length() - 1);
    }

    return result;
}

int eval(const std::string& post) {
    TStack<int, 100> stack;

    for (size_t i = 0; i < post.length(); i++) {
        char c = post[i];

        if (isdigit(c)) {
            int number = 0;
            while (i < post.length() && isdigit(post[i])) {
                number = number * 10 + (post[i] - '0');
                i++;
            }
            stack.push(number);
            i--;
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int b = stack.pop();
            int a = stack.pop();
            int res = 0;

            if (c == '+') {
                res = a + b;
            } else if (c == '-') {
                res = a - b;
            } else if (c == '*') {
                res = a * b;
            } else if (c == '/') {
                res = a / b;
            }

            stack.push(res);
        }
    }

    return stack.pop();
}
