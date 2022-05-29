#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: ./client <Server IP> <Server Port> <Message>");
    exit(0);
  }
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(atoi(argv[2]));
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Can't create socket!");
    exit(0);
  }
  int len = sendto(sockfd, argv[3], strlen(argv[3]), 0,
                   (struct sockaddr *)&servaddr, sizeof(servaddr));
  printf("Sent %s to server!\n", argv[3]);
  char buf[1000];
  recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
  buf[sizeof(buf) - 1] = '\0';
  printf("Recieved %s from server!\n", buf);
  return 0;
}