#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
void deservire_client(int c){

    char caracter;
    char* sir=(char*)malloc(1000 * sizeof(char));
    int* poz=(int*)malloc(100*sizeof(int));


    recv(c, (char*)sir, 100*sizeof(char), 0);
    recv(c,&caracter,sizeof(caracter), 0);
    
    printf ("Am primit %s\n",sir);
    uint16_t lgpoz=0;
    for (int i=0; sir[i]!='\0'; i++)
        if (sir[i]==caracter)
            poz[lgpoz++]=i;
     
    for (int i=0; i<lgpoz; i++)
        poz[i]=htons(poz[i]);
    lgpoz=htons(lgpoz);

    send(c,&lgpoz,sizeof(lgpoz),0);
    send(c,(int*)poz,100*sizeof(int),0);
    free(poz);
    free(sir);

    close(c);

}

int main(){


    int s;
    struct sockaddr_in server, client;

    uint16_t c, l;
    //AF_INET=IPV4
    //SOCK_STREAM=TCP
    s=socket(AF_INET, SOCK_STREAM, 0);
    if (s<0){
        printf("Eroare socket!\n");
        return 1;
    }
    memset(&server, 0, sizeof(server));

    server.sin_port=htons(1111);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=INADDR_ANY;

    if (bind(s, (struct sockaddr*) &server, sizeof(server))<0){
        printf("Binding error!\n");
        return 1;
    } 
    listen(s,5);

    l=sizeof(client);
    memset(&client, 0, sizeof(client));

    while(1)

    {

        c=accept(s,(struct sockaddr*) &client, &l);
        printf("A intrat cineva pe server!\n");

        if (fork()==0){

            deservire_client(c);
            return 0;
        }

    }

    return 0;

}
