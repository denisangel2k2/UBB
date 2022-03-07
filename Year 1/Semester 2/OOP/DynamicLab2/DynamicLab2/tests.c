#include "tests.h"
#include "domain.h"
#include <string.h>
#include <assert.h>
#include "vectordynamic.h"
#include "repo.h"
#include <stdio.h>
#include "service.h"
#include "valid.h"

void runTests() {
	testDomain();
	testDynamicVector();
	testRepo();
	testValid();
	testService();
}
void testDynamicVector() {

	testCreateVector();
	testDestroyVector();
	testSizeVector();
	testAddVector();
	testDeleteVector();
	testUpdateVector();
	testGetElemVector();

}
void testGetElemVector() {
	VectorDinamic* v = create(1);
	add(v, 13);
	assert(getElement(v, 0) == 13);
	destroy(&v);
}
void testDeleteVector() {
	VectorDinamic* v = create(1);
	add(v, 13);
	del(v, 0);
	assert(v->lg == 0);
	destroy(&v);
}
void testUpdateVector() {
	VectorDinamic* v = create(1);
	add(v, 13);
	update(v, 0, 14);
	assert(v->elems[0] == 14);
	destroy(&v);
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
	assert(strcmp(getType(v), "ssssssssss") == 0);
	destroyRepo(repo);
}

void testValid() {
	Offer* of = createOffer(1, "ssssssssss", 3, "sssssssss", 3);
	assert(validateOffer(of) == 0);
	strcpy(of->type, "Casa");
	assert(validateOffer(of) == 1);
	destroyOffer(of);
}

void testService() {
	testServAdd();
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