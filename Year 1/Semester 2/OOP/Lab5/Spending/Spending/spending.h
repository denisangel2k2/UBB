#pragma once

typedef struct {
    int ap_no;
    double sum;
    char* type;
} spending_type;

spending_type* create_spending(int ap_no, double sum, char* type);
void modify_spending(spending_type* spending, double sum, char* type);
void delete_spending(spending_type* spending);
void test_domain();
