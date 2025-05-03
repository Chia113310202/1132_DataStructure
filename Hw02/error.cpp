#include <iostream>
#include <cctype>
#include <cstring>
#include <iomanip>
#include <cmath>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊
    void push(char ch) {
        Node* newNode = new Node(); // 建立新節點
        newNode->data = ch;         // 儲存資料，把字元放進節點
        newNode->next = top;        // 新節點指向原本的頂端
        top = newNode;              // 更新頂端為新節點
    }
    char pop() {
        if (top == nullptr) {                       //如果是空的沒有儲存東西
            cout << "堆疊為空，無法取出元素。\n";   
            return '\0';
        }                                       
        char poppedValue = top->data;               //將頂端資料儲存
        Node* temp = top;                           
        top = top->next;                            // 更新stack頂端為下一個節點
        delete temp;                                // 刪除原本的頂端節點，釋放記憶體
        return poppedValue;                         //回傳頂端資料
    }
    char peek() {
        return (top == nullptr) ? '\0' : top->data;//回傳頂端資料
    }
    bool isEmpty() {
        return top == nullptr; //確認頂端是否為空的
    }
};

// 定義  DoubleNode 結構用儲存數字
struct DoubleNode {
    double data; // 儲存有小數的數值
    DoubleNode* next;//儲存下一筆資料的位子
};

// 使用 linked list 實作堆疊，儲存 double
class IntStack {
private:
    DoubleNode* top;
public:
    IntStack() { top = nullptr; } // 初始化堆疊
    void push(double val) {
        DoubleNode* newNode = new DoubleNode();//建立新節點
        newNode->data = val;                   // 儲存資料，把字元放進節點
        newNode->next = top;                   // 新節點指向原本的頂端
        top = newNode;                         // 更新頂端為新節點
    }
    double pop() {
        if (top == nullptr) {
           cout << "堆疊為空，無法取出元素。\n";
           return '\0';
        }
        double value = top->data;           //儲存頂端資料
        DoubleNode* temp = top;             //創建新節點
        top = top->next;                    //更新stack頂端的節點
        delete temp;                        //釋放記憶體空間
        return value;                       //回傳被刪除的資訊
    }
    bool isEmpty() {
        return top == nullptr;  //確認stack是否為空
    }
};

// 把 infix 裡面的空格去掉
void finalInfix(char* infix, int size) {
    char temp[100]; 
    cin.getline(temp, 100); // 可以輸入有空格的算式到 temp
    int j = 0;
    for (int i = 0; temp[i] != '\0'; i++) {//將輸入的資訊丟入infix陣列中
        if (temp[i] != ' ') {              //如果不是空格則丟入陣列中若為空格則忽略跳到下一個
            infix[j++] = temp[i];
        }
    }
    infix[j] = '\0'; // 結尾
}

// 檢查輸入括號是否對稱出現
bool checkParentheses(const char* infix) {
    int count = 0;//計算左右括弧的數量
    for (int i = 0; infix[i] != '\0'; i++) {
        if (infix[i] == '(') 
            count++;//如果右括弧則+1
        else if (infix[i] == ')') {
            count--;//左括弧-1
            if (count < 0) 
                return false;//如果先出現右括弧則輸出錯誤
        }
    }
    return count == 0;//如果左右括弧對稱輸出true
}

// 檢查輸入符號是否符合要求
bool CheckOperator(const char* infix) {
    for (int i = 0; infix[i] != '\0'; i++) {//歷遍陣列所有內容
        char c = infix[i];
        if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != '^' && c != '.' && c != ' ' && c != '(' && c != ')') {
            return false;//如果有非規定之運算符號則輸出錯誤
        }
    }
    return true;//反之輸出正確
}

// 檢查運算子與數字數量是否合理
bool CheckOperatornum(const char* infix) {
    int opnum = 0, nunum = 0;//計算運算符號及數字出現的次數
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^') {//如果出現規定的運算符號紀錄出現次數
            if (c == '-' && (i == 0 || infix[i - 1] == '('))//確認-代表的是減還是負數
                continue;//如果是負號的話繼續動作不當作運算符號
            opnum++;//計入運算符號出現次數
            
        }
        else if (isdigit(c) || (c == '-' && (i == 0 || infix[i - 1] == '(') && isdigit(infix[i + 1]))) {//
            nunum++;
            if (infix[i] == '-') 
                i++;
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
        } 
        else if (infix[i] == '.') {
            if (i == 0 || !isdigit(infix[i - 1]) || !isdigit(infix[i + 1]) || infix[i + 1] == '.') 
                return false;
        }
    }
    return opnum == nunum - 1;
}

// 判斷運算子優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    if (op == '^') return 3;
    return 0;
}

// 將中序表達式轉為後序
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

// 計算後序表達式結果
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

// 主程式
int main() {
    char infix[100], postfix[100];
    int test = 1;
    while (test) {
        cout << "Enter an Infix expression: ";
        finalInfix(infix, 100);
        if (!checkParentheses(infix)) {//確認括弧的對稱性程式:80~90
            cout << "錯誤 -> 括號不成對！請重新輸入" << endl; continue;
        } else if (!CheckOperator(infix)) {//確認是否有非規定符號在內程式:108~116
            cout << "錯誤 -> 有非規定符號！請重新輸入" << endl; continue;
        } else if (!CheckOperatornum(infix)) {//確認程式的合理性程式:120~151
            cout << "錯誤 -> 運算子有問題！請重新輸入" << endl; continue;
        } else {
            test = 0;
        }
    }
    InfixToPostfix(infix, postfix);
    cout << "Postfix expression: " << postfix << endl;
    double result = evaluatePostfix(postfix);
    // 如果 result 距離四捨五入後的整數非常接近，就視為整數結果，只顯示到小數點後一位
    if (fabs(result - round(result)) < 1e-9) {
        cout << "Result: " << fixed << setprecision(1) << result << endl;//誤差小只顯示整數
    } else {
        cout << "Result: " << fixed << setprecision(6) << result << endl;//誤差大於10^-9所以顯示到小數點後第6位
    }
    return 0;
}

// 可以輸入有空格的算式
// 括號是否對稱出現
// 輸入符號是否符合要求
// 運算符號數量有沒有多（負數不算一個運算子）
// 負數加減做好了
// 小數點多個錯誤也完成了
