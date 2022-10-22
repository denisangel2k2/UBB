#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

int getRand(){
    return random() % 1000 - 500;
}
pthread_rwlock_t m;
void* f1(void* a){
   // pthread_rwlock_rdlock(&m);
    int* n=(int*)a;
   // pthread_mutex_unlock(&m);
    while(1)
    {
        pthread_rwlock_wrlock(&m);
        if (*n>=0 && *n<=1000){
            int x=getRand();
            *n=*n+x;
            printf("%d\n",*n);
        }
        else{
            pthread_rwlock_unlock(&m);
            return NULL;        
        }
        pthread_rwlock_unlock(&m);

    }
    
    return NULL;
}

int main(int argc, char** argv){

    int n;
    n=500;
    srandom(getpid());
    pthread_t t[2];
    pthread_rwlock_init(&m,NULL);
    pthread_create(&t[0],NULL,f1,&n);
    pthread_create(&t[1],NULL,f1,&n);
    pthread_join(t[0],NULL);
    pthread_join(t[1],NULL);
    pthread_rwlock_destroy(&m);
    printf("FINAL: %d",n);

    return 0;
}
