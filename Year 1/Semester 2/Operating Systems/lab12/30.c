#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define THR_NUM 400

pthread_barrier_t barr;

pthread_mutex_t mtx[THR_NUM];
pthread_cond_t cv[THR_NUM];

pthread_t threads1[THR_NUM];
pthread_t threads2[THR_NUM];
pthread_t threads3[THR_NUM];
pthread_t threads4[THR_NUM];
int jucator[THR_NUM];

typedef struct {
    int echipa_curenta;
    int thread_no;
}data;

void* f(void* a){

    pthread_barrier_wait(&barr);
    data info=*(data*)a;
    free(a);
    pthread_mutex_lock(&mtx[info.echipa_curenta]);
    while(jucator[info.echipa_curenta]<info.thread_no){
        pthread_cond_wait(&cv[info.echipa_curenta],&mtx[info.echipa_curenta]);
        
    
    }
    if (jucator[info.echipa_curenta]==3)
        printf("ECHIPA %d a castigat!\n",info.echipa_curenta);
    usleep(150*1000);
    printf("\t\tASTEPT!\n");
    jucator[info.echipa_curenta]++;
     
    pthread_cond_broadcast(&cv[info.echipa_curenta]);
    pthread_mutex_unlock(&mtx[info.echipa_curenta]);
    return NULL;
}

int main(int argc, char** argv){
    int n;
    printf("Introduceti nr=");
    if(scanf("%d",&n)<0) perror("eroare scanf");
    pthread_barrier_init(&barr,NULL,4*n);
    
    for (int i=0; i<n; i++)
    {

        
        pthread_mutex_init(&mtx[i],NULL);
        pthread_cond_init(&cv[i],NULL);
       
        data* k1=(data*)malloc(sizeof(data));
        (*k1).echipa_curenta=i;
        (*k1).thread_no=0;


        pthread_create(&threads1[i],NULL,f,k1);

        data* k2=(data*)malloc(sizeof(data));
        (*k2).echipa_curenta=i;
        (*k2).thread_no=1;


        pthread_create(&threads2[i],NULL,f,k2);
       
         data* k3=(data*)malloc(sizeof(data));
        (*k3).echipa_curenta=i;
        (*k3).thread_no=2;


        pthread_create(&threads3[i],NULL,f,k3);
       
        data* k4=(data*)malloc(sizeof(data));
        (*k4).echipa_curenta=i;
        (*k4).thread_no=3;


        pthread_create(&threads4[i],NULL,f,k4);
    }
    for (int i=0; i<n; i++){
        pthread_join(threads1[i],NULL);
        pthread_join(threads2[i],NULL);
        pthread_join(threads3[i],NULL);
        pthread_join(threads4[i],NULL);

        pthread_mutex_destroy(&mtx[i]);
        pthread_cond_destroy(&cv[i]);
            
    }

    pthread_barrier_destroy(&barr);


    return 0;
}
