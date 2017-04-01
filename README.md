# pwmlib-opi
PWM Library for H3/H2+ Sunxi SoC

このライブラリはOrangePiやNanoPiなど、H3ベースのマシンでハードウェアPWMを使うためのライブラリです。  
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
period 全体のパルス幅  

void pwm_active(float period)  
period Activeのパルス幅  
