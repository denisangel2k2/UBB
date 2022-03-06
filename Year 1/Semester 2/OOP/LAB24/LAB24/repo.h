#pragma once
#include "vectordynamic.h"

typedef struct {
	VectorDinamic* lista;
	//VectorDinamic** undolist;
}Repository;

Repository* createRepo(int capacity);

void destroyRepo(Repository* repo);

void repoAdd(Repository* repo, Offer of);

int uniqueOffer(Repository* repo, Offer of);

int repoUpdate(Repository* repo, Offer of_new);

VectorDinamic* getAll(Repository* repo);