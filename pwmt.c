#include <stdio.h>
#include <stdint.h>
#include <wiringPi.h>
#include "pwm.h"

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
