#include "service.h"
#include "valid.h"

Service* createService(Repository* repo) {
	Service* serv = (Service*)malloc(sizeof(Service));

	serv->repo = repo;
	return serv;
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
	else destroyOffer(of);
}

VectorDinamic* serviceGetAll(Service* serv) {
	return getAll(serv->repo);
}
