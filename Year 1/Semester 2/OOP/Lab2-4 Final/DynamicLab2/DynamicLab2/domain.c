
#include "domain.h"
#include <malloc.h>
#include <string.h>

Offer* createOffer(int id, char type[], int suprafata, char adresa[], double pret) {
	Offer* of = (Offer*)malloc(sizeof(Offer));

	of->id = id;
	of->pret = pret;
	of->suprafata = suprafata;
	of->adresa = (char*)malloc(sizeof(char) * (strlen(adresa) + 1));
	of->type = (char*)malloc(sizeof(char) * (strlen(type) + 1));
	strcpy(of->type, type);
	strcpy(of->adresa, adresa);

	return of;
}

void destroyOffer(Offer* of) {
	free(of->type);
	free(of->adresa);
	free(of);

}

int getID(Offer* of) {
	return of->id;
}
char* getType(Offer* of) {
	return of->type;
}
int getSuprafata(Offer* of) {
	return of->suprafata;
}
char* getAdresa(Offer* of) {
	return of->adresa;
}
double getPret(Offer* of) {
	return of->pret;
}
