#pragma once

#include <iostream>
#include <conio.h>
#include "Node.h"

class Lista {
	Nod* start;
	Nod* end;
	int size; //am modificat size si la trecut drept int deoarece in urma apelari insertAt(x,i) cu i<0, cand se compara întâi i cu size, i fiind negativ cumva iesea
			  //ca ar fi mai mare ca size si il insera la sfarsit in loc sa il insereze la inceput.
public:
	Lista(int);
	Lista(int, int);
	~Lista();
	void insert(int);
	void insertAt(int, int);
	int get(int);
	int length();
	void reverse();
	void removeLast();
	void removeFirst();
	void remove(int);
	bool hasDuplicates();
	bool has(int);
	bool isEmpty();
};