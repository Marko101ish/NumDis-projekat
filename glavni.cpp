#include "funkcija.h"

void main()
{
	
	double a, b, eps, res=0;
	int n;
	double k, e;
	list<Polinom> polyList;
	string ulaz;
	getline(cin, ulaz);

// ---------------------------
//Ovde bih posle dodao sortiranje
//----------------------------

	polyList = ToPoly(deleteBlanks(ulaz));
	polyList.sort();
	polyList.reverse();

	cout << "Unesite interval:" << endl;
	cin >> a >> b;
	cout << "Unesite zeljenu tacnost:" << endl;
	cin >> eps;
	cout << fixed << setprecision(GetDecNum(eps));

	if (Calc(polyList, a) == 0)
		cout << "Resenje: " << a << endl;
	else if (Calc(polyList, b) == 0)
		cout << "Resenje: " << b << endl;
	else
	{
		if (imaResenja(polyList, a, b))
		{
			//Polovljenje			
		
			auto start = std::chrono::high_resolution_clock::now();
			cout << "Resenje metodom polovljenja: " << polovljenje(polyList, a, b, eps) << "    +- " << eps << endl;
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			cout << "relativno vreme:" << microseconds << endl;
			
			//Prosta
			start = chrono::high_resolution_clock::now();
			if (Prosta(polyList, a, b, res, eps))
			{
				elapsed = chrono::high_resolution_clock::now() - start;
				microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
				cout << "Resenje metodom proste iteracije: " << res << " +- " << eps << endl;
				cout << "relativno vreme:" << microseconds << endl;
			}
			else
				cout << "Ne moze se resiti metodom proste iteracije!" << endl;

			//Secica
			start = chrono::high_resolution_clock::now();
			if (Secica(polyList, a, b, res, eps))
			{
				elapsed = chrono::high_resolution_clock::now()-start;
				microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
				cout << "Resenje metodom secice: " << res << " +- " << eps << endl;
				cout << "relativno vreme:" << microseconds << endl;
			}
			else
				cout << "Ne moze se resiti metodom secice!" << endl;

			//Njutn
			start = chrono::high_resolution_clock::now();
			if (Njutn(polyList, a, b, res, eps))
			{
				elapsed = chrono::high_resolution_clock::now() - start;
				microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
				cout << "Resenje Njutnovom metodom: " << res << " +- " << eps << endl;
				cout << "relativno vreme:" << microseconds<< endl;
			}
			else
				cout << "Ne moze se resiti Njutnovom metodom!" << endl;

			//NjutnMod
			start = chrono::high_resolution_clock::now();
			if (NjutnMod(polyList, a, b, res, eps)) 
			{
				elapsed = chrono::high_resolution_clock::now() - start;
				microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
				cout << "Resenje modifikovanovom Njutnovom metodom: " << res << " +- " << eps << endl;
				cout << "relativno vreme:" <<microseconds << endl;
			}
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