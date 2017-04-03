#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 9876 // default port
#define _DEBUG_ 0

int connect_server(struct sockaddr_in * dstAddr, int dstAddrLen) {
  int dstSocket;
  int retry = 0;
  int retryMax = 10;

  while (1) {
    //ソケットの生成
    dstSocket = socket(AF_INET, SOCK_STREAM, 0);
  
    //接続
if(_DEBUG_)    printf("Connecting...");
    if (connect(dstSocket, (struct sockaddr *)dstAddr, dstAddrLen) == 0) return(dstSocket); 
    retry++;
    printf("Can't connect to server...retry=%d\n",retry);
    close(dstSocket);
    if (retry > retryMax) return(-1);
    sleep(1);
  }
}

int main(int argc, char **argv){
  // IP アドレス，ソケット，sockaddr_in 構造体
  char destination[32];
  int dstSocket;
  struct sockaddr_in dstAddr;

  //struct sockaddr_in addr;
  struct hostent *hp;
  uint32_t buf[32];
  int number = 0;
  int numrcv;
//  int retry = 0;
  double period,active;
  uint32_t period_i,active_i;
  int port;

if(_DEBUG_)  printf("argc=%d\n",argc);
  if (argc < 3) {
    printf("Usage:%s period active [port]\n",argv[0]);
    return;
  }
  period = atof(argv[1]);
  active = atof(argv[2]);
  port = PORT;
  if (argc == 4) {
    port = atoi(argv[3]);
  }
  period_i = period * 1000;
  active_i = active * 1000;
if(_DEBUG_)  printf("period=%d active=%d port=%d\n",period_i,active_i,port);
  strcpy(destination,"localhost");
  
  //sockaddr_in 構造体のセット
  bzero((char *)&dstAddr, sizeof(dstAddr));
  dstAddr.sin_family = AF_INET;
  dstAddr.sin_port = htons(PORT);
  
  hp = gethostbyname(destination);
  bcopy(hp->h_addr, &dstAddr.sin_addr, hp->h_length);

  dstSocket = connect_server(&dstAddr, sizeof(dstAddr));
if(_DEBUG_)  printf("dstSocket=%d\n",dstSocket);
  if (dstSocket < 0) {
    printf("Can't connect to server [%s]\n",destination);
    return(-1);
  }
if(_DEBUG_)  printf("%s に接続しました\n",destination);
  
  memset(buf,0,sizeof(buf));
  //パケットの送信
  buf[0] = period_i;
  buf[1] = active_i;
  write(dstSocket, buf, sizeof(buf));
  //パケットの受信
  memset(buf,0,sizeof(buf));
  numrcv = read(dstSocket, buf, 1024);
if(_DEBUG_)  printf("→Recv=%d\n",buf[0]);
  close(dstSocket);
  return(buf[0]);
}
