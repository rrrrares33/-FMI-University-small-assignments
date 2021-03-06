
#include "stdafx.h"
#include "Lista.h"

void f(Lista &L, int x)                                 //Pentru ca functia sa functioneze corect, trebuie sa punem referinta & in Lista L pentru a se transmite modificarile aduse listei prin referinta
{
	L.insert(x);
	for (int i = 1; i <= L.length(); i++)
	{
		std::cout<<L.get(i)<<" ";
	}
}

void afisare(Lista L)                                 //Afișare pentru testarea metodelor
{
	for (int i = 1; i <= L.length(); i++)
	{
		std::cout << L.get(i) << " ";
	}
}

int main()
{
	Lista L(5);
	//Test insert si f()
	f(L, 7);
	std::cout << std::endl;
	f(L, 6);
	std::cout << std::endl;
	f(L, 10);
	std::cout << std::endl<<std::endl;
	//Sfarsit zona de test

	//Test L(X,Y) si insertAt
	Lista M(7,10);
	M.insertAt(203, 20);                            //Cand pozitia este mai mare ca numarul de elemente; (i>=size => insereaza pe ultima pozitie)
	M.insertAt(123, 1);                             //Cand pozitia este mai mica sau egala cu 0; (i<=0 => insereaza pe prima pozitie)
	afisare(M);
	//----------------------

	//Test removeFirst & removeLast
	Lista N(6, 10);
	std::cout << std::endl << std::endl;
	N.removeFirst();
	N.removeLast();
	N.insertAt(123, 1);                             
	N.remove(0);
	N.remove(27);
	afisare(N);
	std::cout << std::endl << std::endl;
	//----------------------------------

	//has test
	Lista H(6, 10);
	H.insertAt(123, 1);
	H.insert(355);
	if (H.has(123))
		std::cout << "DA";
	else
		std::cout << "NU";
	std::cout << std::endl << std::endl;
	//----------------------------

	//hasDuplicates test
	Lista D(1, 10);
	if (D.hasDuplicates())
		std::cout << "DA";
	else
		std::cout << "NU";
	std::cout << std::endl << std::endl;
	//----------------------------------

	//insertAt test
	Lista A(6, 10);
	A.insertAt(11, 4);
	afisare(A);
	std::cout << std::endl << std::endl;
	//---------------------------------

	//remove test
	Lista B(1);
	B.insert(2);
	B.insert(3);
	B.insert(4);
	B.insert(5);
	B.insert(6);
	B.remove(3);
	afisare(B);
	std::cout << std::endl << std::endl;
	//---------------------------------

	//revers test
	Lista C(1);
	C.insert(2);
	C.insert(3);
	C.insert(4);
	C.reverse();
	//-----------

	getchar();
    return 0;
}

