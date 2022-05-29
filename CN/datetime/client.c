#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: ./client <Server IP> <Server Port>");
    exit(0);
  }
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_port = htons(atoi(argv[2]));
  servaddr.sin_family = AF_INET;
  int sockfd;
  if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    perror("Cannot create socket!");
    exit(0);
  }
  int len =
      sendto(sockfd, "", 1, 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
  printf("Sent request to server!\n");
  char buf[1000];
  recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
  printf("Server Date Time : %s\n", buf);
  return 0;
}