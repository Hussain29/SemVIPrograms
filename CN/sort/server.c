#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Incorrect syntax!\nUsage: ./server portno");
    exit(0);
  }
  struct sockaddr_in servaddr;
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(0L);
  servaddr.sin_port = htons(atoi(argv[1]));
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Socket Creation Failed!\n");
    exit(0);
  }
  if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
    perror("Socket Binding Failed!\n");
    exit(0);
  }
  struct sockaddr_in cliaddr;
  int cliaddrlen = 0;
  while (1) {
    char buf[500];
    int len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&cliaddr,
                       &cliaddrlen);
    buf[len] = '\0';
    printf("Recieved Message : %s from client %s \n", buf,
           inet_ntoa(cliaddr.sin_addr));
    int i, j;
    for (i = 0; i < len; i += 2) {
      for (j = i + 2; j < len; j += 2) {
        if (atoi(buf+i) > atoi(buf+j)) {
          char x = buf[i];
          buf[i] = buf[j];
          buf[j] = x;
        }
      }
    }
    sendto(sockfd, buf, len, 0, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
  }
}