#pragma once

#include <iostream>

#define NULL_TELEM -1
#define CAP 10
typedef int TElem;

//first - key      second - frequency
typedef std::pair<TElem, int> TipElem;

class IteratorColectie;

class Nod;

typedef Nod* PNod;

class Nod
{
private:
	TipElem element;
	Nod* urm;
	Nod* ant;
public:
	Nod(TipElem, Nod*, Nod*);
	friend class IteratorColectie;
	friend class Colectie;
};


class Colectie
{
	friend class IteratorColectie;

private:
	/* aici e reprezentarea */
	int m;
	PNod* tabela;
	int dispersie(TElem) const;
	int size=0;
public:
	//constructorul implicit
	Colectie();

	//elimina toate elementele care se repeta
	int stergeToateElementeleRepetitive();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};

