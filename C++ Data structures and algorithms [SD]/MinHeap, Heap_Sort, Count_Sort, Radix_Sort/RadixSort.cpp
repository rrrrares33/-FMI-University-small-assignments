#include <iostream>
#include <conio.h>
using namespace std;
int citireSiMax(int &n, int arr[100])
{
	cin >> n;
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		cin >> arr[i];
		if (max < arr[i])
			max = arr[i];
	}
	return max;
}

void afisare(const int n, const int arr[100])
{
	cout << endl;
	cout << "Elementele din vector dupa sortare sunt :";
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
	cout << endl;
}


void count_Sort(int n, int arr[100], int coef)
{
	int arrFrecv[10];
	for (int i = 0; i <= 9; i++)
		arrFrecv[i] = 0;

	for (int i = 0; i < n; i++)
		arrFrecv[ (arr[i]/coef) % 10] ++;

	for (int i = 1; i <= 9; i++)
		arrFrecv[i] += arrFrecv[i - 1];

	int arrSortat[100];

	for (int i =  n - 1; i >= 0; i--)
	{
		arrSortat[ arrFrecv[ (arr[i] / coef) % 10 ] - 1] = arr[i];
		arrFrecv[(arr[i] / coef) % 10]--;
	}

	for (int i = 0; i < n; i++)
		arr[i] = arrSortat[i];

}

void radixSort(int n, int arr[100], int max) 
{
	int coef = 1;
	for (int coef = 1; max / coef > 0; coef *= 10)
		count_Sort(n, arr, coef);
}


int main()
{
	int n, arr[100], max;  //în max rețin valoarea maxima din vector.
	max = citireSiMax(n, arr);
	radixSort(n, arr, max);
	afisare(n, arr);
	_getch();
	return 0;
}