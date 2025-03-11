#include <iostream>
#include <cmath>
using namespace std;

const int Max_Degree = 2; //最大的次方是200 

class Polynomial {
private:
    int degree;
    float coef[Max_Degree + 1] = {0}; //因為還有常數項，所以係數要加 1 

public:
    void input() 
	{
        cout << "輸入最高次方: ";
        cin >> degree;
        cout << "從最高次方輸入係數: ";
        for (int i = degree; i >= 0; --i) //因為是從最高次方開始，所以要--i 
		{
            cin >> coef[i];
        }
    }

    //輸出多項式
    void print() const 
	{
        bool first = true; //第一個先設true，這樣第一項前面就不會有+號 
        for (int i = degree; i >= 0; --i) 
		{
            if (coef[i] != 0) //係數是0的就不會顯示
			{ 
                if (!first) cout << " + ";
                if (i == 0) //(i == 0)代表是常數項，所以輸出不用加 x^
				{
                    cout << coef[i]; 
                }
				else 
				{
                    cout << coef[i] << "x^" << i;
                }
                first = false;
            }
        }
        cout << endl;
    }

    //加法
    Polynomial add(const Polynomial &p) const 
	{
        Polynomial result;
        result.degree = max(degree, p.degree); //新的多項式次方是兩個多項式中比較大的那一個 
        for (int i = 0; i <= result.degree; ++i) 
		{
            result.coef[i] = coef[i] + p.coef[i]; //係數相加 
        }
        return result;
    }

    //乘法
    Polynomial mult(const Polynomial &p) const 
	{
        Polynomial result;
        result.degree = degree + p.degree; //新的多項式次方是兩個多項式次方的和 
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
    
    //輸出結果 
    void output(const Polynomial& p1, const Polynomial& p2, float x) const 
	{
        //加法
        Polynomial sum = p1.add(p2);
        cout << "Add: ";
        sum.print();

        //乘法
        Polynomial product = p1.mult(p2);
        cout << "Mult: ";
        product.print();

        //帶入x值 
        cout << "Polynomial 1 = p(" << x << ") = " << p1.eval(x) << endl;
        cout << "Polynomial 2 = p(" << x << ") = " << p2.eval(x) << endl;
    }
};

int main() 
{
    Polynomial p1, p2;
    p1.input(); 
    p2.input();

    float x;
    cout << "輸入x的值: ";
    cin >> x;

    p1.output(p1, p2, x);

    return 0;
}

