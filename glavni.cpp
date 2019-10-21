#include "funkcija.h"

void main()
{
	double a, b, eps, res=0;
	int n;
	double k, e;
	list<Polinom> polyList;
	string ulaz;
	getline(cin, ulaz);
	cout << ulaz << endl;


	polyList = ToPoly(deleteBlanks(ulaz));
	ispisPoly(polyList);
	cout << endl;



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
			cout << "Resenje metodom polovljenja: " << polovljenje(polyList, a, b, eps) << "    +- " << eps << endl;
			if (Secica(polyList, a, b, res, eps))
				cout << "Resenje metodom secice: " << res << " +- " << eps << endl;
			else
				cout << "Ne moze se resiti metodom secice!" << endl;
			if (Njutn(polyList, a, b, res, eps))
				cout <<"Resenje Njutnovom metodom: "<<res<<" +- "<<eps << endl;
			else
				cout << "Ne moze se resiti Njutnovom metodom!" << endl;

			if (NjutnMod(polyList, a, b, res, eps))
				cout <<"Resenje modifikovanovom Njutnovom metodom: "<< res<<" +- "<<eps << endl;
			else
				cout << "Ne moze se resiti Njutnovom modifikovanom metodom!" << endl;
		}
		else
		{
			cout << "Nema resenja!" << endl;
		}
	}

	system("pause");
}