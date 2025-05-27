#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Product {
private:
    string name; // 商品名稱
    int exp; // 有效期限
    int popular; // 熱銷程度

public:
    // 建立Product來初始化物件，當Product物件被建立時，它會自動執行這個函式，並把n、e、p的值存入name、exp、popular
    Product(const string& n, int e, int p) : name(n), exp(e), popular(p) {}

    // 取得商品名稱
    string getName() const { 
        return name; 
    } 
    // 取得有效期限
    int getExp() const { 
        return exp; 
    } 
    // 取得熱銷程度
    int getPopular() const { 
        return popular; 
    } 
};

// 從文件中讀取數據並存入向量
vector<Product> readFromFile(const string& filename) {
    vector<Product> products;
    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return products;
    }

    int N; 
    file >> N; // 讀取商品名稱
    file.ignore(); // 因為讀完數字後，下一個字元可能是\n，會干擾後面的getline()

    string line;
    while (getline(file, line)) { // 持續讀取整行內容
        stringstream ss(line); // 創建字符串流 
        string name, ch; // ch是暫時讀到的字串
        int exp, pop;

        ss >> name; // 讀取熱銷程度
        while (ss >> ch) {
            if (isdigit(ch[0])) { // 如果ch[0]是數字，就代表是有效期限
                exp = stoi(ch); // 把字串轉成整數
                break;
            }
            else { // 如果還是文字
                name += " " + ch; // 加空格再加字串
            }  
        }
        ss >> pop; // 讀取熱銷程度

        products.push_back(Product(name, exp, pop)); // 存入向量
    }

    file.close();
    return products;
}

void BubbleSort(vector<Product>& products) {
    int n = products.size();
    for (int i = 0; i < n - 1; i++) { // 因為最後一個不需要比較，所以n-1次
        for (int j = 0; j < n - 1 - i; j++) { // 第i輪之後，右邊的i個已經排好了，就不用再比較
            // 如果前一個的有效期限比較大，就交換
            if (products[j].getExp() > products[j + 1].getExp()) {
                swap(products[j], products[j + 1]);
            }
            // 如果有效期限相同，熱銷程度比較小的放到後面，就交換
            else if (products[j].getExp() == products[j + 1].getExp() && products[j].getPopular() < products[j + 1].getPopular()) {
                swap(products[j], products[j + 1]);
            }
        }
    }
}

int main() {
    // 從文件讀取輸入元素
    string filename = "C:/Users/user/Desktop/DS Lab11/input2.txt"; // 貼上input檔案的正確路徑
    vector<Product> products = readFromFile(filename); // 讀取數據

    if (products.empty()) { // 如果數據為空
        cerr << "No valid data found in file." << endl; // 輸出錯誤信息
        return -1;
    }

    BubbleSort(products); // 呼叫BubbleSort，排序products

    for (const auto& p : products) { // auto用來自動推導變數類型 
        cout << p.getName() << endl;
    }

    return 0;
}
