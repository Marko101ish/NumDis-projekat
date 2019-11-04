#include "funkcija.h"

void main()
{

	cout << "Unesite jednacinu:" << endl;
	
	double a, b, eps, res=0, resT=0;
	int n;
	double k, e;
	list<Polinom> polyList;
	string ulaz;
	getline(cin, ulaz);


	polyList = ToPoly(deleteBlanks(ulaz));
	polyList.sort();
	polyList.reverse();

	cout << "Unesite interval:" << endl;
	cin >> a >> b;
	cout << "Unesite zeljenu tacnost:" << endl;
	cin >> eps;
	cout << fixed << setprecision(GetDecNum(eps));
	cout << endl << endl;
	if (Calc(polyList, a) == 0)
		cout << "Resenje: " << a << endl;
	else if (Calc(polyList, b) == 0)
		cout << "Resenje: " << b << endl;
	else
	{
		if (imaResenja(polyList, a, b))
		{

		#pragma region Polovljenje			
		
			auto start = std::chrono::high_resolution_clock::now();
			cout << "Resenje metodom polovljenja: " << polovljenje(polyList, a, b, eps) << "    +- " << eps << endl;
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			cout << "relativno vreme:" << microseconds << endl;
			
			cout << endl << "-------------------------" << endl;

			#pragma endregion



		#pragma region Prosta
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

			cout << endl << "-------------------------" << endl;

#pragma endregion



		#pragma region Secica
			start = chrono::high_resolution_clock::now();
			if (Secica(polyList, a, b, res, eps))
			{
				elapsed = chrono::high_resolution_clock::now()-start;
				microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
				cout << "Resenje metodom secice: " << res << " +- " << eps << endl;
				resT = res;
				cout << "relativno vreme:" << microseconds << endl;
			}
			else
				cout << "Ne moze se resiti metodom secice!" << endl;


			cout << endl << "-------------------------" << endl;
			#pragma endregion



		#pragma region Njutn

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

			cout << endl << "-------------------------" << endl;
			#pragma endregion



		#pragma region NjutnMod

			start = chrono::high_resolution_clock::now();
			if (NjutnMod(polyList, a, b, res, eps, resT)) 
			{
				elapsed = chrono::high_resolution_clock::now() - start;
				microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
				cout << "Resenje modifikovanovom Njutnovom metodom: " << res << " +- " << eps << endl;
				cout << "relativno vreme:" <<microseconds << endl;
			}
			else
				cout << "Ne moze se resiti Njutnovom modifikovanom metodom!" << endl;

			cout << endl << "-------------------------" << endl;
		#pragma endregion

		}
		else
		{
			cout << "Nema resenja!" << endl;
		}
	}

	system("pause");
}