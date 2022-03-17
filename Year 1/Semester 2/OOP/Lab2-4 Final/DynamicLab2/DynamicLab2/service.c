#include "service.h"
#include "valid.h"


Service* createService(Repository* repo) {
	Service* serv = (Service*)malloc(sizeof(Service));
	if (serv != NULL) {
		serv->repo = repo;
		return serv;
	}
	else return NULL;
	
}

void destroyService(Service* serv) {
	destroyRepo(serv->repo);
	free(serv);
}

int serviceAdd(Service* serv, int id, char type[], int suprafata, char adresa[], double pret) {
	Offer* of = createOffer(id, type, suprafata, adresa, pret);
	if (validateOffer(of))
		return repoAdd(serv->repo, of);
	else {
		destroyOffer(of);
		return 0;

	}
}

int serviceDelete(Service* serv, int id) {
	
	return repoDelete(serv->repo, id);
}

int serviceUpdate(Service* serv, int id, char type[], int suprafata, char adresa[], double pret) {
	Offer* of = createOffer(id, type, suprafata, adresa, pret);
	if (validateOffer(of))
		return repoUpdate(serv->repo, of);
	else {
		destroyOffer(of); 
		return -1; //possibly wrong
	}
}

VectorDinamic* serviceGetAll(Service* serv) {
	return getAll(serv->repo);
}

VectorDinamic* sortPret(Service* serv, int (*compara)(double, double)) {
	VectorDinamic* v = repoCopyOffers(serv->repo, serv->repo->offers);
	for (int i=0; i<len(v); i++)
		for (int j = i+1; j < len(v); j++) {
			Offer* of1 = getElement(v, i);
			Offer* of2 = getElement(v, j);
			if (compara(getPret(of1),getPret(of2))==1)
			{
				Offer aux = *of1;
				*of1 = *of2;
				*of2 = aux;
			}
		}
	return v;
}

VectorDinamic* sortType(Service* serv, int (*compara)(char*, char*)) {
	VectorDinamic* v = repoCopyOffers(serv->repo, serv->repo->offers);
	for (int i = 0; i < len(v)-1 ; i++)
		for (int j = 0; j < len(v); j++) {
			Offer* of1 = getElement(v, i);
			Offer* of2 = getElement(v, j);
			char* t1 = getType(of1);
			char* t2 = getType(of2);
			//printf("%s %s\n", t1, t2);
			if (compara(t1, t2))
			{
				Offer aux = *of1;
				*of1 = *of2;
				*of2 = aux;
			}
		}
	return v;
}
VectorDinamic* serviceFilterSurface(Service* serv, int what) {
	return repoFilterSurface(serv->repo, what);
}
VectorDinamic* serviceFilterPret(Service* serv, double pret) {
	return repoFilterPret(serv->repo, pret);
}
VectorDinamic* serviceFilterTip(Service* serv, char* tip) {
	return repoFilterTip(serv->repo, tip);
}
