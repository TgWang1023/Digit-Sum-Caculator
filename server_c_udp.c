/* 
    Tiange Wang, ID: 3717659, CS 176A Homework 2
    Code Cited: http://www.linuxhowtos.org/data/6/server_udp.c, Sockets Tutorial, Example TCP Server.
*/
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>
#include <stdio.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
   int sock, length, n;
   socklen_t fromlen;
   struct sockaddr_in server;
   struct sockaddr_in from;
   char buf[1024];

   if (argc < 2) {
      fprintf(stderr, "usage: %s port\n", argv[0]);
      exit(0);
   }
   
   sock=socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("Opening socket");
   length = sizeof(server);
   bzero(&server,length);
   server.sin_family=AF_INET;
   server.sin_addr.s_addr=INADDR_ANY;
   server.sin_port=htons(atoi(argv[1]));
   if (bind(sock,(struct sockaddr *)&server,length)<0) 
       error("binding");
   fromlen = sizeof(struct sockaddr_in);

   while(1) {
        n = recvfrom(sock,buf,1024,0,(struct sockaddr *)&from,&fromlen);
        if (n < 0) error("recvfrom");
        if(strlen(buf) == 0) {
            n = sendto(sock,"Sorry, cannot compute!",23,0,(struct sockaddr *)&from,fromlen);
            if (n < 0) error("sendto");
            close(sock);
            return 0; 
        }
        for(int i = 0; i < strlen(buf); i++) {
            if(buf[i] < '0' || buf[i] > '9') {
                n = sendto(sock,"Sorry, cannot compute!",23,0,(struct sockaddr *)&from,fromlen);
                if (n < 0) error("sendto");
                close(sock);
                return 0; 
            }
        }
        int total = 0;
        for(int i = 0; i < strlen(buf); i++) {
            total += (buf[i] - '0');
        }
        sprintf(buf, "%i", total);
        n = sendto(sock, buf, strlen(buf),0,(struct sockaddr *)&from,fromlen);
        if (n < 0) error("sendto");
        if(strlen(buf) <= 1) {
            close(sock);
            return 0; 
        }
     }
}