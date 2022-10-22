#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv){

    if (argc<3){
        printf("Argumente prea putine");
        exit(1);
    }

    FILE *fd_in=fopen(argv[1],"r");
    FILE *fd_out=fopen(argv[2],"w");

    if (fd_in==NULL)
    {
        //fclose(fd_in);
        perror("Eroarea la deschidere fisier : ");
        exit(1);
    }
    if (fd_out==NULL)
    {
        fclose(fd_in);
        perror("Eroarea la deschidere fisier : ");
        exit(1);
    }

    //code
    int **mat;
    int nrL, nrC;

    fscanf(fd_in, "%d %d", &nrL, &nrC);
    mat=(int**)malloc(nrL*sizeof(int*));

    for (int i=0; i<nrL; i++)
        mat[i]=(int*)malloc(nrC*sizeof(int));

    for (int i=0; i<nrL; i++)
        for (int j=0; j<nrC; j++)
            fscanf(fd_in, "%d", &mat[i][j]);

    for (int i=0; i<nrL; i++){
        for (int j=0; j<nrC; j++)
              fprintf(fd_out,"%d ",mat[i][j]);
                   fprintf(fd_out,"\n");
                }
    for (int i=0; i<nrL; i++)
        free(mat[i]);

    free(mat);

    fclose(fd_in);
    fclose(fd_out);

    return 0;
}
