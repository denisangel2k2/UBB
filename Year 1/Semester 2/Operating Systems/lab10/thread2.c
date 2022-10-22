#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
int vf[10];
pthread_mutex_t m;

void* f(void* a){
    int numar=*(int*)a;
    free(a);

    while(numar){
        pthread_mutex_lock(&m);
        vf[numar%10]++;
        pthread_mutex_unlock(&m);
        numar/=10;
    }
    return NULL;
    
}
int main(int argc, char** argv){
    pthread_t t[argc];

    int i=1;
    pthread_mutex_init(&m,NULL);
    while(i<argc){
        int* numar=(int*)malloc(sizeof(int));
        *numar=atoi(argv[i]);
        pthread_create(&t[i],NULL,f,numar);
        i++;
    }

    for (int i=0; i<argc; i++)
        pthread_join(t[i],NULL);

    for (int i=0; i<=9; i++)
        printf("Cifra %d : %d\n",i,vf[i]);
    pthread_mutex_destroy(&m);
    
    return 0;
}
