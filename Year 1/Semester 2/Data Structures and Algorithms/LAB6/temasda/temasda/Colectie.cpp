#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


int Colectie::dispersie(TElem key) const
{
	return abs(key % (this->m));
}

Colectie::Colectie() {
	tabela = new PNod[CAP];

	for (int i = 0; i < CAP; i++)
		tabela[i] = nullptr;

	m = 10;
}

int Colectie::stergeToateElementeleRepetitive() //
{
	int cate = 0;
	for (int i = 0; i < CAP; i++) {
		PNod p = tabela[i];
		while (p != nullptr) {
			int sw = 0;
			while (nrAparitii(p->element.first) > 1) {
				sterge(p->element.first);
				cate++;
				sw = 1;
			}
			if (sw == 1) {
				TElem ele = p->element.first;
				p = p->urm;
				sterge(ele);
				cate++;
			}
			else p = p->urm;
			

		}
	}
	return cate;
}


void Colectie::adauga(TElem elem) { //o(n)   teta(1)   teta(n)    
	int poz = dispersie(elem);
	
	if (tabela[poz] == nullptr) {
		PNod p = new Nod{ TipElem(elem, 1), nullptr, nullptr };
		p->ant = nullptr;
		p->urm = nullptr;
		tabela[poz] = p;
	}
	else {
		PNod nod = tabela[poz];
		while (nod != nullptr && nod->element.first != elem) nod = nod->urm;
		if (nod == nullptr) {
			PNod p = new Nod{ TipElem(elem, 1), nullptr, nullptr };
			p->urm = nullptr;
			p->ant = nullptr;
			tabela[poz]->ant = p;
			p->urm = tabela[poz];
			tabela[poz] = p;
		}
		else nod->element.second++;
		
	}
		
}


bool Colectie::sterge(TElem elem) { //o(n)    //teta(1) - caz favorabil   //teta(n) - caz defavorabil
	int poz = dispersie(elem);
	
	if (tabela[poz] == nullptr)
		return false;

	else {
		PNod nod = tabela[poz];
		while (nod != nullptr && nod->element.first != elem) nod = nod->urm;
		if (nod == nullptr) return false;
		else {
			if (nod->element.second > 1) nod->element.second--;
			else {
				if (nod->ant == nullptr && nod->urm == nullptr)
				{
					delete nod;
					tabela[poz] = nullptr;
					return true;
				}
				else if (nod->ant == nullptr) {
					PNod p = tabela[poz];
					tabela[poz]->urm->ant = nullptr;
					tabela[poz] = tabela[poz]->urm;

					delete p;
					return true;
				}
				else if (nod->urm == nullptr) {
					nod->ant->urm = nullptr;
					delete nod;
					return true;
				}
				else {
					nod->urm->ant = nod->ant;
					nod->ant->urm = nod->urm;
					delete nod;
					return true;
				}
			}
			return true;
		}


	}



	
}


bool Colectie::cauta(TElem elem) const { //o(n) 

	int poz = dispersie(elem);

	PNod nod = tabela[poz];
	while (nod != nullptr && (nod->element).first != elem)
		nod = nod->urm;

	if (nod == nullptr)
		return false;

	return true;
}

int Colectie::nrAparitii(TElem elem) const { // o(n)
	int poz = dispersie(elem);

	PNod nod = tabela[poz];
	while (nod != nullptr && (nod->element).first != elem)
		nod = nod->urm;

	if (nod == nullptr)
		return 0;

	return (nod->element).second;
}


int Colectie::dim() const { // teta(cardinal(tabela[i]), i=0,CAP;

	int nr = 0;
	
	for (int i = 0; i < m; i++) {
		if (tabela[i] != nullptr)
		{
			PNod nod = tabela[i];
			while (nod != nullptr)
			{
				nr += nod->element.second;
				nod = nod->urm;
			}
		}
	}
	return nr;
}


bool Colectie::vida() const { //o(n)
	int nr = 0;
	PNod nod;
	for (int i = 0; i < m; i++) {

		if (tabela[i] != nullptr) {
			nod = tabela[i];
			while (nod != nullptr) {
				nr += (nod->element).second;
				nod = nod->urm;
			}
		}
	}
	return (nr == 0);
}

IteratorColectie Colectie::iterator() const {
	return  IteratorColectie(*this);
}


Colectie::~Colectie() {
	/* de adaugat */
	for (int i = 0; i < m; i++)
		delete[] tabela[i];
	delete[] tabela;
}

Nod::Nod(TipElem e, Nod* ur, Nod* an) : element{ e }, urm{ ur }, ant{ an }{}
