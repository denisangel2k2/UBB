#include "domain.h"
#include <string.h>
#include <malloc.h>

Offer createOffer(int id, char type[], int suprafata, char adresa[], double pret) {

	Offer o;
	o.id = id;
	strcpy(o.type, type);
	o.suprafata = suprafata;
	strcpy(o.adresa, adresa);
	o.pret = pret;

	return o;
}

char* getType(Offer of) {
	return of.type;
}

char* getAddress(Offer of) {
	return of.adresa;
}

int getSuprafata(Offer of) {
	return of.suprafata;
}

double getPret(Offer of) {
	return of.pret;
}
int getID(Offer of) {
	return of.id;
}

Offer equ(Offer o2) {

	Offer o;
	strcpy(o.adresa, o2.adresa);
	o.id = o2.id;
	o.pret = o2.pret;
	o.suprafata = o2.suprafata;
	strcpy(o.type, o2.type);

	return o;
}

int isEqu(Offer o1, Offer o2) {
	if (o1.id == o2.id &&
		o1.suprafata == o2.suprafata &&
		abs(o1.pret - o2.pret) < 0.000001 &&
		strcmp(o1.adresa, o2.adresa) == 0 &&
		strcmp(o1.type, o2.type) == 0)
		return 1;
	else return 0;
}