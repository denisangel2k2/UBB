#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
typedef struct{
    pthread_barrier_t *b;
    pthread_mutex_t* m;
    int* flag;
}data;

void* f(void* arg){    
    data d=*((data*)arg);
    pthread_barrier_wait(d.b);
    while(1){
        int nr=random()%111112;
        pthread_mutex_lock(d.m);
        if (*(d.flag)==0){
            
        printf("%d\n",nr);
            if (nr%1001==0){
                printf("NUMARUL ESTE:%d\n",nr);
                *(d.flag)=1;
                break;
            } 
        }
        else{
            break;
        }
        pthread_mutex_unlock(d.m);
    }
    pthread_mutex_unlock(d.m);
    return NULL;
}
int main(int argc, char** argv){

    srandom(getpid());
    int n=atoi(argv[1]);
    pthread_mutex_t* m=malloc(sizeof(pthread_mutex_t));
    pthread_barrier_t *b=malloc(sizeof(pthread_barrier_t));
    int* flag=malloc(sizeof(int));
    *flag=0;
    pthread_mutex_init(m,NULL);
    pthread_barrier_init(b,NULL,n);
    data d;
    d.flag=flag;
    d.m=m;
    d.b=b;

    pthread_t th[n];

    for (int i=0; i<n; i++){
        pthread_create(&th[i],NULL,f,&d);
    }
    for (int i=0; i<n; i++){
        pthread_join(th[i],NULL);
    }
    pthread_mutex_destroy(m);
    pthread_barrier_destroy(b);
    free(m);
    free(b);
    free(flag);

    return 0;
}
