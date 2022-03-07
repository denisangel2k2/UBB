#include "teste.h"
#include <assert.h>
#include "domain.h"
#include "valid.h"
#include "repo.h"
#include "service.h"
#include "vectordynamic.h"

void RunTests() {
	validTest();
	domainTest();
	repoTest();
	serviceTest();

}

void validTest() {
	Offer oferta = createOffer(1, "Apartament", 300, "asdasd", 90.3);
	assert(validateOffer(oferta) == 1);
	oferta = createOffer(1, "Apartament", 300, "asdasd", -90.3);
	assert(validateOffer(oferta) == 0);
	oferta = createOffer(1, "Apartament", -300, "asdasd", 90.3);
	assert(validateOffer(oferta) == 0);
	oferta = createOffer(1, "Casa", 300, "asdasd", 90.3);
	assert(validateOffer(oferta) == 1);
	oferta = createOffer(-1, "Apartament", 300, "asdasd", -90.3);
	assert(validateOffer(oferta) == 0);
}

void domainTest() {
	Offer oferta = createOffer(1, "Apartament", 300, "asdasd", 90.3);
	assert(getID(oferta) == oferta.id);
	assert(getSuprafata(oferta) == oferta.suprafata);
	assert(getPret(oferta) - oferta.pret < 0.000001);
	assert(strcmp(getAddress(oferta), oferta.adresa) == 0);
	assert(strcmp(getType(oferta), oferta.type) == 0);

	Offer oferta2 = createOffer(2, "Casa", 3, "asdas", 80.3);

	oferta = equ(oferta2);
	assert(getID(oferta) == 2);
	assert(getPret(oferta) - 80.3 < 0.00001);
	assert(getSuprafata(oferta) == 3);
	assert(strcmp(getAddress(oferta), "asdas") == 0);
	assert(strcmp(getType(oferta), "Casa") == 0);

	assert(isEqu(oferta, oferta2) == 1);
	

}

void repoTest() {
	repoAddTest();
	repoUpdateTest();
	repoGetAllTest();
}
void repoAddTest() {
	Repository* rep = createRepo(1);

	Offer of = createOffer(1, "Apartament", 300, "asdasd", 90.3);
	int lg1 = len(rep->lista);
	repoAdd(rep, of);
	assert(len(rep->lista) - 1==lg1);

	destroyRepo(rep);

}
void repoUpdateTest() {

	Repository* rep = createRepo(1);
	Offer of = createOffer(1, "Apartament", 300, "asdasd", 90.3);
	Offer of2 = createOffer(2, "Casa", 3, "asdas", 80.3);

	repoAdd(rep, of);
	int x=repoUpdate(rep, of2);
	assert(x == 0);
	of2.id = 1;
	x = repoUpdate(rep, of2);
	assert(x == 1);
	assert(isEqu(element(rep->lista, 0), of2) == 1);

	destroyRepo(rep);
}
void repoGetAllTest() {
	VectorDinamic* l;
	Repository* repo = createRepo(1);
	Offer of = createOffer(1, "Apartament", 300, "asdasd", 90.3);
	repoAdd(repo, of);

	l = getAll(repo);
	
	destroyRepo(repo);


}
void serviceTest() {
	serviceAddTest();
	serviceUpdateTest();
}

void serviceAddTest() {

	Repository* rep = createRepo(1);
	Service* serv = createService(rep);

	Offer of = createOffer(1, "Apartament", 300, "asdasd", 90.3);
	int lg1 = len(serv->repo->lista);

	assert(serviceAdd(serv, 1, "Apartament", 300, "asdasd", 90.3)==1);
	assert(lg1 == len(serv->repo->lista) - 1);
	//printf("%s", serv->repo->lista->elements[0].type);

	assert(serviceAdd(serv, -1, "Apartament", 300, "asdasd", 90.3) == 0);

	destroyService(serv);
}
void serviceUpdateTest() {
	Repository* repo = createRepo(1);
	Service* serv = createService(repo);

	Offer o=createOffer(1, "Apartament", 300, "asdasd", 90.3);

	repoAdd(serv->repo, o);
	int x = serviceUpdate(serv, 1, "Casa", 150, "das", 9);
	assert(x == 1);
	assert(getPret(element(serv->repo->lista, 0)) - 9 < 0.000001);
	x = serviceUpdate(serv, 2, "Casa", 150, "das", 9);
	assert(x == 0);
	x = serviceUpdate(serv, 1, "Casa", 150, "das", -9);
	assert(x == 0);

	destroyService(serv);
}