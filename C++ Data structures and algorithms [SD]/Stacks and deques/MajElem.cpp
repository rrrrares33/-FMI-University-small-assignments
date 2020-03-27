//Complexitatea este liniara (O(n)) deoarece se executa doar doua parcurgeri ale vectorului
#include <iostream>
#include <conio.h>

int main() {
	int n, i, nr, maj, v[100];

	std::cin >> n;
	for (i = 0; i < n; i++)
		std::cin >> v[i];

	// cautam candidatul la element majoritar
	maj = v[0];     //presupunem ca primul element ar fi majoritar
	nr = 1;         //salvăm numărul de apariții al acestuia
	for (i = 1; i < n; i++)
		if (v[i] == maj) // câtă vreme elementul curent este egal cu majoratul incrementam numărul de majorate găsite
			nr++;
		else {
			nr--;             // altfel decrementam numarul de maj
			if (nr < 0) {      // daca am scazut sub zero
				maj = v[i];    // alegem drept candidat elementul curent
				nr = 1;        // care apare o data
			}
		}

	// verificare candidat la element majoritar
	nr = 0;
	for (i = 0; i < n; i++) // numaram de cit ori apare maj in vector
		if (v[i] == maj)
			nr++;

	if (nr > n / 2) // daca maj apare de mai mult de n/2 ori este majoritar
		std::cout << "Elementul majoritar este " << maj << " si apare de " << nr << " ori.";
	else
		std::cout << "Nu exista element majoritar.";
	_getch();
	return 0;
}