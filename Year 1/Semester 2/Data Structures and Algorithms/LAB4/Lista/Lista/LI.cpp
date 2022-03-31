#include <exception>
#include <iostream>
#include "LI.h"
#include "IteratorLI.h"

int LI::aloca()
{
	int i = primLiber;
	primLiber = urmator[primLiber];
	return i;
}

void LI::dealoca(int i)
{
	urmator[i] = primLiber;
	primLiber = i;
}

void LI::resize()
{

	TElem* elemente_new = new TElem[2*cap];
	TElem* urmator_new = new int[2*cap];
	TElem* anterior_new = new int[2*cap];

	for (int i = 0; i < lungime; i++) {
		elemente_new[i] = elemente[i];
		urmator_new[i] = urmator[i];
		anterior_new[i] = anterior[i];
	}
	for (int i = cap; i < 2*cap-1; i++)
	{
		urmator_new[i] = i + 1;
		anterior_new[i] = i - 1;
	}
	urmator_new[2*cap - 1] = nothing;
	anterior_new[0] = nothing;

	delete[] elemente;
	delete[] urmator;
	delete[] anterior;

	elemente = elemente_new;
	urmator = urmator_new;
	anterior = anterior_new;
	primLiber = cap;
	cap = 2 * cap;
}

LI::LI() {
	prim = nothing;
	ultim = nothing;
	cap = 5;
	lungime = 0;
	primLiber = 0;

	elemente = new TElem[cap];
	urmator = new int[cap];
	anterior = new int[cap];

	for (int i = 0; i < cap; i++)
	{
		urmator[i] = i + 1;
		anterior[i] = i - 1;
	}
	urmator[cap - 1] = nothing;
	anterior[0] = nothing;
	
	
}

int LI::dim() const {
	return lungime;
}


bool LI::vida() const {
	return lungime == 0;
}

TElem LI::element(int i) const {
	if (i >= lungime || i < 0)
		throw std::runtime_error("1");
	else {
		int p = prim;
		int index = 0;
		while (index < i) {
			index++;
			p = urmator[p];
		}
		return elemente[p];
	}
}

TElem LI::modifica(int i, TElem e) {
	if (i >= lungime || i < 0)
		throw 1;
	else {
		int p = prim;
		int index = 0;
		while (index < i) {
			index++;
			p = urmator[p];
		}
		TElem vechi = elemente[p];
		elemente[p] = e;
		return vechi;
	}
}

void LI::adaugaSfarsit(TElem e) {
	
	if (primLiber == nothing)
		resize();

	int nod = aloca();
	
	elemente[nod] = e;
	urmator[nod] = nothing;
	anterior[nod] = ultim;
	urmator[ultim] = nod;

	if (prim == nothing)
		prim = ultim = nod;

	else ultim = nod;

	lungime++;

}

void LI::adauga(int i, TElem e) {
	if (i >= lungime || i < 0)
		throw std::exception();

	if (primLiber == nothing)
		resize();

	int nod = aloca();

	int p = prim;
	int index = 0;
	if (i == 0) {
		elemente[nod] = e;
		anterior[nod] = nothing;
		urmator[nod] = prim;
		prim = nod;
	}
	else if (i == lungime - 1) {
		elemente[nod] = e;
		urmator[nod] = nothing;
		anterior[nod] = ultim;
		urmator[ultim] = nod;
		ultim = nod;
	}
	else {
		while (index < i || p!=nothing) {
			index++;
			p = urmator[p];
		}
		elemente[nod] = e;
		urmator[nod] = urmator[p];
		anterior[nod] = p;
		anterior[urmator[p]] = nod;
		urmator[p] = nod;
	}
	lungime++;


}

TElem LI::sterge(int i) {
	if (i >= lungime || i < 0)
		throw 1;

	int p = prim;
	int index = 0;

	while (index != i) {
		p = urmator[p];
	}

	urmator[anterior[p]] = urmator[p];
	anterior[urmator[p]] = anterior[p];

	dealoca(p);
	lungime--;
	return elemente[p];
	
}

int LI::cauta(TElem e) const{
	int index = 0;
	int p = prim;
	while (e != elemente[p]) {
		p = urmator[p];
	}
	if (p == nothing)
		return -1;
	else return elemente[p];
}

IteratorLI LI::iterator() const {
	return  IteratorLI(*this);
}

LI::~LI() {
	delete[] elemente;
	delete[] urmator;
	delete[] anterior;
}
