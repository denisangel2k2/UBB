#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int getRandInt(int min, int max){
    return random() % (max-min) +min;
}

int main(int argc, char** argv){
    int a2b[2],b2c[2],c2a[2];
    if (pipe(a2b)!=0){
        printf("EROARE");
        exit(1);
    }

    if (pipe(b2c)!=0){
        printf("EROARE");
        close (a2b[0]); close(a2b[1]);
        exit(1);

    }
    if (pipe(c2a)!=0){
        printf("EROARE");
        close (a2b[0]); close(a2b[1]);
        close(b2c[0]); close(b2c[1]);
        exit(1);

    }
    //B
    if (fork()==0){
        int n;
        int* sir;
        close(a2b[1]); close(b2c[0]);
        close(c2a[0]); close(c2a[1]);
        srandom(getpid());
       
        // testez si daca read<=0, la fel si write
        read(a2b[0],&n,sizeof(int));
        sir=(int*)malloc(n*sizeof(int));
        read(a2b[0],sir,n*sizeof(int));
      
        int nr;
        for (int i=0; i<n; i++)
        {
           nr=getRandInt(2,5);
           sir[i]+=nr;
           printf("Procesul B: Numarul %d\n",sir[i]);
        }  
        write(b2c[1],&n, sizeof(int));
        write(b2c[1],sir,n*sizeof(int));

        free(sir);
        close(a2b[0]);
        close(b2c[1]);
        exit(0);
    }
    //testez fork()==-1
    //C
    if (fork()==0){
        int n;
        int* sir;

        close(b2c[1]); close(c2a[0]);
        close(a2b[0]); close(a2b[1]);

        read(b2c[0],&n,sizeof(int));
        sir=(int*)malloc(n*sizeof(int));
        read(b2c[0],sir,n*sizeof(int));

        int sum=0;
        for(int i=0; i<n; i++)
            sum+=sir[i];
        printf("Procesul C : Suma %d\n",sum);
        write(c2a[1],&sum,sizeof(int));

        free(sir);
        close(b2c[0]); close(c2a[1]);
        exit(0);
    }

    //A
    close(b2c[0]); close(b2c[1]);
    close(c2a[1]); close(a2b[0]);
    int n;
    scanf("%d",&n);
    int* sir=(int*)malloc(n*sizeof(int));
    for (int i=0; i<n; i++)
        scanf("%d",&sir[i]);
    write(a2b[1],&n,sizeof(int));
    write(a2b[1],sir,n*sizeof(int));

    int suma=0;
    read(c2a[0],&suma,sizeof(int));
    printf("Procesul A : Suma %d",suma);

    free(sir);
    close(a2b[1]); close(c2a[0]);
    
        return 0;
}
