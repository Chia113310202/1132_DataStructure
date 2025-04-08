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
        newNode->data = ch;      // 儲存資料
        newNode->next = top;        // 新節點指向原本的頂端
        top = newNode;              // 更新頂端為新節點
        //cout << ch << " 已推入堆疊\n";
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
    	if (top == NULL) {  // 如果堆疊是空的
            cout << "堆疊為空，無法取出元素。\n";
            return;            // 結束這次 pop()
        }

        int poppedValue = top->data; // 取得頂端元素的值
        Node* temp = top;            // 用 temp 暫存目前頂端節點
        top = top->next;             // 更新頂端為下一個節點
        delete temp;                 // 釋放記憶體，刪除原頂端節點
        //cout << "已取出元素: " << poppedValue << endl;
 
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
    	int peekValue = top->data; // 取得頂端元素的值
        Node* temp = top;            // 用 temp 暫存目前頂端節點
        top = top->next;             // 更新頂端為下一個節點
       
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
    	if (top->next == NULL){
    		return true;
		}
      	return false;
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
	string postfix;
	char c = '+' || '-' || '*' || '/';
	if (infix == char c);
		postfix = postfix + c;
	if (infix == '(')
		

}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}


