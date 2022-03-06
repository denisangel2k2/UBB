#include "service.h"
#include <stdio.h>


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

	Offer oferta = createOffer(id, type, suprafata, adresa, pret);

	//printf("%d", validateOffer(oferta));

	if (validateOffer(oferta)==1) {
		
		repoAdd(serv->repo, oferta);
		return 1;
	}
	else return 0;

}

int serviceUpdate(Service* serv, int id, char type[], int suprafata, char adresa[], double pret) {
	Offer oferta = createOffer(id, type, suprafata, adresa, pret);
	if (validateOffer(oferta))
		if (repoUpdate(serv->repo, oferta))
			return 1;
		else return 0;
	else return 0;
}
VectorDinamic* serviceGetAll(Service* serv) {
	return getAll(serv->repo);
}