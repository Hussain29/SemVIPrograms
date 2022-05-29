#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Incorrect syntax!\nUsage: ./server portno");
    exit(0);
  }
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[1]));
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Cannot create socket!");
    exit(0);
  }
  if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0) {
    perror("Could not bind socket!");
    exit(0);
  }
  struct sockaddr_in cliaddr;
  memset(&cliaddr, 0, sizeof(cliaddr));
  int cliaddrlen = 0;
  while (1) {
    char buf[500];
    int len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr,
                       &cliaddrlen);
    buf[len] = '\0';
    printf("Recieved Message : %s from client %s \n", buf,
           inet_ntoa(cliaddr.sin_addr));
    sendto(sockfd, buf, len, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
  }
  return 0;
}