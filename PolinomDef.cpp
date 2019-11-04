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
		
		try
		{
			while (po > -1)
			{
				po = ulaz.find('x');
				if (po > -1)
				{
					if ((po == 0) || ( (po==1) && (ulaz[0]='+') ))
					{
						k = 1;
					}
					else if (po == 1 && ulaz[0] == '-')
						k = -1;
					else
						k = stod(ulaz);
				}
				else
				{
					polyList.push_back(Polinom(stod(ulaz), 0));
					break;
				}
				ulaz = ulaz.substr(po + 1);
				e = stod(ulaz);

				Polinom pom(k, e);
				polyList.push_back(pom);

				if (ulaz[0] == '+' || ulaz[0] == '-')
					ulaz = ulaz.substr(1);
				po = fmin(ulaz.find('-'), ulaz.find('+'));
				if (po > -1)
				{
					ulaz = ulaz.substr(po);
				}

			}
		}
		catch(exception)
		{
			cout << "Neodgovarajuc unos!" << endl;
			exit(0);
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
		cout<<ispis;
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
		pom.SetKoef(pom.GetKoef()*pom.GetExp());
		pom.SetExp(expNew);
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
	while (br++ <= n)
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

bool NjutnMod(list<Polinom> fja, double a, double b, double& res, double eps, double resT)
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
	if (imaResenja(fja1, a, b))
	{
		cout << "Prvi izvod nije razlicit od 0 za svako x iz intervala!" << endl;
		return false;
	}

	m1 = fmin(f1bABS, f1aABS);
	m2 = fmax(abs(Calc(fja2, a)), abs(Calc(fja2, b)));
	krit = sqrt((2 * m1 * eps / m2));
	double poc = Calc(fja1,x0);
	int i = 0;
	do
	{
		x1 = x0 - (Calc(fja, x0) / poc);
		razlika = abs(x1 - x0);
		x0 = x1;
		i++;
	} while (razlika>krit);

	if (abs(x1 - resT) > eps)
	{
		cout << "Modifikovanom Njutnovom metodom sporo konvergira!" << endl;
		cout << "Trenutno: " << x1 << endl;
		return false;
	}


	res = x1;
	return true;
}


bool Secica(list<Polinom> fja, double a, double b, double& res, double eps)
{
	list<Polinom> fja1 = izvod(fja);
	list<Polinom> fja2 = izvod(fja1);
	double x0, x1, m1, m2, krit, xn1, f1aABS, f1bABS, razlika;
	if (Calc(fja, a) * Calc(fja2, a) > 0)
		x0 = a;
	else if (Calc(fja, b) * Calc(fja2, b) > 0)
		x0 = b;
	else
	{
		//cout << "Proizvod f(x) i f''(x) nije veci od 0 za x=a ili x=b!" << endl;
		return false;
	}

	if (imaResenja(fja1, a, b) == 1 || imaResenja(fja2, a, b) == 1)
	{
		//cout << "Prvi ili drugi izvod su jednaki nuli na datom intervalu!" << endl;
		return false;
	}

	if (Calc(fja, x0)*Calc(fja, a) < 0)
		x1 = a;
	else if (Calc(fja, x0)*Calc(fja, b) < 0)
		x1 = b;
	else
	{
		cout << "Proizvod f(x0) i f(x) nije manji od 0 za x=a ili x=b!" << endl;
		return false;
	}
	f1aABS = abs(Calc(fja1, a));
	f1bABS = abs(Calc(fja1, b));
	if (f1aABS < f1bABS)
	{
		m1 = f1aABS;
		m2 = f1bABS;
	}
	else
	{
		m1 = f1bABS;
		m2 = f1aABS;
	}
	krit = m1 * eps / (m2 - m1);
	do
	{
		xn1 = x1 - Calc(fja, x1)*(x1 - x0) / (Calc(fja, x1) - Calc(fja, x0));
		razlika = abs(x1 - x0);
		x0 = x1;
		x1 = xn1;
	} while (razlika > krit);

	res = x1;
	return true;
}

int GetDecNum(double num)
{
	int count = 0;
	num = abs(num);
	num = num - int(num);
	while (num < 0.998 && num >0.0000000001)
	{
		num = num * 10;
		count = count + 1;
		num = abs(num - int(num));
	}
	return count;
}

		#pragma region OPERATORI

bool operator < (Polinom const& p1, Polinom const& p2)
{
	if (p1.GetExp() < p2.GetExp())
		return true;
	else
		return false;
}

bool operator > (Polinom const& p1, Polinom const& p2)
{
	if (p1.GetExp() > p2.GetExp())
		return true;
	else
		return false;
}

bool operator == (Polinom const& p1, Polinom const& p2)
{
	if ((p1.GetExp() == p2.GetExp()) && (p1.GetKoef() == p2.GetKoef()))
		return true;
	else
		return false;
}
#pragma endregion

bool Prosta(list<Polinom> fja, double a, double b, double& res, double eps)
{
	list<Polinom>gja=fja;
	Polinom x;
	list<Polinom>::iterator it = gja.end();
	list<Polinom>::iterator pomit;
	double stepen, koef;
	bool flag = false;
	int n=0, br=0;
	do
	{
		gja = fja;
		it--;
		x = *it;
		stepen = x.GetExp();
		koef = x.GetKoef();
		if (stepen != 0)
		{
			if (it != gja.end())
			{
				pomit = it;
				it++;
			}
			gja.erase(pomit);
			for (pomit = gja.begin(); pomit != gja.end(); pomit++)
			{
				pomit->SetKoef(pomit->GetKoef() / (-koef));
			}

			double x0 = a, x1;
			double razlika1, razlika0;
			x1 = pow(Calc(gja, x0),1/stepen);
			razlika1 = abs(x1 - x0);
			for (int i = 0; i < 10; i++)
			{
				razlika0 = razlika1;

				x0 = x1;
				x1 = pow(Calc(gja, x0), 1 / stepen);
				
				razlika1 = abs(x1 - x0);
				if (razlika0 <= razlika1)
					break;
			}
			if (razlika1 < razlika0)
			{
				flag = true; res = x1;
			}
		}
	} while (it != gja.begin());
	return flag;
}

double maxIzvod(list<Polinom> gja, double a, double b, double eps, double stepen)
{
	double max = 0;
	double x0 = a;
	while (x0 < b)
	{
		double pom = abs(pow(Calc(gja, x0 + eps), stepen) - pow(Calc(gja, x0),stepen) / eps);
		if (pom > 1)
			return 2;
		else if (pom > max)
			max = pom;
	}
	return max;
}