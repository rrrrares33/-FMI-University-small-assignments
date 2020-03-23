#include <iostream>
#include <fstream>
#include <conio.h>

using namespace std;

struct stack {
	int val;
	stack *next;                   
};

void push(stack *&top, int data) {
	if (top == nullptr)
	{
		top = new stack;
		top->val = data;
		top->next = nullptr;
	}
	else
	{
		stack *aux = new stack;
		aux->val = data;
		aux->next = top;
		top = aux;
	}
}

int pop(stack *&top) {
	stack *bob = top;
	int gigel = -1;
	if (top != nullptr)
	{
		top = top->next;
		gigel = bob->val;
		delete bob;
	}
	return gigel;
}

int main()
{
	stack *Stiva;
	Stiva = new stack;
	ifstream fin("tarusi.in");                          //tarusii sunt din cel de al doilea exemplu, respectiv :1 2 2 1 3 4 4 3
	int n, x,lastElement, size = 0;
	fin >> n;
	fin >> x;
	lastElement = x;
	push(Stiva, x);
	size = 1;
	for (int i = 1; i < n; i++)
	{
		fin >> x;
		if (x == lastElement)
		{
			size--;
			int aux = pop(Stiva);
			if (Stiva == nullptr)
				lastElement = 0;
			else
				lastElement = Stiva->val;
		}
		else
		{
			size++;
			push(Stiva, x);
			lastElement = x;
		}
	}
	if (size == 0)
		cout << "Solutia este corecta.";
	else
		cout << "Solutia nu este corecta.";
	_getch();
	return 0;
}