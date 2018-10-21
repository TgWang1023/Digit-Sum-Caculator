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
   char buffer[1024];
   char response[1024] = "From Server: ";

   if (argc < 2) {
      fprintf(stderr, "ERROR, no port provided\n");
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
   n = recvfrom(sock,buffer,1024,0,(struct sockaddr *)&from,&fromlen);
   if (n < 0) error("recvfrom");
     buffer[strlen(buffer) - 1] = 0;
     int digitOnly = 1;
     if(strlen(buffer) == 0) {
         digitOnly = 0;
         n = sendto(sock,"From Server: Sorry, cannot compute!\n",36,0,(struct sockaddr *)&from,fromlen);
         if (n < 0) error("send to");
     }
     for(int i = 0; i < strlen(buffer); i++) {
         if(buffer[i] < '0' || buffer[i] > '9') {
             digitOnly = 0;
             n = sendto(sock,"From Server: Sorry, cannot compute!\n",36,0,(struct sockaddr *)&from,fromlen);
             if (n < 0) error("send to");
             break;
         }
     }
     if(digitOnly == 1) {
         while(strlen(buffer) > 1) {
            int total = 0;
            for(int i = 0; i < strlen(buffer); i++) {
                total += (buffer[i] - '0');
            }
            sprintf(buffer, "%i", total);
            strcat(response, buffer);
            strcat(response, "\n");
            n = sendto(sock, response, strlen(response), 0, (struct sockaddr *)&from,fromlen);
            if (n < 0) error("send to");
            strcpy(response, "From Server: ");
         }
     }
   return 0;
}