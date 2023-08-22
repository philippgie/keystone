#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int
main() {
  int s;
  struct sockaddr_in server, addr;
  socklen_t len;

  // make a socket
  if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    char* err = "socket() failed\n";
    write(1, err, strlen(err));
  }

  // connect to a server
  server.sin_family = AF_INET;
  if(inet_pton(AF_INET, "8.8.8.8", &server.sin_addr)<=0) {
    char* err = "inet_pton() failed\n";
    write(1, err, strlen(err));
  }
  server.sin_port = htons(443);

  if(connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
    char* err = "connect() failed %d\n";
    write(1, err, strlen(err));
  }

  // get the peer name
  // we know we just connected to 63.161.169.137:80, so this should print:
  //    Peer IP address: 63.161.169.137
  //    Peer port      : 80

  len = sizeof(addr);
  getpeername(s, (struct sockaddr*)&addr, &len);
  write(1, inet_ntoa(addr.sin_addr), strlen(inet_ntoa(addr.sin_addr)));
  char port[5];
  snprintf(port, 5, "%d", ntohs(addr.sin_port));
  write(1, port, strlen(port));

  return 0;
}
