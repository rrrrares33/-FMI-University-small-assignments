#pragma once

class Nod {
	int info;
	Nod* next;

public:
	Nod() : info(0), next(nullptr) {}

	Nod(int inf, Nod *p): info(inf), next(p) {}

	void setInfo(int x) { this->info = x;}

	int getInfo() {	return this->info; }

	void setNext(Nod *p) {	this->next = p;	}

	Nod* getNext(Nod x) {	return x.next;};

};