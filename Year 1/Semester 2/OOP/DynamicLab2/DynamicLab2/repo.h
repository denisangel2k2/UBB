#pragma once
#include "vectordynamic.h"
#include "domain.h"

typedef struct {

	VectorDinamic* offers;
	VectorDinamic* history;
	int index;
}Repository;

Repository* createRepo(int cap);
void destroyRepo(Repository* repo);
void destroyOffers(VectorDinamic* v);
void destroyHistory(VectorDinamic* v);
void addToHistory(Repository* repo);

int repoAdd(Repository* repo, Offer* of);
int repoUpdate(Repository* repo, Offer* of);
int repoFind(Repository* repo, int id);
int repoDelete(Repository* repo, int id);

int undo(Repository* repo);
int redo(Repository* repo);

VectorDinamic* getAll(Repository* repo);
VectorDinamic* repoCopyOffers(Repository* repo, VectorDinamic* ve);

