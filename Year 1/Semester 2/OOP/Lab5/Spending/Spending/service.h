#pragma once

typedef struct {
    repository* repo;
    VectorDinamic* historyList;
    int historyIndex;

} service;


service* create_service(repository* repo);
/// <summary>
/// 
/// </summary>
/// <param name="v"></param>
void destroyHistory(VectorDinamic* v);
void delete_service(service* srv);
int service_add(service* srv, int ap_no, double sum, char* type);
int service_modify(service* srv, int id, double sum, char* type);
int service_remove(service* srv, int id);
char* service_order(service* srv, int op, int type);
char* service_filter(service* srv, char* field, char* key);
char* service_print(service* srv);
/// <summary>
/// 
/// </summary>
/// <param name="srv"></param>
/// <param name="numar"></param>
/// <param name="suma"></param>
/// <returns></returns>
char* serv_fitler_new(service* srv, int numar, double suma);

int undo(service* srv);
void test_service();