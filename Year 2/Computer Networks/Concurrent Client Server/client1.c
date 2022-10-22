#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(){
    int c;
    struct sockaddr_in server;
    c=socket(AF_INET,SOCK_STREAM,0);
    if (c<0){
        printf("Eroare socket\n");
        return 1;
    }
    memset(&server,0,sizeof(server));
    server.sin_port=htons(1111);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr("127.0.0.1");


    if (connect(c, (struct sockaddr*) &server, sizeof(server))<0){
        printf("Eroare la conectarea la server!\n");
        return 1;
    }
    int* poz=(int*)malloc(100*sizeof(int));
    char* sir=(char*)malloc(100*sizeof(char));
    char t;

    printf("Introduceti string-ul: " );
    fgets(sir,100,stdin);
    printf("Stringul este %s\n",sir);    
     
    printf("\nIntroduceti caracterul: ");
    fgets(&t, 3, stdin); 
    
    send(c, (const char*) sir, 100*sizeof(char), 0);
    send(c, &t, sizeof(t), 0);
   
    uint16_t lgpoz;
    recv(c, &lgpoz, sizeof(lgpoz),0);
    recv(c, (int*)poz, 100*sizeof(int),0);
    printf ("Pozitiile pe care se afla caracterul %c sunt ", t);
    lgpoz=ntohs(lgpoz);
    for (int i=0; i<lgpoz; i++)
        printf("%d ", ntohs(poz[i]));

    free(poz);
    free(sir);
    close(c);


}
