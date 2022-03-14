#include "tests.h"
#include "domain.h"
#include <string.h>
#include <assert.h>
#include "vectordynamic.h"
#include "repo.h"
#include <stdio.h>
#include "service.h"
#include "valid.h"
#include "compare_func.h"

void runTests() {
	testDomain();
	testDynamicVector();
	testRepo();
	testValid();
	testService();
	testCompare();
}
void testDynamicVector() {

	testCreateVector();
	testDestroyVector();
	testSizeVector();
	testAddVector();
	testDeleteVector();
	testUpdateVector();
	testGetElemVector();
	testCopyVector();

}
void testGetElemVector() {
	VectorDinamic* v = create(1);
	add(v, 13);
	assert(getElement(v, 0) == 13);
	assert(getElement(v, -1) == 0);
	destroy(&v);
}
void testDeleteVector() {
	VectorDinamic* v = create(1);
	add(v, 13);
	del(v, 0);
	int x = del(v, -1);
	assert(x == 0);
	assert(v->lg == 0);
	destroy(&v);
}
void testUpdateVector() {
	VectorDinamic* v = create(1);
	add(v, 13);
	update(v, 0, 14);
	int x = update(v, -1,3);
	assert(x == 0);
	assert(v->elems[0] == 14);
	destroy(&v);
}
void testCopyVector() {
	VectorDinamic* v = create(1);
	add(v, 131);
	VectorDinamic* copie = copy(v);
	
	assert(len(copie) == 1);
	destroy(&v);
	destroy(&copie);
}


void testCreateVector() {
	VectorDinamic* v = create(1);
	assert(v->lg == 0);
	assert(v->capacity = 1);
	destroy(&v);
}
void testDestroyVector() {
	VectorDinamic* v = create(1);
	destroy(&v);
}

void testSizeVector() {
	VectorDinamic* v = create(1);
	int x = 33;

	add(v, &x);
	add(v, &x);
	add(v, &x);

	assert(len(v) == 3);
	destroy(&v);
}

void testAddVector() {
	VectorDinamic* v = create(1);
	int x = 33;

	add(v, &x);
	add(v, &x);
	add(v, &x);

	assert(len(v) == 3);
	destroy(&v);
}
void testDomain() {
	testCreateOffer();
	testDestroyOffer();
}
void testCreateOffer() {
	Offer* of = createOffer(3, "Casa", 300, "asd", 3);
	assert(getID(of) == 3);
	assert(getPret(of) - 3 < 0.000001);
	assert(getSuprafata(of) == 300);
	assert(strcmp(getType(of), "Casa") == 0);
	assert(strcmp(getAdresa(of), "asd") == 0);
	destroyOffer(of);
}
void testDestroyOffer() {
	Offer* of = createOffer(1, "Casa", 300, "asd", 3);
	destroyOffer(of);

}

void testRepo() {
	testRepoCreate();
	testRepoDestroy();
	testRepoAdd();
	testRepoFind();
	testRepoUpdate();
	testRepoDelete();
	testRepoCopyOffers();
	testAddToHistory();
	testRepoGetAll();
	testRepoFitlerSurf();
	testRepoFitlerPret();
	testRepoFilterTip();
}

void testRepoFilterTip() {
	Repository* repo = createRepo(10);

	Offer* of = createOffer(1, "Casa", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = repoFilterTip(repo, "Casa");
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);

	v = repoFilterTip(repo, "s");
	assert(len(v) == 0);

	destroyOffers(v);
	destroy(&v);

	destroyRepo(repo);

}
void testRepoFitlerPret() {
	Repository* repo = createRepo(10);

	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = repoFilterPret(repo, 3);
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);
	
	v = repoFilterPret(repo, 2);

	assert(len(v) == 0);

	destroyOffers(v);
	destroy(&v);

	destroyRepo(repo);
}
void testRepoFitlerSurf() {

	Repository* repo = createRepo(10);
	
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = repoFilterSurface(repo, 3);
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);

	v = repoFilterSurface(repo, 4);
	assert(len(v) == 0);

	destroyOffers(v);
	destroy(&v);

	destroyRepo(repo);
}

void testRepoCreate() {
	Repository* repo = createRepo(10);
	assert(len(repo->offers) == 0);
	destroyRepo(repo);
}

void testRepoDestroy() {
	Repository* repo = createRepo(10);
	destroyRepo(repo);
	
}
void testRepoAdd() {
	Repository* repo = createRepo(10);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	Offer* of1 = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);
	repoAdd(repo, of1);
	assert(len(repo->offers) == 1);
	destroyRepo(repo);
}

void testRepoFind() {
	Repository* repo = createRepo(10);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	//Offer* of1 = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);
	assert(repoFind(repo,1)==0);
	assert(repoFind(repo,2) == -1);
	destroyRepo(repo);
}

void testRepoUpdate() {
	Repository* repo = createRepo(10);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	Offer* of1 = createOffer(1, "333", 3, "sssssssss", 3);
	Offer* of2 = createOffer(2, "333", 3, "sssssssss", 3);
	repoAdd(repo, of);

	assert(repoUpdate(repo, of1) == 1);
	assert(repoUpdate(repo, of2) == 0);

	destroyRepo(repo);
}

