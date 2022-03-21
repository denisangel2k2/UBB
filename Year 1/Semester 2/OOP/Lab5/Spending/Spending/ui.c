//
// Created by leonard on 16.03.2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spending.h"
#include "repository.h"
#include "service.h"
#include "ui.h"

ui_type* create_ui(service* srv) {
    ui_type* ui = malloc(sizeof(ui_type));
    ui->srv = srv;
    return ui;
}

void delete_ui(ui_type* ui) {
    delete_service(ui->srv);
    free(ui);
}

void ui_help() {
    printf("'help' - afiseaza comenzile\n");
    printf("'add' - adauga o factura\n");
    printf("'remove' - sterge o factura\n");
    printf("'modify' - modifica o factura\n");
    printf("'print' - afiseaza toate facturile\n");
    printf("'order' - ordoneaza facturile dupa suma (crescator/descrescator)\n");
    printf("'filter' - filtreaza facturile dupa suma sau tip (ex tip = 'gaz')\n");
    printf("'undo' - efectueaza undo la ultima operatie\n");
    printf("'nfilter' - efectueaza filtrare dupa numar si suma\n");
}

void ui_add(service* srv) {
    printf("Introdu numarul apartamentului, suma si tipul cheltuielii:\n");
    int no_ap;
    double sum;
    char* type = malloc(sizeof(char) * 10);
    scanf("%d %lf %s", &no_ap, &sum, type);
    service_add(srv, no_ap, sum, type);
    free(type);
}
void ui_remove(service* srv) {
    int id;
    printf("Introdu id-ul cheltuielii: ");
    scanf("%d", &id);
    service_remove(srv, id);
}
void ui_modify(service* srv) {
    printf("Introdu id-ul, noua suma si noul tip pentru cheltuiala: ");
    int id;
    double sum;
    char* type = malloc(sizeof(char) * 10);
    scanf("%d %lf %s", &id, &sum, type);
    service_modify(srv, id, sum, type);
    free(type);
}
void ui_print(service* srv) {
    char* result = service_print(srv);
    if (result == NULL) {
        printf("Lista este goala or malloc error!\n");
    }
    else {
        printf("%s", result);
        free(result);
    }
}

void ui_undo(ui_type* ui) {
    int un=undo(ui->srv);
    if (un == -1) {
        printf("Nu se poate efectua undo!\n");
    }
}

void ui_order(service* srv) {
    int op = 0, type = 0;
    printf("Introdu 0 pentru a sorta descrescator si 1 pentru crescator: ");
    scanf("%d", &op);
    printf("Introdu 0 pentru a sorta dupa suma si 1 pentru a sorta dupa tip: ");
    scanf("%d", &type);
    char* result = service_order(srv, op, type);
    printf("%s", result);
    free(result);
}

void ui_filter(service* srv) {
    //field and key + validation
    char* field = malloc(sizeof(char) * 10);
    char* key = malloc(sizeof(char) * 10);
    char* result;
    printf("Introdu campul dupa care vrei sa filtrez(numar/suma/tip): ");
    scanf("%s", field);
    printf("Introdu valoarea dupa care vrei sa filtrezi, %s = ", field);
    scanf("%s", key);
    result = service_filter(srv, field, key);
    printf("%s", result);
    free(result);
    free(field);
    free(key);
}
void ui_filter_new(ui_type* ui) {
    printf("Filtrare dupa numar si suma:\n\n");
    int numar;
    printf("Numar: ");
    scanf("%d", &numar);
    double suma;
    printf("\nSuma: ");
    scanf("%lf", &suma);

    char* result = serv_fitler_new(ui->srv, numar, suma);
    if (result == NULL)
        printf("Nu este nimic de printat!\n");
    else {
        printf("%s", result);
        free(result);
    }
    
}
void ui_run(ui_type* ui) {
    char* input = malloc(sizeof(char) * 50);
    printf("Salutare, aceasta aplicatie gestioneaza facturile tale\n"
        "pentru a afla ce poti face in aplicatie introdu comanda 'help'\n"
        "iar daca vrei sa iesi din aplicatie introdu comanda 'exit'\n");
    while (1) {
        scanf("%s", input);
        if (!strcmp(input, "exit")) {
            printf("Bye\n");
            free(input);
            return;
        }
        else if (!strcmp(input, "help")) {
            ui_help();
        }
        else if (!strcmp(input, "add")) {
            ui_add(ui->srv);
        }
        else if (!strcmp(input, "modify")) {
            ui_modify(ui->srv);
        }
        else if (!strcmp(input, "remove")) {
            ui_remove(ui->srv);
        }
        else if (!strcmp(input, "order")) {
            ui_order(ui->srv);
            return;
        }
        else if (!strcmp(input, "filter")) {
            ui_filter(ui->srv);
            return;
        }
        else if (!strcmp(input, "print")) {
            ui_print(ui->srv);
        }
        else if (!strcmp(input, "undo")) {
            ui_undo(ui);
        }
        else if (!strcmp(input, "nfilter")) {
            ui_filter_new(ui);
        }
        else {
            printf("Ai introdus o comanda invalida, introdu 'help' daca te-ai blocat\n");
        }
    }
    free(input);
}