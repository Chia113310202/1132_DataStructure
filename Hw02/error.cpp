#include <iostream>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;
public:
    Stack() { top = nullptr; }
    void push(char ch) {
        Node* newNode = new Node();
        newNode->data = ch;
        newNode->next = top;
        top = newNode;
    }
    char pop() {
        if (top == nullptr) {
            cout << "堆疊為空，無法取出元素。\n";
            return '\0';
        }
        char poppedValue = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return poppedValue;
    }
    char peek() {
        return (top == nullptr) ? '\0' : top->data;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};

struct DoubleNode {
    double data;
    DoubleNode* next;
};

class IntStack {
private:
    DoubleNode* top;
public:
    IntStack() { top = nullptr; }
    void push(double val) {
        DoubleNode* newNode = new DoubleNode();
        newNode->data = val;
        newNode->next = top;
        top = newNode;
    }
    double pop() {
        if (top == nullptr) return 0;
        double value = top->data;
        DoubleNode* temp = top;
        top = top->next;
        delete temp;
        return value;
    }
    bool isEmpty() {
        return top == nullptr;
    }
};

void finalInfix(char* infix, int size) {
    char temp[100]; 
    cin.getline(temp, 100);
    int j = 0;
    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] != ' ') {
            infix[j++] = temp[i];
        }
    }
    infix[j] = '\0';
}

bool checkParentheses(const char* infix) {
    int count = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(') count++;
        else if (infix[i] == ')') {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

bool CheckOperator(const char* infix) {
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != '^' && c != '.' && c != ' ' && c != '(' && c != ')') {
            return false;
        }
    }
    return true;
}

bool CheckOperatornum(const char* infix) {
    int opnum = 0, nunum = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {
            if (c == '-' && (i == 0 || infix[i - 1] == '(')) continue;
            opnum++;
        }
        else if (isdigit(c) || (c == '-' && (i == 0 || infix[i - 1] == '(') && isdigit(infix[i + 1]))) {
            nunum++;
            if (infix[i] == '-') i++;
            bool hasDot = false;
            while (isdigit(infix[i]) || infix[i] == '.') {
                if (infix[i] == '.') {
                    if (hasDot || i == 0 || !isdigit(infix[i - 1]) || !isdigit(infix[i + 1]) || infix[i + 1] == '.')
                        return false;
                    hasDot = true;
                }
                i++;
            }
            i--;
        } else if (infix[i] == '.') {
            if (i == 0 || !isdigit(infix[i - 1]) || !isdigit(infix[i + 1]) || infix[i + 1] == '.') return false;
        }
    }
    return opnum == nunum - 1;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

void InfixToPostfix(const char* infix, char* postfix) {
    Stack stack;
    int j = 0;
    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];
        if (isalnum(c) || (c == '-' && (i == 0 || infix[i - 1] == '('))) {
            if (infix[i] == '-') {
                postfix[j++] = c;
                i++; c = infix[i];
            }
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = c;
                i++; c = infix[i];
            }
            postfix[j++] = ' ';
            i--;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty()) {
                char top = stack.pop();
                if (top == '(') break;
                postfix[j++] = top; postfix[j++] = ' ';
            }
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)) {
                postfix[j++] = stack.pop(); postfix[j++] = ' ';
            }
            stack.push(c);
        }
    }
    while (!stack.isEmpty()) {
        postfix[j++] = stack.pop(); postfix[j++] = ' ';
    }
    postfix[j] = '\0';
}

double evaluatePostfix(const char* postfix) {
    IntStack stack;
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isdigit(c) || (c == '-' && (i == 0 || postfix[i - 1] == ' '))) {
            double num = 0; bool isNegative = false;
            if (postfix[i] == '-') { isNegative = true; i++; }
            while (isdigit(postfix[i])) { num = num * 10 + (postfix[i] - '0'); i++; }
            if (postfix[i] == '.') {
                i++;
                char n = postfix[i];
                double decimal = 0, place = 0.1;
                while (isdigit(n)) {
                    decimal += (n - '0') * place;
                    place *= 0.1;
                    i++; n = postfix[i];
                }
                num += decimal;
            }
            if (isNegative) num = -num;
            stack.push(num); i--;
        } else if (c == ' ') continue;
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
            double b = stack.pop(), a = stack.pop();
            if (c == '+') stack.push(a + b);
            else if (c == '-') stack.push(a - b);
            else if (c == '*') stack.push(a * b);
            else if (c == '/') stack.push(a / b);
            else if (c == '^') stack.push(pow(a, b));
            else if (c == '%') stack.push(fmod(a, b));
        }
    }
    return stack.pop();
}

int main() {
    char infix[100], postfix[100];
    int test = 1;
    while (test) {
        cout << "Enter an Infix expression: ";
        finalInfix(infix, 100);
        if (!checkParentheses(infix)) {
            cout << "錯誤 -> 括號不成對！請重新輸入" << endl; continue;
        } else if (!CheckOperator(infix)) {
            cout << "錯誤 -> 有非規定符號！請重新輸入" << endl; continue;
        } else if (!CheckOperatornum(infix)) {
            cout << "錯誤 -> 運算子有問題！請重新輸入" << endl; continue;
        } else {
            test = 0;
        }
    }
    InfixToPostfix(infix, postfix);
    cout << "Postfix expression: " << postfix << endl;
    double result = evaluatePostfix(postfix);
    if (fabs(result - round(result)) < 1e-9) {
        cout << "Result: " << fixed << setprecision(1) << result << endl;
    } else {
        cout << "Result: " << fixed << setprecision(6) << result << endl;
    }
    return 0;
}
