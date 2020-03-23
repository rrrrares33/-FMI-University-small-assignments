#include <iostream>
#include <conio.h>

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
		delete RIGHT;
		delete LEFT;
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
	//Început stivă exercitiul 1;
	stack *top = nullptr;
	std::cout << "Afisare exercitiu cu stiva: ";
	push(top, 1);
	std::cout << pop(top) << ' '; // afișează 1
	push(top, 2);
	push(top, 3);
	std::cout << pop(top) << ' '; // afișează 3
	std::cout << pop(top) << ' '; // afișează 2
	std::cout << pop(top) << ' ' << std::endl << std::endl; // afișează -1
	//Sfarsit stivă exercitiul 1;

	//Început coada dublu înlănțuită 2;
	DEQUEUE *LEFT = nullptr, *RIGHT = nullptr;
	std::cout << "Afisare exercitiu cu coada dublu inlantuita: ";
	pushLEFT(LEFT, 
		RIGHT, 1);
	pushRIGHT(LEFT, RIGHT, 2);
	std::cout<<popRIGHT(LEFT, RIGHT)<<' ';
	std::cout<<popLEFT(LEFT, RIGHT)<<' ';
	pushRIGHT(LEFT, RIGHT, 3);
	//Sfarsit coada dublu inlantuita 2;
	
	
	_getch();
	return 0;
}