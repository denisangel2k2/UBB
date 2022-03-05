#include "Matrice.h"

#include <exception>

using namespace std;

Matrice::Matrice(int m, int n) {	/* de adaugat */

	if (n <= 0 || m <= 0) {
		throw exception();
	}
	this->nC = n;
	this->nL = m;
	this->lungime_Coloana = 0;

	Linie = new int[nL+1];

	for (int i = 0; i < nL + 1; i++)
		Linie[i] = 0;

	Coloana = new int[0];
	Valoare = new TElem[0];

}
Matrice::~Matrice() {	delete[] Linie;	delete[] Coloana;	delete[] Valoare;}
int Matrice::nrLinii() const{	/* Returneaza numarul de linii din matrice */
	return nL;
}

int Matrice::nrColoane() const{	/* Returneaza numarul de coloane din matrice */
	return nC;
}

TElem Matrice::element(int i, int j) const{	/* Returneaza elementul de pe linia i, coloana j din matrice */
	if ((i < 0 || i >= nL) || (j < 0 || j >= nC)) {
		throw exception();
	}

		
	for (int index = Linie[i]; index <= Linie[i + 1] - 1; index++) {
		if (Coloana[index] == j)
			return Valoare[index];
	}
	return NULL_TELEMENT;
}

TElem Matrice::modifica(int i, int j, TElem e) {
	/* modifica elementul de pe o linie si o coloana si returneaza vechea valoare */

	if ((i < 0 || i >= nL) || (j < 0 || j >= nC)) { 
		throw exception();
	}

	//Caut elementul si daca il gasesc il returnez si ii schimb valoarea

	for (int index = Linie[i]; index <= Linie[i + 1] - 1; index++)
		if (Coloana[index] == j) {	
			TElem Valoare_veche = Valoare[index];
			Valoare[index] = e;
			return Valoare_veche;
		}

	//Daca nu il adaug

	//actualizez vectorul de linii

	for (int index = i + 1; index < nL + 1; index++) {

		Linie[index]++;
	}

	int lungime_new = lungime_Coloana + 1;
	int* new_Coloana = new int[lungime_new];
	
	TElem* new_Valoare = new TElem[lungime_new];

	for (int index = 0; index < Linie[i]; index++)
	{
		new_Coloana[index] = Coloana[index];
		new_Valoare[index] = Valoare[index];
	}

	for (int index = Linie[i]; index < lungime_new - 1 ; index++) {
		new_Coloana[index+1] = Coloana[index];
		new_Valoare[index+1] = Valoare[index];
	}

	new_Coloana[Linie[i]] = j;
	new_Valoare[Linie[i]] = e;
	
	delete[] Coloana;
	delete[] Valoare;

	Coloana = new_Coloana;
	Valoare = new_Valoare;

	lungime_Coloana = lungime_new;

	return NULL_TELEMENT;
}

