#include <iostream>
#include <conio.h>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class Min_Heap {
	int n;
	int array[100];
	bool checkPos(int i)		//Verific dacă elementul de pe pozitia i respectă regula ca fiecare fiul al sau sa fie mai mare ca el
	{
		if (2 * i + 1 <= n)
		{
			if (this->array[i] < this->array[2 * i] && this->array[i] < this->array[2 * i + 1])
				return true;
			else
				return false;
		}
		else if (2 * i <= n)
		{
			if (this->array[i] < this->array[2 * i])
				return true;
			else
				return false;
		}
		return true;
	}
	bool checkBoth(int i) { return (this->array[i] > this->array[2 * i] && this->array[i] > this->array[2 * i + 1]); };
	bool checkLeft(int i) { return (this->array[i] > this->array[2 * i]); }
	bool checkRight(int i) { return (this->array[i] > this->array[2 * i + 1]); }
	int findLower(int i)
	{
		if (array[2 * i] < array[2 * i + 1])
			return 2 * i;
		return 2 * i + 1;
	}
public:
	Min_Heap() : n(0) {};
	Min_Heap(int nr, int vector[100]) : n(nr)
	{
		for (int i = 1; i <= n; i++)
			array[i] = vector[i];
	}
	Min_Heap(Min_Heap& aux) 
	{
		this->n = aux.n;
		for (int i = 1; i <= this->n; i++)
			this->array[i] = aux.array[i];
	}
	~Min_Heap() {
		n = 0;
	}
	int getNrElemente() { return this->n; };
	friend istream& operator >> (istream & in, Min_Heap & aux)
	{
		cout << "Introduceti numarul de elemente din Min_Heap : "; in >> aux.n; cout << endl;
		for (int i = 1; i <= aux.n; i++)
		{
			cout << "Introduceti elementul de pe pozitia " << i << " din Min_Heap : ";
			in >> aux.array[i];
		}
		return in;
	}
	friend ostream& operator << (ostream& out, Min_Heap & aux)
	{
		out << endl << "Min_Heap este urmatorul : ";
		for (int i = 1; i <= aux.n; i++)
			out << aux.array[i] << ' ';
		out << endl;
		return out;
	}
	Min_Heap& operator = (const Min_Heap & aux)
	{
		this->n = aux.n;
		for (int i = 1; i <= this->n; i++)
			this->array[i] = aux.array[i];
	}
	void insertValue(int x)
	{
		n++;
		array[n] = x;
		int aux = n;
		while (!checkPos(aux / 2) && aux != 1)
		{
			std::swap(array[aux], array[aux / 2]);
			aux /= 2;
		}
	}
	int extractRoot()
	{
		int root = this->array[1];
		array[1] = array[n];
		n--;

		int aux = 1;
		while (!checkPos(aux) && (2 * aux <= n))
		{
			if ((2 * aux + 1) <= n)
			{
				if (checkBoth(aux))
				{
					int lower = findLower(aux);
					std::swap(this->array[aux], this->array[lower]);
					aux = lower;
				}
				else if (checkLeft(aux))
				{
					std::swap(this->array[aux], this->array[2 * aux]);
					aux = 2 * aux;
				}
				else if (checkRight(aux))
				{
					std::swap(this->array[aux], this->array[2 * aux + 1]);
					aux = 2 * aux + 1;
				}
			}
			else
			{
				if (checkLeft(aux))
				{
					std::swap(this->array[aux], this->array[2 * aux]);
					aux = 2 * aux;
				}
			}
		}
		return root;
	};
};

void citireVector(int &n, int arr[100])
{
	cout << "Introduceti numarul de elemente din vector : ";
	cin >> n;
	cout << endl;
	for (int i = 1; i <= n; i++)
	{
		cout << "Introduceti elementul de pe pozitia " << i << " din vector : ";
		cin >> arr[i];
	}
	cout << endl;
}
void afisareVector(int &n, int arr[100])
{
	cout << "Elementele vectorului sunt : ";
	for (int i = 1; i <= n; i++)
		cout << arr[i] << ' ';
	cout << endl;
}
Min_Heap heapify(int n, int arr[100]) 
{
	int arrAux[1];
	arrAux[1] = arr[1];
	Min_Heap A(1, arrAux);
	for (int i = 2; i <= n; i++)
		A.insertValue(arr[i]);
	return A;
}
void Heap_Sort(Min_Heap A, int vecSortat[100])
{
	int i = 1;
	while (A.getNrElemente() != 1)
		vecSortat[i++] = A.extractRoot();
	vecSortat[i] = A.extractRoot();
}

int main()
{
	cout << "Se citeste un vector de numere oarecare." << endl << endl;
	int n, arr[100];
	citireVector(n,arr);
	afisareVector(n,arr);
	Min_Heap A = heapify(n, arr);  //transform vectorul într-un heap prin heapify
	cout << A;
	int vecSortat[100];
	Heap_Sort(A, vecSortat);
	cout << endl;
	cout << "Vectorul sortat este urmatorul." << endl;
	afisareVector(n, vecSortat);
	_getch();
	return 0;
}