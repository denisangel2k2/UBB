#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main(int argc, char** argv){
    int p2f[2];
    int f2p[2];
    if (pipe(p2f)==-1){
        printf("ERROR!\n");
        exit(1);
    }
    if (pipe(f2p)==-1){
        printf("ERROR!\n");
        close(p2f[0]); close(p2f[1]);
        exit(1);
    }

    int Fork=fork();


    if (Fork==-1)
    { 
        close(p2f[0]); close(p2f[1]);
        close(f2p[0]); close(f2p[1]);
        printf("EROARE!!!\n");
    }
    //fiu
    else if (Fork==0){
        close(f2p[0]); close(p2f[1]);
        char* filepath=(char*)malloc(20);
        char* sir=(char*)malloc(50);
        int lungime=0;
        if (read(p2f[0],&lungime,sizeof(int))>0){
            if (read(p2f[0], filepath,lungime*sizeof(char))>0){
                int desc=open(filepath,O_RDONLY);
                int lungime_sir=0;
                int poz=-1;    
                while((lungime_sir=read(desc,sir,50))>0){
                    for (int i=0; i<lungime_sir; i++)
                        if (sir[i]=='.')
                        {poz=i;
                            break;}
                    if (poz!=-1)
                        for (int i=0; i<poz; i++)
                            if (sir[i]>='a' && sir[i]<='z')
                                sir[i]-=32;
                    if (write(f2p[1],&lungime_sir,sizeof(int))>0){
                        if(write(f2p[1],sir,lungime_sir*sizeof(char))<0)
                        {
                            free(filepath);
                            free(sir);
                            exit(1);
                        }
                    }
                    else {
                       
                        free(filepath);
                        free(sir);
                        exit(1);
                    }

                }
                close(desc);

            }
            else{
                //close pipes
                free(filepath);
                free(sir);
                exit(1);
            } 
        }
        free(filepath);
        free(sir);
        close(f2p[1]); close(p2f[0]);
        exit(0);
    }    //parinte
    close(f2p[1]); close(p2f[0]);
    char* filepath=(char*)malloc(20);
    memset(filepath,0,20);
    scanf("%s",filepath);
    int lungime=strlen(filepath);
    if (write(p2f[1],&lungime,sizeof(int))>0)
        if(write(p2f[1],filepath,sizeof(char)*lungime)>0){

            char* cuvinte=(char*)malloc(50);
            while(1){
                int lungime=0;
                if (read(f2p[0],&lungime,sizeof(int))>0){
                    if (read(f2p[0],cuvinte,lungime*sizeof(char))>0){
                        printf("%s",cuvinte);    
                    }
                }
                if (lungime<50)
                    break;
            }

            free(cuvinte);
        }
    free(filepath);
    close(f2p[0]); close(p2f[1]);

    return 0;
}
