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
            opnum++;//紀錄運算符號出現次數
            
        }
        //若為負號或者是負號合理使用的方式
        else if (isdigit(c) || (c == '-' && (i == 0 || infix[i - 1] == '(') && isdigit(infix[i + 1]))) {
            nunum++;// 如果是數字或合法的負數開頭，數字數量加一
            if (infix[i] == '-') 
                i++;//如果是負數，略過負號
            bool hasDot = false;//確認是否有小數點
            while (isdigit(infix[i]) || infix[i] == '.') {
                if (infix[i] == '.') {
                    if (hasDot || i == 0 || !isdigit(infix[i - 1]) || !isdigit(infix[i + 1]) || infix[i + 1] == '.')
                        return false;// 小數點錯誤格式檢查：重複、開頭、孤立小數點等
                    hasDot = true;
                }
                i++;//一直退到非小數以外的東西
            }
            i--;// 回退一格，避免 for 迴圈漏讀下個字元
        } 
        else if (infix[i] == '.') {
            if (i == 0 || !isdigit(infix[i - 1]) || !isdigit(infix[i + 1]) || infix[i + 1] == '.') 
                return false;// 小數點錯誤格式檢查：小數點連續出現或是小數點前後不為數字等等。
        }
    }
    return opnum == nunum - 1;//最終判斷結果運算符號會少於數字一個
}

// 判斷運算子優先順序
int precedence(char op) {
    if (op == '+' || op == '-') return 1;//+以及-的優先程度最低
    if (op == '*' || op == '/' || op == '%') return 2;//乘以及除的優先程度次之
    if (op == '^') return 3;//優先程度最高的是次方
    return 0;
}

// 將中序表達式轉為後序
void InfixToPostfix(const char* infix, char* postfix) {
    Stack stack;// 建立一個運算子堆疊，用來暫存符號與括號
    int j = 0;// j 是 postfix 字串的索引，控制輸出位置
    for (int i = 0; i < strlen(infix); i++) {//歷經所有字串
        char c = infix[i];
        // 如果是數字或合法的負數（位於開頭或左括號後面）
        if (isalnum(c) || (c == '-' && (i == 0 || infix[i - 1] == '('))) {//
            if (infix[i] == '-') {
                postfix[j++] = c;// 如果是數字或合法的負數（位於開頭或左括號後面）
                i++;// 略過負號，往後看數字
                c = infix[i];// 更新 c 為下一個數字
            }
            // 讀入完整數字（包含小數點）
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[j++] = c;// 數字或小數點寫入 postfix
                i++; 
                c = infix[i];// 讀下一個字元
            }
            postfix[j++] = ' ';// 數字結束後補上空格做區隔
            i--;// 回退一格，因為 for 迴圈還會再 i++
        } 
        // 如果遇到左括號，直接壓入堆疊
        else if (c == '(') 
            stack.push(c);
         // 如果遇到右括號，就把堆疊中的運算子全部彈出直到左括號為止 
        else if (c == ')') {
            while (!stack.isEmpty()) {
                char top = stack.pop();// 拿出堆疊頂端符號
                if (top == '(') // 遇到左括號則停止
                    break;
                postfix[j++] = top;// 不是左括號的話，寫入 postfix
                postfix[j++] = ' ';// 寫入空格分隔
            }
        }
        // 如果是一般運算子（+ - * / ^ %）
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
        // 只要堆疊非空，且堆疊頂端的優先權 >= 當前運算子，就先彈出   
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(c)){
                postfix[j++] = stack.pop(); // 彈出並寫入 postfix
                postfix[j++] = ' ';//加入空格
            }
            stack.push(c); // 最後將目前的運算子壓入堆疊
        }
    }
    
    // 把堆疊中剩餘的運算子全數彈出到 postfix 中
    while (!stack.isEmpty()) {
        postfix[j++] = stack.pop(); postfix[j++] = ' ';
    }
    postfix[j] = '\0';// 字串結尾符號標示 postfix 結束
}

// 計算後序表達式結果
double evaluatePostfix(const char* postfix) {
    IntStack stack;// 建立一個 double 型的堆疊來儲存中間計算結果
    
    for (int i = 0; postfix[i] != '\0'; i++) {// 逐字讀取 postfix
        char c = postfix[i];
        
        // 如果遇到數字或合法的負數
        if (isdigit(c) || (c == '-' && (i == 0 || postfix[i - 1] == ' '))) {
            double num = 0; 
            bool isNegative = false;
            
            // 如果是負號開頭，設定為負數
            if (postfix[i] == '-') {
                isNegative = true; 
                i++;//跳過負號
            }   
            //讀取整數部分
            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0'); // 組合數字
                i++; 
            }   
            //讀取小數部分
            if (postfix[i] == '.') {
                i++;//跳過小數點
                char n = postfix[i];//得取小數點後第一個字元
                double decimal = 0;
                double place = 0.1;// 小數位的位值起始為 0.1
                
                while (isdigit(n)) {
                    decimal += (n - '0') * place;// 加上每位小數的實際值
                    place *= 0.1;// 每多一位數就乘 0.1
                    i++; 
                    n = postfix[i];// 讀取下一位
                }
                num += decimal;// 將小數部分加回整數
            }
            
            //如果已知為負數轉換成負數
            if (isNegative)
                num = -num;
            stack.push(num); //將完整數字推入stack中
            i--;// 迴圈會再 i++，因此這裡回退一格以避免跳過下一個符號
        } 
        //跳過空格
        else if (c == ' ') 
            continue;
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') {
            double b = stack.pop(), a = stack.pop();
            if (c == '+') stack.push(a + b);
            else if (c == '-') stack.push(a - b);
            else if (c == '*') stack.push(a * b);
            else if (c == '/') stack.push(a / b);
            else if (c == '^') stack.push(pow(a, b));// 使用 cmath 的 pow 函式進行次方計算
            else if (c == '%') stack.push(fmod(a, b));// 使用 cmath 的fmod 計算浮點數取餘數
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
