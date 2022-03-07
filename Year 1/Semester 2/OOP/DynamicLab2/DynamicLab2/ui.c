#include "ui.h"
#include <stdio.h>
#include <string.h>
#include "domain.h"

UI* createUI(Service* serv) {
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->service = serv;
	return ui;
}

void destroyUI(UI* ui) {
	destroyService(ui->service);
	free(ui);
}

void addUI(UI* ui) {
	int id;
	char type[90];
	int suprafata;
	char adresa[100];
	double pret;

	printf("Folositi urmatorul pattern: [ID, Tip, Suprafata, Adresa, Pret]:\n");
	scanf("%d, ", &id);
	scanf("%s, ", type);
	type[strlen(type) - 1] = '\0';
	scanf("%d, ", &suprafata);
	scanf("%s, ", adresa);
	adresa[strlen(adresa) - 1] = '\0';
	scanf("%lf", &pret);
	int x = serviceAdd(ui->service, id, type, suprafata, adresa, pret);

	if (x == 1)
		printf("Adaugat cu succes!\n");
	else printf("Elementul este invalid sau exista deja.\n");
}
void printUI(UI* ui) {
	VectorDinamic* l = serviceGetAll(ui->service);
	for (int i = 0; i < len(l); i++)
		printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(l, i)), getType(getElement(l, i)), getSuprafata(getElement(l, i)), getAdresa(getElement(l, i)), getPret(getElement(l, i)));

	printf("\n\n\n");

}
void updateUI(UI* ui) {
	int id;
	char type[90];
	int suprafata;
	char adresa[100];
	double pret;

	printf("Folositi urmatorul pattern: [ID, Tip, Suprafata, Adresa, Pret]:\n");
	scanf("%d, ", &id);
	scanf("%s, ", type);
	type[strlen(type) - 1] = '\0';
	scanf("%d, ", &suprafata);
	scanf("%s, ", adresa);
	adresa[strlen(adresa) - 1] = '\0';
	scanf("%lf", &pret);

	int x = serviceUpdate(ui->service, id, type, suprafata, adresa, pret);

	if (x)
		printf("Actualizat cu succes!\n");
	else printf("Elementul este invalid sau nu exista.\n");
}
void deleteUI(UI* ui) {
	int id;
	printf("Folositi urmatorul pattern: [ID]:\n");

	scanf("%d", &id);
	int x = serviceDelete(ui->service, id);
	if (x)
		printf("Sters cu succes!\n");
	else printf("ID invalid/elementul nu exista!");

}

void UI_RUN(UI* ui) {
	int cmd;
	while (1) {
		printf("Alegeti o functionalitate:\n");
		printf("1. Adaugare oferta\n");
		printf("2. Actualizare oferta\n");
		printf("3. Printeaza ofertele\n");
		printf("4. Sterge oferta\n");
		printf(">>>");
		scanf("%d", &cmd);

		if (cmd == 1)
			addUI(ui);
		else if (cmd == 2)
			updateUI(ui);
		else if (cmd == 3)
			printUI(ui);
		else if (cmd == 4)
			deleteUI(ui);
		else if (cmd == 99)
		{
			destroyUI(ui);
			break;
		}
	}
}