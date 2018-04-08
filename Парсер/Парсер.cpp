#include "string"
#include <sstream>
#include <iostream>
#include <iomanip> 

using namespace std;

class Parser
{
private:
	double number();
	double expr();
	double factor();
	double brackets();
	stringstream m_expr_stream;

public:
	double Calc(string str_expr)
	{
		m_expr_stream = stringstream(str_expr);
		return expr();
	}
};

double Parser::number()
{
    int res = 0;
	double tmp = 0;
	int res2 = 0;
	string str;
	char c;
	for (;;)
	{
		c= m_expr_stream.get();
		if (c >= '0' && c <= '9') {
			res = res * 10 + c - '0';
			tmp = res;
		}
		else if (c == '.') {
			str = to_string(res);
			str = str + c;
				do   {
					c = m_expr_stream.get();
					res2 = 0;
					if (c >= '0' && c <= '9') {
						res2 = res2 * 10 + c - '0';
						str = str + to_string(res2);
					}
					else{
						m_expr_stream.putback(c);
						istringstream iss(str, istringstream::in);
						iss >> tmp;
					}
				} while (c >= '0' && c <= '9');

			}
		
		else
		{
			m_expr_stream.putback(c);
			return tmp;
		}
	}
}

double Parser::brackets()
{
	char c = m_expr_stream.get();
	if (c == '(')
	{
		double x = expr();
		m_expr_stream.get();
		return x;
	}
	else
	{
		m_expr_stream.putback(c);
		return number();
	}
}

double Parser::factor()
{
	double x = brackets();
	for (;;)
	{
		char c = m_expr_stream.get();
		switch (c)
		{
		case '*':
			x *= brackets();
			break;
		case '/':
			x /= brackets();
			break;
		default:
			m_expr_stream.putback(c);
			return x;
		}
	}
}

double Parser::expr()
{
	double x = factor();
	for (;;)
	{
		char c = m_expr_stream.get();
		switch (c)
		{
		case '+':
			x += factor();
			break;
		case '-':
			x -= factor();
			break;
	
		default:
			m_expr_stream.putback(c);
			return x;
		}
	}
}

int main()
{
	Parser p;
	string st;
	cin >> st;
	double res = p.Calc(st);
	cout << round(res * 1000) / 1000;	
	system("pause");
	return 0;
}
