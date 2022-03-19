//
// Created by leonard on 10.03.2022.
//

#include<assert.h>
#include <stdlib.h>
#include "string.h"
#include "spending.h"

spending_type* create_spending(int ap_no, double sum, char* type) {
    spending_type* spending = malloc(sizeof(spending_type));
    spending->type = malloc(sizeof(char) * 100);
    strcpy(spending->type, type);
    spending->sum = sum;
    spending->ap_no = ap_no;
    return spending;
}

void modify_spending(spending_type* spending, double sum, char* type) {
    spending->sum = sum;
    strcpy(spending->type, type);
}

void delete_spending(spending_type* spending) {
    free(spending->type);
    free(spending);
}

void test_domain() {
    int ap_no = 10;
    double sum = 20;
    char type[] = "gaz";
    spending_type* spending = create_spending(ap_no, sum, type);
    assert(spending->ap_no == ap_no);
    assert(spending->sum == sum);
    assert(!strcmp(spending->type, type));
    modify_spending(spending, 20.4, "curent");
    assert(spending->sum != sum);
    assert(strcmp(spending->type, type) != 0);
    delete_spending(spending);
}