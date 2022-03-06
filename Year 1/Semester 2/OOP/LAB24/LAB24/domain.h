#pragma once

typedef struct {
	int id;
	char type[50];
	int suprafata;
	char adresa[100];
	double pret;
}Offer;

Offer createOffer(int id, char type[], int suprafata, char adresa[], double pret);

char* getType(Offer of);

char* getAddress(Offer of);

double getPret(Offer of);

int getSuprafata(Offer of);

int getID(Offer of);

Offer equ(Offer o2);

int isEqu(Offer o1, Offer o2);