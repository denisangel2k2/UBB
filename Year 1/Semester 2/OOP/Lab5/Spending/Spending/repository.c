//
// Created by leonard on 13.03.2022.
//

#include "spending.h"
#include "repository.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "spending.h"

repository* create_repository() {

    repository* repo = malloc(sizeof(repository));
    repo->capacity = 1;
    repo->size = 0;
    repo->list = malloc(repo->capacity * sizeof(spending_type));

    return  repo;
}

repository* copyRepo(repository* repo) {

    repository* copieRepo = create_repository();
    for (int i = 0; i < repo->size; i++) {
        spending_type* sp = create_spending(repo->list[i]->ap_no, repo->list[i]->sum, repo->list[i]->type);
        repository_add(copieRepo, sp);
    }
    return copieRepo;

}

void delete_repository(repository* repo) {
    for (int i = 0; i < repo->size; ++i) {
        delete_spending(repo->list[i]);
    }
    
    free(repo->list);
    free(repo);
}

void realloc_repository(repository* repo, int new_capacity) {
    spending_type** new_list = malloc(new_capacity * sizeof(spending_type));
    for (int i = 0; i < repo->size; ++i) {
        new_list[i] = repo->list[i];
    }

   
    free(repo->list);
    
    repo->list = new_list;
    repo->capacity = new_capacity;
}

void repository_add(repository* repo, spending_type* spending) {
    if (repo->size == repo->capacity) {
        realloc_repository(repo, repo->capacity * 2);
    }
    repo->list[repo->size] = spending;
    repo->size++;
}

void repository_modify(repository* repo, int id, double sum, char* type) {
    modify_spending(repo->list[id], sum, type);
}

int repository_delete(repository* repo, int id) {
    if (id >= repo->size) {
        return 0;
    }
    delete_spending(repo->list[id]);
    for (int i = id; i <= repo->size; ++i) {
        repo->list[i] = repo->list[i + 1];
    }
    --repo->size;
    return 1;
}

repository* repository_filter(repository* repo, char* field, char* key) {
    repository* filtered = create_repository();
    realloc_repository(filtered, repo->size);
    //spending_type* s;
    for (int i = 0; i < repo->size; ++i) {
        if (!strcmp(field, "numar")) {
            if (atoi(key) == repo->list[i]->ap_no) {
               // s = create_spending(repo->list[i]->ap_no, repo->list[i]->sum, repo->list[i]->type);
               // repository_add(filtered, s);
                filtered->list[filtered->size] = repo->list[i];
                ++filtered->size;
            }
        }
        else if (!strcmp(field, "suma")) {
            if (atoi(key) == repo->list[i]->sum) {
               // s = create_spending(repo->list[i]->ap_no, repo->list[i]->sum, repo->list[i]->type);
               // repository_add(filtered, s);
                filtered->list[filtered->size] = repo->list[i];
                ++filtered->size;
            }
        }
        else if (!strcmp(field, "tip")) {
            if (!strcmp(key, repo->list[i]->type)) {
                //s = create_spending(repo->list[i]->ap_no, repo->list[i]->sum, repo->list[i]->type);
                //repository_add(filtered, s);
                filtered->list[filtered->size] = repo->list[i];
                ++filtered->size;
            }
        }
        
    }
    return filtered;
}



void swap(repository* ordered, int i, int j) {
    spending_type* spending = ordered->list[i];
    ordered->list[i] = ordered->list[j];
    ordered->list[j] = spending;
}

void sort(repository* ordered, int op, int type) {
    for (int i = 0; i < ordered->size; ++i) {
        for (int j = i + 1; j < ordered->size; ++j) {
            if (type==1) {
                if (op) {
                    if (strcmp(ordered->list[i]->type, ordered->list[j]->type) > 0) {
                        swap(ordered, i, j);
                    }
                }
                else {
                    if (strcmp(ordered->list[j]->type, ordered->list[i]->type) > 0) {
                        swap(ordered, i, j);
                    }
                }
            }
            else if (type == 0) {
                if (op) {
                    if (ordered->list[i]->sum > ordered->list[j]->sum) {
                        swap(ordered, i, j);
                    }
                }
                else {
                    if (ordered->list[i]->sum < ordered->list[j]->sum) {
                        swap(ordered, i, j);
                    }
                }
            }
            else if (type==2) {
                if (op) {
                    if (ordered->list[i]->sum > ordered->list[j]->sum)
                        swap(ordered, i, j);

                    else if (ordered->list[i]->sum - ordered->list[j]->sum < 0.00001)

                        if (strcmp(ordered->list[i]->type, ordered->list[j]->type) > 0)
                            swap(ordered, i, j);

                        else if (strcmp(ordered->list[i]->type, ordered->list[j]->type) == 0)
                            if (ordered->list[i]->ap_no > ordered->list[j]->ap_no)
                                swap(ordered, i, j);
                }
                else {
                    if (ordered->list[i]->sum < ordered->list[j]->sum)
                        swap(ordered, i, j);

                    else if (ordered->list[i]->sum - ordered->list[j]->sum < 0.00001)

                        if (strcmp(ordered->list[i]->type, ordered->list[j]->type) < 0)
                            swap(ordered, i, j);

                        else if (strcmp(ordered->list[i]->type, ordered->list[j]->type) == 0)
                            if (ordered->list[i]->ap_no < ordered->list[j]->ap_no)
                                swap(ordered, i, j);
                }
            }
          }
        }
    }

repository* repository_order(repository* repo, int op, int type) {
    repository* ordered = create_repository();
    realloc_repository(ordered, repo->size);
  
    ordered->size = repo->size;
    for (int i = 0; i < ordered->size; ++i) {
       
        ordered->list[i] = repo->list[i];
    }
    sort(ordered, op, type);
    return ordered;
}

void test_repository() {
    repository* repo = create_repository();
    spending_type* spending = create_spending(21, 100.5, "curent");
    repository_add(repo, spending);
    spending = create_spending(20, 205.12, "curent");
    repository_add(repo, spending);
    spending = create_spending(20, 200, "gaz");
    repository_add(repo, spending);
    repository_modify(repo, 0, 123, "curent");
    repository* filtered = repository_filter(repo, "numar", "20");
    assert(filtered->size == 2);
    free(filtered->list);
    free(filtered);
    filtered = repository_filter(repo, "suma", "200");
    assert(filtered->size == 1);
    free(filtered->list);
    free(filtered);
    filtered = repository_filter(repo, "tip", "curent");
    assert(filtered->size == 2);
    free(filtered->list);
    free(filtered);
    repository* ordered = repository_order(repo, 0, 0);
    free(ordered->list);
    free(ordered);
    ordered = repository_order(repo, 0, 1);
    free(ordered->list);
    free(ordered);
    ordered = repository_order(repo, 1, 0);
    free(ordered->list);
    free(ordered);
    ordered = repository_order(repo, 1, 1);
    free(ordered->list);
    free(ordered);
    ordered = repository_order(repo, 1, 2);
    free(ordered->list);
    free(ordered);
    ordered = repository_order(repo, 0, 2);
    free(ordered->list);
    free(ordered);
    assert(repository_delete(repo, 0) == 1);
    assert(repository_delete(repo, 100) == 0);
    delete_repository(repo);
}