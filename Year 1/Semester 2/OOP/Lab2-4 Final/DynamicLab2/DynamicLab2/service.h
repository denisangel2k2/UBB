#pragma once
#include "repo.h"
typedef struct {
	Repository* repo;
}Service;

Service* createService(Repository* repo);
void destroyService(Service* serv);

VectorDinamic* sortPret(Service* serv, int (*compara)(double, double));
VectorDinamic* sortType(Service* serv, int (*compara)(char*, char*));
int serviceDelete(Service* serv, int id);
int serviceUpdate(Service* serv, int id, char type[], int suprafata, char adresa[], double pret);
VectorDinamic* serviceGetAll(Service* serv);

VectorDinamic* serviceFilterSurface(Service* serv, int what);
VectorDinamic* serviceFilterPret(Service* serv, double pret);
VectorDinamic* serviceFilterTip(Service* serv, char* tip);

int serviceAdd(Service* serv, int id, char type[], int suprafata, char adresa[], double pret);