#include "funkcija.h"

void main()
{
	double k,e;
	list<Polinom> polyList;
	string ulaz;
	getline(cin, ulaz);
	cout<<ulaz<<endl;
	polyList=ToPoly(deleteBlanks(ulaz));
	ispisPoly(polyList);
	cout<<"P(2): "<<Calc(polyList,2)<<endl;
	system("pause");
}