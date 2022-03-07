#pragma once
#include "repo.h"
#include "domain.h"
#include <malloc.h>
#include "valid.h"
#include "vectordynamic.h"

typedef struct {
	Repository* repo;
}Service;

Service* createService(Repository* repo);

void destroyService(Service* serv);

int serviceAdd(Service* serv, int id, char type[], int suprafata, char adresa[], double pret);

int serviceUpdate(Service* serv, int id, char type[], int suprafata, char adresa[], double pret);

VectorDinamic* serviceGetAll(Service* serv);
