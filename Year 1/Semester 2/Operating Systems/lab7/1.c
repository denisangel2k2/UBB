#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
int main(int argc, char** argv){
    
    if (argc<2){
        printf("Nu exista argumente");
        return 0;            
    }

    int f2p[2];
    pipe(f2p);

    FILE* desc=fopen(argv[1],"r");

    if (fork()==0){
        close(f2p[0]);
        int n;
        fscanf(desc,"%d",&n);

        int **mat;
        mat=(int**)malloc(n*sizeof(int*));
        for (int i=0; i<n; i++)
            mat[i]=(int*)malloc(n*sizeof(int));

        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                fscanf(desc,"%d",&mat[i][j]);

        int suma=0;
        for (int i=0; i<n; i++)
            suma+=mat[i][i];

        write(f2p[1], &suma, sizeof(int));
        close(f2p[1]);

        for (int i=0; i<n; i++)
            free(mat[i]);
        free(mat);

        exit(0);
    }

    int sum;
    read(f2p[0],&sum,sizeof(int));
    printf("%d",sum);
    fclose(desc);
    close(f2p[0]); close(f2p[1]);
    wait(0);

    return 0;
}
