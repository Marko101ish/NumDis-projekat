#include "funkcija.h"
using namespace std;
double Polinom::Calc(double x)
{
	double res=0;
	res=_koef*pow(x, _exp);
	return res;
}

double Calc(list<Polinom> polyList, double x)
{
	if(!polyList.empty())
	{
		double result=0;
		Polinom pom;
		list<Polinom>::iterator it = polyList.begin();
		do
		{
			pom=*it;
			result+=pom.Calc(x);
			advance(it,1);
		}
		while(it!=polyList.end());
		return result;
	}
	else
	{
		cout<<"Prazna lista!";
		return 0;
	}
}

list<Polinom> ToPoly(string ulaz)
{
	int po=ulaz.find('x');
	double k,e;
	list<Polinom> polyList;
	if(po>-1)
	{
		while (po > -1)
		{
			po = ulaz.find('x');
			if (po > -1)
			{
				if (po == 0)
				{
					k = 1;
				}
				else
					k = stod(ulaz);
			}
			else
			{
				polyList.push_back(Polinom(stod(ulaz),0));
				break;
			}
			ulaz=ulaz.substr(po+1);
			e=stod(ulaz);

			Polinom pom(k,e);
			polyList.push_back(pom);

			if(ulaz[0]=='+' || ulaz[0]=='-')
				ulaz=ulaz.substr(1);
			po=fmin(ulaz.find('-'), ulaz.find('+'));
			if(po>-1)
			{
				ulaz=ulaz.substr(po);
			}
		
		}
	}
	else
	{
		try
		{
			polyList.push_back(Polinom(stod(ulaz)));
		}
		catch(int i)
		{
			cout<<"Neodgovarajuc ulaz!"<<endl;
		}
	}
	return polyList;
}

string deleteBlanks(string ulaz)
{
	string izlaz;
	for(int i=0; i<ulaz.length();i++)
	{
		if(ulaz[i]!=' ')
			izlaz+=ulaz[i];
	}
	return izlaz;
}

void ispisPoly(list<Polinom> polyList)
{
	if(!polyList.empty())
	{
		string ispis;
		list<Polinom>::iterator it = polyList.begin();
		do
		{
		Polinom x=*it;
		double koef, exp;
		koef=x.GetKoef();
		exp=x.GetExp();
		if(koef!=0)
		{
			if(koef>0)
				ispis+="+";
			if (koef!=1)
			{
				ispis += to_string(koef);
			}
			else if(exp==0)
				ispis += to_string(koef);
			if(exp!=0)
			{
				ispis+="x^";
				if(exp>0)
					ispis+="+";
				ispis+=to_string(exp)+" ";
			}
		}
		advance(it,1);
		}
		while(it!=polyList.end());
		cout<<ispis<<endl;
	}
	else
		cout<<"Prazna lista!"<<endl;
}

list<Polinom> izvod(list<Polinom> fja)
{
	list<Polinom> fjaNew;
	while (!fja.empty())
	{
		Polinom pom = fja.front();
		fja.pop_front();
		if (pom.GetExp() == 0)
			continue;
		double expNew = pom.GetExp() - 1;
		pom.SetKoef(pom.GetKoef()*pom.GetExp());	pom.SetExp(expNew);
		fjaNew.push_back(pom);
	}
	return fjaNew;
}

bool imaResenja(list<Polinom> fja, double a, double b) 
{
	if (Calc(fja, a)*Calc(fja, b) <= 0)
		return true;
	else if (Calc(fja, a)*Calc(fja, b) > 0)
		return false;
}

double polovljenje(list<Polinom> fja, double a, double b, double eps)
{

	int n = getN(a, b, eps);
		
	int br = 0;
	double x = (a + b) / 2;
	while (br++ < n)
	{
		x = (a + b) / 2;
		if (!Calc(fja, x))
			return x;
		if (imaResenja(fja, a, x))
			b = x;
		else
			a = x;
	}
	return x;
	
}

int getN(double a, double b, double eps)
{
	double c=log2((b - a) / eps) - 1;

	return ceil(c);
}


bool Njutn(list<Polinom> fja, double a, double b, double& res, double eps)
{
	list<Polinom> fja1 = izvod(fja);
	list<Polinom> fja2 = izvod(fja1);
	double x0, m1, m2, x1, krit, n, f1aABS, f1bABS, razlika;
	if (Calc(fja, a) * Calc(fja2, a) > 0)
		x0 = a;
	else if (Calc(fja, b) * Calc(fja2, b) > 0)
		x0 = b;
	else return false;
	f1aABS = abs(Calc(fja1, a));
	f1bABS = abs(Calc(fja1, b));
	if (fja.size() == 1)
	{
		cout << "Prvi izvod nije razlicit od 0 za svako x iz intervala!" << endl;
		return false;
	}
	if (imaResenja(fja1,a,b))
	{
		cout << "Prvi izvod nije razlicit od 0 za svako x iz intervala!" << endl;
		return false;
	}

	m1 = fmin(f1bABS, f1aABS);
	m2 = fmax(abs(Calc(fja2, a)), abs(Calc(fja2, b)));
	krit = sqrt((2 * m1 * eps / m2));
	do
	{
		x1 = x0 - (Calc(fja, x0) / Calc(fja1, x0));
		razlika = abs(x1 - x0);
		x0 = x1;
	} while (razlika>krit);
	res = x1;
	return true;
}