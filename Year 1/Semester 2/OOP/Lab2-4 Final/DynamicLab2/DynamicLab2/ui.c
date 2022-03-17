#include "ui.h"
#include <stdio.h>
#include <string.h>
#include "domain.h"
#include "compare_func.h"
#include <assert.h>

UI* createUI(Service* serv) {
	UI* ui = (UI*)malloc(sizeof(UI));
	
	if (ui != NULL) {
		ui->service = serv;
		return ui;
	}
	else return NULL;
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
	int s1=scanf("%d, ", &id);
	int o1=scanf("%s, ", type);

	assert(o1);

	type[strlen(type) - 1] = '\0';
	int s2=scanf("%d, ", &suprafata);
	int o2=scanf("%s, ", adresa);

	if (o2)
		assert(1);

	adresa[strlen(adresa) - 1] = '\0';
	int s3=scanf("%lf", &pret);
	if (s1 != 0 && s2 != 0 && s3 != 0) {
		int x = serviceAdd(ui->service, id, type, suprafata, adresa, pret);

		if (x == 1)
			printf("Adaugat cu succes!\n");
		else printf("Elementul este invalid sau exista deja.\n");
	}
	
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
	int s1=scanf("%d, ", &id);
	int o1=scanf("%s, ", type);
	type[strlen(type) - 1] = '\0';
	int s2=scanf("%d, ", &suprafata);
	int o2=scanf("%s, ", adresa);

	// if we recreate the pattern of the input so that we read strings with fgets
	// then this o1 and o2 if wouldn't be a problem

	if (o1 && o2)
		assert(1);

	adresa[strlen(adresa) - 1] = '\0';
	int s3=scanf("%lf", &pret);
	if (s1 != 0 && s2 != 0 && s3 != 0) {
		int x = serviceUpdate(ui->service, id, type, suprafata, adresa, pret);

		if (x)
			printf("Actualizat cu succes!\n");
		else printf("Elementul este invalid sau nu exista.\n");
	}
	
}
void deleteUI(UI* ui) {
	int id;
	printf("Folositi urmatorul pattern: [ID]:\n");

	int o1=scanf("%d", &id);
	if (o1 != 0) {
		int x = serviceDelete(ui->service, id);
		if (x)
			printf("Sters cu succes!\n");
		else printf("ID invalid/elementul nu exista!");
	}
	

}
void filterUI(UI* ui) {
	int cmd;
	printf("Filtrati dupa:\n1. Suprafata\n2. Tip\n3. Pret\n");
	int s1=scanf("%d", &cmd);
	if (s1 != 0) {
		VectorDinamic* temp = NULL;
		if (cmd == 1) {
			printf("Introduceti suprafata dupa care sa se filtreze (suprafata>): ");
			int what;
			int s2=scanf("%d", &what);
			if (s2 != 0) {
				temp = serviceFilterSurface(ui->service, what);
				for (int i = 0; i < len(temp); i++)
					printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));
				printf("\n\n\n");
				for (int i = 0; i < len(temp); i++)
					destroyOffer(getElement(temp, i));
				destroy(&temp);
			}
			
		}

		else if (cmd == 2) {
			printf("Introduceti tipul dupa care sa se filtreze : ");
			char what[90];
			int s3=scanf("%s", what);
			if (s3 != 0) {
				temp = serviceFilterTip(ui->service, what);
				for (int i = 0; i < len(temp); i++)
					printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));
				printf("\n\n\n");
				for (int i = 0; i < len(temp); i++)
					destroyOffer(getElement(temp, i));
				destroy(&temp);
			}
			

		}

		else if (cmd == 3) {
			printf("Introduceti pretul dupa care sa se filtreze : ");
			double what;
			int s4=scanf("%lf", &what);
			if (s4 != 0) {
				temp = serviceFilterPret(ui->service, what);
				for (int i = 0; i < len(temp); i++)
					printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));
				printf("\n\n\n");
				for (int i = 0; i < len(temp); i++)
					destroyOffer(getElement(temp, i));
				destroy(&temp);
			}
			
		}
		else printf("Comanda invalida!\n");
	}
	
	
	
}
void sortUI(UI* ui) {
	int cmd;
	VectorDinamic* temp;
	printf("Sortati dupa:\n1. Pret\n2. Tip\n");
	int s1=scanf("%d", &cmd);
	if (s1 != 0) {
		if (cmd == 1)
		{
			int what;
			printf("1. Crescator\n2. Descrescator\n");
			int s2=scanf("%d", &what);

			if (s2 != 0) {
				if (what == 1)
				{
					temp = sortPret(ui->service, comparePretAsc);
					for (int i = 0; i < len(temp); i++)
						printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));
					printf("\n\n\n");
					for (int i = 0; i < len(temp); i++)
						destroyOffer(getElement(temp, i));
					destroy(&temp);
				}
				else if (what == 2)
				{

					temp = sortPret(ui->service, comparePretDsc);
					for (int i = 0; i < len(temp); i++)
						printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));

					printf("\n\n\n");

					for (int i = 0; i < len(temp); i++)
						destroyOffer(getElement(temp, i));
					destroy(&temp);
				}
				else printf("Comanda invalida!\n");
			}
			
		}
		else if (cmd == 2)
		{
			int what;
			printf("1. Descrescator\n2. Crescator\n");
			int s3=scanf("%d", &what);
			if (s3 != 0) {
				if (what == 1)
				{
					temp = sortType(ui->service, compareTypeAsc);
					for (int i = 0; i < len(temp); i++)
						printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));
					printf("\n\n\n");
					for (int i = 0; i < len(temp); i++)
						destroyOffer(getElement(temp, i));
					destroy(&temp);
				}
				else if (what == 2)
				{

					temp = sortType(ui->service, compareTypeDsc);
					for (int i = 0; i < len(temp); i++)
						printf("\tID: %d\tTip: %s\tSuprafata: %d\tAdresa: %s\tPret: %lf\n", getID(getElement(temp, i)), getType(getElement(temp, i)), getSuprafata(getElement(temp, i)), getAdresa(getElement(temp, i)), getPret(getElement(temp, i)));

					printf("\n\n\n");

					for (int i = 0; i < len(temp); i++)
						destroyOffer(getElement(temp, i));
					destroy(&temp);
				}
				else printf("Comanda invalida!\n");
			}
			
		}
		else printf("Comanda invalida!\n");
	}
	
}
void UI_RUN(UI* ui) {
	int cmd;
	while (1) {
		printf("Alegeti o functionalitate:\n");
		printf("1. Adaugare oferta\n");
		printf("2. Actualizare oferta\n");
		printf("3. Printeaza ofertele\n");
		printf("4. Sterge oferta\n");
		printf("5. Filtreaza\n");
		printf("6. Sorteaza\n");
		printf("99. \texit\n");
		printf(">>>");
		int s1=scanf("%d", &cmd);
		
		if (s1 != 0) {
			if (cmd == 1)
				addUI(ui);
			else if (cmd == 2)
				updateUI(ui);
			else if (cmd == 3)
				printUI(ui);
			else if (cmd == 4)
				deleteUI(ui);
			else if (cmd == 5)
				filterUI(ui);
			else if (cmd == 6)
				sortUI(ui);
			else if (cmd == 99)
			{
				destroyUI(ui);
				break;
			}
		}
		else printf("Comanda invalida!\n");
		
	}
}