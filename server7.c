#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6540

void main(){
     struct sockaddr_in client,server;
    int sd, nsd, clen=sizeof(client);
    char msg[512];

    bzero((char *)&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_port=htons(SERVER_PORT);
    
    sd=socket(AF_INET,SOCK_DGRAM,0);
    bind(sd,(struct sockaddr*)&server,sizeof(server));
    // listen(sd, 5);

    while(1){
    do{
        memset(msg,0x0,512);
        recvfrom(sd,msg,512,0,(struct sockaddr*)&client,&clen);
        sendto(sd,msg,strlen(msg)+1,0,(struct sockaddr*)&client,sizeof(client));
    }while(strcmp(msg,"stop"));
    }
}