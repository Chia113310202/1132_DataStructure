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

        char poppedValue = top->data; // 取得頂端元素的值
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

struct DoubleNode {
    double data;//儲存有小數的數值
    DoubleNode* next;
};
//計算數值 IntStack
class IntStack {
private:
    DoubleNode* top;
public:
    IntStack() { top = nullptr; }//construct

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

// 把 infix裡面的空格去掉
void finalInfix(char* infix, int size) {
    char temp[100]; 
    cin.getline(temp, 100); // 可以輸入有空格的算式到 temp

    int j = 0;
    for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] != ' ') { // 不是空格就加到 infix 
            infix[j++] = temp[i];
        }
    }
    infix[j] = '\0'; // 結尾
}

// 檢查輸入括號是否對稱出現
bool checkParentheses(const char* infix){
	int count = 0; 
	for (int i = 0; infix[i] != '\0'; i++) {
		// 遇到一個左括號 +1 
        if (infix[i] == '(') {
            count++;
        }
        // 遇到一個右括號 -1 
        else if (infix[i] == ')'){
        	count--;
        	if (count < 0) return false; // 右括號比左括號先出現 
		}
	}
	if (count == 0) return true;
	else return false;
}

//檢查輸入符號是否符合要求
bool CheckOperator(const char* infix){
    for(int i = 0 ; infix[i] != '\0' ; i++){
        char c = infix[i];
        if (!isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '%' && c != '^' && c != '.'  && c != ' '  && c != '('  && c != ')') {
            return false;
        }
    }
    return true;
}

//檢查運算符號數量
bool CheckOperatornum(const char *infix){
    int opnum = 0;
    int nunum = 0;
    
    for(int i = 0 ; infix[i] != '\0' ; i++){
        char c = infix[i];
        if ( c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^'){
			if (c == '-' && (i == 0 || infix[i - 1] == '(')) {
                // 判斷 -是運算子還是負號，負號會在第一位或是 (後面 
                continue;
            }
			opnum++;
		}
        
		// 負數跟小數點    
        else if (isdigit(c) || (c == '-' && (i == 0 || infix[i - 1] == '(') && isdigit(infix[i + 1]))){
            nunum++; 
            if (infix[i] == '-'){ // 負號跳過 
            	i++;
			}
            while (isdigit(infix[i]) || infix[i] == '.') { 
                i++; // 有小數點就跳過後面數字部分
            }
            i--; 
        }
    }
    
    return opnum == nunum - 1; // 運算子數量 =數字數量 -1
}

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/' || op == '%') return 2;
	if (op == '^') return 3;
	return 0;

}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
	Stack stack; //建一個 stack來放運算子 
    int j = 0; //j是 postfix的寫入位置 

    for (int i = 0; i < strlen(infix); i++) {
        char c = infix[i];
        
		// 如果是英文或數字、第一位就是 -號，或是 (後面是負號就直接加入到 postfix 
        if (isalnum(c) || (c == '-' && (i == 0 || infix[i-1] == '('))) {
            if (infix[i] == '-'){
            	postfix[j++] = c;
            	i++;
            	c = infix[i]; // 把負號跟數字合成一個數 
			}
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = c;// 只要還是數字或 . 就繼續加到 postfix
                i++;
            	c = infix[i];
            }
            postfix[j++] = ' '; // 後面沒有數字後加一個空隔
            i--; // 讀完這個數之後會 i++，所以要減回去 
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
    			postfix[j++] = top; // 其他的加進 postfix
    			postfix[j++] = ' '; // 運算子後加空格
  			}
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
        	// stack頂端的運算值優先度比較高，就先拿出來 
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)) {
                postfix[j++] = stack.pop();
                postfix[j++] = ' '; // 運算子後加空格
            }
            stack.push(c); // 最後再把自己放入 stack 
        }
    }

    // 清空堆疊剩下的東西
    while (!stack.isEmpty()) {
    	postfix[j++] = stack.pop(); // 把堆疊裡剩下的運算子都拿出來加到 postfix
    	postfix[j++] = ' '; // 運算子後加空格
    }
    postfix[j] = '\0'; // 結尾
}

double evaluatePostfix(const char* postfix) {
    IntStack stack; //建一個堆疊，拿來放運算過程的結果 

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i]; //讀 postfix每一個字 
		
        // 如果是數字就加進堆疊
        if (isdigit(c) || (c == '-' && (i == 0 || postfix[i-1] == '('))) {
            //double num = c - '0'; // c - '0'是用 ASCII碼 
            double num = 0;
            
            if (postfix[i] == '-'){
            	i++; // 如果是負數就直接讀數字是多少，等下再加回去 
			}
            
            while (isdigit(postfix[i])) {
        		num = num * 10 + (postfix[i] - '0'); // 讀到的第一個數字 num還是 0，第二個數字時第一個數字就要 *10變成十位數 
        		i++;
    		}
    		if (postfix[i] == '.') {
                i++; // 跳過小數點
                char n = postfix[i]; // 把目前的小數點以後的數字放進 n
                double decimal = 0; // 小數點後面一開始是 0 
                double place = 0.1; // 小數點後第一位是 *0.1 
                
                while (isdigit(n)) {
        			decimal = decimal + (n - '0') * place;  
					place = place * 0.1; // 因為處理完小數點後一位了，後一位要再 *0.1
        			i++;
        			n = postfix[i];
    			}
    			num = num + decimal; // 整數加上小數部分 
            }
            if (c == '-'){ // 如果剛剛讀的是負數，現在把負號加回去 
            	num = -num;
			}
            stack.push(num);
            i--; // while有加了，要減回去 
        }
        else if (c == ' ') {
    		continue; // 空格就直接跳過
		}
        // 是運算子就取出兩個數去計算 
        else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
            double b = stack.pop(); // 堆疊最上面的數字 
            double a = stack.pop(); // 最上面數字的下一個 

            if (c == '+') stack.push(a + b);
            else if (c == '-') stack.push(a - b);
            else if (c == '*') stack.push(a * b);
            else if (c == '/') stack.push(a / b);
            else if (c == '^') stack.push(pow(a, b));
            else if (c == '%') stack.push(fmod(a, b));
        }
    }

    return stack.pop(); // 最後的答案
}

int main() {
    char infix[100], postfix[100];
    int test =1;
    while (test){
    	cout << "Enter an Infix expression: "; // 輸入中序表達式
    	finalInfix(infix, 100); // 存的是沒有空格的算式 
    
    	// 檢查輸入括號
		if (!checkParentheses(infix)) { //程式在90行
        	cout << "錯誤 -> 括號不成對！請重新輸入" << endl;
        	continue; // 回去重新輸入 
    	}
    	
    	else if(!CheckOperator(infix)){ //程式在106行
    	    cout << "錯誤 -> 有非規定符號！請重新輸入" << endl;
        	continue; // 回去重新輸入 
    	}
    	else if(!CheckOperatornum(infix)){
    	    cout << "錯誤 -> 運算子有問題！請重新輸入" << endl;
        	continue; // 回去重新輸入 
    	}
    	else{
			test=0;
		}
    	    
    }
    
	InfixToPostfix(infix, postfix); // 轉換為後序表達式	
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式
	
	double result = evaluatePostfix(postfix);
	if (fabs(result - round(result)) < 1e-9) {
        cout << "Result: " << fixed << setprecision(1) << result << endl;
    } 
    else {
        cout << "Result: " << fixed << setprecision(6) << result << endl;
    }
    
    
    return 0;
}

//可以輸入有空格的算式
//括號是否對稱出現
//輸入符號是否符合要求
//運算符號數量有沒有多(負數不算一個運算子)
