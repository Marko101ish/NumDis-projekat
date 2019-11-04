#ifndef _funkcija
#define _funkcija

#include <list> 
#include<iostream>
#include<string>
#include<math.h>
#include<ctime>
#include<chrono>
#include<iomanip>
using namespace std;

class Polinom 
{
	double _koef, _exp;
	

public:
	Polinom(double koef=0, double exp=0)
	{
		_koef=koef;
		_exp=exp;
	}
	// ----------------------------
	// Promenio u const, zbog sortiranja kasnije
	//OPERATORI

	friend bool operator < (Polinom const& p1, Polinom const& p2);
	friend bool operator > (Polinom const& p1, Polinom const& p2);
	friend bool operator == (Polinom const& p1, Polinom const& p2);

	double GetKoef() const
	{
		return _koef;
	}
	double GetExp() const
	{
		return _exp;
	}
	
	// --------------------
	void SetKoef(double koef)
	{
		_koef=koef;
	}
	void SetExp(double exp)
	{
		_exp=exp;
	}
	double Calc(double);
};

double Calc(list<Polinom>, double);
list<Polinom> ToPoly(string);
string deleteBlanks(string);
void ispisPoly(list<Polinom>);
list<Polinom> izvod(list<Polinom> fja);
bool imaResenja(list<Polinom> fja, double a, double b);

double polovljenje(list<Polinom> fja, double a, double b, double eps);
int getN(double a, double b, double eps);
bool Njutn(list<Polinom> fja, double a, double b, double& res, double eps);
bool Secica(list<Polinom> fja, double a, double b, double& res, double eps);
bool Prosta(list<Polinom> fja, double a, double b, double& res, double eps);
int GetDecNum(double eps);
double maxIzvod(list<Polinom> gja, double a, double b, double eps, double stepen);
bool NjutnMod(list<Polinom> fja, double a, double b, double& res, double eps, double resT);



#endif