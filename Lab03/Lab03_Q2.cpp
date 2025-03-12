#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
private:
    int degree;
    float *coef;

public:
    Polynomial(int d = 0) 
	{
        degree = d;
        coef = new float[degree + 1](); 
    } 
    //輸入多項式的最高次方和係數 
    void input() 
	{
        cout << "輸入最高次方: ";
        cin >> degree;
        delete[] coef; //釋放舊的記憶體，記憶體才不會浪費 
        coef = new float[degree + 1](); // 重新分配記憶體 
        cout << "從最高次方輸入係數: ";
        for (int i = degree; i >= 0; i--) 
		{
            cin >> coef[i];
        }
    }

    //輸出多項式  //這邊都跟靜態一樣 
    void print() const 
	{
        int count = 0; //計算輸出幾項了 
        for (int i = degree; i >= 0; i--) //從最高次方開始輸出 
		{
            if (coef[i] != 0) //係數是0的就不會顯示
			{ 
                if (count > 0) //因為第一項的 count還等於零，所以沒有輸出+號 
					cout << " + "; 
            }    
            cout << coef[i]; 
            
            if (i > 0) //常數項不用加 x^
			{ 
                cout << "x^" << i;
            }

            count++; //輸出一項就加上去 
        }
		cout << endl;
	}

    //加法 
    Polynomial add(const Polynomial &p) const 
	{	
		Polynomial result;
		//新的多項式次方是兩個多項式中比較大的那一個
        if (degree > p.degree) {
        	result.degree = degree;
    	} else {
        	result.degree = p.degree;
    	}  
        
        for (int i = 0; i <= result.degree; i++) 
		{
            float coef1 = 0; //儲存Polynomial 1的係數 
            float coef2 = 0; //儲存Polynomial 2的係數 
            
        	//要取 i次方的係數 
        	if (i <= degree) 
			{
            	coef1 = coef[i];
        	}
        	if (i <= p.degree) 
			{
            	coef2 = p.coef[i];
        	}
        	
        	result.coef[i] = coef1 + coef2; //係數相加 
        } 
        return result;
    }

    //乘法  //這邊都跟靜態一樣 
    Polynomial mult(const Polynomial &p) const 
	{
        Polynomial result(degree + p.degree); //新的多項式次方是兩個多項式次方的和 
        for (int i = 0; i <= degree; i++) 
		{
            for (int j = 0; j <= p.degree; j++) 
			{
                result.coef[i + j] += coef[i] * p.coef[j]; //係數相乘
            }
        }
        return result;
    }
    
	//帶入x的值
    float eval(float x) const 
	{
        float result = 0;
        for (int i = 0; i <= degree; i++) 
		{
            result += coef[i] * pow(x, i); //係數乘以x的幾次方 
        }
        return result;
    }
    
    //輸出結果  //這邊都跟靜態一樣  
    void printAdd(const Polynomial& p1, const Polynomial& p2) const 
	{
        Polynomial sum = p1.add(p2); //p1跟 p2帶回 add那邊算一算之後再傳回來
        cout << "Add: ";
        sum.print(); //輸出 p1跟 p2相加的結果
    }
    //乘法
    void printMult(const Polynomial& p1, const Polynomial& p2) const 
	{
        Polynomial product = p1.mult(p2); //p1跟 p2帶回 mult那邊算一算之後再傳回來
        cout << "Mult: ";
        product.print(); //輸出 p1跟 p2相乘的結果 
    }
    //帶入x值 
    void printEval(const Polynomial& p, float x) const 
	{
        cout << "Polynomial = p(" << x << ") = " << p.eval(x) << endl;
    }

	//輸出結果 
    void output(const Polynomial& p1, const Polynomial& p2, float x) const 
	{
		//加法 
		printAdd(p1, p2);

        //乘法
        printMult(p1, p2);

        //帶 x的值
        printEval(p1, x);
        printEval(p2, x);
    }
};

//這邊都跟靜態一樣
int main() 
{
    Polynomial p1(0), p2(0);
    p1.input(); //讀取第一個多項式 
    p2.input(); //讀取第二個多項式 

    float x;
    cout << "輸入x的值: ";
    cin >> x;

    p1.output(p1, p2, x); //這裡要回去到 class的 output，然後輸出

    return 0;
}
