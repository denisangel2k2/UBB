#pragma once

typedef struct {
	int id;
	char* type;
	int suprafata;
	char* adresa;
	double pret;

}Offer;

Offer* createOffer(int id, char type[], int suprafata, char adresa[], double pret);
void destroyOffer(Offer* of);
int getID(Offer* of);
char* getType(Offer* of);
int getSuprafata(Offer* of);
char* getAdresa(Offer* of);
double getPret(Offer* of);