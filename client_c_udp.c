/* 
    Tiange Wang, ID: 3717659, CS 176A Homework 2
    Code Cited: http://www.linuxhowtos.org/data/6/client_udp.c, Sockets Tutorial, Example TCP Server.
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[256];
   
   if (argc != 3) { printf("usage: %s hostname port\n", argv[0]);
                    exit(1);
   }
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");

   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);

   printf("Enter String: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    buffer[strlen(buffer) - 1] = '\0';
    while(1) {
        n = sendto(sock,buffer,strlen(buffer)+1,0,(const struct sockaddr *)&server,length);
        if(n < 0) 
            error("ERROR writing to socket");
        bzero(buffer,256);
        n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
        if(n < 0) 
            error("ERROR reading from socket");
        write(1,"From Server: ",13);
        write(1,buffer,n);
        write(1,"\n",1);
        if(strlen(buffer) <= 1 || strcmp(buffer, "Sorry, cannot compute!") == 0) {
            close(sock);
            return 0;
        }
    }

}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}