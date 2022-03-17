
#include "CP.h"
#include <exception>
#include <stdio.h>

using namespace std;


CP::CP(Relatie r) {
	/* de adaugat */
	prim = nullptr;
	ultim = nullptr;
	funcPrioritate = r;
}

Nod::Nod(Element e, PNod urm, PNod ant) {
	this->e = e;
	this->urmator = urm;
	this->anterior = ant;
}

Element Nod::Elem() {
	return e;
}


void CP::adauga(TElem e, TPrioritate p) {
	/* de adaugat */
	PNod deAdaugat = new Nod(Element(e, p), nullptr, nullptr);

	if (prim == nullptr) {
		prim = deAdaugat;
		ultim = prim;
		
		
	}
	else {
		Nod* p = prim;
		if (funcPrioritate(deAdaugat->Elem().second, p->Elem().second)) { // trebuie adaugat pe prima pozitie
			deAdaugat->urmator = prim;
			prim->anterior = deAdaugat;
			prim = deAdaugat;
			return;
		}
		while (p != nullptr) {
			//merge pana cand da de pozitia potrivita 
			if (!funcPrioritate(deAdaugat->Elem().second, p->Elem().second))
				p = p->urmator;
			else {
				//elementul trebuie adaugat inainte de p-ul gasit
				deAdaugat->urmator = p;
				deAdaugat->anterior = p->anterior;
				p->anterior = deAdaugat;
				deAdaugat->anterior->urmator = deAdaugat;
				return;
			}
		}
		if (p == nullptr) {
			// trebuie adaugat pe ultima pozitie
			deAdaugat->anterior = ultim;
			ultim->urmator = deAdaugat;
			ultim = deAdaugat;
			return;
			
		}
	}
}

//arunca exceptie daca coada e vida
Element CP::element() const {
	/* de adaugat */
	if (prim == nullptr)
		throw exception();
	
	return Element(prim->Elem().first, prim->Elem().second);

	return pair <TElem, TPrioritate>(-1, -1);       // copy constructor
	
}

Element CP::sterge() {
	/* de adaugat */
	if (prim == nullptr) {
		throw exception();
		return Element(-1, -1);
	}
	else if (prim->urmator == nullptr)
	{
		PNod p = prim;
		Element t = Element(p->Elem().first, p->Elem().second);
		delete p;
		prim = nullptr;
		return t;
	}
	else {
		PNod p = prim;
		prim = prim->urmator;
		prim->anterior = nullptr;
		Element t = Element(p->Elem().first, p->Elem().second);
		delete p;
		return t;
	}
	

	return pair <TElem, TPrioritate>(-1, -1);
}

bool CP::vida() const {
	/* de adaugat */
	if (prim == nullptr)
		return true;
	else return false;
}


CP::~CP() {
	/* de adaugat */
	while (prim != nullptr) {
		PNod p = prim;
		prim = prim->urmator;
		delete p;
	}
};



