#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

struct DEQUEUE {
	int val;
	DEQUEUE *prev, *next;
};

void pushRIGHT(DEQUEUE *&LEFT, DEQUEUE  *&RIGHT, int x)
{
	if (LEFT == RIGHT && RIGHT == nullptr)
	{
		LEFT = new DEQUEUE;
		LEFT->prev = nullptr;
		LEFT->next = nullptr;
		RIGHT = LEFT;
		LEFT->val = x;
	}
	else
	{
		DEQUEUE *aux = new DEQUEUE;
		aux->prev = RIGHT;
		aux->val = x;
		LEFT->next = aux;
		LEFT = aux;
	}
}

void pushLEFT(DEQUEUE *&LEFT, DEQUEUE  *&RIGHT, int x)
{
	if (LEFT == RIGHT && RIGHT == nullptr)
	{
		LEFT = new DEQUEUE;
		LEFT->prev = nullptr;
		LEFT->next = nullptr;
		RIGHT = LEFT;
		LEFT->val = x;
	}
	else
	{
		DEQUEUE *aux = new DEQUEUE;
		aux->prev = LEFT;
		aux->val = x;
		LEFT->next = aux;
		LEFT = aux;
	}
}

int popRIGHT(DEQUEUE *&LEFT, DEQUEUE  *&RIGHT)
{
	if (LEFT == RIGHT && RIGHT == nullptr)
		return -1;
	else if (LEFT == RIGHT)
	{
		int aux = RIGHT->val;
		RIGHT = nullptr;
		LEFT = nullptr;
		return aux;
	}
	int aux = RIGHT->val;
	DEQUEUE *aux1 = RIGHT;
	RIGHT = RIGHT->prev;
	delete aux1;
	return aux;
}

int popLEFT(DEQUEUE *&LEFT, DEQUEUE  *&RIGHT)
{
	if (LEFT == RIGHT && RIGHT == nullptr)
		return -1;
	else if (LEFT == RIGHT)
	{
		int aux = LEFT->val;
		delete RIGHT;
		delete LEFT;
		return aux;
	}
	int aux = LEFT->val;
	DEQUEUE *aux1 = LEFT;
	LEFT = LEFT->prev;
	delete aux1;
	return aux;
}

int main()
{
	//PROGRAM
	DEQUEUE *LEFT = nullptr, *RIGHT = nullptr;
	ifstream fin("matrice.in");
	int n, array[100][100];
	fin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			fin >> array[i][j];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
	cout << endl << endl << endl;

	int aux = 1;
	for (int i = 0; i < n ; i++)
		for (int j = 0; j < n ; j++)
		{
			if (array[i][j] == 1)
			{
				aux++;
				array[i][j] = aux;
				pushLEFT(LEFT, RIGHT, i);
				pushRIGHT(LEFT, RIGHT, j);
				while (LEFT != nullptr || RIGHT !=nullptr)
				{
					int jaux = popLEFT(LEFT, RIGHT);
					int iaux =	popRIGHT(LEFT, RIGHT);

					if (array[iaux - 1][jaux] == 1)
					{
						pushLEFT(LEFT, RIGHT, iaux - 1);
						pushRIGHT(LEFT, RIGHT, jaux);
						array[iaux - 1][jaux] = aux;
					}
					if (array[iaux][jaux + 1] == 1)
					{
						pushLEFT(LEFT, RIGHT, iaux);
						pushRIGHT(LEFT, RIGHT, jaux + 1);
						array[iaux][jaux + 1] = aux;
					}
					if (array[iaux][jaux - 1] == 1)
					{
						pushLEFT(LEFT, RIGHT, iaux);
						pushRIGHT(LEFT, RIGHT, jaux - 1);
						array[iaux][jaux-1] = aux;
					}
					if (array[iaux + 1][jaux] == 1)
					{
						pushLEFT(LEFT, RIGHT, iaux + 1);
						pushRIGHT(LEFT, RIGHT, jaux);
						array[iaux + 1][jaux] = aux;
					}
				}

			}
		}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << array[i][j] << " ";
		cout << endl;
	}
	//FINAL PROGRAM
	_getch();
	return 0;
}