void testRepoDelete() {
	Repository* repo = createRepo(10);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);
	assert(len(repo->offers) == 1);
	repoDelete(repo, of->id);
	assert(len(repo->offers) == 0);
	int x=repoDelete(repo, 3);
	assert(x == 0);
	destroyRepo(repo);
}
void testRepoCopyOffers() {
	Repository* repo = createRepo(10);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = repoCopyOffers(repo, repo->offers);
	assert(len(v) == 1);
	destroyRepo(repo);
	assert(len(v) == 1);

	for (int i = 0; i < len(v); i++)
		destroyOffer(v->elems[i]);

	destroy(&v);
}
void testAddToHistory() {
	Repository* repo = createRepo(10);
	
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);
	addToHistory(repo);
	assert(repo->index == 1);

	destroyRepo(repo);
}

void testRepoGetAll() {
	Repository* repo = createRepo(10);

	VectorDinamic* v = getAll(repo);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	assert(len(v) == 1);
	assert(strcmp(getType(getElement(v,0)), "ssssssssss") == 0);
	destroyRepo(repo);
}

void testValid() {
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	assert(validateOffer(of) == 0);
	strcpy(of->type, "Casa");
	assert(validateOffer(of) == 1);
	of->id = -1;
	assert(validateOffer(of) == 0);
	of->id = 1;
	of->pret = -1;
	assert(validateOffer(of) == 0);
	of->pret = 3;
	of->suprafata = -1;
	assert(validateOffer(of) == 0);
	destroyOffer(of);
}

void testService() {
	testServAdd();
	testServDelete();
	testServUpdate();
	testServGetAll();
	testServSortPret();
	testServSortType();
	testServFitlerSurf();
	testServFitlerPret();
	testServFitlerTip();
}

void testServAdd() {

	Repository* repo = createRepo(10);
	Service* serv = createService(repo);

	

	int x = serviceAdd(serv, 1, "ssssssssss", 3, "sssssssss", 3);
	assert(x == 0);
	x = serviceAdd(serv, 1, "Casa", 3, "sssssssss", 3);
	assert(x == 1);
	assert(len(serv->repo->offers)==1);
	
	destroyService(serv);

}

void testServDelete() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	int x = serviceDelete(serv, 1);
	assert(x == 1);
	
	destroyService(serv);

}

void testServUpdate() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);


	int x = serviceUpdate(serv, 1, "Teren", 3, "3", 3);

	assert(x == 1);
	x= serviceUpdate(serv, -1, "Teren", 3, "3", 3);
	assert(x == -1);
	destroyService(serv);

}
void testServGetAll() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);
	VectorDinamic* v = serviceGetAll(serv);
	assert(len(v) == 0);

	destroyService(serv);

}
void testServSortPret() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);

	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3.1);
	Offer* of2 = createOffer(2, "ssssssssss", 3, "sssssssss", 3.2);
	Offer* of3 = createOffer(3, "ssssssssss", 3, "sssssssss", 3.3);
	repoAdd(repo, of);
	repoAdd(repo, of2);
	repoAdd(repo, of3);

	VectorDinamic* v = sortPret(serv, comparePretAsc);
	
	//printf("%lf ", getPret(getElement(v, 2)));
	assert(getPret(getElement(v, 2)) - 3.3 < 0.0001);

	

	destroyOffers(v);
	destroy(&v);

	v = sortPret(serv, comparePretDsc);
	
	//printf("%lf", getPret(getElement(v, 2)));

	assert(getPret(getElement(v, 0)) - 3.3 < 0.0001);

	destroyOffers(v);
	destroy(&v);
	
	destroyService(serv);
}
void testServSortType() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);

	Offer* of = createOffer(1, "aa", 3, "sssssssss", 3.1);
	Offer* of2 = createOffer(2, "bb", 3, "sssssssss", 3.2);
	Offer* of3 = createOffer(3, "cc", 3, "sssssssss", 3.3);
	repoAdd(repo, of);
	repoAdd(repo, of2);
	repoAdd(repo, of3);

	VectorDinamic* v = sortType(serv, compareTypeAsc);

	
	assert(strcmp(getType(getElement(v, 0)), "aa") == 0);
	


	destroyOffers(v);
	destroy(&v);

	v = sortType(serv, compareTypeDsc);
	assert(strcmp(getType(getElement(v, 2)), "aa") == 1);
	destroyOffers(v);
	destroy(&v);

	destroyService(serv);

}
void testServFitlerSurf() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);

	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = serviceFilterSurface(serv, 3);
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);

	v = serviceFilterSurface(serv, 4);
	assert(len(v) == 0);

	destroyOffers(v);
	destroy(&v);

	destroyService(serv);
}
void testServFitlerPret() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);

	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = serviceFilterPret(serv, 3);
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);

	v = serviceFilterPret(serv, 2);
	assert(len(v) == 0);

	destroyOffers(v);
	destroy(&v);

	v = serviceFilterPret(serv, 5);
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);

	destroyService(serv);
}
void testServFitlerTip() {
	Repository* repo = createRepo(10);
	Service* serv = createService(repo);

	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	repoAdd(repo, of);

	VectorDinamic* v = serviceFilterTip(serv, "ssssssssss");
	assert(len(v) == 1);

	destroyOffers(v);
	destroy(&v);

	v = serviceFilterTip(serv, "s");
	assert(len(v) == 0);

	destroyOffers(v);
	destroy(&v);

	destroyService(serv);
}

void testCompare() {
	//assert(comparePretAsc(1.1, 1.2) == 1);
	//assert(comparePretDsc(1.1, 1.2) == 0);
	//assert(compareTypeAsc("aa", "bb") == 1);
	//assert(compareTypeDsc("aa", "bb") == 0);
}