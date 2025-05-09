#include <iostream>
#include <cctype>
#include <cstring>
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

    // Push 操作：將元素放入堆疊
    void push(char ch) {
    	Node* newNode = new Node(); // 建立新節點
        newNode->data = ch;         // 儲存資料，把字元放進節點 
        newNode->next = top;        // 新節點指向原本的頂端
        top = newNode;              // 更新頂端為新節點
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
    	if (top == nullptr) {  // 如果堆疊是空的
            cout << "堆疊為空，無法取出元素。\n";
            return '\0';            // 結束這次 pop()
        }

        int poppedValue = top->data; // 取得頂端元素的值
        Node* temp = top;            // 用 temp 暫存目前頂端節點
        top = top->next;             // 更新頂端為下一個節點
        delete temp;                 // 釋放記憶體，刪除原頂端節點
		return poppedValue;          // 回傳剛剛的資料 
    }  

    // Peek 操作：取得頂端元素但不移除
    char peek() {
    	if (top == nullptr) {
            return '\0';
        }
        return top->data;
    }
    
    // 判斷堆疊是否為空
    bool isEmpty() {
    	return top == nullptr;
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;

}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
	Stack stack; //建一個 stack來放運算子 
    int j = 0; //j是 postfix的寫入位置 

    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];
        
		// 如果是英文或數字，就直接加入到 postfix 
        if (isalnum(c)) {
            postfix[j++] = c;
        }
        // 如果是 (，就直接放到 stack
        else if (c == '(') {
            stack.push(c);
        }
        // 如果是 (，要把括號中的運算子都拿出來
        else if (c == ')') {
            while (!stack.isEmpty()) {
    			char top = stack.pop();
    			if (top == '(') { // 遇到 ( 就停 
        			break;  
    			}
    			postfix[j++] = top;  // 其他的加進 postfix
  			}
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
        	// stack頂端的運算值優先度比較高，就先拿出來 
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)) {
                postfix[j++] = stack.pop();
            }
            stack.push(c); // 最後再把自己放入 stack 
        }
    }

    // 清空堆疊剩下的東西
    while (!stack.isEmpty()) {
    	// 把堆疊裡剩下的運算子都拿出來加到 postfix
        postfix[j++] = stack.pop();
    }

    postfix[j] = '\0'; // 結尾
		

}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}
