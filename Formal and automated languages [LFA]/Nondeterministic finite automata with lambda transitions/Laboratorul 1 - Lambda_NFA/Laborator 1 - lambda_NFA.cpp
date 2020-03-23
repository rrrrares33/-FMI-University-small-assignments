#include <iostream>
#include <conio.h>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;

class LNFA
{
	set<int> Q, F;
	set<char> Sigma;
	set<int> q0;
	map<pair<int, char>, set<int>> delta;

public:
	LNFA() { this->q0 = {}; }
	LNFA(set<int> Q, set<char> Sigma, map<pair<int, char>, set<int>> delta, set<int> q0, set<int> F)
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

	friend istream& operator >> (istream&, LNFA&);

	bool isFinalState(set<int>);
	set<int> deltaStar(set<int>, string);
	set<int> lambdaInchidere(set<int>);
};

bool LNFA::isFinalState(set<int> q)
{
	for (int i : q)
	{
		if (F.find(i) != F.end())
			return true;
	}

	return false;
}

set<int> LNFA::deltaStar(set<int> s, string w)
{
	int n = w.length();
	set<int> localFinalStates;
	for (int i : s)
	{
		for (int j : delta[{i, w[0]}])
			localFinalStates.insert(j);
	}

	if (n == 0 || (n == 1 && w == "@") )
	{
		return localFinalStates; //daca sunt într-o stare finala o returnez
	}
	else if (n == 1) 
	{
		return lambdaInchidere(localFinalStates); //daca sirul mai are doar un element, returneze lambainchiderea starilor finale
	}

	localFinalStates = lambdaInchidere(localFinalStates); //apelez lambda inchidere pentru sir

	return deltaStar(localFinalStates, w.substr(1, w.length() - 1)); //apelez recursiv functia pentru sir fara primul si ultimul caracter
}

set<int> LNFA::lambdaInchidere(set<int> q)
{
	set<int> aux;
	aux.insert(q.begin(), q.end());

	bool da = true;
	while (da)
	{
		da = false;
		for (int i : deltaStar(aux, "@"))
			if (aux.find(i) == aux.end())
			{
				da = true;
				aux.insert(i);
			}
	}
	return aux;
}

istream& operator >> (istream& f, LNFA& M)
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
	LNFA M;

	ifstream fin("lambda-NFA.txt");
	fin >> M;
	fin.close();

	set<int> lastStates = M.deltaStar(M.getInitialState(), "ab");
	

	if (M.isFinalState(lastStates))
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

