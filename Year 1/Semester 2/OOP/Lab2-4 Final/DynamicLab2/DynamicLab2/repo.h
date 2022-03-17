#pragma once
#include "vectordynamic.h"
#include "domain.h"

typedef struct {

	VectorDinamic* offers;
	VectorDinamic* history;
	int index;
}Repository;
/*
Constructor de repo
pre : cap -int
post : Repository*
*/
Repository* createRepo(int cap);
/*
Destructor de repo
pre : Repository*
post : True
*/
void destroyRepo(Repository* repo);
/*
Functie care distruge ofertele din repo
pre : VectorDinamic*
post : True
*/
void destroyOffers(VectorDinamic* v);
/*
Functie care distruge lista de undo din repo
pre : VectorDinamic*
post : True
*/


void destroyHistory(VectorDinamic* v);
/*
Functie care adauga o lista la lista de repo
pre : VectorDinamic*
post : True
*/
void addToHistory(Repository* repo);
/*
Functie care adauga un element in repo
pre : Repository*
post : Elementul este adaugat
*/
int repoAdd(Repository* repo, Offer* of);
/*
Functie care actualizeaza un element in repo
pre : Repository*
post : 1 - Elementul este actualizat
		0 - altfel
*/
int repoUpdate(Repository* repo, Offer* of);
/*
Functie care cauta un element in repo
pre : Repository*
post : 1 - daca este gasit
		-1 - altfel
*/
int repoFind(Repository* repo, int id);
/*
Functie care sterge un element din repo
pre : Repository*
post : 1 - daca este gasit si sters
		-1 - altfel
*/
int repoDelete(Repository* repo, int id);

int undo(Repository* repo);
int redo(Repository* repo);

VectorDinamic* getAll(Repository* repo);
VectorDinamic* repoCopyOffers(Repository* repo, VectorDinamic* ve);

VectorDinamic* repoFilterSurface(Repository* repo, int what);
VectorDinamic* repoFilterPret(Repository* repo, double pret);
VectorDinamic* repoFilterTip(Repository* repo, char* tip);


