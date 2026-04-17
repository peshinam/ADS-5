// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int N>
class TStack {
private:
    T arr[N];
    int top;

public:
    TStack() {
        top = -1;
    }

    void push(T value) {
        if (top < N - 1) {
            top++;
            arr[top] = value;
        }
    }

    T pop() {
        if (top >= 0) {
            top--;
            return arr[top + 1];
        }
        return T();
    }

    T getTop() {
        if (top >= 0) {
            return arr[top];
        }
        return T();
    }

    bool isEmpty() {
        return top == -1;
    }
};

#endif  // INCLUDE_TSTACK_H_
