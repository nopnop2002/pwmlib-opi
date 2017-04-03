/*
 hardware PWM server
*/
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "pwm.h"

#define PORT 9876 // default port
#define _DEBUG_ 0

int main(int argc, char **argv){
  int i;
  int srcSocket; //自分
  int dstSocket; //相手
  // sockaddr_in 構造体
  struct sockaddr_in srcAddr;
  struct sockaddr_in dstAddr;
  socklen_t dstAddrSize;
  // 各種パラメータ
  int numrcv;
  uint32_t buf[32];
  int port;
  bool init = 0;
  float period;
  float active;
  uint32_t freq;

  port = PORT;
  if (argc == 2) {
    port = atoi(argv[1]);
  }
if(_DEBUG_)  printf("port=%d\n",port);

  // sockaddr_in 構造体のセット
  bzero((char *)&srcAddr, sizeof(srcAddr));
  srcAddr.sin_port = htons(PORT);
  srcAddr.sin_family = AF_INET;
  srcAddr.sin_addr.s_addr = INADDR_ANY;
    
  // ソケットの生成（ストリーム型）
  srcSocket = socket(AF_INET, SOCK_STREAM, 0);
  // ソケットのバインド
  bind(srcSocket, (struct sockaddr *)&srcAddr, sizeof(srcAddr));
  // 接続の許可
  listen(srcSocket, 5);
  
  while(1){
    // 接続の受付け
if(_DEBUG_)    printf("Wait from client request\n");
    dstAddrSize = sizeof(dstAddr);
    dstSocket = accept(srcSocket, (struct sockaddr *)&dstAddr, &dstAddrSize);
if(_DEBUG_)    printf("accept from %s\n",inet_ntoa(dstAddr.sin_addr));
        
    while(1) { // クライアントがSocketをクローズしてからこちらもクローズする
      //パケットの受信
      memset(buf,0,sizeof(buf));
      numrcv = read(dstSocket, buf, 1024);
if(_DEBUG_)      printf("numrcv=%d\n",numrcv);
      if(numrcv ==0 || numrcv ==-1 ){ // client close socket
        close(dstSocket); break;
      }
if(_DEBUG_)      printf("Recv=[%d,%d]\n",buf[0],buf[1]);
      if (!init) {
        period = buf[0];
        period = period / 1000.0;
if(_DEBUG_)        printf("period=%f\n",period);
        freq = pwm_begin(period);
if(_DEBUG_)        printf("freq=%d\n",freq);
        init = 1;
      }
      active = buf[1];
      active = active / 1000.0;
if(_DEBUG_)      printf("active=%f\n",active);
      pwm_active(active);
      delay(500);

      // パケットの送信
      buf[0] = freq;
      write(dstSocket, buf, numrcv);
if(_DEBUG_)      printf("->Send=%d\n",buf[0]);
    } // end while
  } // end for
  return(0);
}
