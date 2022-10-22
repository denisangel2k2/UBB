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
    int a2b[2], b2a[2];
    pipe(a2b);
    pipe(b2a);


    int f=fork();
    if (f==0){
        srandom(getpid());
        close(a2b[1]);
        close(b2a[0]);

        int nr=getRandInt(100,1000);
        printf("%d\n",nr);
        int found=0, guess=0;
        while(!found){
            read(a2b[0],&guess,sizeof(int));
            if (abs(guess-nr)<50)
                found=1;
            write(b2a[1],&found,sizeof(int));

        }
        close(a2b[0]);
        close(b2a[1]);
        exit(0);
    }
    close(a2b[0]);
    close(b2a[1]);
    srandom(getpid());
    int found=0, count=0;

    while(!found){
        count++;
        int guess=getRandInt(50,1050);
        write(a2b[1],&guess,sizeof(int));
        read(b2a[0],&found,sizeof(int));
    }
    wait(0);
    printf("Count : %d",count);
    close(a2b[1]);
    close(b2a[0]);

    return 0; 
}
