#include "stdafx.h"
#include <conio.h>
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;

class NFA
{
	set<int> Q, F;
	set<char> Sigma;
	set<int> q0;
	map<pair<int, char>, set<int>> delta;

public:
	NFA() { this->q0 = {}; }
	NFA(set<int> Q, set<char> Sigma, map<pair<int, char>, set<int>> delta, set<int> q0, set<int> F)
	{
		this->Q = Q;
		this->Sigma = Sigma;
		this->delta = delta;
		this->q0 = q0;
		this->F = F;
	}

	set<int> getQ() const { return this->Q; }
	set<int> getF() const { return this->F; }
	set<char> getSigma() const { return this->Sigma; }
	set<int> getInitialState() const { return this->q0; }
	map<pair<int, char>, set<int>> getDelta() const { return this->delta; }

	friend istream& operator >> (istream&, NFA&);

	bool isFinalState(set<int> q);
	set<int> deltaStar(set<int>, string);
};

bool NFA::isFinalState(set<int> q)
{
	for (int i : q) 
	{
		if (F.find(i) != F.end())
			return true;
	}

	return false;
}

set<int> NFA::deltaStar(set<int> s, string w)
{
	int n = w.length();
	set<int> localFinalStates;
	// din prima stare in care suntem
	// ( pentru ca suntem intr−un set<int> s )
	// adaugam in localFinalStates
	// toate tranzitiile cu prima litera din w
	for (int i : s)
		for (int j : delta[{ i, w[0] }] )
	{
			localFinalStates.insert(j);
	}
	// am efectuat o tranzitie , micsorez n−ul
	n--;
	// daca n = 0 , inseamna ca returnez starile finale adaugate
	if(n == 0)
	{
		return localFinalStates;
	}
	int contor = 0;
	// altfel , cat timp n != 0
	while(n)
	{
		set<int> auxiliar;
		// ma mut in starile finale in care am ajuns
		// efectuand o tranzitie
		// adica daca din 0 cu a am ajun si in 1 3 4 5
		// acum iterez  in {1 , 3 , 4 , 5}
		// pentru a face tranzitii cu urmatoarea litera
		// si stochez starile in auxiliar
		for(int i : localFinalStates)
		{
			for(int j : delta[{ i, w[contor + 1] }])
				auxiliar.insert(j);
		}
		n--;
		contor++;
		// golesc set−ul de localFinalStates
		localFinalStates.clear();
		// mut din auxiliar in localFinalStates
		for(int i : auxiliar)
			localFinalStates.insert(i);
		auxiliar.clear();
	}
	return localFinalStates;
}

istream& operator >> (istream& f, NFA& M)
{
	int noOfStates;
	f >> noOfStates;
	for (int i = 0; i < noOfStates; ++i)
	{
		int q;
		f >> q;
		M.Q.insert(q);
	}

	int noOfLetters;
	f >> noOfLetters;
	for (int i = 0; i < noOfLetters; ++i)
	{
		char ch;
		f >> ch;
		M.Sigma.insert(ch);
	}

	int noOfTransitions;
	f >> noOfTransitions;
	for (int i = 0; i < noOfTransitions; ++i)
	{
		int stareInitiala, nrStari;
		set<int> Stari;
		char ch;
		f >> stareInitiala >> ch >> nrStari;
		for (int i = 0; i < nrStari; i++)
		{
			int x;
			f >> x;
			Stari.insert(x);
		}
		M.delta[{stareInitiala, ch}] = Stari;
	}

	int noOfInitialStates;
	f >> noOfInitialStates;
	for (int i = 0; i < noOfInitialStates; ++i)
	{
		int x;
		f >> x;
		M.q0.insert(x);
	}

	int noOfFinalStates;
	f >> noOfFinalStates;
	for (int i = 0; i < noOfFinalStates; ++i)
	{
		int q;
		f >> q;
		M.F.insert(q);
	}

	return f;
}

int main()
{
	NFA M;

	ifstream fin("NFA.txt");
	fin >> M;
	fin.close();

	set<int> lastState = M.deltaStar(M.getInitialState(), "aabaa");    // aabaa - acceptat; aaba - neacceptat

	if (M.isFinalState(lastState))
	{
		cout << "Cuvant acceptat";
	}
	else
	{
		cout << "Cuvant respins";
	}

	getchar();
	return 0;
}