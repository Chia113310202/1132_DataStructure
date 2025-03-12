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
        for (int i = degree; i >= 0; --i) 
		{
            cin >> coef[i];
        }
    }

    //輸出多項式  //這邊都跟靜態一樣 
    void print() const 
	{
        bool first = true; //第一個先設true，這樣第一項前面就不會有+號
        for (int i = degree; i >= 0; --i) //從最高次方開始輸出 
		{
            if (coef[i] != 0) //係數是0的就不會顯示 
			{ 
                if (!first) cout << " + "; //不是第一項就加+號 
                if (i == 0) //(i == 0)代表是常數項，所以輸出不用加 x^ 
				{
                    cout << coef[i]; 
                }
				else
				{ 
                    cout << coef[i] << "x^" << i;
                }
                first = false; //第一項之後就改成 false 
            }
        }
        cout << endl;
    }

    //加法 
    Polynomial add(const Polynomial &p) const 
	{
        int maxDegree = max(degree, p.degree); //新的多項式次方是兩個多項式中比較大的那一個 
        Polynomial result(maxDegree);  //新的多項式的 degree
        for (int i = 0; i <= maxDegree; ++i) 
		{
            float coef1 = 0; //儲存Polynomial 1的係數 
            float coef2 = 0; //儲存Polynomial 2的係數 
            
            //要取 i次方的係數 
            if (i <= degree) 
			{
                coef1 = coef[i];
            }
            //要取 i次方的係數 
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
        for (int i = 0; i <= degree; ++i) 
		{
            for (int j = 0; j <= p.degree; ++j) 
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
        for (int i = 0; i <= degree; ++i) 
		{
            result += coef[i] * pow(x, i); //係數乘以x的幾次方 
        }
        return result;
    }
    
    //輸出結果  //這邊都跟靜態一樣  
    void output(const Polynomial &p1, const Polynomial &p2, float x) const 
	{
        //加法
        Polynomial sum = p1.add(p2); //p1跟 p2帶回 add那邊算一算之後再傳回來
        cout << "Add: ";
        sum.print(); //輸出 p1跟 p2相加的結果

        //乘法 
        Polynomial product = p1.mult(p2); //p1跟 p2帶回 mult那邊算一算之後再傳回來
        cout << "Mult: ";
        product.print(); //輸出 p1跟 p2相乘的結果 
 

        //帶入x值 
        cout << "Polynomial 1 = p(" << x << ") = " << p1.eval(x) << endl;
        cout << "Polynomial 2 = p(" << x << ") = " << p2.eval(x) << endl;
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
