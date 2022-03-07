#include "repo.h"
#include <malloc.h>
#include <string.h>

Repository* createRepo(int cap) {

	Repository* repo = (Repository*)malloc(sizeof(Repository));
	repo->offers = create(cap);
	repo->history = create(2);
	repo->index = -1;
	return repo;

}
void destroyOffers(VectorDinamic* v) {
	for (int i = 0; i < len(v); i++)
		destroyOffer(v->elems[i]);
}

void destroyHistory(VectorDinamic* v) {
	VectorDinamic* lista;
	for (int i = 0; i < len(v); i++) { 
		lista = (VectorDinamic*)getElement(v, i); //copiez cate o lista din lista de liste din history
		destroyOffers(lista); // distrug elementele din lista
		destroy(&lista); //distrug vectorul dinamic
	}
}

void destroyRepo(Repository* repo) {
	destroyOffers(repo->offers);
	destroy(&(repo->offers));
	destroyHistory(repo->history);
	destroy(&(repo->history));
	free(repo);
}
VectorDinamic* repoCopyOffers(Repository* repo, VectorDinamic* ve) {
	VectorDinamic* v = create(1);
	Offer* ofini;
	Offer* ofcopy;
	for (int i = 0; i < len(ve); i++) {
		ofini = getElement(ve, i);
		ofcopy = createOffer(ofini->id, ofini->type, ofini->suprafata, ofini->adresa, ofini->pret);
		add(v, ofcopy);
	}
	return v;
}
void addToHistory(Repository* repo) {
	VectorDinamic* copieOffers = repoCopyOffers(repo, repo->offers);
	add(repo->history,copieOffers);
	repo->index++;
}

int repoFind(Repository* repo, int id) {
	for (int i = 0; i < len(repo->offers); i++) {
		Offer* o = getElement(repo->offers, i);
		if (o->id == id)
			return i;
	}
	return -1;
}

int repoAdd(Repository* repo, Offer* of) {
	if (repoFind(repo, of->id)!=-1) {
		destroyOffer(of);
		return 0;
	}
	addToHistory(repo);
	add(repo->offers, of);

	return 1;

}

int repoUpdate(Repository* repo, Offer* of) {
	int pos = repoFind(repo, of->id);
	if (pos == -1) {
		destroyOffer(of);
		return 0;
	}
	else {
		Offer* temp = getElement(repo->offers, pos);

		addToHistory(repo);
		update(repo->offers, pos, of);
		destroyOffer(temp);
		return 1;
	}

	

	
}

int repoDelete(Repository* repo, int id) {
	int pos = repoFind(repo, id);
	if (pos == -1)
		return 0;

	addToHistory(repo);

	Offer* oferta_de_sters = getElement(repo->offers, pos);	
	destroyOffer(oferta_de_sters);
	del(repo->offers, pos);

	return 1;
}

VectorDinamic* getAll(Repository* repo) {
	return repo->offers;
	/*VectorDinamic* v = create(1);
	for (int i = 0; i < len(repo->offers); i++) {
		add(v, repo->offers->elems[i]);
	}
	return v;
	*/
}