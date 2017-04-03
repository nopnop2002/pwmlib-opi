#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wiringPi.h>


uint16_t pwm_enable() {
  int fd;
  int rc;
  char buf[2];
  
  fd = open ("/sys/class/pwm-sunxi-opi0/pwm0/run",O_RDWR);
  if (fd == -1) return -1;
  read(fd,buf,2);
  rc = buf[0] - '0';
//  printf("<enable>buf=%c rc=%d\n",buf[0],rc);
  buf[0] = '1';
  write(fd,buf,1);
  close(fd);
  return rc;
}

uint16_t pwm_disable() {
  int fd;
  int rc;
  char buf[2];
  
  fd = open ("/sys/class/pwm-sunxi-opi0/pwm0/run",O_RDWR);
  if (fd == -1) return -1;
  read(fd,buf,2);
  rc = buf[0] - '0';
//  printf("<disable>buf=%c rc=%d\n",buf[0],rc);
  buf[0] = '0';
  write(fd,buf,1);
  close(fd);
  return rc;
}


uint16_t pwm_prescale(uint16_t val) {
  int fd;
  int rc;
  char buf[3];
  
  fd = open ("/sys/class/pwm-sunxi-opi0/pwm0/prescale",O_RDWR);
  if (fd == -1) return -1;
  read(fd,buf,3);
  int i;
  for(i=0;i<3;i++) {
//    printf("<prescale>buf[%d]=%c[%02x]\n",i,buf[i],buf[i]);
    if (buf[i] == 0x0a) buf[i] = 0;
  }
  rc = atoi(buf);
//  printf("<prescale>buf=%s rc=%d\n",buf,rc);
  sprintf(buf,"%d",val);
  write(fd,buf,strlen(buf));
  close(fd);
  return rc;
}

uint16_t pwm_entirecycles(uint16_t val) {
  int fd;
  int rc;
  char buf[6];
  
  fd = open ("/sys/class/pwm-sunxi-opi0/pwm0/entirecycles",O_RDWR);
  if (fd == -1) return -1;
  read(fd,buf,6);
  int i;
  for(i=0;i<6;i++) {
//    printf("<entirecycles>buf[%d]=%c[%02x]\n",i,buf[i],buf[i]);
    if (buf[i] == 0x0a) buf[i] = 0;
  }
  rc = atoi(buf);
//  printf("<entirecycles>buf=%s rc=%d\n",buf,rc);
  sprintf(buf,"%d",val);
  write(fd,buf,strlen(buf));
  close(fd);
  return rc;
}


uint16_t pwm_activecycles(uint16_t val) {
  int fd;
  int rc;
  char buf[6];
  
  fd = open ("/sys/class/pwm-sunxi-opi0/pwm0/activecycles",O_RDWR);
  if (fd == -1) return -1;
  read(fd,buf,6);
  int i;
  for(i=0;i<6;i++) {
//    printf("<activecycles>buf[%d]=%c[%02x]\n",i,buf[i],buf[i]);
    if (buf[i] == 0x0a) buf[i] = 0;
  }
  rc = atoi(buf);
//  printf("<activecycles>buf=%s rc=%d\n",buf,rc);
  sprintf(buf,"%d",val);
  write(fd,buf,strlen(buf));
  close(fd);
  return rc;
}


uint32_t pwm_freqperiod(void) {
  int fd;
  int rc;
  char buf[10];
  
  fd = open ("/sys/class/pwm-sunxi-opi0/pwm0/freqperiod",O_RDONLY);
  if (fd == -1) return -1;
  read(fd,buf,10);
  int i;
  for(i=0;i<10;i++) {
//    printf("<freqperiod>buf[%d]=%c[%02x]\n",i,buf[i],buf[i]);
    if (buf[i] == 0x0a) buf[i] = 0;
  }
  rc = atoi(buf);
//  printf("<freqperiod>buf=%s rc=%d\n",buf,rc);
  close(fd);
  return rc;
}

/*
 period : PWM period (mSec)
 return : freqperiod (Hz)
*/
uint32_t pwm_begin(float period) {
  uint16_t prescale;
  uint16_t rc;
  uint32_t freq;
  prescale = (period * 1000) / 5;
//  printf("<pwm_begin>prescale=%d\n",prescale);
  rc = pwm_enable();
  if (rc < 0) return -1;
  delay(100);
  rc = pwm_prescale(0);
  if (rc < 0) return -1;
  delay(100);
  rc = pwm_entirecycles(prescale);
  if (rc < 0) return -1;
  delay(200);
  freq = pwm_freqperiod();
//  printf("<pwm_begin>freq=%d\n",freq);
  return freq;
}

/*
 period : PWM active period (mSec)
*/
void pwm_active(float period) {
  int rc;
  uint16_t pwm;
  pwm = (period * 1000) / 5;
//  printf("pwm=%d\n",pwm);
  rc = pwm_activecycles(pwm);
  return;
}

void pwm_end(void) {
  int rc;
  rc = pwm_disable();
  return;
}

#if 0
int main() {
  uint16_t rc;
  uint32_t freq;
  int pwm;

  rc = pwm_enable();
  printf("pwm_enable=%d\n",rc);
  delay(100);

  rc = pwm_prescale(0);
  printf("pwm_prescale=%d\n",rc);
  delay(100);

  rc = pwm_entirecycles(4000);
  printf("pwm_entirecycles=%d\n",rc);
  delay(100);

  rc = pwm_activecycles(290);
  printf("pwm_activecycles=%d\n",rc);
  delay(500);

  for(pwm=290;pwm>124;pwm--) {
    rc = pwm_activecycles(pwm);
//    printf("pwm_activecycles=%d\n",rc);
    delay(50);
  }

  for(pwm=125;pwm<471;pwm++) {
    rc = pwm_activecycles(pwm);
//    printf("pwm_activecycles=%d\n",rc);
    delay(50);
  }

  rc = pwm_activecycles(290);
  printf("pwm_activecycles=%d\n",rc);
  delay(500);

  rc = pwm_disable();
  printf("pwm_disable=%d\n",rc);

  freq = pwm_begin(20.0);
  printf("freqperiod=%d\n",freq);
  pwm_active(1.45); // angle 0
  delay(500);
  pwm_active(2.35); // angle +90
  delay(500);
  pwm_active(1.45); // angle 0
  delay(500);
  pwm_active(0.625); // angle -90
  delay(500);
  pwm_active(1.45); // angle 0
  delay(500);
  pwm_end();
}
#endif
