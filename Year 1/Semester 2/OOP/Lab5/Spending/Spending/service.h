#pragma once

typedef struct {
    repository* repo;
    VectorDinamic* historyList;
    int historyIndex;

} service;


service* create_service(repository* repo);
void destroyHistory(VectorDinamic* v);
void delete_service(service* srv);
int service_add(service* srv, int ap_no, double sum, char* type);
int service_modify(service* srv, int id, double sum, char* type);
int service_remove(service* srv, int id);
char* service_order(service* srv, int op, int type);
char* service_filter(service* srv, char* field, char* key);
char* service_print(service* srv);

int undo(service* srv);
void test_service();