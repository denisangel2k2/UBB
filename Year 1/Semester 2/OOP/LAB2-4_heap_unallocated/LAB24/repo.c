#include "repo.h"
#include <malloc.h>
#include <stdlib.h>
#include <string.h>



Repository* createRepo(int capacity) {

	Repository* repo = (Repository*)malloc(sizeof(Repository));
	repo->lista = create(capacity);
	
	return repo;
}

void destroyRepo(Repository* repo) {
	destroy(repo->lista);
	free(repo);
}

int uniqueOffer(Repository* repo, Offer of) {
	for (int i = 0; i < len(repo->lista); i++) {
		if (getID(repo->lista->elements[i]) == getID(of) ||
			strcmp(getAddress(repo->lista->elements[i]), getAddress(of)) == 0)
			return 1;

	}
	return 0;
}

void repoAdd(Repository* repo, Offer of) {
	if (uniqueOffer(repo,of)==0)
		add(repo->lista, of);
}

int repoUpdate(Repository* repo, Offer of_new) {

	for (int i=0; i<len(repo->lista); i++)
		if (getID(element(repo->lista, i)) == getID(of_new))
		{
			repo->lista->elements[i] = equ(of_new);
			return 1;
		}
	return 0;

}

VectorDinamic* getAll(Repository* repo) {
	//return repo->lista;

	VectorDinamic* v = create(1);

	for (int i = 0; i < len(repo->lista); i++)
		add(v, repo->lista->elements[i]);

	return v;
}