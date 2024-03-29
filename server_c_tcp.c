/* 
    Tiange Wang, ID: 3717659, CS 176A Homework 2
    Code Cited: http://www.linuxhowtos.org/data/6/server.c, Sockets Tutorial, Example TCP Server.
*/
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno;
     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr,"usage: %s port\n", argv[0]);
         exit(1);
     }
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&(int){ 1 }, sizeof(int)) == -1) {
        error("setsockopt");
        exit(1);
     }

     if (sockfd < 0) 
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
                 (struct sockaddr *) &cli_addr, 
                 &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");
     bzero(buffer,256);
     int wrongStr = 0;
     while(1) {
        wrongStr = 0;
        n = read(newsockfd,buffer,255);
        if (n < 0) error("ERROR reading from socket");
        if(strlen(buffer) == 0) {
            n = write(newsockfd,"Sorry, cannot compute!",23);
            if (n < 0) error("ERROR writing to socket");
            close(newsockfd);
            close(sockfd);
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&(int){ 1 }, sizeof(int)) == -1) {
                error("setsockopt");
                exit(1);
            }

            if (sockfd < 0) 
                error("ERROR opening socket");
            bzero((char *) &serv_addr, sizeof(serv_addr));
            portno = atoi(argv[1]);
            serv_addr.sin_family = AF_INET;
            serv_addr.sin_addr.s_addr = INADDR_ANY;
            serv_addr.sin_port = htons(portno);
            if (bind(sockfd, (struct sockaddr *) &serv_addr,
                    sizeof(serv_addr)) < 0) 
                    error("ERROR on binding");
            listen(sockfd,5);
            clilen = sizeof(cli_addr);
            newsockfd = accept(sockfd, 
                        (struct sockaddr *) &cli_addr, 
                        &clilen);
            if (newsockfd < 0) 
                error("ERROR on accept");
            bzero(buffer,256);
            wrongStr = 1;
        }
        for(int i = 0; i < strlen(buffer); i++) {
            if(buffer[i] < '0' || buffer[i] > '9') {
                n = write(newsockfd,"Sorry, cannot compute!",23);
                if (n < 0) error("ERROR writing to socket");
                close(newsockfd);
                close(sockfd);
                sockfd = socket(AF_INET, SOCK_STREAM, 0);
                if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&(int){ 1 }, sizeof(int)) == -1) {
                    error("setsockopt");
                    exit(1);
                }

                if (sockfd < 0) 
                    error("ERROR opening socket");
                bzero((char *) &serv_addr, sizeof(serv_addr));
                portno = atoi(argv[1]);
                serv_addr.sin_family = AF_INET;
                serv_addr.sin_addr.s_addr = INADDR_ANY;
                serv_addr.sin_port = htons(portno);
                if (bind(sockfd, (struct sockaddr *) &serv_addr,
                        sizeof(serv_addr)) < 0) 
                        error("ERROR on binding");
                listen(sockfd,5);
                clilen = sizeof(cli_addr);
                newsockfd = accept(sockfd, 
                            (struct sockaddr *) &cli_addr, 
                            &clilen);
                if (newsockfd < 0) 
                    error("ERROR on accept");
                bzero(buffer,256);
                wrongStr = 1;
            }
        }
        if (wrongStr == 0) {
            int total = 0;
            for(int i = 0; i < strlen(buffer); i++) {
                total += (buffer[i] - '0');
            }
            sprintf(buffer, "%i", total);
            n = write(newsockfd, buffer, strlen(buffer));
            if (n < 0) error("ERROR writing to socket");
            if(strlen(buffer) <= 1) {
                close(newsockfd);
                close(sockfd);
                sockfd = socket(AF_INET, SOCK_STREAM, 0);
                if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&(int){ 1 }, sizeof(int)) == -1) {
                    error("setsockopt");
                    exit(1);
                }

                if (sockfd < 0) 
                    error("ERROR opening socket");
                bzero((char *) &serv_addr, sizeof(serv_addr));
                portno = atoi(argv[1]);
                serv_addr.sin_family = AF_INET;
                serv_addr.sin_addr.s_addr = INADDR_ANY;
                serv_addr.sin_port = htons(portno);
                if (bind(sockfd, (struct sockaddr *) &serv_addr,
                        sizeof(serv_addr)) < 0) 
                        error("ERROR on binding");
                listen(sockfd,5);
                clilen = sizeof(cli_addr);
                newsockfd = accept(sockfd, 
                            (struct sockaddr *) &cli_addr, 
                            &clilen);
                if (newsockfd < 0) 
                    error("ERROR on accept");
                bzero(buffer,256);
            }
        }
     }
}
