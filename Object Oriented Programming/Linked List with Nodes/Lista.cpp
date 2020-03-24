
#include "stdafx.h"
#include "Lista.h"


Lista::Lista(int x) {                                  //Constructor     (MERGE)
	size = 1;
	start = new Nod;
	start->setInfo(x);
}

Lista::Lista(int x, int y) {							//Constructor     (MERGE)
	if (x == 1)
	{
		size = 1;
		start = new Nod;
		start->setInfo(y);
		start->setNext(nullptr);
	}
	else if (x == 2)
	{
		size = 2;
		start = new Nod;
		start->setInfo(y);
		end = new Nod;
		start->setNext(end);
		end->setInfo(y);
		end->setNext(nullptr);
	}
	else
	{
		size = x;
		start = new Nod;
		Nod *current;
		current = start;
		start->setInfo(y);
		for (int i = 2; i < size; i++)
		{
			Nod *aux;
			aux = new Nod;
			aux->setInfo(y);
			current->setNext(aux);
			current = aux;
		}
		end = new Nod;
		current->setNext(end);
		end->setInfo(y);
		end->setNext(nullptr);
	}
}

Lista::~Lista() {										//Destructor (Destructor pentru lista)
	Nod *p = start->getNext(*start);
	Nod *aux;
	while (p != nullptr)
	{
		aux = p;
		p = p->getNext(*p);
		delete aux;
	}
	start = end = nullptr;
	size = 0;
}

void Lista::insert(int x) {							//insert x at the end of the list (!!!!!!!!! MERGE !!!!!!!!!!!!!)
	if (size == 1)
	{
		size++;
		end = new Nod;
		start->setNext(end);
		end->setInfo(x);
		end->setNext(nullptr);
	}
	else
	{
		size++;
		Nod* aux = end;
		end = new Nod;
		aux->setNext(end);
		end->setNext(nullptr);
		end->setInfo(x);
	}
}

void Lista::insertAt(int x, int i) {									//insert x on position i
	if (i >= size)
	{
		insert(x);
	}
	else if (i <= 1)
	{
		size++;
		Nod *aux;
		aux = new Nod;
		aux->setNext(start);
		aux->setInfo(x);
		start = aux;
	}
	else
	{
		Nod *prv = start;
		for (int k = 1; k < i - 1; k++)
		{
			if (!prv)
			{
				std::cout << "Something went wrong!" << std::endl;
				break;
			}
			else
			{
				prv = prv->getNext(*prv);
			}
		}
		if (prv)
		{
			Nod *aux = new Nod;
			Nod *nxt = prv->getNext(*prv);
			if (aux)
			{
				prv->setNext(aux);
				aux->setNext(nxt);
				aux->setInfo(x);
				size++;
			}
		}
	}
}

int Lista::get(int i)					             //Return element from position i;
{
	Nod* aux = this->start;
	for (int k = 2; k <= i; k++)
	{
		aux = aux->getNext(*aux);
	}
	return aux->getInfo();
}

int Lista::length()
{                               //Return size of list;
	return size;
}

void Lista::reverse() 							 //Returneaza lista scrisă invers;
{
	int v[200];
	Nod *p = start;
	for (int i = 1; i <= size; i++)
	{
		v[i] = p->getInfo();
		p = p->getNext(*p);
	}

	for (int i = 1; i <= size / 2; i++)
	{
		int aux = v[i];
		v[i] = v[size - i + 1];
		v[size - i + 1] = aux;
	}

	Lista temp(v[1]);
	for (int i = 2; i <= size; i++)
	{
		temp.insert(v[i]);
	}

	for (int i = 1; i <= temp.length(); i++)
	{
		std::cout << temp.get(i) << " ";
	}

}

void Lista::removeFirst()							 //deletes first element;
{
	Nod *aux = start->getNext(*start);
	start->setNext(aux->getNext(*aux));
	start->setInfo(aux->getInfo());
	size--;
}

void Lista::removeLast()                            //deletes last element;
{
	Nod *aux = start->getNext(*start);
	size--;
	for (int i = 1; i < size; i++)
		aux = aux->getNext(*aux);
	aux->setNext(nullptr);
	end = aux;
}

void Lista::remove(int i)							 //deletes element from position i;
{
	if (i <= 1)
		removeFirst();
	else if (i >= size)
		removeLast();
	else
	{
		Nod *p = start;
		for (int k = 2; k < i; k++)
			p = p->getNext(*p);
		Nod *aux = p->getNext(*p);
		aux = aux->getNext(*aux);
		p->setNext(aux);
		size--;
	}
}

bool Lista::hasDuplicates()						 //Checks if list has duplicates;
{
	if (size <= 1)
		return false;
	int v[200];
	Nod *p = start->getNext(*start);
	for (int i = 1; i <= size && p->getNext(*p) != nullptr; i++)
	{
		v[i] = p->getInfo();
		p = p->getNext(*p);
	}
	for (int i = 1; i <= size - 1; i++)
		for (int j = 1; j <= size; j++)
			if ((i != j) && (v[i] == v[j]))
				return true;
	return false;
}

bool Lista::has(int x)								 //Checks if list has element x;
{
	if (size == 0)
		return false;
	Nod *p = start;
	for (int i = 1; i <= size; i++)
	{
		if (p->getInfo() == x)
			return true;
		p->getNext(*p);
	}
	return false;
}

bool Lista::isEmpty()                               //Checks if list is empty;
{
	if (size == 0)
		return true;
	return false;
};