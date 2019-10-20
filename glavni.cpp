#include "funkcija.h"

void main()
{
	double a, b, eps, res;
	int n;
	double k, e;
	list<Polinom> polyList;
	string ulaz;
	getline(cin, ulaz);
	cout << ulaz << endl;


	polyList = ToPoly(deleteBlanks(ulaz));
	ispisPoly(polyList);



	cout << "Unesite interval:" << endl;
	cin >> a >> b;
	cout << "Unesite zeljenu tacnost:" << endl;
	cin >> eps;

	if (Calc(polyList, a) == 0)
		cout << "Resenje: " << a << endl;
	else if (Calc(polyList, b) == 0)
		cout << "Resenje: " << b << endl;
	else
	{
		if (imaResenja(polyList, a, b))
		{
			//cout << "Resenje metodom polovljenja: " << polovljenje(polyList, a, b, eps) << "    +- " << eps << endl;
			if (Njutn(polyList, a, b, res, eps))
				cout << res << endl;
			else
				cout << "Ne moze se resiti Njutnovom metodom!" << endl;


		}
		else
		{
			cout << "Nema resenja!" << endl;
		}
	}


	system("pause");
}