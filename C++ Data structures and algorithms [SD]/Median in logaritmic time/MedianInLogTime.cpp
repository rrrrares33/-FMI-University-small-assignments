#include <iostream>
#include <conio.h>

using namespace std;

int min(int x, int y)
{
	if (x <= y)
		return x;
	return y;
}

int max(int x, int y){
	if (x >= y)
		return x;
	return y;
}

int getMedianFast(int arr1[], int arr2[], int l1, int l2, int n1, int n2)
{
	//verific dacă mă aflu într-o situație finală
	if (n1 - l1 < 0 || n2 - l2 < 0)
		return -1;
	else if (n1 - l1 == 0)
		return min(arr1[l1], arr2[l2]);
	else if (n1 - l1 == 1)
		return min(max(arr1[l1], arr2[l2]), min(arr1[l1 + 1], arr2[l2 + 1]));
	//intializez medianele
	int med1 = arr1[(n1 + l1) / 2], med2 = arr2[(n2 + l2) / 2];
	if (med1 == med2)
		return med1;
	else if (med1 < med2)
	{
		if ((n1 - l1) % 2 != 0 && n1 - l1 > 1)
			return getMedianFast(arr1, arr2, (n1 + l1) / 2 + 1, l2, n1, (n2 + l2) / 2);
		return getMedianFast(arr1, arr2, (n1 + l1) / 2, l2, n1, (n2 + l2) / 2);
	}
	else
	{
		if ((n2 - l2) % 2 != 0 && n2 - l2 > 1)
			return getMedianFast(arr1, arr2, l1, (n2 + l2) / 2 + 1, (n1 + l1) / 2, n2);
		return getMedianFast(arr1, arr2, l1, (n2 + l2) / 2, (n1 + l1) / 2, n2);
	}
}

//Next very slow function will be used to test the fast first one.
void naiveSort(int arr[], int n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j])
				std::swap(arr[i], arr[j]);
}

int getMedianSuperSlow(int arr1[], int arr2[], int n1, int n2)
{
	if (n1 == 0 || n2 == 0)
		return -1;
	if (arr1[n1 - 1] <= arr2[0])
		return arr1[n1 - 1];
	else if (arr2[n2 - 1] <= arr1[0])
		return arr2[n2 - 1];
	int arrFinal[200], nf = 0;
	for (int i = 0; i < n1; i++)
		arrFinal[++nf] = arr1[i];
	for (int i = 0; i < n2; i++)
		arrFinal[++nf] = arr2[i];
	naiveSort(arrFinal, nf);
	return arrFinal[nf/2];
}

void printArray(int arr[], int n)
{
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
}

int main()
{
	while (true)	//Stress Testing
	{
		int arr1[100], arr2[100];
		int n = rand() % 100;
		cout << "-------------------------------------------------------------"<<endl;
		cout << "Numarul elementelor este de: " << n;
		cout << endl;
		for (int i = 0; i < n; i++)
		{
			arr1[i] = rand() % 1000;
			arr2[i] = rand() % 1000;
		}
		naiveSort(arr1, n);
		naiveSort(arr2, n);
		printArray(arr1, n);
		printArray(arr2, n);
		if (getMedianFast(arr1, arr2, 0, 0, n - 1, n - 1) == getMedianSuperSlow(arr1, arr2, n, n))
		{
			cout <<endl<< "DA" << ' ' << getMedianFast(arr1, arr2, 0, 0, n - 1, n - 1 ) << ' ' << getMedianSuperSlow(arr1, arr2, n, n) << endl;
			cout << endl;
		}
		else 
		{
			cout <<endl<< "NU" << ' ' << getMedianFast(arr1, arr2, 0, 0, n - 1, n - 1) << ' ' << getMedianSuperSlow(arr1, arr2, n, n) << endl;
			cout << endl;
			break;
		}
		_getch(); //Press anything to go from a test to the next one
	}
	/*
	int arr1[100] = { 1, 3, 9, 13, 21, 26, 30};
	int arr2[100] = { 2, 10, 17, 25, 29, 30, 36};
	std::cout << getMedianSuperSlow(arr1, arr2, 7, 7);
	std::cout << getMedianFast(arr1, arr2, 0, 0, 6, 6);
	*/
	_getch();
	return 0;
}