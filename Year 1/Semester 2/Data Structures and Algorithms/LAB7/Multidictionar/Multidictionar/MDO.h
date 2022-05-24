#pragma once

#include <vector>

using namespace std;

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare >TElem;



class Nod;
class IteratorMDO;

typedef Nod* PNod;

class Nod {

	friend class MDO;
	friend class IteratorMDO;
	Nod(TElem e, PNod st, PNod dr, PNod tata);
	PNod stanga();
	PNod dreapta();
	pair<TCheie,vector<TValoare>>& element();
	

public:
private:
	PNod st, dr;
	PNod tata;
	pair< TCheie, vector<TValoare> >e;
	

};


typedef bool(*Relatie)(TCheie, TCheie);

class MDO {
	friend class IteratorMDO;
    private:
		PNod rad;
		Relatie rel;



		PNod adauga_rec(PNod p, TCheie c, TValoare v, PNod);
		PNod cauta_rec(PNod, TCheie) const;
		PNod sterge_rec(PNod, TCheie, TValoare);
		PNod minim(PNod p) const;
		PNod succesor(PNod) const;

    public:


	// constructorul implicit al MultiDictionarului Ordonat
	MDO(Relatie r);

	
	// adauga o pereche (cheie, valoare) in MDO
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	IteratorMDO iterator() const;

	// destructorul 	
	~MDO();

};
