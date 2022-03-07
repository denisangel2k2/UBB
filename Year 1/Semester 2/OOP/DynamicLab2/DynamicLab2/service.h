#pragma once
#include "repo.h"
typedef struct {
	Repository* repo;
}Service;

Service* createService(Repository* repo);
void destroyService(Service* serv);

int serviceDelete(Service* serv, int id);
int serviceUpdate(Service* serv, int id, char type[], int suprafata, char adresa[], double pret);
VectorDinamic* serviceGetAll(Service* serv);
int serviceAdd(Service* serv, int id, char type[], int suprafata, char adresa[], double pret);