# pwmlib-opi
PWM Library for H3/H2+ Sunxi SoC

このライブラリはOrangePiやNanoPiなど、H3/H2+ベースのボードでハードウェアPWMを使うためのライブラリです。  
以下のボードで動作を確認しています。  
OrangePi PC(H3)  
OrangePi ZERO(H2+)  
NanoPi M1(H3)

このライブラリを使うためには以下のドライバーを有効にする必要が有ります。  
https://github.com/iboguslavsky/pwm-sunxi-opi0  

---

以下のプログラムでSG90マイクロサーボモータが 0°→ -90° → +90° → 0° に動きます。  
cc -o pwm pwm.c -lwiringPi  
sudo ./pwm  

void pwm_begin(float period)  
period : 全体のパルス幅  

void pwm_active(float period)  
period : Activeのパルス幅  

---

This library is the library to use hardware PWM by a board of H3/H2+ base such as OrangePi and NanoPi.  
I'm confirming that it works by the following board.  
OrangePi PC(H3)  
OrangePi ZERO(H2+)  
NanoPi M1(H3)

You have to make the following driver effective to use this library.  
https://github.com/iboguslavsky/pwm-sunxi-opi0  

---

SG90 micro servomotor works by the following program.  
cc -o pwm pwm.c -lwiringPi  
sudo ./pwm  

void pwm_begin(float period)  
period : entire pulse width(mSec)  

void pwm_active(float period)  
period :  active pulse width(mSec)  

