#include <iostream>
#include <conio.h>
using namespace std;
//Am ales sa aplic algoritmul intre [0,100] intervalul putand fi schimbat in functie de cerintele problemei, algoritmul ramanand la fel
int main()
{
	int arr[100], n, arrFrecv[100], nFrecv = 0;		
	cout << "Introduceti numarul de elemente din vector : "; cin >> n; cout << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << "Introduceti element : "; cin >> arr[i];
		if (arr[i] > nFrecv)
			nFrecv = arr[i];
	}
	cout << endl;
	for (int i = 1; i <= nFrecv; i++)
		arrFrecv[i] = 0;

	for (int i = 1; i <= n; i++)
		arrFrecv[arr[i]] ++;
	int aux = 0;

	for (int i = 1; i <= nFrecv; i++)
	{
		arrFrecv[i] += aux;
		aux = arrFrecv[i];
	}

	for (int i = 1; i <= n; i++)
		arr[i] = 0;

	for (int i = 1; i <= nFrecv; i++)
	{
		while (arr[arrFrecv[i]] == 0)
		{
			arr[arrFrecv[i]] = i;
			arrFrecv[i] --;
		}
	}
	cout << "Vectorul sortat este : ";
	for (int i = 1; i <= n; i++)
		cout << arr[i] << ' ';

	_getch();
	return 0;
}